#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnCancel_clicked();

    void on_btnBrowse_clicked();

    void on_btnEncryp_clicked();

    void on_btnDecrypt_clicked();

    void on_btnSave_clicked();


    void on_checkPw_toggled(bool checked);

    void on_input_Textedit_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
