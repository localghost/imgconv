#include "dialog.h"
#include "ui_dialog.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->destination->setText(QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0));
}

Dialog::~Dialog()
{
    delete ui;
}

std::size_t Dialog::get_width() const
{
   return ui->editWidth->value();
}

std::size_t Dialog::get_height() const
{
   return ui->editHeight->value();
}

std::string Dialog::get_destination() const
{
    return ui->destination->text().toStdString();
}

bool Dialog::keep_aspect_ratio() const
{
   return ui->checkKeepAspectRatio->isChecked();
}

bool Dialog::convert() const
{
   return ui->checkConvert->isChecked();
}

void Dialog::on_pushButton_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this, tr("Choose destination folder"));
    if (!path.isEmpty()) ui->destination->setText(path);
}

void Dialog::on_buttonBox_accepted()
{
   accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

void Dialog::on_checkOverwrite_stateChanged(int state)
{
   ui->pushButton->setEnabled(state == Qt::CheckState::Unchecked);
   ui->destination->setEnabled(state == Qt::CheckState::Unchecked);
}

void Dialog::on_checkConvert_stateChanged(int state)
{
//    ui->editQuality->setEnabled(state == Qt::CheckState::Checked);
}
