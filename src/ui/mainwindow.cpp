#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <iterator>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QProgressDialog>
#include <QMenu>
#include <QAction>
#include <QPalette>
#include "dialog.h"
#include "pipelineeditor.h"
#include <base/exception.h>
#include <base/log.h>
#include <im/image.h>
#include <im/imageaction.h>
#include <im/resizeaction.h>
#include <im/exportaction.h>

#include "action.h"
#include "resizeaction.h"
#include "exportaction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    listContextMenu_(new QMenu(this))
{
    ui->setupUi(this);
    setupListContextMenu();
    QAction* action = new QAction("raz", this);
    ui->menuAction->addAction(action);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupListContextMenu()
{
   listContextMenu_->addAction(ui->actionRemove);
   listContextMenu_->addAction(ui->actionRemove_All);
}

void MainWindow::on_actionAdd_triggered()
{
    QStringList selected = QFileDialog::getOpenFileNames(this, tr("Add file"));
    std::copy(selected.begin(), selected.end(), std::back_inserter(files));
    ui->listWidget->addItems(selected);
    if (!selected.empty())
    {
        ui->actionResize->setEnabled(true);
        ui->actionRemove_All->setEnabled(true);
    }
}

void MainWindow::on_actionRemove_triggered()
{
    auto selected = ui->listWidget->selectedItems();
    for (auto& i : selected)
        files.erase(std::find(files.begin(), files.end(), i->text()));
    qDeleteAll(ui->listWidget->selectedItems());
    if (ui->listWidget->count() == 0)
    {
       ui->actionResize->setEnabled(false);
       ui->actionRemove_All->setEnabled(false);
    }
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
        bool convert_to_jpg = dialog->convert();

        auto progress = new QProgressDialog();
        progress->setLabelText(tr("Processing images..."));

        QFutureWatcher<void> watcher;
        QObject::connect(&watcher, SIGNAL(finished()), progress, SLOT(reset()));
        QObject::connect(progress, SIGNAL(canceled()), &watcher, SLOT(cancel()));
        QObject::connect(&watcher, SIGNAL(progressRangeChanged(int,int)), progress, SLOT(setRange(int,int)));
        QObject::connect(&watcher, SIGNAL(progressValueChanged(int)), progress, SLOT(setValue(int)));


        std::unique_ptr<im::ImageAction> filter{new im::ResizeAction{width, height, keep_aspect_ratio}};
        std::unique_ptr<im::ExportAction> saveas{new im::ExportAction{dest}};
        if (convert_to_jpg)
        {
          saveas->format(im::ExportFormat{im::ImageFormat::JPG, 10});
        }

        std::vector<std::unique_ptr<im::ImageAction>> actions;
        actions.push_back(std::move(filter));
        actions.push_back(std::move(saveas));

        watcher.setFuture(QtConcurrent::map(files.begin(), files.end(), [&actions](const QString& path){
            QFileInfo src{path};
            im::Image img;
            img.read(src.filePath().toStdString());
            for (auto& action : actions)
            {
              img.call(action.get());
            }
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
                                 tr("Processing some of the images failed.\nCheck standard error output.\n"));
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

void MainWindow::on_actionRemove_All_triggered()
{
    ui->listWidget->clear();
    files.clear();
    ui->actionResize->setEnabled(false);
    ui->actionRemove->setEnabled(false);
    ui->actionRemove_All->setEnabled(false);
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::closeAllWindows();
}

void MainWindow::on_actionPipelineEditor_triggered()
{
  auto dialog = new PipelineEditor(this);
  dialog->exec();
}

void MainWindow::on_actionResize_Export_triggered()
{
  Pipeline pipeline;
  pipeline.add_action(std::unique_ptr<Action>(new ResizeAction(this)));
  pipeline.add_action(std::unique_ptr<Action>(new ExportAction(this)));

  if (!pipeline.configure()) return;

  im::Pipeline impipe = pipeline.compile();

  auto progress = new QProgressDialog();
  progress->setLabelText(tr("Processing images..."));

  QFutureWatcher<void> watcher;
  QObject::connect(&watcher, SIGNAL(finished()), progress, SLOT(reset()));
  QObject::connect(progress, SIGNAL(canceled()), &watcher, SLOT(cancel()));
  QObject::connect(&watcher, SIGNAL(progressRangeChanged(int,int)), progress, SLOT(setRange(int,int)));
  QObject::connect(&watcher, SIGNAL(progressValueChanged(int)), progress, SLOT(setValue(int)));

  watcher.setFuture(QtConcurrent::map(files.begin(), files.end(), [&impipe](const QString& path){
      QFileInfo src{path};
      im::Image img;
      img.read(src.filePath().toStdString());
      impipe.run(img);
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
                           tr("Processing some of the images failed.\nCheck standard error output.\n"));
  }
}
