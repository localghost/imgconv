#ifndef EXPORTACTION_H
#define EXPORTACTION_H

#include <QDialog>
#include <ui/action.h>

namespace Ui {
class ExportAction;
}

class ExportAction : public QDialog, public Action
{
  Q_OBJECT

public:
  explicit ExportAction(QWidget* parent = nullptr);
  ~ExportAction();

  void configure() override;
  std::unique_ptr<im::ImageAction> compile() override;
  std::string name() const;
  QString description() const override { return ""; }

private slots:
  void on_pushButton_clicked();

private:
  Ui::ExportAction* ui_{nullptr};
};

#endif // EXPORTACTION_H
