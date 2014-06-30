/********************************************************************************
** Form generated from reading UI file 'testacqdriver.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTACQDRIVER_H
#define UI_TESTACQDRIVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testAcqDriverClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *initBtn;
    QPushButton *startCapBtn;
    QPushButton *releaseBtn;
    QPushButton *readDataBtn;
    QLabel *imageLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testAcqDriverClass)
    {
        if (testAcqDriverClass->objectName().isEmpty())
            testAcqDriverClass->setObjectName(QStringLiteral("testAcqDriverClass"));
        testAcqDriverClass->resize(622, 468);
        centralWidget = new QWidget(testAcqDriverClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        initBtn = new QPushButton(centralWidget);
        initBtn->setObjectName(QStringLiteral("initBtn"));

        horizontalLayout->addWidget(initBtn);

        startCapBtn = new QPushButton(centralWidget);
        startCapBtn->setObjectName(QStringLiteral("startCapBtn"));

        horizontalLayout->addWidget(startCapBtn);

        releaseBtn = new QPushButton(centralWidget);
        releaseBtn->setObjectName(QStringLiteral("releaseBtn"));

        horizontalLayout->addWidget(releaseBtn);

        readDataBtn = new QPushButton(centralWidget);
        readDataBtn->setObjectName(QStringLiteral("readDataBtn"));

        horizontalLayout->addWidget(readDataBtn);


        verticalLayout->addLayout(horizontalLayout);

        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        verticalLayout->addWidget(imageLabel);

        testAcqDriverClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(testAcqDriverClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 622, 17));
        testAcqDriverClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testAcqDriverClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        testAcqDriverClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(testAcqDriverClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        testAcqDriverClass->setStatusBar(statusBar);

        retranslateUi(testAcqDriverClass);

        QMetaObject::connectSlotsByName(testAcqDriverClass);
    } // setupUi

    void retranslateUi(QMainWindow *testAcqDriverClass)
    {
        testAcqDriverClass->setWindowTitle(QApplication::translate("testAcqDriverClass", "testAcqDriver", 0));
        initBtn->setText(QApplication::translate("testAcqDriverClass", "\345\210\235\345\247\213\345\214\226", 0));
        startCapBtn->setText(QApplication::translate("testAcqDriverClass", "\345\274\200\345\247\213\351\207\207\351\233\206", 0));
        releaseBtn->setText(QApplication::translate("testAcqDriverClass", "\351\200\200\345\207\272\345\215\270\350\275\275", 0));
        readDataBtn->setText(QApplication::translate("testAcqDriverClass", "\350\257\273\345\217\226\346\225\260\346\215\256\345\271\266\346\230\276\347\244\272", 0));
        imageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class testAcqDriverClass: public Ui_testAcqDriverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTACQDRIVER_H
