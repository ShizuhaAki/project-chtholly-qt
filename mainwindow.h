#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_new_clicked();

    void on_result_linkActivated(const QString &link);

    void on_pushButton_clicked();

    void on_pushButton_about_clicked();

    void on_pushButton_save_clicked();
    
    void on_pushButton_read_clicked();
    
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_import_clicked();

private:
    Ui::MainWindow *ui;
    void showStatus(QString);
};
#endif // MAINWINDOW_H
