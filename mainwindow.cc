/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "filetable.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *conversio;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *convertResult;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    FileTable *sourceTable;
    QPushButton *chooseSourceButton;
    QLabel *sourceSize;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    FileTable *targetTable;
    QPushButton *chooseTargetButton;
    QLabel *targetSize;
    QTextBrowser *convertOutput;
    QLabel *label_3;
    QPushButton *convertButton;
    QProgressBar *convertProgress;
    QSpacerItem *verticalSpacer_3;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QWidget *parametres;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_4;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *transformOption;
    QComboBox *transformType;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *reduceOption;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1044, 706);
        MainWindow->setStyleSheet(QString::fromUtf8("* {\n"
"	font-family: mono;\n"
"	background: white;\n"
"}\n"
"QPushButton\n"
"{\n"
"	background: black;\n"
"	color: white;\n"
"	\n"
"	padding: 5px;\n"
"    border-style: outset;\n"
"    border-width: 5px;\n"
"    border-radius: 0px;\n"
"    border-color: black;\n"
"}\n"
"QPushButton::pressed\n"
"{	\n"
"	background: white;\n"
"	color: black;\n"
"}\n"
"QTextEdit\n"
"{\n"
"	background: white;\n"
"}\n"
"QFrame {\n"
"	border: 0px;\n"
"	padding: 0px;\n"
"	margin: 0px;\n"
"}\n"
"QTreeView\n"
"{\n"
"	background: rgb(226, 226, 226)\n"
"}\n"
"QTabWidget\n"
"{\n"
"	border-radius: 0px;\n"
"	padding: 0px;\n"
"}\n"
"\n"
"QTableWidget {\n"
"	padding: 10px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        conversio = new QWidget();
        conversio->setObjectName(QString::fromUtf8("conversio"));
        gridLayout_3 = new QGridLayout(conversio);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 7, 0, 1, 1);

        convertResult = new QLabel(conversio);
        convertResult->setObjectName(QString::fromUtf8("convertResult"));
        convertResult->setEnabled(true);

        gridLayout_3->addWidget(convertResult, 7, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 7, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(conversio);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        sourceTable = new FileTable(conversio);
        sourceTable->setObjectName(QString::fromUtf8("sourceTable"));

        verticalLayout->addWidget(sourceTable);

        chooseSourceButton = new QPushButton(conversio);
        chooseSourceButton->setObjectName(QString::fromUtf8("chooseSourceButton"));

        verticalLayout->addWidget(chooseSourceButton);

        sourceSize = new QLabel(conversio);
        sourceSize->setObjectName(QString::fromUtf8("sourceSize"));
        sourceSize->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(sourceSize);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(conversio);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        targetTable = new FileTable(conversio);
        targetTable->setObjectName(QString::fromUtf8("targetTable"));

        verticalLayout_3->addWidget(targetTable);

        chooseTargetButton = new QPushButton(conversio);
        chooseTargetButton->setObjectName(QString::fromUtf8("chooseTargetButton"));

        verticalLayout_3->addWidget(chooseTargetButton);

        targetSize = new QLabel(conversio);
        targetSize->setObjectName(QString::fromUtf8("targetSize"));
        targetSize->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(targetSize);


        horizontalLayout->addLayout(verticalLayout_3);


        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 4);

        convertOutput = new QTextBrowser(conversio);
        convertOutput->setObjectName(QString::fromUtf8("convertOutput"));
        convertOutput->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(convertOutput->sizePolicy().hasHeightForWidth());
        convertOutput->setSizePolicy(sizePolicy);
        convertOutput->setMinimumSize(QSize(0, 2));
        convertOutput->setMaximumSize(QSize(16777215, 100));

        gridLayout_3->addWidget(convertOutput, 6, 0, 1, 4);

        label_3 = new QLabel(conversio);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("mono"));
        font.setPointSize(20);
        font.setItalic(false);
        font.setUnderline(false);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("* {\n"
"	padding: 0px;\n"
"}"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 4);

        convertButton = new QPushButton(conversio);
        convertButton->setObjectName(QString::fromUtf8("convertButton"));
        convertButton->setMinimumSize(QSize(200, 0));
        convertButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(convertButton, 7, 3, 1, 1);

        convertProgress = new QProgressBar(conversio);
        convertProgress->setObjectName(QString::fromUtf8("convertProgress"));
        convertProgress->setEnabled(false);
        convertProgress->setMinimumSize(QSize(0, 50));
        convertProgress->setStyleSheet(QString::fromUtf8("QProgressBar:horizontal {\n"
"text-align: center;\n"
"border-radius: 0px;\n"
"}\n"
"QProgressBar::chunk:horizontal {\n"
"background: rgb(80, 240, 80);\n"
"}"));
        convertProgress->setValue(0);
        convertProgress->setTextVisible(true);
        convertProgress->setInvertedAppearance(false);

        gridLayout_3->addWidget(convertProgress, 5, 0, 1, 4);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_3, 4, 0, 1, 1);

        line = new QFrame(conversio);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setStyleSheet(QString::fromUtf8("* {\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 1, 0, 1, 4);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_2, 2, 0, 1, 4);

        tabWidget->addTab(conversio, QString());
        parametres = new QWidget();
        parametres->setObjectName(QString::fromUtf8("parametres"));
        gridLayout_2 = new QGridLayout(parametres);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_4, 4, 0, 1, 1);

        label_4 = new QLabel(parametres);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("* {\n"
"	padding: 0px;\n"
"}"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        frame = new QFrame(parametres);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        transformOption = new QCheckBox(frame);
        transformOption->setObjectName(QString::fromUtf8("transformOption"));

        horizontalLayout_4->addWidget(transformOption);

        transformType = new QComboBox(frame);
        transformType->addItem(QString());
        transformType->addItem(QString());
        transformType->addItem(QString());
        transformType->addItem(QString());
        transformType->setObjectName(QString::fromUtf8("transformType"));

        horizontalLayout_4->addWidget(transformType);


        gridLayout_2->addWidget(frame, 6, 0, 1, 1);

        frame_2 = new QFrame(parametres);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        reduceOption = new QCheckBox(frame_2);
        reduceOption->setObjectName(QString::fromUtf8("reduceOption"));

        horizontalLayout_3->addWidget(reduceOption);


        gridLayout_2->addWidget(frame_2, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 7, 0, 1, 1);

        line_2 = new QFrame(parametres);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setStyleSheet(QString::fromUtf8("* {\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_2, 3, 0, 1, 1);

        tabWidget->addTab(parametres, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1044, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        convertResult->setText(QCoreApplication::translate("MainWindow", "Correctament convertit amb els par\303\240metres demanats", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Arxius a convertir", nullptr));
        chooseSourceButton->setText(QCoreApplication::translate("MainWindow", "Seleccionar Font", nullptr));
        sourceSize->setText(QCoreApplication::translate("MainWindow", "MB", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Arxius convertits", nullptr));
        chooseTargetButton->setText(QCoreApplication::translate("MainWindow", "Seleccionar Dest\303\255", nullptr));
        targetSize->setText(QCoreApplication::translate("MainWindow", "MB", nullptr));
        convertOutput->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'mono'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Conversor", nullptr));
        convertButton->setText(QCoreApplication::translate("MainWindow", "Convertir", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(conversio), QCoreApplication::translate("MainWindow", "Conversor", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Par\303\240metres", nullptr));
        transformOption->setText(QCoreApplication::translate("MainWindow", "Transformar a:", nullptr));
        transformType->setItemText(0, QCoreApplication::translate("MainWindow", "mpv", nullptr));
        transformType->setItemText(1, QCoreApplication::translate("MainWindow", "mp4", nullptr));
        transformType->setItemText(2, QCoreApplication::translate("MainWindow", "avi", nullptr));
        transformType->setItemText(3, QCoreApplication::translate("MainWindow", "mp3", nullptr));

        reduceOption->setText(QCoreApplication::translate("MainWindow", "Redu\303\257r l'escala a la meitat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(parametres), QCoreApplication::translate("MainWindow", "Par\303\240metres", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
