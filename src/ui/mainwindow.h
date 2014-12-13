#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionResize_triggered();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_listWidget_itemSelectionChanged();

    void on_actionRemove_All_triggered();

private:
    void setupListContextMenu();

    Ui::MainWindow *ui;
    std::vector<QString> files;
    QMenu* listContextMenu_;
};

#endif // MAINWINDOW_H
