/********************************************************************************
** Form generated from reading UI file 'dialogcreateplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCREATEPLAYER_H
#define UI_DIALOGCREATEPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogCreatePlayer
{
public:
    QLineEdit *lineEditPWD;
    QLineEdit *lineEditPlayerName;
    QLabel *label_2;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogCreatePlayer)
    {
        if (DialogCreatePlayer->objectName().isEmpty())
            DialogCreatePlayer->setObjectName(QStringLiteral("DialogCreatePlayer"));
        DialogCreatePlayer->resize(400, 182);
        lineEditPWD = new QLineEdit(DialogCreatePlayer);
        lineEditPWD->setObjectName(QStringLiteral("lineEditPWD"));
        lineEditPWD->setGeometry(QRect(130, 70, 231, 22));
        lineEditPlayerName = new QLineEdit(DialogCreatePlayer);
        lineEditPlayerName->setObjectName(QStringLiteral("lineEditPlayerName"));
        lineEditPlayerName->setGeometry(QRect(130, 30, 231, 22));
        label_2 = new QLabel(DialogCreatePlayer);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(54, 70, 71, 21));
        label_2->setScaledContents(false);
        label = new QLabel(DialogCreatePlayer);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 91, 21));
        label->setScaledContents(false);
        buttonBox = new QDialogButtonBox(DialogCreatePlayer);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 130, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(DialogCreatePlayer);

        QMetaObject::connectSlotsByName(DialogCreatePlayer);
    } // setupUi

    void retranslateUi(QDialog *DialogCreatePlayer)
    {
        DialogCreatePlayer->setWindowTitle(QApplication::translate("DialogCreatePlayer", "Dialog", nullptr));
        label_2->setText(QApplication::translate("DialogCreatePlayer", "Password : ", nullptr));
        label->setText(QApplication::translate("DialogCreatePlayer", "Player name : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogCreatePlayer: public Ui_DialogCreatePlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCREATEPLAYER_H
