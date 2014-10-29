#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <iterator>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QProgressDialog>
#include <QMenu>
#include "dialog.h"
#include "image.h"
#include "imagefilter.h"
#include "resizefilter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    listContextMenu_(new QMenu(this))
{
    ui->setupUi(this);
    setupListContextMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupListContextMenu()
{
   listContextMenu_->addAction(ui->actionRemove);
}

void MainWindow::on_actionAdd_triggered()
{
    QStringList selected = QFileDialog::getOpenFileNames(this, tr("Add file"));
    std::copy(selected.begin(), selected.end(), std::back_inserter(files));
    ui->listWidget->addItems(selected);
    ui->actionResize->setEnabled(true);
}

void MainWindow::on_actionRemove_triggered()
{
    auto selected = ui->listWidget->selectedItems();
    for (auto& i : selected)
        files.erase(std::find(files.begin(), files.end(), i->text()));
    qDeleteAll(ui->listWidget->selectedItems());
    if (ui->listWidget->count() == 0)
       ui->actionResize->setEnabled(false);
}

void MainWindow::on_actionResize_triggered()
{
    auto dialog = new Dialog(this);
    if (dialog->exec() == QDialog::Accepted)
    {
        size_t width = dialog->get_width();
        size_t height = dialog->get_height();
        qDebug() << "requested size: " << width << "x" << height;
        if (width == 0 || height == 0)
        {
            QMessageBox::warning(this,
                                 tr("Invalid size"),
                                 tr("Neither width nor height can be 0"));
            return;
        }
        bool keep_aspect_ratio = dialog->keep_aspect_ratio();
        std::string dest = dialog->get_destination();

        auto progress = new QProgressDialog();
        progress->setLabelText(tr("Processing images..."));

        QFutureWatcher<void> watcher;
        QObject::connect(&watcher, SIGNAL(finished()), progress, SLOT(reset()));
        QObject::connect(progress, SIGNAL(canceled()), &watcher, SLOT(cancel()));
        QObject::connect(&watcher, SIGNAL(progressRangeChanged(int,int)), progress, SLOT(setRange(int,int)));
        QObject::connect(&watcher, SIGNAL(progressValueChanged(int)), progress, SLOT(setValue(int)));

        std::unique_ptr<im::ImageFilter> filter{new im::ResizeFilter{width, height, keep_aspect_ratio}};
        watcher.setFuture(QtConcurrent::map(files.begin(), files.end(), [&filter, &dest](const QString& path){
            QFileInfo src{path};
            im::Image img;
            img.read(src.filePath().toStdString());
            img.apply_filter(filter.get());
            img.write((QString::fromStdString(dest) + QDir::separator() + src.fileName()).toStdString());
        }));

        progress->exec();

        try
        {
            watcher.waitForFinished();
            QMessageBox::information(this, tr("Result"), tr("All images processed successfully."));
        }
        catch (const std::exception& ex)
        {
            QMessageBox::warning(this,
                                 tr("Result"),
                                 tr("Processing some of the images failed.\nPlease copy below line and send to zkostrzewa@gmail.com\n") + ex.what());
        }
    }
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint& pos)
{
   listContextMenu_->exec(ui->listWidget->mapToGlobal(pos));
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    ui->actionRemove->setEnabled(!ui->listWidget->selectedItems().empty());
}
