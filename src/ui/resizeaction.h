#ifndef RESIZEACTION_H
#define RESIZEACTION_H

#include <QDialog>
#include <ui/action.h>

namespace Ui {
class ResizeAction;
}

namespace im {
class ResizeAction;
}

class ResizeAction : public QDialog, public Action
{
  Q_OBJECT

public:
  explicit ResizeAction(QWidget *parent = 0);
  ~ResizeAction();

  bool configure() override;
  std::unique_ptr<im::ImageAction> compile() override;
  QString description() const override { return ""; }

  std::string name() const;

private:
  Ui::ResizeAction* ui_{nullptr};
};

#endif // RESIZEACTION_H
