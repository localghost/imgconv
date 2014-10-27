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

void Dialog::on_checkBox_stateChanged(int state)
{
    ui->pushButton->setEnabled(state == Qt::CheckState::Unchecked);
    ui->destination->setEnabled(state == Qt::CheckState::Unchecked);
}
