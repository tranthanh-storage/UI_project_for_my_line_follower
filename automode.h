#ifndef AUTOMODE_H
#define AUTOMODE_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QDebug>

namespace Ui {
class autoMode;
}

class autoMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit autoMode(QWidget *parent = nullptr);
    ~autoMode();

private slots:
    void on_pushButton_clicked();

    void onNetworkReply2(QNetworkReply* reply);

    void on_start_clicked();

private:
    Ui::autoMode *ui;
    QNetworkAccessManager *networkManager;
};

#endif // AUTOMODE_H
