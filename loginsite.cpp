#include "loginsite.h"
#include "ui_loginsite.h"
#include "mainwindow.h"

loginSite::loginSite(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginSite)
{
    ui->setupUi(this);
}

loginSite::~loginSite()
{
    delete ui;
}

void loginSite::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == "omg") {
        QMessageBox::information(this,"Controller","Login success");
        this->hide();
        MainWindow *v = new MainWindow ();
        v->show();
    }
}


