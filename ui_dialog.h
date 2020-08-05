/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *m_qt;
    QLineEdit *m_msg;
    QLabel *membernum;
    QTextBrowser *m_msgShow;
    QTextBrowser *m_anc;
    QListWidget *m_alive;
    QPushButton *m_send;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 513);
        m_qt = new QPushButton(Dialog);
        m_qt->setObjectName(QString::fromUtf8("m_qt"));
        m_qt->setGeometry(QRect(690, 460, 101, 31));
        m_msg = new QLineEdit(Dialog);
        m_msg->setObjectName(QString::fromUtf8("m_msg"));
        m_msg->setGeometry(QRect(20, 460, 551, 31));
        membernum = new QLabel(Dialog);
        membernum->setObjectName(QString::fromUtf8("membernum"));
        membernum->setGeometry(QRect(590, 130, 141, 21));
        m_msgShow = new QTextBrowser(Dialog);
        m_msgShow->setObjectName(QString::fromUtf8("m_msgShow"));
        m_msgShow->setGeometry(QRect(20, 20, 551, 421));
        m_anc = new QTextBrowser(Dialog);
        m_anc->setObjectName(QString::fromUtf8("m_anc"));
        m_anc->setGeometry(QRect(590, 20, 191, 101));
        m_anc->setReadOnly(true);
        m_alive = new QListWidget(Dialog);
        m_alive->setObjectName(QString::fromUtf8("m_alive"));
        m_alive->setGeometry(QRect(585, 150, 201, 291));
        m_send = new QPushButton(Dialog);
        m_send->setObjectName(QString::fromUtf8("m_send"));
        m_send->setGeometry(QRect(580, 460, 101, 32));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "SoChat", nullptr));
        m_qt->setText(QCoreApplication::translate("Dialog", "Quit", nullptr));
        membernum->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p>Online Member(s) [1]</p></body></html>", nullptr));
        m_send->setText(QCoreApplication::translate("Dialog", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
