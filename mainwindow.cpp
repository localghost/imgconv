#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <iterator>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "dialog.h"
#include "imimage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_triggered()
{
    QStringList selected = QFileDialog::getOpenFileNames(this, tr("Add file"));
    std::copy(selected.begin(), selected.end(), std::back_inserter(files));
    ui->listWidget->addItems(selected);
}

void MainWindow::on_actionRemove_triggered()
{
    auto selected = ui->listWidget->selectedItems();
    for (auto& i : selected)
        files.erase(std::find(files.begin(), files.end(), i->text()));
    qDeleteAll(ui->listWidget->selectedItems());
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
        std::string dest = dialog->get_destination();
        for (int i = 0; i < ui->listWidget->count(); ++i)
        {
            auto selected = ui->listWidget->item(i);
            QFileInfo source{selected->text()};
            ui->statusBar->showMessage(tr("Resizing ") + selected->text());
            try
            {
                IMImage img;
                img.read(source.filePath().toStdString());
                img.resize(width, height);
                img.write((QString::fromStdString(dest) + QDir::separator() + source.fileName()).toStdString());
            }
            catch (const std::exception& ex)
            {
               QMessageBox::warning(this,
                                    tr("Error occurred"),
                                    tr("Exception: ") + ex.what() + "\n" +
                                       tr("Please send details to zkostrzewa@gmail.com"));
            }
        }
        QMessageBox::information(this, tr("Resize"), tr("Done."));
        ui->statusBar->clearMessage();
    }
}
