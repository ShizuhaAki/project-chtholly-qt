#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMap>
#include <QString>
#include <QInputDialog>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QMap <int, QString> stuName;
int tot;
void MainWindow::on_pushButton_new_clicked()
{
    //warns the user of potential overwrite of log file
    int ret = QMessageBox::warning(this, "警告", "新建一个新的存档会覆盖原有的存档。\n 确认要继续吗？", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    int num = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                         tr("学生人数"), QLineEdit::Normal,
                                         1, 100000);
    if (num != 0) tot = num;
    ui->statusbar->showMessage("学生人数已经设置为" + QString::number(tot), 1000);
}



void MainWindow::on_result_linkActivated(const QString &link)
{
    //Clicking on this should result in the same as clicking the button
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_pushButton_clicked()
{

}
