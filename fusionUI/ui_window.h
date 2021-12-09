/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H
#pragma execution_character_set("utf-8")

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

QT_BEGIN_NAMESPACE

class Ui_windowClass
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QPushButton* Button1;
    QPushButton* Button2;
    //QPushButton* Button3;
    QPushButton* Button4;
    QPushButton* Button5;
    QLabel* label_img1;
    QLabel* label_img2;
    QLabel* label_imgf;
    QComboBox* comboBox;

    void setupUi(QMainWindow *windowClass)
    {
        if (windowClass->objectName().isEmpty())
            windowClass->setObjectName(QString::fromUtf8("windowClass"));
        windowClass->resize(1000,800);

        centralWidget = new QWidget(windowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

        Button1 = new QPushButton("读取图像1",centralWidget);
        Button1->setObjectName(QString::fromUtf8("Button1"));
        Button1->setGeometry(QRect(100, 700, 100,30));

        Button2 = new QPushButton("读取图像2", centralWidget);
        Button2->setObjectName(QString::fromUtf8("Button2"));
        Button2->setGeometry(QRect(250, 700, 100, 30));

        //Button3 = new QPushButton("载入模型", centralWidget);
        //Button3->setObjectName(QString::fromUtf8("Button3"));
        //Button3->setGeometry(QRect(400, 700, 100, 30));

        Button4 = new QPushButton("融合！", centralWidget);
        Button4->setObjectName(QString::fromUtf8("Button4"));
        Button4->setGeometry(QRect(550, 700, 100, 30));

        Button5 = new QPushButton("保存为", centralWidget);
        Button5->setObjectName(QString::fromUtf8("Button5"));
        Button5->setGeometry(QRect(700, 700, 100, 30));

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(700, 50, 100, 30));
        comboBox->addItem("CT-MR");
        comboBox->addItem("MR-MR");
        comboBox->addItem("MR-SPECT");

        label_img1 = new QLabel(centralWidget);
        label_img1->setObjectName(QString::fromUtf8("label_img1"));
        label_img1->setGeometry(QRect(100, 100, 300,300));

        label_img2 = new QLabel(centralWidget);
        label_img2->setObjectName(QString::fromUtf8("label_img2"));
        label_img2->setGeometry(QRect(100, 400, 300, 300));

        label_imgf = new QLabel(centralWidget);
        label_imgf->setObjectName(QString::fromUtf8("label_imgf"));
        label_imgf->setGeometry(QRect(400, 250, 300, 300));

        windowClass->setCentralWidget(centralWidget);


        statusBar = new QStatusBar(windowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        windowClass->setStatusBar(statusBar);

        retranslateUi(windowClass);

        QMetaObject::connectSlotsByName(windowClass);
    } // setupUi

    void retranslateUi(QMainWindow *windowClass)
    {
        windowClass->setWindowTitle(QCoreApplication::translate("windowClass", "window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class windowClass: public Ui_windowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
