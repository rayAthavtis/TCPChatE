#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtNetwork>
#include "rsaoperate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QTcpSocket *sock;  // 试探
    QTcpSocket *client;
    QString username;
    QString password;
    quint16 pt;
    RsaOperate clir;
    PublicK p_key;

private slots:
    QString getTime();
    void get_port();
    void msg_handle();
    void on_m_send_clicked();
    void del_Connection();
    void on_m_qt_clicked();
};
#endif // DIALOG_H
