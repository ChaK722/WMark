/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *imageLabel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *selectButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *modeBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *textBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *colorBox;
    QSpacerItem *verticalSpacer;
    QPushButton *applyButton;
    QPushButton *saveButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(877, 658);
        MainWindow->setMaximumSize(QSize(6000, 4000));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        imageLabel = new QLabel(centralwidget);
        imageLabel->setObjectName("imageLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy);
        imageLabel->setScaledContents(false);

        horizontalLayout_2->addWidget(imageLabel);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        selectButton = new QPushButton(groupBox);
        selectButton->setObjectName("selectButton");

        verticalLayout->addWidget(selectButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        modeBox = new QComboBox(groupBox);
        modeBox->addItem(QString());
        modeBox->addItem(QString());
        modeBox->addItem(QString());
        modeBox->setObjectName("modeBox");

        horizontalLayout->addWidget(modeBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        textBox = new QComboBox(groupBox);
        textBox->addItem(QString());
        textBox->addItem(QString());
        textBox->setObjectName("textBox");

        horizontalLayout_3->addWidget(textBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        colorBox = new QComboBox(groupBox);
        colorBox->addItem(QString());
        colorBox->addItem(QString());
        colorBox->addItem(QString());
        colorBox->addItem(QString());
        colorBox->addItem(QString());
        colorBox->addItem(QString());
        colorBox->addItem(QString());
        colorBox->addItem(QString());
        colorBox->setObjectName("colorBox");
        colorBox->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(colorBox->sizePolicy().hasHeightForWidth());
        colorBox->setSizePolicy(sizePolicy2);
        colorBox->setMinimumSize(QSize(84, 32));
        colorBox->setMaximumSize(QSize(84, 32));

        horizontalLayout_4->addWidget(colorBox);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        applyButton = new QPushButton(groupBox);
        applyButton->setObjectName("applyButton");

        verticalLayout->addWidget(applyButton);

        saveButton = new QPushButton(groupBox);
        saveButton->setObjectName("saveButton");

        verticalLayout->addWidget(saveButton);


        horizontalLayout_2->addWidget(groupBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 877, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        imageLabel->setText(QString());
        groupBox->setTitle(QString());
        selectButton->setText(QCoreApplication::translate("MainWindow", "Select Image", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        modeBox->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        modeBox->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        modeBox->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Text", nullptr));
        textBox->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        textBox->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Text Color", nullptr));
        colorBox->setItemText(0, QCoreApplication::translate("MainWindow", "Black", nullptr));
        colorBox->setItemText(1, QCoreApplication::translate("MainWindow", "White", nullptr));
        colorBox->setItemText(2, QCoreApplication::translate("MainWindow", "Red", nullptr));
        colorBox->setItemText(3, QCoreApplication::translate("MainWindow", "Green", nullptr));
        colorBox->setItemText(4, QCoreApplication::translate("MainWindow", "Blue", nullptr));
        colorBox->setItemText(5, QCoreApplication::translate("MainWindow", "Yellow", nullptr));
        colorBox->setItemText(6, QCoreApplication::translate("MainWindow", "Cyan", nullptr));
        colorBox->setItemText(7, QCoreApplication::translate("MainWindow", "Magenta", nullptr));

        applyButton->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
