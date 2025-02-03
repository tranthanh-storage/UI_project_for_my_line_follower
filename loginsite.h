#ifndef LOGINSITE_H
#define LOGINSITE_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class loginSite; }
QT_END_NAMESPACE
namespace Ui {
class loginSite;
}

class loginSite : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginSite(QWidget *parent = nullptr);
    ~loginSite();

private slots:
    void on_pushButton_clicked();

private:
    Ui::loginSite *ui;
};

#endif // LOGINSITE_H
