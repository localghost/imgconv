#include "exportaction.h"
#include "ui_exportaction.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <base/assert.h>
#include <im/exportaction.h>
#include <im/image.h>

ExportAction::ExportAction(QWidget* const parent)
  : QDialog(parent),
    ui_(new Ui::ExportAction)
{
  ui_->setupUi(this);
  // TODO For Linux that could be TempLocation
  ui_->destination->setText(QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0));
}

ExportAction::~ExportAction()
{
  delete ui_;
}

bool ExportAction::configure()
{
  return (exec() == QDialog::Accepted);
}

std::unique_ptr<im::ImageAction> ExportAction::compile()
{
  BOOST_ASSERT(result() == QDialog::Accepted);
  std::unique_ptr<im::ExportAction> result{new im::ExportAction{}};
  result->format(im::ExportFormat{im::ImageFormat::JPG, 10});
  result->destination(ui_->destination->text().toStdString());
  return std::unique_ptr<im::ImageAction>(result.release());
}

std::string ExportAction::name() const
{
  return "Export";
}

void ExportAction::on_pushButton_clicked()
{
  auto path = QFileDialog::getExistingDirectory(this, tr("Choose destination folder"));
  if (!path.isEmpty()) ui_->destination->setText(path);
}
