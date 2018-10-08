/********************************************************************************
** Form generated from reading UI file 'dialogloadplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOADPLAYER_H
#define UI_DIALOGLOADPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogLoadPlayer
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEditPlayerName;
    QLineEdit *lineEditPWD;

    void setupUi(QDialog *DialogLoadPlayer)
    {
        if (DialogLoadPlayer->objectName().isEmpty())
            DialogLoadPlayer->setObjectName(QStringLiteral("DialogLoadPlayer"));
        DialogLoadPlayer->resize(400, 179);
        buttonBox = new QDialogButtonBox(DialogLoadPlayer);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 130, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_2 = new QLabel(DialogLoadPlayer);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 70, 71, 21));
        label_2->setScaledContents(false);
        label = new QLabel(DialogLoadPlayer);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(34, 30, 80, 21));
        label->setScaledContents(false);
        lineEditPlayerName = new QLineEdit(DialogLoadPlayer);
        lineEditPlayerName->setObjectName(QStringLiteral("lineEditPlayerName"));
        lineEditPlayerName->setGeometry(QRect(130, 30, 231, 22));
        lineEditPWD = new QLineEdit(DialogLoadPlayer);
        lineEditPWD->setObjectName(QStringLiteral("lineEditPWD"));
        lineEditPWD->setGeometry(QRect(130, 70, 231, 22));

        retranslateUi(DialogLoadPlayer);

        QMetaObject::connectSlotsByName(DialogLoadPlayer);
    } // setupUi

    void retranslateUi(QDialog *DialogLoadPlayer)
    {
        DialogLoadPlayer->setWindowTitle(QApplication::translate("DialogLoadPlayer", "Dialog", nullptr));
        label_2->setText(QApplication::translate("DialogLoadPlayer", "Password : ", nullptr));
        label->setText(QApplication::translate("DialogLoadPlayer", "Player name : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogLoadPlayer: public Ui_DialogLoadPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOADPLAYER_H
