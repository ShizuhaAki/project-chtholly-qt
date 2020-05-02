/*
    Project Chtholly Qt
    Copyright (C) 2020 Shu Shang

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMap>
#include <QString>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QTextStream>
#include <QDir>
#include <QSet>
#include <QFile>
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
QMap <int, QString> namelist;
bool useStuName = false, importedStuName = false;
QSet <int> ok;
int tot;
void MainWindow::showStatus(QString prompt) {
    ui->statusbar->showMessage(prompt, 1000);
}
void MainWindow::on_pushButton_new_clicked()
{
    //warns the user of potential overwrite of log file
    int ret = QMessageBox::warning(this, "警告", "新建一个新的存档会覆盖原有的存档。\n 确认要继续吗？", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    //prompts the user to enter the total number of students
    int num = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                         tr("学生人数"), QLineEdit::Normal,
                                         1, 100000);
    //Initiallizes the total number of students
    if (num != 0) tot = num;
    ui->statusbar->showMessage("学生人数已经设置为" + QString::number(tot), 1000);
    //Put all numbers into available pool
    for (int i = 1; i <= tot; i++) ok.insert(i);

}
void MainWindow::on_result_linkActivated(const QString &link)
{
    //Clicking on this should result in the same as clicking the button
    //To avoid confusion, this feature is disabled by default, uncomment the next line to enable it.
    //MainWindow::on_pushButton_clicked();
}
QRandomGenerator rng;
void MainWindow::on_pushButton_clicked()
{
    //randomizes a number from the available number pool
    if (ok.empty()) {
        int ret = QMessageBox::warning(this, "警告", "所有号码已经全部抽取完成\n 您想要重新初始化吗？", QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No) {
            return;
        }
        else {
            for (int i = 1; i <= tot; i++) ok.insert(i);    //re-initiallizes
        }
    }

    int nid = rng.bounded(0, ok.size());
    int nxtStu = ok.values().takeAt(nid);
    //if the checkbox is checked, display the name of the student
    if (ui->checkBox->checkState() == Qt::CheckState::Checked) {
        ui->result->setText(namelist[nxtStu]);
    }
    else ui->result->setNum(nxtStu);
    ok.erase(ok.find(nxtStu));
    ui->statusbar->showMessage("剩余" + QString::number(ok.size()), 1000);
}

void MainWindow::on_pushButton_about_clicked()
{

    QMessageBox::about(this, tr("关于"),
             tr(R"(Project-Chtholly Qt, Version 0.9.3
这是使用 Qt 实现的跨平台课堂学号抽取系统。
本程序为自由软件；您可依据自由软件基金会所发表的GNU通用公共许可证条款，对本程序再次发布和/或修改；无论您依据的是本许可证的第三版，或（您可选的）任一日后发行的版本。
本程序是基于使用目的而加以发布，然而不负任何担保责任；亦无对适售性或特定目的适用性所为的默示性担保。详情请参照GNU通用公共许可证。)"));
}

void MainWindow::on_pushButton_save_clicked()
{
    QFile ouf("save.moe");
    if (!ouf.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("错误"), "存档文件无法在写入模式下打开");
        return;
    }
    QTextStream out(&ouf);
    out << tot << " " << tot - ok.size() << endl;
    for (int i = 1; i <= tot; i++) {
        if (!ok.contains(i)) out << i << endl;
    }
    showStatus("成功写入存档文件");
}

void MainWindow::on_pushButton_read_clicked()
{
    //reads and parses APP_PATH/save.moe
    QFile inf("save.moe");
    if (!inf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("错误"), "存档文件无法在只读模式下打开");
        return;
    }
    QTextStream in(&inf);
    int t, num; in >> t >> num;
    QSet <int> bad;
    for (int i = 1; i <= num; i++) {
        int x;
        in >> x;
        bad.insert(x);
    }
    ok.clear();
    for (int i = 1; i <= t; i++) {
        if (!bad.contains(i)) ok.insert(i);
    }
    tot = t;
    showStatus("成功读取存档文件，剩余：" + QString::number(ok.size()));
}

