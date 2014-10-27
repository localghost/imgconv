#ifndef DIALOG_H
#define DIALOG_H

#include <cstddef>
#include <string>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    std::size_t get_width() const;
    std::size_t get_height() const;
    std::string get_destination() const;

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_checkBox_stateChanged(int arg1);

private:
    bool validateInput();

    Ui::Dialog *ui;
    std::size_t width_{0};
    std::size_t height_{0};
};

#endif // DIALOG_H
