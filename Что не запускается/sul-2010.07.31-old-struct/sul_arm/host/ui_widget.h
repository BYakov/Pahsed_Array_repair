/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Sat 24. Jul 18:21:50 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *mainLayout;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spbNsamples;
    QLabel *label_3;
    QSpinBox *spbFrequency;
    QPushButton *btnSetParam;
    QPushButton *btnStartAdc;
    QPushButton *btnResultAdc;
    QPushButton *btnStart;
    QSpinBox *periodVal;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLabel *l_mean;
    QLabel *label_6;
    QLabel *l_rms;
    QPushButton *btnBufferAdc;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(412, 211);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        verticalLayoutWidget_2 = new QWidget(Widget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(5, 180, 401, 25));
        mainLayout = new QVBoxLayout(verticalLayoutWidget_2);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(5, 5, 5, 5);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 5, 244, 170));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 225, 140));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(5);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spbNsamples = new QSpinBox(gridLayoutWidget);
        spbNsamples->setObjectName(QString::fromUtf8("spbNsamples"));
        spbNsamples->setMinimum(1);
        spbNsamples->setMaximum(8194);
        spbNsamples->setValue(1024);

        gridLayout->addWidget(spbNsamples, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        spbFrequency = new QSpinBox(gridLayoutWidget);
        spbFrequency->setObjectName(QString::fromUtf8("spbFrequency"));
        spbFrequency->setMinimum(0);
        spbFrequency->setMaximum(1000000000);
        spbFrequency->setValue(10000);

        gridLayout->addWidget(spbFrequency, 1, 1, 1, 1);

        btnSetParam = new QPushButton(gridLayoutWidget);
        btnSetParam->setObjectName(QString::fromUtf8("btnSetParam"));

        gridLayout->addWidget(btnSetParam, 3, 0, 1, 1);

        btnStartAdc = new QPushButton(gridLayoutWidget);
        btnStartAdc->setObjectName(QString::fromUtf8("btnStartAdc"));

        gridLayout->addWidget(btnStartAdc, 4, 0, 1, 1);

        btnResultAdc = new QPushButton(gridLayoutWidget);
        btnResultAdc->setObjectName(QString::fromUtf8("btnResultAdc"));

        gridLayout->addWidget(btnResultAdc, 5, 0, 1, 1);

        btnStart = new QPushButton(gridLayoutWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout->addWidget(btnStart, 5, 1, 1, 1);

        periodVal = new QSpinBox(gridLayoutWidget);
        periodVal->setObjectName(QString::fromUtf8("periodVal"));
        periodVal->setMaximum(5000);
        periodVal->setSingleStep(10);

        gridLayout->addWidget(periodVal, 4, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 3, 1, 1, 1);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(255, 5, 151, 170));
        gridLayoutWidget_2 = new QWidget(groupBox_2);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 20, 130, 140));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        l_mean = new QLabel(gridLayoutWidget_2);
        l_mean->setObjectName(QString::fromUtf8("l_mean"));
        l_mean->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(l_mean, 1, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        l_rms = new QLabel(gridLayoutWidget_2);
        l_rms->setObjectName(QString::fromUtf8("l_rms"));
        l_rms->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(l_rms, 3, 0, 1, 1);

        btnBufferAdc = new QPushButton(gridLayoutWidget_2);
        btnBufferAdc->setObjectName(QString::fromUtf8("btnBufferAdc"));

        gridLayout_2->addWidget(btnBufferAdc, 4, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Widget", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\220\320\246\320\237", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "\320\247\320\270\321\201\320\273\320\276 \320\262\321\213\320\261\320\276\321\200\320\276\320\272", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\262\321\213\320\261\320\276\321\200\320\276\320\272", 0, QApplication::UnicodeUTF8));
        btnSetParam->setText(QApplication::translate("Widget", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnStartAdc->setText(QApplication::translate("Widget", "\320\241\321\202\320\260\321\200\321\202 \320\220\320\246\320\237", 0, QApplication::UnicodeUTF8));
        btnResultAdc->setText(QApplication::translate("Widget", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 \320\220\320\246\320\237", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("Widget", "\320\241\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "\320\237\320\265\321\200\320\270\320\276\320\264 \320\267\320\260\320\277\321\200\320\276\321\201\320\260", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Widget", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\220\320\246\320\237", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "\320\241\321\200\320\265\320\264\320\275\320\265\320\265", 0, QApplication::UnicodeUTF8));
        l_mean->setText(QApplication::translate("Widget", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Widget", "\320\241\320\232\320\236", 0, QApplication::UnicodeUTF8));
        l_rms->setText(QApplication::translate("Widget", "0", 0, QApplication::UnicodeUTF8));
        btnBufferAdc->setText(QApplication::translate("Widget", "\320\221\321\203\321\204\320\265\321\200 \320\220\320\246\320\237", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
