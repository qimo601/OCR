/********************************************************************************
** Form generated from reading UI file 'OcrControl.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCRCONTROL_H
#define UI_OCRCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OcrControl
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout;
    QFrame *horseFrame;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *titleHBoxLayout;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_6;
    QHBoxLayout *itemHBoxLayout;
    QLabel *indexLbel_1;
    QTextEdit *horseNameEdit_1;
    QLabel *winLbl_1;
    QLabel *PLALbl_1;
    QHBoxLayout *itemHBoxLayout_2;
    QLabel *indexLbel_2;
    QTextEdit *horseNameEdit_2;
    QLabel *winLbl_2;
    QLabel *PLALbl_2;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QLabel *label;
    QLabel *sessionLbl;
    QLabel *label_2;
    QLabel *raceTimeLbl;
    QLabel *imageLbl;
    QFrame *frame_2;
    QLabel *label_7;
    QLabel *label_8;
    QFrame *frame_4;
    QPushButton *connectBtn;
    QPushButton *requestHorseInfoBtn;
    QTextBrowser *textBrowser;
    QPushButton *loginBtn;
    QPushButton *disconnectBtn;
    QPushButton *requestRaceIdBtn;
    QPushButton *submitRaceTimeBtn;
    QPushButton *submitRealBtn;
    QPushButton *startAcqBtn;
    QPushButton *stopAcqBtn;

    void setupUi(QWidget *OcrControl)
    {
        if (OcrControl->objectName().isEmpty())
            OcrControl->setObjectName(QStringLiteral("OcrControl"));
        OcrControl->resize(1191, 877);
        verticalLayout_3 = new QVBoxLayout(OcrControl);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frame_5 = new QFrame(OcrControl);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horseFrame = new QFrame(OcrControl);
        horseFrame->setObjectName(QStringLiteral("horseFrame"));
        horseFrame->setFrameShape(QFrame::StyledPanel);
        horseFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(horseFrame);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        titleHBoxLayout = new QHBoxLayout();
        titleHBoxLayout->setSpacing(6);
        titleHBoxLayout->setObjectName(QStringLiteral("titleHBoxLayout"));
        label_4 = new QLabel(horseFrame);
        label_4->setObjectName(QStringLiteral("label_4"));

        titleHBoxLayout->addWidget(label_4);

        label_5 = new QLabel(horseFrame);
        label_5->setObjectName(QStringLiteral("label_5"));

        titleHBoxLayout->addWidget(label_5);

        label_3 = new QLabel(horseFrame);
        label_3->setObjectName(QStringLiteral("label_3"));

        titleHBoxLayout->addWidget(label_3);

        label_6 = new QLabel(horseFrame);
        label_6->setObjectName(QStringLiteral("label_6"));

        titleHBoxLayout->addWidget(label_6);


        verticalLayout_4->addLayout(titleHBoxLayout);

        itemHBoxLayout = new QHBoxLayout();
        itemHBoxLayout->setSpacing(6);
        itemHBoxLayout->setObjectName(QStringLiteral("itemHBoxLayout"));
        indexLbel_1 = new QLabel(horseFrame);
        indexLbel_1->setObjectName(QStringLiteral("indexLbel_1"));
        indexLbel_1->setAlignment(Qt::AlignCenter);

        itemHBoxLayout->addWidget(indexLbel_1);

        horseNameEdit_1 = new QTextEdit(horseFrame);
        horseNameEdit_1->setObjectName(QStringLiteral("horseNameEdit_1"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horseNameEdit_1->sizePolicy().hasHeightForWidth());
        horseNameEdit_1->setSizePolicy(sizePolicy);
        horseNameEdit_1->setMaximumSize(QSize(16777215, 20));

        itemHBoxLayout->addWidget(horseNameEdit_1);

        winLbl_1 = new QLabel(horseFrame);
        winLbl_1->setObjectName(QStringLiteral("winLbl_1"));
        winLbl_1->setAlignment(Qt::AlignCenter);

        itemHBoxLayout->addWidget(winLbl_1);

        PLALbl_1 = new QLabel(horseFrame);
        PLALbl_1->setObjectName(QStringLiteral("PLALbl_1"));
        PLALbl_1->setAlignment(Qt::AlignCenter);

        itemHBoxLayout->addWidget(PLALbl_1);

        itemHBoxLayout->setStretch(0, 1);
        itemHBoxLayout->setStretch(1, 3);
        itemHBoxLayout->setStretch(2, 3);
        itemHBoxLayout->setStretch(3, 3);

        verticalLayout_4->addLayout(itemHBoxLayout);

        itemHBoxLayout_2 = new QHBoxLayout();
        itemHBoxLayout_2->setSpacing(6);
        itemHBoxLayout_2->setObjectName(QStringLiteral("itemHBoxLayout_2"));
        indexLbel_2 = new QLabel(horseFrame);
        indexLbel_2->setObjectName(QStringLiteral("indexLbel_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(indexLbel_2->sizePolicy().hasHeightForWidth());
        indexLbel_2->setSizePolicy(sizePolicy1);
        indexLbel_2->setAlignment(Qt::AlignCenter);

        itemHBoxLayout_2->addWidget(indexLbel_2);

        horseNameEdit_2 = new QTextEdit(horseFrame);
        horseNameEdit_2->setObjectName(QStringLiteral("horseNameEdit_2"));
        sizePolicy.setHeightForWidth(horseNameEdit_2->sizePolicy().hasHeightForWidth());
        horseNameEdit_2->setSizePolicy(sizePolicy);
        horseNameEdit_2->setMaximumSize(QSize(16777215, 20));

        itemHBoxLayout_2->addWidget(horseNameEdit_2);

        winLbl_2 = new QLabel(horseFrame);
        winLbl_2->setObjectName(QStringLiteral("winLbl_2"));
        sizePolicy1.setHeightForWidth(winLbl_2->sizePolicy().hasHeightForWidth());
        winLbl_2->setSizePolicy(sizePolicy1);
        winLbl_2->setAlignment(Qt::AlignCenter);

        itemHBoxLayout_2->addWidget(winLbl_2);

        PLALbl_2 = new QLabel(horseFrame);
        PLALbl_2->setObjectName(QStringLiteral("PLALbl_2"));
        sizePolicy1.setHeightForWidth(PLALbl_2->sizePolicy().hasHeightForWidth());
        PLALbl_2->setSizePolicy(sizePolicy1);
        PLALbl_2->setAlignment(Qt::AlignCenter);

        itemHBoxLayout_2->addWidget(PLALbl_2);

        itemHBoxLayout_2->setStretch(0, 1);
        itemHBoxLayout_2->setStretch(1, 3);
        itemHBoxLayout_2->setStretch(2, 3);
        itemHBoxLayout_2->setStretch(3, 3);

        verticalLayout_4->addLayout(itemHBoxLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout->addWidget(horseFrame);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_3 = new QFrame(OcrControl);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 54, 31));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        sessionLbl = new QLabel(frame_3);
        sessionLbl->setObjectName(QStringLiteral("sessionLbl"));
        sessionLbl->setGeometry(QRect(90, 30, 101, 31));
        QFont font1;
        font1.setPointSize(15);
        sessionLbl->setFont(font1);
        sessionLbl->setStyleSheet(QStringLiteral("background-color: rgb(169, 181, 255);"));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(340, 30, 81, 31));
        label_2->setFont(font);
        raceTimeLbl = new QLabel(frame_3);
        raceTimeLbl->setObjectName(QStringLiteral("raceTimeLbl"));
        raceTimeLbl->setGeometry(QRect(440, 30, 101, 31));
        raceTimeLbl->setFont(font1);
        raceTimeLbl->setStyleSheet(QStringLiteral("background-color: rgb(255, 133, 135);"));

        verticalLayout->addWidget(frame_3);

        imageLbl = new QLabel(OcrControl);
        imageLbl->setObjectName(QStringLiteral("imageLbl"));

        verticalLayout->addWidget(imageLbl);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);

        verticalLayout_2->addLayout(horizontalLayout);

        frame_2 = new QFrame(OcrControl);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 20, 73, 12));
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 40, 73, 12));

        verticalLayout_2->addWidget(frame_2);

        frame_4 = new QFrame(OcrControl);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setStyleSheet(QStringLiteral(""));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        connectBtn = new QPushButton(frame_4);
        connectBtn->setObjectName(QStringLiteral("connectBtn"));
        connectBtn->setGeometry(QRect(70, 40, 101, 41));
        requestHorseInfoBtn = new QPushButton(frame_4);
        requestHorseInfoBtn->setObjectName(QStringLiteral("requestHorseInfoBtn"));
        requestHorseInfoBtn->setGeometry(QRect(370, 10, 101, 41));
        textBrowser = new QTextBrowser(frame_4);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(590, 10, 256, 121));
        loginBtn = new QPushButton(frame_4);
        loginBtn->setObjectName(QStringLiteral("loginBtn"));
        loginBtn->setGeometry(QRect(190, 40, 101, 41));
        disconnectBtn = new QPushButton(frame_4);
        disconnectBtn->setObjectName(QStringLiteral("disconnectBtn"));
        disconnectBtn->setGeometry(QRect(70, 90, 101, 41));
        requestRaceIdBtn = new QPushButton(frame_4);
        requestRaceIdBtn->setObjectName(QStringLiteral("requestRaceIdBtn"));
        requestRaceIdBtn->setGeometry(QRect(370, 50, 101, 41));
        submitRaceTimeBtn = new QPushButton(frame_4);
        submitRaceTimeBtn->setObjectName(QStringLiteral("submitRaceTimeBtn"));
        submitRaceTimeBtn->setGeometry(QRect(370, 90, 101, 41));
        submitRealBtn = new QPushButton(frame_4);
        submitRealBtn->setObjectName(QStringLiteral("submitRealBtn"));
        submitRealBtn->setGeometry(QRect(370, 130, 101, 41));
        startAcqBtn = new QPushButton(frame_4);
        startAcqBtn->setObjectName(QStringLiteral("startAcqBtn"));
        startAcqBtn->setGeometry(QRect(480, 10, 101, 41));
        stopAcqBtn = new QPushButton(frame_4);
        stopAcqBtn->setObjectName(QStringLiteral("stopAcqBtn"));
        stopAcqBtn->setGeometry(QRect(480, 60, 101, 41));

        verticalLayout_2->addWidget(frame_4);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 7);
        verticalLayout_2->setStretch(2, 3);
        verticalLayout_2->setStretch(3, 3);

        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(OcrControl);

        QMetaObject::connectSlotsByName(OcrControl);
    } // setupUi

    void retranslateUi(QWidget *OcrControl)
    {
        OcrControl->setWindowTitle(QApplication::translate("OcrControl", "OcrControl", 0));
        label_4->setText(QApplication::translate("OcrControl", "\345\272\217\345\210\227\345\217\267", 0));
        label_5->setText(QApplication::translate("OcrControl", "\351\251\254\345\220\215", 0));
        label_3->setText(QApplication::translate("OcrControl", "WIN", 0));
        label_6->setText(QApplication::translate("OcrControl", "PLA", 0));
        indexLbel_1->setText(QApplication::translate("OcrControl", "1", 0));
        winLbl_1->setText(QApplication::translate("OcrControl", "82.5", 0));
        PLALbl_1->setText(QApplication::translate("OcrControl", "21.0", 0));
        indexLbel_2->setText(QApplication::translate("OcrControl", "1", 0));
        winLbl_2->setText(QApplication::translate("OcrControl", "82.5", 0));
        PLALbl_2->setText(QApplication::translate("OcrControl", "21.0", 0));
        label->setText(QApplication::translate("OcrControl", "\345\234\272\346\254\241\357\274\232", 0));
        sessionLbl->setText(QString());
        label_2->setText(QApplication::translate("OcrControl", "\345\200\222\350\256\241\346\227\266\357\274\232", 0));
        raceTimeLbl->setText(QString());
        imageLbl->setText(QApplication::translate("OcrControl", "TextLabel", 0));
        label_7->setText(QApplication::translate("OcrControl", "QIN", 0));
        label_8->setText(QApplication::translate("OcrControl", "1", 0));
        connectBtn->setText(QApplication::translate("OcrControl", "\350\277\236\346\216\245", 0));
        requestHorseInfoBtn->setText(QApplication::translate("OcrControl", "\350\257\267\346\261\202\351\251\254\344\277\241\346\201\257", 0));
        loginBtn->setText(QApplication::translate("OcrControl", "\347\231\273\351\231\206", 0));
        disconnectBtn->setText(QApplication::translate("OcrControl", "\346\226\255\345\274\200", 0));
        requestRaceIdBtn->setText(QApplication::translate("OcrControl", "\350\257\267\346\261\202RaceId", 0));
        submitRaceTimeBtn->setText(QApplication::translate("OcrControl", "\346\217\220\344\272\244\346\257\224\350\265\233\346\227\266\351\225\277", 0));
        submitRealBtn->setText(QApplication::translate("OcrControl", "\346\217\220\344\272\244\345\256\236\346\227\266\346\225\260\346\215\256", 0));
        startAcqBtn->setText(QApplication::translate("OcrControl", "\345\274\200\345\247\213\345\256\236\346\227\266\351\207\207\351\233\206", 0));
        stopAcqBtn->setText(QApplication::translate("OcrControl", "\345\201\234\346\255\242\345\256\236\346\227\266\351\207\207\351\233\206", 0));
    } // retranslateUi

};

namespace Ui {
    class OcrControl: public Ui_OcrControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCRCONTROL_H
