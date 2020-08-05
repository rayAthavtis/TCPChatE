#include "dialog.h"
#include "ui_dialog.h"

#include <QMessageBox>
#include <QInputDialog>
#include "desoperate.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    bool is_init;
    username = QInputDialog::getText(this, tr("Login"), tr("Name please"), QLineEdit::Normal, "", &is_init);
    if (!is_init || username.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Use Anonymous instead."));
        username = "Anonymous";
    }
    p_key.p_e = p_key.p_n = 0;
    password = "";
    pt = 6667;  // 默认第一个
    ui->m_anc->append("Notice \nPlease civilize chat. \nBeware of personal information leakage. ");
    ui->m_alive->addItem(username);

    sock = new QTcpSocket(this);
    client = new QTcpSocket(this);
    sock->connectToHost("127.0.0.1", 6666);

    connect(sock, SIGNAL(readyRead()), this, SLOT(get_port()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(del_Connection()));
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getTime() {
    time_t t = time(nullptr);
    char date_time[64] = {0};
    strftime(date_time, sizeof(date_time)-1, "%Y-%m-%d %H:%M:%S", localtime(&t));
    return date_time;
}

void Dialog::get_port() {
    QByteArray given_pt = sock->readAll();

    pt = given_pt.toUShort();
    client->connectToHost("127.0.0.1", pt);
    connect(client, SIGNAL(readyRead()), this, SLOT(msg_handle()));
    // DesOperate desop(password);
    PublicK m_pk = clir.getPublicKey();
    // 公开信息不用加密
    QString cc = "0\n" + username + "\n" + tr("%1").arg(m_pk.p_e) + "\n" + tr("%1").arg(m_pk.p_n);
    // qDebug()<<"cc:"<<cc;
    // QString cc = desop.msg_handle(username);
    // QMessageBox::information(this, "cc: ", cc);
    client->write(cc.toLocal8Bit());

    sock->disconnectFromHost();
}

void Dialog::msg_handle() {
    QByteArray msg = client->readAll();
    QString tmp = msg.data();
    QStringList pkt = tmp.split('\n');
    int max = pkt.size();
    switch (pkt.at(0).toInt()) {
    case 1:  {  // 收到公钥 1 e n
        if (max<3) { return ; }
        // QMessageBox::information(this, "cc: ", tmp);
        p_key.p_e = pkt.at(1).toULongLong();
        p_key.p_n = pkt.at(2).toULongLong();
        // 第一个进聊天室的人，生成聊天室des密码
        if (pt==6667) {
            // 随机生成
            QString ktmp = "ABCDEFGHIJKLMNOPQRSDUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
            for (int i=0; i<8; i++) {
                int idx = QRandomGenerator::global()->bounded(36);
                password.append(ktmp.at(idx));
            }
            // qDebug()<<"psd: "<<password;
            QString tt = RsaOperate::rsaEncode(password, p_key.p_e, p_key.p_n);
            // qDebug()<<"tt: "<<tt;
            QString cc = "2\n" + tt;
            client->write(cc.toLocal8Bit());
        }
        break;
    }
    case 3: {  // 新增/退出聊天消息 3 dE(msg num names)
        if (max<2) { return ; }
        DesOperate desop(password);
        QString mm = desop.remsg(pkt.at(1));
        // qDebug()<<"mm: "<<mm;
        QStringList list = mm.split('\n');  // msg num names
        if (list.size()<3) { return ; }
        ui->m_msgShow->append(list.at(0));
        ui->m_msgShow->append("-----------------------------------------------------------------------------------------");
        ui->membernum->setText("Online Member(s) ["+ list.at(1) + "]");
        QStringList names = list.at(2).split(' ');
        ui->m_alive->clear();
        ui->m_alive->addItems(names);
        break;
    }
    case 4: { // 聊天室已存在，获取聊天室des密钥 [4 rE(psd)] 3 dE(msg num)
        if (max<3) { return ; }
        password = clir.rsaDecode(pkt.at(1));
        // qDebug()<<"psd: "<<password;

        DesOperate desop(password);
        QString mm = desop.remsg(pkt.at(3));
        QStringList list = mm.split('\n');  // msg num names
        if (list.size()<3) { return ; }
        ui->m_msgShow->append(list.at(0));
        ui->m_msgShow->append("-----------------------------------------------------------------------------------------");
        ui->membernum->setText("Online Member(s) ["+ list.at(1) + "]");
        QStringList names = list.at(2).split(' ');
        ui->m_alive->clear();
        ui->m_alive->addItems(names);
        break;
    }
    case 7: {  // 聊天消息 7 msg
        if (max<2) { return ; }
        DesOperate desop(password);
        QString mm = desop.remsg(pkt.at(1));
        if (mm.startsWith(username)) {
            mm = "ME:" + mm.split(':').at(1);
        }
        QString btf = "【" + getTime() + "】" + mm;
        ui->m_msgShow->append(btf);
        break;
    }
    }
}

void Dialog::del_Connection() {
    sock->deleteLater();
}

void Dialog::on_m_send_clicked() {
    QString msg = ui->m_msg->text();
    if (msg.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Empty!"));
        return ;
    }
    msg = username + ": " + msg;
    DesOperate desop(password);
    QString cc = "7\n" + desop.msg_handle(msg);
    client->write(cc.toLocal8Bit());

    ui->m_msg->setText("");
}

void Dialog::on_m_qt_clicked() {
    int is_quit = QMessageBox::question(this, "Check", "Logout?");
    if (is_quit==QMessageBox::Yes) {
        QString m_quit = "quit";
        DesOperate desop(password);
        QString cc = "6\n" + desop.msg_handle(m_quit);
        client->write(cc.toLocal8Bit());
        client->disconnectFromHost();
    }
}
