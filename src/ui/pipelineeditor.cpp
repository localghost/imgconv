#include "pipelineeditor.h"
#include "ui_pipelineeditor.h"

#include <QStringList>
#include <QListWidgetItem>

PipelineEditor::PipelineEditor(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PipelineEditor)
{
  ui->setupUi(this);
  QStringList list;
  list << "raz";
  list << "dwa";
  list << "trzy";
  ui->listWidget->addItems(list);
}

PipelineEditor::~PipelineEditor()
{
  delete ui;
}

void PipelineEditor::on_cancel_clicked()
{
    reject();
}
