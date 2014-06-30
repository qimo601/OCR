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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OcrControl
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_5;
    QLabel *versionNumLabel;
    QHBoxLayout *horizontalLayout;
    QFrame *horseFrame;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *titleHBoxLayout;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_6;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLabel *sessionLbl;
    QLabel *label_2;
    QLabel *raceTimeLbl;
    QLabel *imageLbl;
    QFrame *frame_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *qinFrame;
    QVBoxLayout *verticalLayout_5;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *QINLabel;
    QLabel *adTimeLbl;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_59;
    QLabel *imageFileNameLabel;
    QWidget *page_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_61;
    QLabel *label_62;
    QLabel *label_63;
    QLabel *label_64;
    QLabel *label_65;
    QLabel *label_66;
    QLabel *label_67;
    QLabel *label_68;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_69;
    QLabel *label_70;
    QLabel *label_71;
    QLabel *label_72;
    QLabel *label_73;
    QLabel *label_74;
    QLabel *label_75;
    QLabel *label_76;
    QLabel *label_77;
    QLabel *label_78;
    QLabel *label_79;
    QLabel *label_80;
    QLabel *label_81;
    QFrame *qplFrame;
    QVBoxLayout *verticalLayout_12;
    QWidget *layoutWidget_6;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_82;
    QLabel *label_83;
    QLabel *label_84;
    QLabel *label_85;
    QLabel *label_86;
    QLabel *label_87;
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
        versionNumLabel = new QLabel(frame_5);
        versionNumLabel->setObjectName(QStringLiteral("versionNumLabel"));
        versionNumLabel->setGeometry(QRect(930, 10, 221, 41));
        versionNumLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 130, 80);"));
        versionNumLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(frame_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horseFrame = new QFrame(OcrControl);
        horseFrame->setObjectName(QStringLiteral("horseFrame"));
        horseFrame->setFrameShape(QFrame::StyledPanel);
        horseFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(horseFrame);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        titleHBoxLayout = new QHBoxLayout();
        titleHBoxLayout->setSpacing(6);
        titleHBoxLayout->setObjectName(QStringLiteral("titleHBoxLayout"));
        label_4 = new QLabel(horseFrame);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);

        titleHBoxLayout->addWidget(label_4);

        label_5 = new QLabel(horseFrame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        titleHBoxLayout->addWidget(label_5);

        label_3 = new QLabel(horseFrame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        titleHBoxLayout->addWidget(label_3);

        label_6 = new QLabel(horseFrame);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        titleHBoxLayout->addWidget(label_6);

        titleHBoxLayout->setStretch(0, 1);
        titleHBoxLayout->setStretch(1, 3);
        titleHBoxLayout->setStretch(2, 1);
        titleHBoxLayout->setStretch(3, 1);

        verticalLayout_4->addLayout(titleHBoxLayout);


        horizontalLayout->addWidget(horseFrame);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_3 = new QFrame(OcrControl);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_3);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label = new QLabel(frame_3);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        horizontalLayout_8->addWidget(label);

        sessionLbl = new QLabel(frame_3);
        sessionLbl->setObjectName(QStringLiteral("sessionLbl"));
        QFont font2;
        font2.setPointSize(15);
        sessionLbl->setFont(font2);
        sessionLbl->setStyleSheet(QStringLiteral("background-color: rgb(169, 181, 255);"));

        horizontalLayout_8->addWidget(sessionLbl);

        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        horizontalLayout_8->addWidget(label_2);

        raceTimeLbl = new QLabel(frame_3);
        raceTimeLbl->setObjectName(QStringLiteral("raceTimeLbl"));
        raceTimeLbl->setFont(font2);
        raceTimeLbl->setStyleSheet(QStringLiteral("background-color: rgb(255, 133, 135);"));

        horizontalLayout_8->addWidget(raceTimeLbl);


        verticalLayout->addWidget(frame_3);

        imageLbl = new QLabel(OcrControl);
        imageLbl->setObjectName(QStringLiteral("imageLbl"));
        imageLbl->setStyleSheet(QStringLiteral("background-color: rgb(6, 6, 6);"));

        verticalLayout->addWidget(imageLbl);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 5);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);

        verticalLayout_2->addLayout(horizontalLayout);

        frame_2 = new QFrame(OcrControl);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(frame_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(9, -1, 1151, 201));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        qinFrame = new QFrame(page);
        qinFrame->setObjectName(QStringLiteral("qinFrame"));
        qinFrame->setGeometry(QRect(40, 30, 656, 141));
        qinFrame->setStyleSheet(QLatin1String("QFrame{\n"
"    border: 1px solid #9D9D9D;\n"
"	background-color: #FFFFFF;\n"
"	border-radius:0px;\n"
"    padding:0 0px;\n"
"	margin-right: 10px;\n"
"}"));
        qinFrame->setFrameShape(QFrame::StyledPanel);
        qinFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(qinFrame);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, 0, -1, 0);
        layoutWidget_2 = new QWidget(page);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 50, 16, 116));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMinimumSize(QSize(0, 14));
        label_14->setMaximumSize(QSize(21, 14));

        verticalLayout_7->addWidget(label_14);

        label_15 = new QLabel(layoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(0, 14));
        label_15->setMaximumSize(QSize(21, 14));

        verticalLayout_7->addWidget(label_15);

        label_16 = new QLabel(layoutWidget_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(0, 14));
        label_16->setMaximumSize(QSize(21, 14));

        verticalLayout_7->addWidget(label_16);

        label_17 = new QLabel(layoutWidget_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMinimumSize(QSize(0, 14));
        label_17->setMaximumSize(QSize(21, 14));

        verticalLayout_7->addWidget(label_17);

        label_18 = new QLabel(layoutWidget_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMinimumSize(QSize(0, 14));
        label_18->setMaximumSize(QSize(21, 14));

        verticalLayout_7->addWidget(label_18);

        label_19 = new QLabel(layoutWidget_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setMinimumSize(QSize(0, 14));
        label_19->setMaximumSize(QSize(21, 14));

        verticalLayout_7->addWidget(label_19);

        QINLabel = new QLabel(page);
        QINLabel->setObjectName(QStringLiteral("QINLabel"));
        QINLabel->setGeometry(QRect(50, 0, 54, 31));
        QINLabel->setStyleSheet(QString::fromUtf8("QLabel#label_60\n"
"{\n"
"  color: rgb(255, 97, 24);\n"
"  font: 75 20pt \"\346\226\260\345\256\213\344\275\223\";\n"
"}"));
        adTimeLbl = new QLabel(page);
        adTimeLbl->setObjectName(QStringLiteral("adTimeLbl"));
        adTimeLbl->setGeometry(QRect(800, 40, 71, 81));
        adTimeLbl->setStyleSheet(QStringLiteral("background-color: rgb(255, 130, 80);"));
        adTimeLbl->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(690, 30, 16, 136));
        verticalLayout_6 = new QVBoxLayout(layoutWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(0, 14));
        label_7->setMaximumSize(QSize(21, 14));

        verticalLayout_6->addWidget(label_7);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 14));
        label_8->setMaximumSize(QSize(21, 14));

        verticalLayout_6->addWidget(label_8);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(0, 14));
        label_9->setMaximumSize(QSize(21, 14));

        verticalLayout_6->addWidget(label_9);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(0, 14));
        label_10->setMaximumSize(QSize(21, 14));

        verticalLayout_6->addWidget(label_10);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(0, 14));
        label_11->setMaximumSize(QSize(21, 14));

        verticalLayout_6->addWidget(label_11);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(0, 14));
        label_12->setMaximumSize(QSize(21, 14));

        verticalLayout_6->addWidget(label_12);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(0, 14));
        label_13->setMaximumSize(QSize(21, 14));

        verticalLayout_6->addWidget(label_13);

        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(140, 10, 542, 20));
        layoutWidget1->setMinimumSize(QSize(36, 14));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget1);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setMinimumSize(QSize(36, 14));
        label_21->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_21);

        label_22 = new QLabel(layoutWidget1);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setMinimumSize(QSize(36, 14));
        label_22->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_22);

        label_23 = new QLabel(layoutWidget1);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setMinimumSize(QSize(36, 14));
        label_23->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_23);

        label_24 = new QLabel(layoutWidget1);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setMinimumSize(QSize(36, 14));
        label_24->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_24);

        label_25 = new QLabel(layoutWidget1);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setMinimumSize(QSize(36, 14));
        label_25->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_25);

        label_26 = new QLabel(layoutWidget1);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setMinimumSize(QSize(36, 14));
        label_26->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_26);

        label_27 = new QLabel(layoutWidget1);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setMinimumSize(QSize(36, 14));
        label_27->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_27);

        label_28 = new QLabel(layoutWidget1);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setMinimumSize(QSize(36, 14));
        label_28->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_28);

        label_29 = new QLabel(layoutWidget1);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setMinimumSize(QSize(36, 14));
        label_29->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_29);

        label_30 = new QLabel(layoutWidget1);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setMinimumSize(QSize(36, 14));
        label_30->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_30);

        label_31 = new QLabel(layoutWidget1);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setMinimumSize(QSize(36, 14));
        label_31->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_31);

        label_32 = new QLabel(layoutWidget1);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setMinimumSize(QSize(36, 14));
        label_32->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_32);

        label_59 = new QLabel(layoutWidget1);
        label_59->setObjectName(QStringLiteral("label_59"));
        label_59->setMinimumSize(QSize(36, 14));
        label_59->setMaximumSize(QSize(36, 14));

        horizontalLayout_7->addWidget(label_59);

        imageFileNameLabel = new QLabel(page);
        imageFileNameLabel->setObjectName(QStringLiteral("imageFileNameLabel"));
        imageFileNameLabel->setGeometry(QRect(940, 40, 71, 81));
        imageFileNameLabel->setStyleSheet(QStringLiteral("background-color: rgb(255, 130, 80);"));
        imageFileNameLabel->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        layoutWidget2 = new QWidget(page_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(720, 20, 16, 136));
        verticalLayout_11 = new QVBoxLayout(layoutWidget2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_61 = new QLabel(layoutWidget2);
        label_61->setObjectName(QStringLiteral("label_61"));
        label_61->setMinimumSize(QSize(0, 14));
        label_61->setMaximumSize(QSize(21, 14));

        verticalLayout_11->addWidget(label_61);

        label_62 = new QLabel(layoutWidget2);
        label_62->setObjectName(QStringLiteral("label_62"));
        label_62->setMinimumSize(QSize(0, 14));
        label_62->setMaximumSize(QSize(21, 14));

        verticalLayout_11->addWidget(label_62);

        label_63 = new QLabel(layoutWidget2);
        label_63->setObjectName(QStringLiteral("label_63"));
        label_63->setMinimumSize(QSize(0, 14));
        label_63->setMaximumSize(QSize(21, 14));

        verticalLayout_11->addWidget(label_63);

        label_64 = new QLabel(layoutWidget2);
        label_64->setObjectName(QStringLiteral("label_64"));
        label_64->setMinimumSize(QSize(0, 14));
        label_64->setMaximumSize(QSize(21, 14));

        verticalLayout_11->addWidget(label_64);

        label_65 = new QLabel(layoutWidget2);
        label_65->setObjectName(QStringLiteral("label_65"));
        label_65->setMinimumSize(QSize(0, 14));
        label_65->setMaximumSize(QSize(21, 14));

        verticalLayout_11->addWidget(label_65);

        label_66 = new QLabel(layoutWidget2);
        label_66->setObjectName(QStringLiteral("label_66"));
        label_66->setMinimumSize(QSize(0, 14));
        label_66->setMaximumSize(QSize(21, 14));

        verticalLayout_11->addWidget(label_66);

        label_67 = new QLabel(layoutWidget2);
        label_67->setObjectName(QStringLiteral("label_67"));
        label_67->setMinimumSize(QSize(0, 14));
        label_67->setMaximumSize(QSize(21, 14));

        verticalLayout_11->addWidget(label_67);

        label_68 = new QLabel(page_2);
        label_68->setObjectName(QStringLiteral("label_68"));
        label_68->setGeometry(QRect(80, 0, 51, 21));
        label_68->setStyleSheet(QString::fromUtf8("QLabel#label_68\n"
"{\n"
"	color: rgb(154, 66, 255);\n"
"	font: 75 16pt \"\346\226\260\345\256\213\344\275\223\";\n"
"}"));
        layoutWidget_5 = new QWidget(page_2);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(170, 0, 542, 20));
        layoutWidget_5->setMinimumSize(QSize(36, 14));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_69 = new QLabel(layoutWidget_5);
        label_69->setObjectName(QStringLiteral("label_69"));
        label_69->setMinimumSize(QSize(36, 14));
        label_69->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_69);

        label_70 = new QLabel(layoutWidget_5);
        label_70->setObjectName(QStringLiteral("label_70"));
        label_70->setMinimumSize(QSize(36, 14));
        label_70->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_70);

        label_71 = new QLabel(layoutWidget_5);
        label_71->setObjectName(QStringLiteral("label_71"));
        label_71->setMinimumSize(QSize(36, 14));
        label_71->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_71);

        label_72 = new QLabel(layoutWidget_5);
        label_72->setObjectName(QStringLiteral("label_72"));
        label_72->setMinimumSize(QSize(36, 14));
        label_72->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_72);

        label_73 = new QLabel(layoutWidget_5);
        label_73->setObjectName(QStringLiteral("label_73"));
        label_73->setMinimumSize(QSize(36, 14));
        label_73->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_73);

        label_74 = new QLabel(layoutWidget_5);
        label_74->setObjectName(QStringLiteral("label_74"));
        label_74->setMinimumSize(QSize(36, 14));
        label_74->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_74);

        label_75 = new QLabel(layoutWidget_5);
        label_75->setObjectName(QStringLiteral("label_75"));
        label_75->setMinimumSize(QSize(36, 14));
        label_75->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_75);

        label_76 = new QLabel(layoutWidget_5);
        label_76->setObjectName(QStringLiteral("label_76"));
        label_76->setMinimumSize(QSize(36, 14));
        label_76->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_76);

        label_77 = new QLabel(layoutWidget_5);
        label_77->setObjectName(QStringLiteral("label_77"));
        label_77->setMinimumSize(QSize(36, 14));
        label_77->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_77);

        label_78 = new QLabel(layoutWidget_5);
        label_78->setObjectName(QStringLiteral("label_78"));
        label_78->setMinimumSize(QSize(36, 14));
        label_78->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_78);

        label_79 = new QLabel(layoutWidget_5);
        label_79->setObjectName(QStringLiteral("label_79"));
        label_79->setMinimumSize(QSize(36, 14));
        label_79->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_79);

        label_80 = new QLabel(layoutWidget_5);
        label_80->setObjectName(QStringLiteral("label_80"));
        label_80->setMinimumSize(QSize(36, 14));
        label_80->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_80);

        label_81 = new QLabel(layoutWidget_5);
        label_81->setObjectName(QStringLiteral("label_81"));
        label_81->setMinimumSize(QSize(36, 14));
        label_81->setMaximumSize(QSize(36, 14));

        horizontalLayout_9->addWidget(label_81);

        qplFrame = new QFrame(page_2);
        qplFrame->setObjectName(QStringLiteral("qplFrame"));
        qplFrame->setGeometry(QRect(70, 20, 656, 161));
        qplFrame->setStyleSheet(QLatin1String("QFrame{\n"
"    border: 1px solid #9D9D9D;\n"
"	background-color: #FFFFFF;\n"
"	border-radius:0px;\n"
"    padding:0 0px;\n"
"	margin-right: 10px;\n"
"}"));
        qplFrame->setFrameShape(QFrame::StyledPanel);
        qplFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_12 = new QVBoxLayout(qplFrame);
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(-1, 0, -1, 0);
        layoutWidget_6 = new QWidget(page_2);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(50, 50, 16, 121));
        verticalLayout_13 = new QVBoxLayout(layoutWidget_6);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_82 = new QLabel(layoutWidget_6);
        label_82->setObjectName(QStringLiteral("label_82"));
        label_82->setMinimumSize(QSize(0, 14));
        label_82->setMaximumSize(QSize(21, 14));

        verticalLayout_13->addWidget(label_82);

        label_83 = new QLabel(layoutWidget_6);
        label_83->setObjectName(QStringLiteral("label_83"));
        label_83->setMinimumSize(QSize(0, 14));
        label_83->setMaximumSize(QSize(21, 14));

        verticalLayout_13->addWidget(label_83);

        label_84 = new QLabel(layoutWidget_6);
        label_84->setObjectName(QStringLiteral("label_84"));
        label_84->setMinimumSize(QSize(0, 14));
        label_84->setMaximumSize(QSize(21, 14));

        verticalLayout_13->addWidget(label_84);

        label_85 = new QLabel(layoutWidget_6);
        label_85->setObjectName(QStringLiteral("label_85"));
        label_85->setMinimumSize(QSize(0, 14));
        label_85->setMaximumSize(QSize(21, 14));

        verticalLayout_13->addWidget(label_85);

        label_86 = new QLabel(layoutWidget_6);
        label_86->setObjectName(QStringLiteral("label_86"));
        label_86->setMinimumSize(QSize(0, 14));
        label_86->setMaximumSize(QSize(21, 14));

        verticalLayout_13->addWidget(label_86);

        label_87 = new QLabel(layoutWidget_6);
        label_87->setObjectName(QStringLiteral("label_87"));
        label_87->setMinimumSize(QSize(0, 14));
        label_87->setMaximumSize(QSize(21, 14));

        verticalLayout_13->addWidget(label_87);

        stackedWidget->addWidget(page_2);

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
        verticalLayout_2->setStretch(2, 4);
        verticalLayout_2->setStretch(3, 3);

        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(OcrControl);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OcrControl);
    } // setupUi

    void retranslateUi(QWidget *OcrControl)
    {
        OcrControl->setWindowTitle(QApplication::translate("OcrControl", "OcrControl", 0));
        versionNumLabel->setText(QApplication::translate("OcrControl", "ADTime", 0));
        label_4->setText(QApplication::translate("OcrControl", "\345\272\217\345\217\267", 0));
        label_5->setText(QApplication::translate("OcrControl", "\351\251\254\345\220\215", 0));
        label_3->setText(QApplication::translate("OcrControl", "WIN", 0));
        label_6->setText(QApplication::translate("OcrControl", "PLA", 0));
        label->setText(QApplication::translate("OcrControl", "\345\234\272\346\254\241\357\274\232", 0));
        sessionLbl->setText(QString());
        label_2->setText(QApplication::translate("OcrControl", "\345\200\222\350\256\241\346\227\266\357\274\232", 0));
        raceTimeLbl->setText(QString());
        imageLbl->setText(QApplication::translate("OcrControl", "TextLabel", 0));
        label_14->setText(QApplication::translate("OcrControl", "9", 0));
        label_15->setText(QApplication::translate("OcrControl", "10", 0));
        label_16->setText(QApplication::translate("OcrControl", "11", 0));
        label_17->setText(QApplication::translate("OcrControl", "12", 0));
        label_18->setText(QApplication::translate("OcrControl", "13", 0));
        label_19->setText(QApplication::translate("OcrControl", "14", 0));
        QINLabel->setText(QApplication::translate("OcrControl", "QIN", 0));
        adTimeLbl->setText(QApplication::translate("OcrControl", "ADTime", 0));
        label_7->setText(QApplication::translate("OcrControl", "1", 0));
        label_8->setText(QApplication::translate("OcrControl", "2", 0));
        label_9->setText(QApplication::translate("OcrControl", "3", 0));
        label_10->setText(QApplication::translate("OcrControl", "4", 0));
        label_11->setText(QApplication::translate("OcrControl", "5", 0));
        label_12->setText(QApplication::translate("OcrControl", "6", 0));
        label_13->setText(QApplication::translate("OcrControl", "7", 0));
        label_21->setText(QApplication::translate("OcrControl", "2", 0));
        label_22->setText(QApplication::translate("OcrControl", "3", 0));
        label_23->setText(QApplication::translate("OcrControl", "4", 0));
        label_24->setText(QApplication::translate("OcrControl", "5", 0));
        label_25->setText(QApplication::translate("OcrControl", "6", 0));
        label_26->setText(QApplication::translate("OcrControl", "7", 0));
        label_27->setText(QApplication::translate("OcrControl", "8", 0));
        label_28->setText(QApplication::translate("OcrControl", "9", 0));
        label_29->setText(QApplication::translate("OcrControl", "10", 0));
        label_30->setText(QApplication::translate("OcrControl", "11", 0));
        label_31->setText(QApplication::translate("OcrControl", "12", 0));
        label_32->setText(QApplication::translate("OcrControl", "13", 0));
        label_59->setText(QApplication::translate("OcrControl", "14", 0));
        imageFileNameLabel->setText(QApplication::translate("OcrControl", "imageName", 0));
        label_61->setText(QApplication::translate("OcrControl", "1", 0));
        label_62->setText(QApplication::translate("OcrControl", "2", 0));
        label_63->setText(QApplication::translate("OcrControl", "3", 0));
        label_64->setText(QApplication::translate("OcrControl", "4", 0));
        label_65->setText(QApplication::translate("OcrControl", "5", 0));
        label_66->setText(QApplication::translate("OcrControl", "6", 0));
        label_67->setText(QApplication::translate("OcrControl", "7", 0));
        label_68->setText(QApplication::translate("OcrControl", "QPL", 0));
        label_69->setText(QApplication::translate("OcrControl", "2", 0));
        label_70->setText(QApplication::translate("OcrControl", "3", 0));
        label_71->setText(QApplication::translate("OcrControl", "4", 0));
        label_72->setText(QApplication::translate("OcrControl", "5", 0));
        label_73->setText(QApplication::translate("OcrControl", "6", 0));
        label_74->setText(QApplication::translate("OcrControl", "7", 0));
        label_75->setText(QApplication::translate("OcrControl", "8", 0));
        label_76->setText(QApplication::translate("OcrControl", "9", 0));
        label_77->setText(QApplication::translate("OcrControl", "10", 0));
        label_78->setText(QApplication::translate("OcrControl", "11", 0));
        label_79->setText(QApplication::translate("OcrControl", "12", 0));
        label_80->setText(QApplication::translate("OcrControl", "13", 0));
        label_81->setText(QApplication::translate("OcrControl", "14", 0));
        label_82->setText(QApplication::translate("OcrControl", "9", 0));
        label_83->setText(QApplication::translate("OcrControl", "10", 0));
        label_84->setText(QApplication::translate("OcrControl", "11", 0));
        label_85->setText(QApplication::translate("OcrControl", "12", 0));
        label_86->setText(QApplication::translate("OcrControl", "13", 0));
        label_87->setText(QApplication::translate("OcrControl", "14", 0));
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
