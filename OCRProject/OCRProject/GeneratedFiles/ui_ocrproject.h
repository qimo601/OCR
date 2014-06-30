/********************************************************************************
** Form generated from reading UI file 'ocrproject.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCRPROJECT_H
#define UI_OCRPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OCRProjectClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *connectHostBtn;
    QPushButton *disconnectBtn;
    QPushButton *sendDataBtn;
    QTextEdit *logTextEdit;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OCRProjectClass)
    {
        if (OCRProjectClass->objectName().isEmpty())
            OCRProjectClass->setObjectName(QStringLiteral("OCRProjectClass"));
        OCRProjectClass->resize(600, 400);
        centralWidget = new QWidget(OCRProjectClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        connectHostBtn = new QPushButton(centralWidget);
        connectHostBtn->setObjectName(QStringLiteral("connectHostBtn"));

        horizontalLayout->addWidget(connectHostBtn);

        disconnectBtn = new QPushButton(centralWidget);
        disconnectBtn->setObjectName(QStringLiteral("disconnectBtn"));

        horizontalLayout->addWidget(disconnectBtn);

        sendDataBtn = new QPushButton(centralWidget);
        sendDataBtn->setObjectName(QStringLiteral("sendDataBtn"));

        horizontalLayout->addWidget(sendDataBtn);


        verticalLayout->addLayout(horizontalLayout);

        logTextEdit = new QTextEdit(centralWidget);
        logTextEdit->setObjectName(QStringLiteral("logTextEdit"));

        verticalLayout->addWidget(logTextEdit);


        horizontalLayout_2->addLayout(verticalLayout);

        OCRProjectClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OCRProjectClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        OCRProjectClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(OCRProjectClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OCRProjectClass->setStatusBar(statusBar);

        retranslateUi(OCRProjectClass);

        QMetaObject::connectSlotsByName(OCRProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *OCRProjectClass)
    {
        OCRProjectClass->setWindowTitle(QApplication::translate("OCRProjectClass", "OCRProject", 0));
        connectHostBtn->setText(QApplication::translate("OCRProjectClass", "Connect", 0));
        disconnectBtn->setText(QApplication::translate("OCRProjectClass", "Disconnect", 0));
        sendDataBtn->setText(QApplication::translate("OCRProjectClass", "Send Data", 0));
    } // retranslateUi

};

namespace Ui {
    class OCRProjectClass: public Ui_OCRProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCRPROJECT_H
