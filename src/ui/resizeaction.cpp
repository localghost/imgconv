#include "resizeaction.h"
#include "ui_resizeaction.h"

#include <base/assert.h>
#include <im/image.h>
#include <im/resizeaction.h>

ResizeAction::ResizeAction(QWidget *parent) :
  QDialog(parent),
  ui_(new Ui::ResizeAction)
{
  ui_->setupUi(this);
}

ResizeAction::~ResizeAction()
{
  delete ui_;
}

void ResizeAction::configure()
{
  exec();
}

std::unique_ptr<im::ImageAction> ResizeAction::compile()
{
  BOOST_ASSERT(result() == QDialog::Accepted);
  std::unique_ptr<im::ResizeAction> result{new im::ResizeAction{}};
  result->width(ui_->width->value());
  result->height(ui_->height->value());
  result->keep_aspect_ratio(ui_->keep_aspect_ratio->isChecked());
  return std::unique_ptr<im::ImageAction>(result.release());
}

std::string ResizeAction::name() const
{
  return "Resize";
}
