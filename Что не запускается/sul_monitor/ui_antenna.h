/********************************************************************************
** Form generated from reading UI file 'antenna.ui'
**
** Created: Sat 24. Jan 14:19:31 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANTENNA_H
#define UI_ANTENNA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_antenna
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_7;
    QComboBox *cbShowParam;
    QLabel *label;
    QCheckBox *cbShowText;
    QSpinBox *elementSize;
    QPushButton *pbDebug;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QLabel *lb_moduleNumber;
    QLabel *lb_factoryNumber;
    QLabel *label_13;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *lb_lineNumber;
    QLabel *lb_connNumber;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *lb_moduleChNumber;
    QLabel *lb_lineChNumber;
    QLabel *label_10;
    QLabel *lb_antennaChNumber;
    QLabel *label_11;
    QLabel *lb_X;
    QLabel *label_12;
    QLabel *lb_Y;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QComboBox *cbSelecetTest;
    QGridLayout *gridLayout_3;
    QCheckBox *cbSingleAbonent;
    QLabel *label_3;
    QSpinBox *spbAbonentIndex;
    QLabel *lbAbonentAddress;
    QLabel *label_4;
    QSpinBox *spbTestParamIndex;
    QPushButton *pbStartTest;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QGridLayout *gridLayout_10;
    QVBoxLayout *antennaLayout;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *antenna)
    {
        if (antenna->objectName().isEmpty())
            antenna->setObjectName(QString::fromUtf8("antenna"));
        antenna->resize(995, 706);
        centralwidget = new QWidget(antenna);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_7 = new QGridLayout(groupBox_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(4);
        gridLayout_7->setVerticalSpacing(6);
        gridLayout_7->setContentsMargins(4, 8, 4, 2);
        cbShowParam = new QComboBox(groupBox_5);
        cbShowParam->setObjectName(QString::fromUtf8("cbShowParam"));

        gridLayout_7->addWidget(cbShowParam, 0, 0, 1, 1);

        label = new QLabel(groupBox_5);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_7->addWidget(label, 2, 0, 1, 1);

        cbShowText = new QCheckBox(groupBox_5);
        cbShowText->setObjectName(QString::fromUtf8("cbShowText"));
        cbShowText->setChecked(false);

        gridLayout_7->addWidget(cbShowText, 1, 0, 1, 1);

        elementSize = new QSpinBox(groupBox_5);
        elementSize->setObjectName(QString::fromUtf8("elementSize"));
        elementSize->setMinimum(1);
        elementSize->setMaximum(100);
        elementSize->setValue(11);

        gridLayout_7->addWidget(elementSize, 3, 0, 1, 1);

        pbDebug = new QPushButton(groupBox_5);
        pbDebug->setObjectName(QString::fromUtf8("pbDebug"));

        gridLayout_7->addWidget(pbDebug, 5, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 6, 0, 1, 1);


        gridLayout->addWidget(groupBox_5, 2, 1, 2, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(4, 10, 4, 4);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lb_moduleNumber = new QLabel(groupBox);
        lb_moduleNumber->setObjectName(QString::fromUtf8("lb_moduleNumber"));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lb_moduleNumber->setFont(font);

        gridLayout_2->addWidget(lb_moduleNumber, 0, 1, 1, 1);

        lb_factoryNumber = new QLabel(groupBox);
        lb_factoryNumber->setObjectName(QString::fromUtf8("lb_factoryNumber"));
        lb_factoryNumber->setFont(font);

        gridLayout_2->addWidget(lb_factoryNumber, 5, 1, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 4, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 5, 0, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        lb_lineNumber = new QLabel(groupBox);
        lb_lineNumber->setObjectName(QString::fromUtf8("lb_lineNumber"));
        lb_lineNumber->setFont(font);

        gridLayout_2->addWidget(lb_lineNumber, 3, 1, 1, 1);

        lb_connNumber = new QLabel(groupBox);
        lb_connNumber->setObjectName(QString::fromUtf8("lb_connNumber"));
        lb_connNumber->setFont(font);

        gridLayout_2->addWidget(lb_connNumber, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        lb_moduleChNumber = new QLabel(groupBox);
        lb_moduleChNumber->setObjectName(QString::fromUtf8("lb_moduleChNumber"));
        lb_moduleChNumber->setFont(font);

        gridLayout_2->addWidget(lb_moduleChNumber, 2, 1, 1, 1);

        lb_lineChNumber = new QLabel(groupBox);
        lb_lineChNumber->setObjectName(QString::fromUtf8("lb_lineChNumber"));
        lb_lineChNumber->setFont(font);

        gridLayout_2->addWidget(lb_lineChNumber, 4, 1, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 6, 0, 1, 1);

        lb_antennaChNumber = new QLabel(groupBox);
        lb_antennaChNumber->setObjectName(QString::fromUtf8("lb_antennaChNumber"));
        lb_antennaChNumber->setFont(font);

        gridLayout_2->addWidget(lb_antennaChNumber, 6, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 7, 0, 1, 1);

        lb_X = new QLabel(groupBox);
        lb_X->setObjectName(QString::fromUtf8("lb_X"));
        lb_X->setFont(font);

        gridLayout_2->addWidget(lb_X, 7, 1, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 8, 0, 1, 1);

        lb_Y = new QLabel(groupBox);
        lb_Y->setObjectName(QString::fromUtf8("lb_Y"));
        lb_Y->setFont(font);

        gridLayout_2->addWidget(lb_Y, 8, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(4, 8, 4, 4);
        cbSelecetTest = new QComboBox(groupBox_3);
        cbSelecetTest->setObjectName(QString::fromUtf8("cbSelecetTest"));

        verticalLayout->addWidget(cbSelecetTest);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        cbSingleAbonent = new QCheckBox(groupBox_3);
        cbSingleAbonent->setObjectName(QString::fromUtf8("cbSingleAbonent"));

        gridLayout_3->addWidget(cbSingleAbonent, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 0, 1, 1, 1);

        spbAbonentIndex = new QSpinBox(groupBox_3);
        spbAbonentIndex->setObjectName(QString::fromUtf8("spbAbonentIndex"));
        spbAbonentIndex->setEnabled(false);

        gridLayout_3->addWidget(spbAbonentIndex, 1, 0, 1, 1);

        lbAbonentAddress = new QLabel(groupBox_3);
        lbAbonentAddress->setObjectName(QString::fromUtf8("lbAbonentAddress"));
        lbAbonentAddress->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbAbonentAddress, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_4, 2, 0, 1, 2);

        spbTestParamIndex = new QSpinBox(groupBox_3);
        spbTestParamIndex->setObjectName(QString::fromUtf8("spbTestParamIndex"));

        gridLayout_3->addWidget(spbTestParamIndex, 3, 0, 1, 2);


        verticalLayout->addLayout(gridLayout_3);

        pbStartTest = new QPushButton(groupBox_3);
        pbStartTest->setObjectName(QString::fromUtf8("pbStartTest"));

        verticalLayout->addWidget(pbStartTest);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(groupBox_3, 1, 1, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 0));
        gridLayout_10 = new QGridLayout(widget);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        antennaLayout = new QVBoxLayout();
        antennaLayout->setSpacing(1);
        antennaLayout->setObjectName(QString::fromUtf8("antennaLayout"));

        gridLayout_10->addLayout(antennaLayout, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 3, 1);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 3, 0, 1, 1);

        antenna->setCentralWidget(centralwidget);
        menubar = new QMenuBar(antenna);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 995, 21));
        antenna->setMenuBar(menubar);
        statusbar = new QStatusBar(antenna);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        antenna->setStatusBar(statusbar);

        retranslateUi(antenna);

        QMetaObject::connectSlotsByName(antenna);
    } // setupUi

    void retranslateUi(QMainWindow *antenna)
    {
        antenna->setWindowTitle(QApplication::translate("antenna", "MainWindow", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("antenna", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        cbShowParam->clear();
        cbShowParam->insertItems(0, QStringList()
         << QApplication::translate("antenna", "\320\232\320\260\320\275\320\260\320\273\321\213 \320\262 \320\274\320\276\320\264\321\203\320\273\320\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("antenna", "\320\232\320\260\320\275\320\260\320\273\321\213 \320\275\320\260 \320\273\320\270\320\275\320\265\320\271\320\272\320\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("antenna", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\260\321\217 \321\204\320\260\320\267\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("antenna", "\320\232\321\200\321\203\321\202\320\270\320\267\320\275\320\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("antenna", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 X", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("antenna", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 Y", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("antenna", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\260 \320\264\320\270\320\260\320\263\321\200\320\260\320\274\320\274\321\213", 0, QApplication::UnicodeUTF8));
        cbShowText->setText(QApplication::translate("antenna", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        pbDebug->setText(QApplication::translate("antenna", "\320\236\321\202\320\273\320\260\320\264\320\272\320\260", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("antenna", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\272\320\260\320\275\320\260\320\273\320\260", 0, QApplication::UnicodeUTF8));
        lb_moduleNumber->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        lb_factoryNumber->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("antenna", "\320\232\320\260\320\275\320\260\320\273 \320\275\320\260 \320\273\320\270\320\275\320\265\320\271\320\272\320\265:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("antenna", "\320\233\320\270\320\275\320\265\320\271\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("antenna", "\320\227\320\260\320\262\320\276\320\264\321\201\320\272\320\276\320\271 \320\275\320\276\320\274\320\265\321\200:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("antenna", "\320\232\320\260\320\275\320\260\320\273 \320\274\320\276\320\264\321\203\320\273\321\217:", 0, QApplication::UnicodeUTF8));
        lb_lineNumber->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        lb_connNumber->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("antenna", "\320\241\320\276\320\265\320\264\320\270\320\275\320\270\321\202\320\265\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("antenna", "\320\234\320\276\320\264\321\203\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        lb_moduleChNumber->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        lb_lineChNumber->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("antenna", "\320\232\320\260\320\275\320\260\320\273 \320\260\320\275\321\202\320\265\320\275\320\275\321\213:", 0, QApplication::UnicodeUTF8));
        lb_antennaChNumber->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("antenna", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 X:", 0, QApplication::UnicodeUTF8));
        lb_X->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("antenna", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 Y:", 0, QApplication::UnicodeUTF8));
        lb_Y->setText(QApplication::translate("antenna", "0", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("antenna", "\320\222\320\270\320\264 \320\277\321\200\320\276\320\262\320\265\321\200\320\272\320\270", 0, QApplication::UnicodeUTF8));
        cbSingleAbonent->setText(QApplication::translate("antenna", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("antenna", "\320\220\320\264\321\200\320\265\321\201", 0, QApplication::UnicodeUTF8));
        lbAbonentAddress->setText(QApplication::translate("antenna", "0x0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("antenna", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200 \321\202\320\265\321\201\321\202\320\260", 0, QApplication::UnicodeUTF8));
        pbStartTest->setText(QApplication::translate("antenna", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class antenna: public Ui_antenna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANTENNA_H
