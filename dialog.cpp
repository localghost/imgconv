#include "dialog.h"
#include "ui_dialog.h"

#include <QStandardPaths>
#include <QFileDialog>

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
    bool ok = true;
    auto result = ui->editWidth->text().toUInt(&ok);
    return (ok ? size_t(result) : 0);
}

std::size_t Dialog::get_height() const
{
    bool ok = true;
    auto result = ui->editHeight->text().toUInt(&ok);
    return (ok ? size_t(result) : 0);
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

void Dialog::on_checkBox_stateChanged(int arg1)
{
    ui->pushButton->setEnabled(!ui->checkBox->isChecked());
    ui->destination->setEnabled(!ui->checkBox->isChecked());
}
