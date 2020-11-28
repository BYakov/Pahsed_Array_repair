/********************************************************************************
** Form generated from reading UI file 'sul_monitor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUL_MONITOR_H
#define UI_SUL_MONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sul_monitorClass
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QToolBox *toolBox;
    QWidget *page;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_5;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rbtAxisX;
    QRadioButton *rbtAxisY;
    QRadioButton *rbtAxisXY;
    QGroupBox *groupBox_6;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *scanAngle;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QDoubleSpinBox *value_x0;
    QLabel *label;
    QDoubleSpinBox *value_y0;
    QLabel *label_2;
    QSpinBox *period;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *scanSectorMax;
    QDoubleSpinBox *scanSector;
    QLabel *label_5;
    QDoubleSpinBox *step_dr;
    QLabel *label_6;
    QPushButton *btnStart;
    QPushButton *btnStep;
    QPushButton *btnReset;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLabel *currentX;
    QLabel *label_9;
    QLabel *label_10;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *currentY;
    QLabel *label_13;
    QLabel *label_14;
    QWidget *verticalLayoutWidget_11;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_19;
    QProgressBar *progressBar;
    QGroupBox *groupBox_9;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *page_3;
    QToolBox *fabonents;
    QWidget *page_2;
    QTableView *ftable1;
    QWidget *page_6;
    QTableView *ftable2;
    QWidget *page_7;
    QTableView *ftable3;
    QWidget *page_8;
    QTableView *ftable4;
    QWidget *page_9;
    QTableView *ftable5;
    QGroupBox *groupBox_7;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnFlashFileOpen;
    QPushButton *btnFlashErase;
    QPushButton *btnFlashLoad;
    QPushButton *btnFlashCheck;
    QGroupBox *groupBox_10;
    QWidget *verticalLayoutWidget_13;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_27;
    QLabel *lblFileCRC;
    QLabel *label_25;
    QLabel *lblHwCRC;
    QWidget *verticalLayoutWidget_14;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_22;
    QSpinBox *spbSegmentNumber;
    QWidget *page_4;
    QGroupBox *groupBox_8;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnRamOpen;
    QPushButton *btnRamErase;
    QPushButton *btnRamLoad;
    QPushButton *btnRamSave;
    QToolBox *rabonents;
    QWidget *page_10;
    QTableView *rtable1;
    QWidget *page_11;
    QTableView *rtable2;
    QWidget *page_12;
    QTableView *rtable3;
    QWidget *page_13;
    QTableView *rtable4;
    QWidget *page_14;
    QTableView *rtable5;
    QGroupBox *groupBox_15;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *verticalLayout_7;
    QRadioButton *rbtFillRamRandom;
    QRadioButton *rbtFillRamPattern;
    QSpinBox *lePatternValue;
    QPushButton *btnFillRam;
    QGroupBox *groupBox_16;
    QWidget *verticalLayoutWidget_8;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_16;
    QSpinBox *spbRamStepValue;
    QPushButton *btnIncRamValue;
    QPushButton *btnDecRamValue;
    QWidget *page_5;
    QGroupBox *groupBox_13;
    QTableView *tblDataOut;
    QGroupBox *groupBox_12;
    QTableView *tblHdrOut;
    QGroupBox *groupBox_14;
    QTableView *tblDataIn;
    QGroupBox *groupBox_17;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_8;
    QSpinBox *abonentIndex;
    QLabel *label_12;
    QComboBox *abonentCmd;
    QLabel *label_17;
    QSpinBox *msgBlockNum;
    QLabel *label_18;
    QSpinBox *msgBlockSize;
    QLabel *label_20;
    QSpinBox *dbgPeriod;
    QPushButton *btnSend;
    QPushButton *btnShowView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *barLayout;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbtCOM1;
    QRadioButton *rbtCOM2;
    QRadioButton *rbtRS4851;
    QRadioButton *rbtRS4852;
    QPushButton *btnDraw;
    QGroupBox *groupBox_11;

    void setupUi(QWidget *sul_monitorClass)
    {
        if (sul_monitorClass->objectName().isEmpty())
            sul_monitorClass->setObjectName(QString::fromUtf8("sul_monitorClass"));
        sul_monitorClass->setWindowModality(Qt::WindowModal);
        sul_monitorClass->resize(751, 590);
        verticalLayoutWidget = new QWidget(sul_monitorClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(5, 0, 740, 455));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        toolBox = new QToolBox(verticalLayoutWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 738, 345));
        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(5, 135, 381, 75));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(15, 20, 170, 45));
        horizontalLayoutWidget_2 = new QWidget(groupBox_5);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 155, 20));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        rbtAxisX = new QRadioButton(horizontalLayoutWidget_2);
        rbtAxisX->setObjectName(QString::fromUtf8("rbtAxisX"));
        rbtAxisX->setChecked(true);

        horizontalLayout_2->addWidget(rbtAxisX);

        rbtAxisY = new QRadioButton(horizontalLayoutWidget_2);
        rbtAxisY->setObjectName(QString::fromUtf8("rbtAxisY"));

        horizontalLayout_2->addWidget(rbtAxisY);

        rbtAxisXY = new QRadioButton(horizontalLayoutWidget_2);
        rbtAxisXY->setObjectName(QString::fromUtf8("rbtAxisXY"));

        horizontalLayout_2->addWidget(rbtAxisXY);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(190, 20, 175, 45));
        horizontalLayoutWidget_3 = new QWidget(groupBox_6);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(44, 18, 85, 22));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        scanAngle = new QDoubleSpinBox(horizontalLayoutWidget_3);
        scanAngle->setObjectName(QString::fromUtf8("scanAngle"));
        scanAngle->setDecimals(3);
        scanAngle->setMinimum(-90.000000000000000);
        scanAngle->setMaximum(90.000000000000000);

        horizontalLayout_3->addWidget(scanAngle);

        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(5, 0, 381, 130));
        gridLayoutWidget = new QWidget(groupBox_3);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(15, 15, 355, 110));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        value_x0 = new QDoubleSpinBox(gridLayoutWidget);
        value_x0->setObjectName(QString::fromUtf8("value_x0"));
        value_x0->setDecimals(3);
        value_x0->setMaximum(90.000000000000000);

        gridLayout->addWidget(value_x0, 1, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        value_y0 = new QDoubleSpinBox(gridLayoutWidget);
        value_y0->setObjectName(QString::fromUtf8("value_y0"));
        value_y0->setDecimals(3);
        value_y0->setMaximum(90.000000000000000);

        gridLayout->addWidget(value_y0, 1, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        period = new QSpinBox(gridLayoutWidget);
        period->setObjectName(QString::fromUtf8("period"));
        period->setMaximum(5000);
        period->setSingleStep(10);
        period->setValue(50);

        gridLayout->addWidget(period, 1, 3, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 2, 1, 1, 1);

        scanSectorMax = new QDoubleSpinBox(gridLayoutWidget);
        scanSectorMax->setObjectName(QString::fromUtf8("scanSectorMax"));
        scanSectorMax->setDecimals(3);
        scanSectorMax->setMaximum(90.000000000000000);
        scanSectorMax->setValue(45.000000000000000);

        gridLayout->addWidget(scanSectorMax, 3, 1, 1, 1);

        scanSector = new QDoubleSpinBox(gridLayoutWidget);
        scanSector->setObjectName(QString::fromUtf8("scanSector"));
        scanSector->setDecimals(3);
        scanSector->setMaximum(90.000000000000000);
        scanSector->setSingleStep(1.000000000000000);
        scanSector->setValue(20.000000000000000);

        gridLayout->addWidget(scanSector, 3, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 2, 2, 1, 1);

        step_dr = new QDoubleSpinBox(gridLayoutWidget);
        step_dr->setObjectName(QString::fromUtf8("step_dr"));
        step_dr->setDecimals(3);
        step_dr->setMinimum(0.001000000000000);
        step_dr->setMaximum(10.000000000000000);
        step_dr->setSingleStep(1.000000000000000);
        step_dr->setValue(0.500000000000000);

        gridLayout->addWidget(step_dr, 3, 3, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 2, 3, 1, 1);

        btnStart = new QPushButton(gridLayoutWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout->addWidget(btnStart, 1, 4, 1, 1);

        btnStep = new QPushButton(gridLayoutWidget);
        btnStep->setObjectName(QString::fromUtf8("btnStep"));

        gridLayout->addWidget(btnStep, 2, 4, 1, 1);

        btnReset = new QPushButton(gridLayoutWidget);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        gridLayout->addWidget(btnReset, 3, 4, 1, 1);

        groupBox_4 = new QGroupBox(page);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(5, 210, 381, 135));
        horizontalLayoutWidget_4 = new QWidget(groupBox_4);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 30, 350, 20));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(horizontalLayoutWidget_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);

        currentX = new QLabel(horizontalLayoutWidget_4);
        currentX->setObjectName(QString::fromUtf8("currentX"));
        currentX->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(currentX);

        label_9 = new QLabel(horizontalLayoutWidget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        label_10 = new QLabel(horizontalLayoutWidget_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_10);

        horizontalLayoutWidget_5 = new QWidget(groupBox_4);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 64, 350, 20));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(horizontalLayoutWidget_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_4->addWidget(label_11);

        currentY = new QLabel(horizontalLayoutWidget_5);
        currentY->setObjectName(QString::fromUtf8("currentY"));
        currentY->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(currentY);

        label_13 = new QLabel(horizontalLayoutWidget_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_4->addWidget(label_13);

        label_14 = new QLabel(horizontalLayoutWidget_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_14);

        verticalLayoutWidget_11 = new QWidget(groupBox_4);
        verticalLayoutWidget_11->setObjectName(QString::fromUtf8("verticalLayoutWidget_11"));
        verticalLayoutWidget_11->setGeometry(QRect(10, 89, 360, 38));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget_11);
        verticalLayout_11->setSpacing(2);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(verticalLayoutWidget_11);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        verticalLayout_11->addWidget(label_19);

        progressBar = new QProgressBar(verticalLayoutWidget_11);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout_11->addWidget(progressBar);

        groupBox_9 = new QGroupBox(page);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(390, 0, 341, 345));
        tabWidget = new QTabWidget(groupBox_9);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 25, 326, 311));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        toolBox->addItem(page, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\273\321\203\321\207\320\276\320\274"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 738, 345));
        fabonents = new QToolBox(page_3);
        fabonents->setObjectName(QString::fromUtf8("fabonents"));
        fabonents->setGeometry(QRect(115, 0, 620, 345));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 620, 210));
        ftable1 = new QTableView(page_2);
        ftable1->setObjectName(QString::fromUtf8("ftable1"));
        ftable1->setGeometry(QRect(0, 0, 620, 210));
        fabonents->addItem(page_2, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 1"));
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        page_6->setGeometry(QRect(0, 0, 96, 26));
        ftable2 = new QTableView(page_6);
        ftable2->setObjectName(QString::fromUtf8("ftable2"));
        ftable2->setGeometry(QRect(0, 0, 620, 210));
        fabonents->addItem(page_6, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 2"));
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        page_7->setGeometry(QRect(0, 0, 96, 26));
        ftable3 = new QTableView(page_7);
        ftable3->setObjectName(QString::fromUtf8("ftable3"));
        ftable3->setGeometry(QRect(0, 0, 620, 210));
        fabonents->addItem(page_7, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 3"));
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        page_8->setGeometry(QRect(0, 0, 96, 26));
        ftable4 = new QTableView(page_8);
        ftable4->setObjectName(QString::fromUtf8("ftable4"));
        ftable4->setGeometry(QRect(0, 0, 620, 210));
        fabonents->addItem(page_8, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 4"));
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        page_9->setGeometry(QRect(0, 0, 96, 26));
        ftable5 = new QTableView(page_9);
        ftable5->setObjectName(QString::fromUtf8("ftable5"));
        ftable5->setGeometry(QRect(0, 0, 620, 210));
        fabonents->addItem(page_9, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 5"));
        groupBox_7 = new QGroupBox(page_3);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(5, 0, 105, 120));
        verticalLayoutWidget_3 = new QWidget(groupBox_7);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 15, 85, 97));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnFlashFileOpen = new QPushButton(verticalLayoutWidget_3);
        btnFlashFileOpen->setObjectName(QString::fromUtf8("btnFlashFileOpen"));

        verticalLayout_3->addWidget(btnFlashFileOpen);

        btnFlashErase = new QPushButton(verticalLayoutWidget_3);
        btnFlashErase->setObjectName(QString::fromUtf8("btnFlashErase"));

        verticalLayout_3->addWidget(btnFlashErase);

        btnFlashLoad = new QPushButton(verticalLayoutWidget_3);
        btnFlashLoad->setObjectName(QString::fromUtf8("btnFlashLoad"));

        verticalLayout_3->addWidget(btnFlashLoad);

        btnFlashCheck = new QPushButton(verticalLayoutWidget_3);
        btnFlashCheck->setObjectName(QString::fromUtf8("btnFlashCheck"));

        verticalLayout_3->addWidget(btnFlashCheck);

        groupBox_10 = new QGroupBox(page_3);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(5, 120, 105, 140));
        verticalLayoutWidget_13 = new QWidget(groupBox_10);
        verticalLayoutWidget_13->setObjectName(QString::fromUtf8("verticalLayoutWidget_13"));
        verticalLayoutWidget_13->setGeometry(QRect(10, 15, 85, 80));
        verticalLayout_13 = new QVBoxLayout(verticalLayoutWidget_13);
        verticalLayout_13->setSpacing(1);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_27 = new QLabel(verticalLayoutWidget_13);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setWordWrap(true);

        verticalLayout_13->addWidget(label_27);

        lblFileCRC = new QLabel(verticalLayoutWidget_13);
        lblFileCRC->setObjectName(QString::fromUtf8("lblFileCRC"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        lblFileCRC->setFont(font);

        verticalLayout_13->addWidget(lblFileCRC);

        label_25 = new QLabel(verticalLayoutWidget_13);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setWordWrap(true);

        verticalLayout_13->addWidget(label_25);

        lblHwCRC = new QLabel(verticalLayoutWidget_13);
        lblHwCRC->setObjectName(QString::fromUtf8("lblHwCRC"));
        lblHwCRC->setFont(font);

        verticalLayout_13->addWidget(lblHwCRC);

        verticalLayoutWidget_14 = new QWidget(groupBox_10);
        verticalLayoutWidget_14->setObjectName(QString::fromUtf8("verticalLayoutWidget_14"));
        verticalLayoutWidget_14->setGeometry(QRect(10, 95, 85, 40));
        verticalLayout_14 = new QVBoxLayout(verticalLayoutWidget_14);
        verticalLayout_14->setSpacing(1);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(verticalLayoutWidget_14);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        verticalLayout_14->addWidget(label_22);

        spbSegmentNumber = new QSpinBox(verticalLayoutWidget_14);
        spbSegmentNumber->setObjectName(QString::fromUtf8("spbSegmentNumber"));
        spbSegmentNumber->setMaximum(11);

        verticalLayout_14->addWidget(spbSegmentNumber);

        toolBox->addItem(page_3, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 flash"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 738, 345));
        groupBox_8 = new QGroupBox(page_4);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(5, 0, 105, 125));
        verticalLayoutWidget_4 = new QWidget(groupBox_8);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(15, 15, 77, 105));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        btnRamOpen = new QPushButton(verticalLayoutWidget_4);
        btnRamOpen->setObjectName(QString::fromUtf8("btnRamOpen"));

        verticalLayout_4->addWidget(btnRamOpen);

        btnRamErase = new QPushButton(verticalLayoutWidget_4);
        btnRamErase->setObjectName(QString::fromUtf8("btnRamErase"));

        verticalLayout_4->addWidget(btnRamErase);

        btnRamLoad = new QPushButton(verticalLayoutWidget_4);
        btnRamLoad->setObjectName(QString::fromUtf8("btnRamLoad"));

        verticalLayout_4->addWidget(btnRamLoad);

        btnRamSave = new QPushButton(verticalLayoutWidget_4);
        btnRamSave->setObjectName(QString::fromUtf8("btnRamSave"));

        verticalLayout_4->addWidget(btnRamSave);

        rabonents = new QToolBox(page_4);
        rabonents->setObjectName(QString::fromUtf8("rabonents"));
        rabonents->setGeometry(QRect(115, 0, 620, 345));
        page_10 = new QWidget();
        page_10->setObjectName(QString::fromUtf8("page_10"));
        page_10->setGeometry(QRect(0, 0, 620, 210));
        rtable1 = new QTableView(page_10);
        rtable1->setObjectName(QString::fromUtf8("rtable1"));
        rtable1->setGeometry(QRect(0, 0, 620, 210));
        rabonents->addItem(page_10, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 1"));
        page_11 = new QWidget();
        page_11->setObjectName(QString::fromUtf8("page_11"));
        page_11->setGeometry(QRect(0, 0, 96, 26));
        rtable2 = new QTableView(page_11);
        rtable2->setObjectName(QString::fromUtf8("rtable2"));
        rtable2->setGeometry(QRect(0, 0, 620, 210));
        rabonents->addItem(page_11, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 2"));
        page_12 = new QWidget();
        page_12->setObjectName(QString::fromUtf8("page_12"));
        page_12->setGeometry(QRect(0, 0, 96, 26));
        rtable3 = new QTableView(page_12);
        rtable3->setObjectName(QString::fromUtf8("rtable3"));
        rtable3->setGeometry(QRect(0, 0, 620, 210));
        rabonents->addItem(page_12, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 3"));
        page_13 = new QWidget();
        page_13->setObjectName(QString::fromUtf8("page_13"));
        page_13->setGeometry(QRect(0, 0, 96, 26));
        rtable4 = new QTableView(page_13);
        rtable4->setObjectName(QString::fromUtf8("rtable4"));
        rtable4->setGeometry(QRect(0, 0, 620, 210));
        rabonents->addItem(page_13, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 4"));
        page_14 = new QWidget();
        page_14->setObjectName(QString::fromUtf8("page_14"));
        page_14->setGeometry(QRect(0, 0, 96, 26));
        rtable5 = new QTableView(page_14);
        rtable5->setObjectName(QString::fromUtf8("rtable5"));
        rtable5->setGeometry(QRect(0, 0, 620, 210));
        rabonents->addItem(page_14, QString::fromUtf8(" \320\220\320\261\320\276\320\275\320\265\320\275\321\202 5"));
        groupBox_15 = new QGroupBox(page_4);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        groupBox_15->setGeometry(QRect(5, 130, 106, 110));
        verticalLayoutWidget_7 = new QWidget(groupBox_15);
        verticalLayoutWidget_7->setObjectName(QString::fromUtf8("verticalLayoutWidget_7"));
        verticalLayoutWidget_7->setGeometry(QRect(15, 15, 80, 90));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_7);
        verticalLayout_7->setSpacing(2);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        rbtFillRamRandom = new QRadioButton(verticalLayoutWidget_7);
        rbtFillRamRandom->setObjectName(QString::fromUtf8("rbtFillRamRandom"));
        rbtFillRamRandom->setChecked(true);

        verticalLayout_7->addWidget(rbtFillRamRandom);

        rbtFillRamPattern = new QRadioButton(verticalLayoutWidget_7);
        rbtFillRamPattern->setObjectName(QString::fromUtf8("rbtFillRamPattern"));

        verticalLayout_7->addWidget(rbtFillRamPattern);

        lePatternValue = new QSpinBox(verticalLayoutWidget_7);
        lePatternValue->setObjectName(QString::fromUtf8("lePatternValue"));
        lePatternValue->setMaximum(31);

        verticalLayout_7->addWidget(lePatternValue);

        btnFillRam = new QPushButton(verticalLayoutWidget_7);
        btnFillRam->setObjectName(QString::fromUtf8("btnFillRam"));

        verticalLayout_7->addWidget(btnFillRam);

        groupBox_16 = new QGroupBox(page_4);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        groupBox_16->setGeometry(QRect(5, 240, 105, 100));
        verticalLayoutWidget_8 = new QWidget(groupBox_16);
        verticalLayoutWidget_8->setObjectName(QString::fromUtf8("verticalLayoutWidget_8"));
        verticalLayoutWidget_8->setGeometry(QRect(15, 18, 77, 76));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_8);
        verticalLayout_8->setSpacing(3);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_16 = new QLabel(verticalLayoutWidget_8);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_5->addWidget(label_16);

        spbRamStepValue = new QSpinBox(verticalLayoutWidget_8);
        spbRamStepValue->setObjectName(QString::fromUtf8("spbRamStepValue"));
        spbRamStepValue->setMinimum(1);
        spbRamStepValue->setMaximum(31);

        horizontalLayout_5->addWidget(spbRamStepValue);


        verticalLayout_8->addLayout(horizontalLayout_5);

        btnIncRamValue = new QPushButton(verticalLayoutWidget_8);
        btnIncRamValue->setObjectName(QString::fromUtf8("btnIncRamValue"));

        verticalLayout_8->addWidget(btnIncRamValue);

        btnDecRamValue = new QPushButton(verticalLayoutWidget_8);
        btnDecRamValue->setObjectName(QString::fromUtf8("btnDecRamValue"));

        verticalLayout_8->addWidget(btnDecRamValue);

        toolBox->addItem(page_4, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 ram"));
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setGeometry(QRect(0, 0, 738, 345));
        groupBox_13 = new QGroupBox(page_5);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        groupBox_13->setGeometry(QRect(415, 0, 150, 340));
        tblDataOut = new QTableView(groupBox_13);
        tblDataOut->setObjectName(QString::fromUtf8("tblDataOut"));
        tblDataOut->setEnabled(true);
        tblDataOut->setGeometry(QRect(15, 15, 120, 320));
        groupBox_12 = new QGroupBox(page_5);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setGeometry(QRect(250, 0, 150, 340));
        tblHdrOut = new QTableView(groupBox_12);
        tblHdrOut->setObjectName(QString::fromUtf8("tblHdrOut"));
        tblHdrOut->setEnabled(true);
        tblHdrOut->setGeometry(QRect(15, 15, 120, 320));
        groupBox_14 = new QGroupBox(page_5);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        groupBox_14->setGeometry(QRect(580, 0, 150, 340));
        tblDataIn = new QTableView(groupBox_14);
        tblDataIn->setObjectName(QString::fromUtf8("tblDataIn"));
        tblDataIn->setEnabled(true);
        tblDataIn->setGeometry(QRect(15, 15, 120, 320));
        groupBox_17 = new QGroupBox(page_5);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        groupBox_17->setGeometry(QRect(5, 0, 231, 340));
        verticalLayoutWidget_6 = new QWidget(groupBox_17);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(40, 30, 150, 290));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(verticalLayoutWidget_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_6->addWidget(label_8);

        abonentIndex = new QSpinBox(verticalLayoutWidget_6);
        abonentIndex->setObjectName(QString::fromUtf8("abonentIndex"));
        abonentIndex->setMinimum(1);
        abonentIndex->setMaximum(5);

        verticalLayout_6->addWidget(abonentIndex);

        label_12 = new QLabel(verticalLayoutWidget_6);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_6->addWidget(label_12);

        abonentCmd = new QComboBox(verticalLayoutWidget_6);
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->addItem(QString());
        abonentCmd->setObjectName(QString::fromUtf8("abonentCmd"));

        verticalLayout_6->addWidget(abonentCmd);

        label_17 = new QLabel(verticalLayoutWidget_6);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        verticalLayout_6->addWidget(label_17);

        msgBlockNum = new QSpinBox(verticalLayoutWidget_6);
        msgBlockNum->setObjectName(QString::fromUtf8("msgBlockNum"));
        msgBlockNum->setMinimum(0);
        msgBlockNum->setMaximum(16);
        msgBlockNum->setValue(0);

        verticalLayout_6->addWidget(msgBlockNum);

        label_18 = new QLabel(verticalLayoutWidget_6);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        verticalLayout_6->addWidget(label_18);

        msgBlockSize = new QSpinBox(verticalLayoutWidget_6);
        msgBlockSize->setObjectName(QString::fromUtf8("msgBlockSize"));
        msgBlockSize->setMinimum(0);
        msgBlockSize->setMaximum(128);
        msgBlockSize->setValue(128);

        verticalLayout_6->addWidget(msgBlockSize);

        label_20 = new QLabel(verticalLayoutWidget_6);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        verticalLayout_6->addWidget(label_20);

        dbgPeriod = new QSpinBox(verticalLayoutWidget_6);
        dbgPeriod->setObjectName(QString::fromUtf8("dbgPeriod"));
        dbgPeriod->setMaximum(5000);
        dbgPeriod->setSingleStep(10);
        dbgPeriod->setValue(0);

        verticalLayout_6->addWidget(dbgPeriod);

        btnSend = new QPushButton(verticalLayoutWidget_6);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setCheckable(true);

        verticalLayout_6->addWidget(btnSend);

        btnShowView = new QPushButton(verticalLayoutWidget_6);
        btnShowView->setObjectName(QString::fromUtf8("btnShowView"));
        btnShowView->setCheckable(true);

        verticalLayout_6->addWidget(btnShowView);

        toolBox->addItem(page_5, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260\320\274\320\270"));

        verticalLayout->addWidget(toolBox);

        horizontalLayoutWidget = new QWidget(sul_monitorClass);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 567, 750, 21));
        barLayout = new QHBoxLayout(horizontalLayoutWidget);
        barLayout->setSpacing(6);
        barLayout->setContentsMargins(11, 11, 11, 11);
        barLayout->setObjectName(QString::fromUtf8("barLayout"));
        barLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(sul_monitorClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 460, 120, 105));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(5, 15, 110, 92));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        rbtCOM1 = new QRadioButton(verticalLayoutWidget_2);
        rbtCOM1->setObjectName(QString::fromUtf8("rbtCOM1"));

        verticalLayout_2->addWidget(rbtCOM1);

        rbtCOM2 = new QRadioButton(verticalLayoutWidget_2);
        rbtCOM2->setObjectName(QString::fromUtf8("rbtCOM2"));

        verticalLayout_2->addWidget(rbtCOM2);

        rbtRS4851 = new QRadioButton(verticalLayoutWidget_2);
        rbtRS4851->setObjectName(QString::fromUtf8("rbtRS4851"));
        rbtRS4851->setChecked(true);

        verticalLayout_2->addWidget(rbtRS4851);

        rbtRS4852 = new QRadioButton(verticalLayoutWidget_2);
        rbtRS4852->setObjectName(QString::fromUtf8("rbtRS4852"));

        verticalLayout_2->addWidget(rbtRS4852);

        btnDraw = new QPushButton(sul_monitorClass);
        btnDraw->setObjectName(QString::fromUtf8("btnDraw"));
        btnDraw->setGeometry(QRect(670, 540, 75, 23));
        groupBox_11 = new QGroupBox(sul_monitorClass);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(130, 460, 536, 105));

        retranslateUi(sul_monitorClass);

        toolBox->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);
        fabonents->setCurrentIndex(0);
        rabonents->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(sul_monitorClass);
    } // setupUi

    void retranslateUi(QWidget *sul_monitorClass)
    {
        sul_monitorClass->setWindowTitle(QApplication::translate("sul_monitorClass", "sul_monitor", nullptr));
        groupBox_2->setTitle(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        groupBox_5->setTitle(QApplication::translate("sul_monitorClass", "\320\236\321\201\321\214 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        rbtAxisX->setText(QApplication::translate("sul_monitorClass", "X", nullptr));
        rbtAxisY->setText(QApplication::translate("sul_monitorClass", "Y", nullptr));
        rbtAxisXY->setText(QApplication::translate("sul_monitorClass", "XY", nullptr));
        groupBox_6->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\263\320\276\320\273 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217, \302\260", nullptr));
        groupBox_3->setTitle(QApplication::translate("sul_monitorClass", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 X", nullptr));
        label_2->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 Y", nullptr));
        label_3->setText(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\270\320\276\320\264, \320\274\321\201", nullptr));
        label_4->setText(QApplication::translate("sul_monitorClass", "\320\223\321\200\320\260\320\275\320\270\321\206\320\260, \302\260", nullptr));
        label_5->setText(QApplication::translate("sul_monitorClass", "\320\241\320\265\320\272\321\202\320\276\321\200, \302\260", nullptr));
        label_6->setText(QApplication::translate("sul_monitorClass", "\320\250\320\260\320\263", nullptr));
        btnStart->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        btnStep->setText(QApplication::translate("sul_monitorClass", "\320\250\320\260\320\263", nullptr));
        btnReset->setText(QApplication::translate("sul_monitorClass", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        groupBox_4->setTitle(QApplication::translate("sul_monitorClass", "\320\242\320\265\320\272\321\203\321\211\320\270\320\265 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        label_7->setText(QApplication::translate("sul_monitorClass", "X:", nullptr));
        currentX->setText(QApplication::translate("sul_monitorClass", "0", nullptr));
        label_9->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\264", nullptr));
        label_10->setText(QApplication::translate("sul_monitorClass", "0x0", nullptr));
        label_11->setText(QApplication::translate("sul_monitorClass", "Y:", nullptr));
        currentY->setText(QApplication::translate("sul_monitorClass", "0", nullptr));
        label_13->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\264", nullptr));
        label_14->setText(QApplication::translate("sul_monitorClass", "0x0", nullptr));
        label_19->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\202\321\203\321\201 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", nullptr));
        groupBox_9->setTitle(QApplication::translate("sul_monitorClass", "\320\237\320\276\320\264\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\273\321\203\321\207\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("sul_monitorClass", "\320\222\320\260\321\200\320\270\320\260\320\275\321\202 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("sul_monitorClass", "\320\222\320\260\321\200\320\270\320\260\320\275\321\202 2", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\273\321\203\321\207\320\276\320\274", nullptr));
        fabonents->setItemText(fabonents->indexOf(page_2), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 1", nullptr));
        fabonents->setItemText(fabonents->indexOf(page_6), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 2", nullptr));
        fabonents->setItemText(fabonents->indexOf(page_7), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 3", nullptr));
        fabonents->setItemText(fabonents->indexOf(page_8), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 4", nullptr));
        fabonents->setItemText(fabonents->indexOf(page_9), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 5", nullptr));
        groupBox_7->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213", nullptr));
        btnFlashFileOpen->setText(QApplication::translate("sul_monitorClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        btnFlashErase->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\270\321\200\320\260\320\275\320\270\320\265", nullptr));
        btnFlashLoad->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", nullptr));
        btnFlashCheck->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\275\321\202\321\200\320\276\320\273\321\214", nullptr));
        groupBox_10->setTitle(QApplication::translate("sul_monitorClass", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        label_27->setText(QApplication::translate("sul_monitorClass", "CRC \321\204\320\260\320\271\320\273\320\260:", nullptr));
        lblFileCRC->setText(QApplication::translate("sul_monitorClass", "0x0000", nullptr));
        label_25->setText(QApplication::translate("sul_monitorClass", "CRC \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\276\320\262:", nullptr));
        lblHwCRC->setText(QApplication::translate("sul_monitorClass", "0x0000", nullptr));
        label_22->setText(QApplication::translate("sul_monitorClass", "\320\235\320\276\320\274\320\265\321\200 \321\201\320\265\320\263\320\274\320\265\320\275\321\202\320\260 ", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 flash", nullptr));
        groupBox_8->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213", nullptr));
        btnRamOpen->setText(QApplication::translate("sul_monitorClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        btnRamErase->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\270\321\200\320\260\320\275\320\270\320\265", nullptr));
        btnRamLoad->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", nullptr));
        btnRamSave->setText(QApplication::translate("sul_monitorClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        rabonents->setItemText(rabonents->indexOf(page_10), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 1", nullptr));
        rabonents->setItemText(rabonents->indexOf(page_11), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 2", nullptr));
        rabonents->setItemText(rabonents->indexOf(page_12), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 3", nullptr));
        rabonents->setItemText(rabonents->indexOf(page_13), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 4", nullptr));
        rabonents->setItemText(rabonents->indexOf(page_14), QApplication::translate("sul_monitorClass", " \320\220\320\261\320\276\320\275\320\265\320\275\321\202 5", nullptr));
        groupBox_15->setTitle(QApplication::translate("sul_monitorClass", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265", nullptr));
        rbtFillRamRandom->setText(QApplication::translate("sul_monitorClass", "\320\241\320\273\321\203\321\207\320\260\320\271\320\275\320\276\320\265", nullptr));
        rbtFillRamPattern->setText(QApplication::translate("sul_monitorClass", "\320\247\320\270\321\201\320\273\320\276\320\262\320\276\320\265", nullptr));
        btnFillRam->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        groupBox_16->setTitle(QApplication::translate("sul_monitorClass", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260", nullptr));
        label_16->setText(QApplication::translate("sul_monitorClass", "\320\250\320\260\320\263", nullptr));
        btnIncRamValue->setText(QApplication::translate("sul_monitorClass", "\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202", nullptr));
        btnDecRamValue->setText(QApplication::translate("sul_monitorClass", "\320\224\320\265\320\272\321\200\320\265\320\274\320\265\320\275\321\202", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 ram", nullptr));
        groupBox_13->setTitle(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\265\320\264\320\260\321\207\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        groupBox_12->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\320\275\321\213\320\271 \320\261\320\273\320\276\320\272", nullptr));
        groupBox_14->setTitle(QApplication::translate("sul_monitorClass", "\320\237\321\200\320\270\320\265\320\274 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        groupBox_17->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        label_8->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", nullptr));
        label_12->setText(QApplication::translate("sul_monitorClass", "\320\242\320\270\320\277 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", nullptr));
        abonentCmd->setItemText(0, QApplication::translate("sul_monitorClass", "host_eeprom_data", nullptr));
        abonentCmd->setItemText(1, QApplication::translate("sul_monitorClass", "host_ram_data", nullptr));
        abonentCmd->setItemText(2, QApplication::translate("sul_monitorClass", "target_eeprom_to_plm", nullptr));
        abonentCmd->setItemText(3, QApplication::translate("sul_monitorClass", "target_ram_to_plm", nullptr));
        abonentCmd->setItemText(4, QApplication::translate("sul_monitorClass", "target_eeprom_clear", nullptr));
        abonentCmd->setItemText(5, QApplication::translate("sul_monitorClass", "target_ram_clear", nullptr));
        abonentCmd->setItemText(6, QApplication::translate("sul_monitorClass", "target_eeprom_data", nullptr));
        abonentCmd->setItemText(7, QApplication::translate("sul_monitorClass", "target_ram_data", nullptr));
        abonentCmd->setItemText(8, QApplication::translate("sul_monitorClass", "target_eeprom_crc", nullptr));
        abonentCmd->setItemText(9, QApplication::translate("sul_monitorClass", "target_ram_crc", nullptr));
        abonentCmd->setItemText(10, QApplication::translate("sul_monitorClass", "target_ctrl_impulse", nullptr));
        abonentCmd->setItemText(11, QApplication::translate("sul_monitorClass", "target_impulse_return", nullptr));
        abonentCmd->setItemText(12, QApplication::translate("sul_monitorClass", "target_ctrl_channel", nullptr));
        abonentCmd->setItemText(13, QApplication::translate("sul_monitorClass", "target_channel_return", nullptr));
        abonentCmd->setItemText(14, QApplication::translate("sul_monitorClass", "target_ctrl_calc", nullptr));
        abonentCmd->setItemText(15, QApplication::translate("sul_monitorClass", "target_calc_return", nullptr));
        abonentCmd->setItemText(16, QApplication::translate("sul_monitorClass", "host_to_target", nullptr));
        abonentCmd->setItemText(17, QApplication::translate("sul_monitorClass", "target_to_host", nullptr));
        abonentCmd->setItemText(18, QApplication::translate("sul_monitorClass", "target_address", nullptr));
        abonentCmd->setItemText(19, QApplication::translate("sul_monitorClass", "target_reset", nullptr));

        label_17->setText(QApplication::translate("sul_monitorClass", "\320\235\320\276\320\274\320\265\321\200 \320\261\320\273\320\276\320\272\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label_18->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\260\320\271\321\202 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label_20->setText(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\270\320\276\320\264 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271, \320\274\321\201", nullptr));
        btnSend->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        btnShowView->setText(QApplication::translate("sul_monitorClass", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260\320\274\320\270", nullptr));
        groupBox->setTitle(QApplication::translate("sul_monitorClass", "\320\230\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201 \321\201\320\262\321\217\320\267\320\270", nullptr));
        rbtCOM1->setText(QApplication::translate("sul_monitorClass", "\320\241OM-1", nullptr));
        rbtCOM2->setText(QApplication::translate("sul_monitorClass", "COM-2", nullptr));
        rbtRS4851->setText(QApplication::translate("sul_monitorClass", "RS485-1", nullptr));
        rbtRS4852->setText(QApplication::translate("sul_monitorClass", "RS485-2", nullptr));
        btnDraw->setText(QApplication::translate("sul_monitorClass", "\320\223\321\200\320\260\321\204\320\270\320\272\320\260", nullptr));
        groupBox_11->setTitle(QApplication::translate("sul_monitorClass", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 \321\201\320\270\321\201\321\202\320\265\320\274\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sul_monitorClass: public Ui_sul_monitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUL_MONITOR_H
