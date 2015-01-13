#ifndef PIPELINEEDITOR_H
#define PIPELINEEDITOR_H

#include <QDialog>

namespace Ui {
  class PipelineEditor;
}

class PipelineEditor : public QDialog
{
  Q_OBJECT

public:
  explicit PipelineEditor(QWidget *parent = 0);
  ~PipelineEditor();

private slots:
  void on_cancel_clicked();

private:
  Ui::PipelineEditor *ui;
};

#endif // PIPELINEEDITOR_H
