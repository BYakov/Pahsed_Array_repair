/********************************************************************************
** Form generated from reading UI file 'sul_monitor.ui'
**
** Created: Sat 10. Jul 10:37:37 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUL_MONITOR_H
#define UI_SUL_MONITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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
    QGroupBox *groupBox_18;
    QSpinBox *spbZone;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QDoubleSpinBox *value_x0;
    QLabel *label;
    QDoubleSpinBox *value_y0;
    QLabel *label_2;
    QSpinBox *period;
    QLabel *label_3;
    QDoubleSpinBox *scanSectorMax;
    QLabel *label_5;
    QDoubleSpinBox *step_dr;
    QLabel *label_6;
    QPushButton *btnStart;
    QPushButton *btnSetBeam;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLabel *currentX;
    QLabel *label_9;
    QLabel *currentXcode;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *currentY;
    QLabel *label_13;
    QLabel *currentYcode;
    QWidget *verticalLayoutWidget_11;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_19;
    QProgressBar *progressBar;
    QGroupBox *groupBox_9;
    QToolBox *toolBox_2;
    QWidget *page_15;
    QWidget *page_17;
    QWidget *page_16;
    QPushButton *btnNewConfig;
    QWidget *page_3;
    QGroupBox *groupBox_21;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_5;
    QLabel *label_30;
    QLabel *label_24;
    QLabel *label_25;
    QSpinBox *spbSegmentNumber;
    QLabel *label_22;
    QLabel *label_29;
    QSpinBox *spbFlashAbonentNumber;
    QLabel *lblFileCRC;
    QLabel *label_33;
    QLabel *lblHwCRC;
    QPushButton *btnFlashCheck;
    QPushButton *btnFlashErase;
    QPushButton *btnFlashFileOpen;
    QPushButton *btnFlashLoad;
    QLabel *label_27;
    QGroupBox *gbFlashData;
    QTableView *ftable;
    QWidget *page_4;
    QGroupBox *groupBox_7;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QLabel *label_32;
    QPushButton *btnRamOpen;
    QPushButton *btnRamLoad;
    QPushButton *btnRamErase;
    QPushButton *btnRamSave;
    QRadioButton *rbtFillRamPattern;
    QRadioButton *rbtFillRamRandom;
    QSpinBox *lePatternValue;
    QPushButton *btnFillRam;
    QLabel *label_34;
    QLabel *label_16;
    QSpinBox *spbRamStepValue;
    QPushButton *btnIncRamValue;
    QPushButton *btnDecRamValue;
    QLabel *label_31;
    QLabel *label_35;
    QSpinBox *spbRamAbonentNumber;
    QLabel *label_36;
    QGroupBox *gbRamData;
    QTableView *rtable;
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
    QGroupBox *groupBox_11;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *btnDraw;
    QPushButton *btnSysCtrl;
    QLabel *label_14;
    QLabel *label_10;
    QLabel *label_15;
    QLabel *label_21;
    QSpinBox *spbLowLevel;
    QSpinBox *spbTopLevel;
    QSpinBox *spbPauseDuration;
    QSpinBox *spbResetDuration;
    QSpinBox *spbScaleValue;
    QPushButton *btnGridArray;
    QPushButton *btnSetScale;
    QGroupBox *groupBox_19;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_23;
    QLabel *lbActiveAbonents;
    QSpinBox *spbAbonentIndex;
    QLabel *lbAbonentAddr;
    QPushButton *btnRestartSystem;

    void setupUi(QWidget *sul_monitorClass)
    {
        if (sul_monitorClass->objectName().isEmpty())
            sul_monitorClass->setObjectName(QString::fromUtf8("sul_monitorClass"));
        sul_monitorClass->setWindowModality(Qt::WindowModal);
        sul_monitorClass->resize(751, 590);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/monitor/main_icon"), QSize(), QIcon::Normal, QIcon::Off);
        sul_monitorClass->setWindowIcon(icon);
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
        groupBox_6->setGeometry(QRect(190, 20, 125, 45));
        horizontalLayoutWidget_3 = new QWidget(groupBox_6);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 18, 85, 22));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        scanAngle = new QDoubleSpinBox(horizontalLayoutWidget_3);
        scanAngle->setObjectName(QString::fromUtf8("scanAngle"));
        scanAngle->setDecimals(3);
        scanAngle->setMinimum(0);
        scanAngle->setMaximum(180);

        horizontalLayout_3->addWidget(scanAngle);

        groupBox_18 = new QGroupBox(groupBox_2);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        groupBox_18->setGeometry(QRect(320, 20, 55, 45));
        spbZone = new QSpinBox(groupBox_18);
        spbZone->setObjectName(QString::fromUtf8("spbZone"));
        spbZone->setEnabled(true);
        spbZone->setGeometry(QRect(5, 17, 45, 22));
        spbZone->setMaximum(7);
        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(5, 0, 381, 130));
        gridLayoutWidget = new QWidget(groupBox_3);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(15, 20, 355, 105));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        value_x0 = new QDoubleSpinBox(gridLayoutWidget);
        value_x0->setObjectName(QString::fromUtf8("value_x0"));
        value_x0->setDecimals(4);
        value_x0->setMinimum(-90);
        value_x0->setMaximum(90);

        gridLayout->addWidget(value_x0, 1, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        value_y0 = new QDoubleSpinBox(gridLayoutWidget);
        value_y0->setObjectName(QString::fromUtf8("value_y0"));
        value_y0->setDecimals(4);
        value_y0->setMinimum(-90);
        value_y0->setMaximum(90);

        gridLayout->addWidget(value_y0, 1, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        period = new QSpinBox(gridLayoutWidget);
        period->setObjectName(QString::fromUtf8("period"));
        period->setMaximum(5000);
        period->setSingleStep(10);
        period->setValue(20);

        gridLayout->addWidget(period, 1, 3, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        scanSectorMax = new QDoubleSpinBox(gridLayoutWidget);
        scanSectorMax->setObjectName(QString::fromUtf8("scanSectorMax"));
        scanSectorMax->setDecimals(3);
        scanSectorMax->setMaximum(90);
        scanSectorMax->setValue(60);

        gridLayout->addWidget(scanSectorMax, 3, 1, 1, 2);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 2, 1, 1, 2);

        step_dr = new QDoubleSpinBox(gridLayoutWidget);
        step_dr->setObjectName(QString::fromUtf8("step_dr"));
        step_dr->setDecimals(4);
        step_dr->setMinimum(-10);
        step_dr->setMaximum(10);
        step_dr->setSingleStep(0.5);
        step_dr->setValue(0.5);

        gridLayout->addWidget(step_dr, 3, 3, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 2, 3, 1, 1);

        btnStart = new QPushButton(gridLayoutWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout->addWidget(btnStart, 3, 4, 1, 1);

        btnSetBeam = new QPushButton(gridLayoutWidget);
        btnSetBeam->setObjectName(QString::fromUtf8("btnSetBeam"));

        gridLayout->addWidget(btnSetBeam, 1, 4, 1, 1);

        groupBox_4 = new QGroupBox(page);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(5, 210, 381, 135));
        horizontalLayoutWidget_4 = new QWidget(groupBox_4);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 26, 360, 20));
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

        currentXcode = new QLabel(horizontalLayoutWidget_4);
        currentXcode->setObjectName(QString::fromUtf8("currentXcode"));
        currentXcode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(currentXcode);

        horizontalLayoutWidget_5 = new QWidget(groupBox_4);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 53, 360, 20));
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

        currentYcode = new QLabel(horizontalLayoutWidget_5);
        currentYcode->setObjectName(QString::fromUtf8("currentYcode"));
        currentYcode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(currentYcode);

        verticalLayoutWidget_11 = new QWidget(groupBox_4);
        verticalLayoutWidget_11->setObjectName(QString::fromUtf8("verticalLayoutWidget_11"));
        verticalLayoutWidget_11->setGeometry(QRect(10, 83, 360, 38));
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
        groupBox_9->setEnabled(false);
        groupBox_9->setGeometry(QRect(390, 0, 341, 345));
        toolBox_2 = new QToolBox(groupBox_9);
        toolBox_2->setObjectName(QString::fromUtf8("toolBox_2"));
        toolBox_2->setEnabled(false);
        toolBox_2->setGeometry(QRect(10, 20, 321, 316));
        page_15 = new QWidget();
        page_15->setObjectName(QString::fromUtf8("page_15"));
        page_15->setGeometry(QRect(0, 0, 321, 235));
        toolBox_2->addItem(page_15, QString::fromUtf8(" \320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \321\204\320\260\320\271\320\273\320\260 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\241\320\243\320\233"));
        page_17 = new QWidget();
        page_17->setObjectName(QString::fromUtf8("page_17"));
        page_17->setGeometry(QRect(0, 0, 321, 235));
        toolBox_2->addItem(page_17, QString::fromUtf8(" \320\237\320\276\320\264\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\273\321\203\321\207\320\260 (\320\262\320\260\321\200\320\270\320\260\320\275\321\202 1)"));
        page_16 = new QWidget();
        page_16->setObjectName(QString::fromUtf8("page_16"));
        page_16->setGeometry(QRect(0, 0, 321, 235));
        btnNewConfig = new QPushButton(page_16);
        btnNewConfig->setObjectName(QString::fromUtf8("btnNewConfig"));
        btnNewConfig->setGeometry(QRect(240, 200, 75, 23));
        toolBox_2->addItem(page_16, QString::fromUtf8(" \320\237\320\276\320\264\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\273\321\203\321\207\320\260 (\320\262\320\260\321\200\320\270\320\260\320\275\321\202 2)"));
        toolBox->addItem(page, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\273\321\203\321\207\320\276\320\274"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 738, 345));
        groupBox_21 = new QGroupBox(page_3);
        groupBox_21->setObjectName(QString::fromUtf8("groupBox_21"));
        groupBox_21->setGeometry(QRect(5, 242, 725, 101));
        gridLayoutWidget_5 = new QWidget(groupBox_21);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(20, 16, 685, 80));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_30 = new QLabel(gridLayoutWidget_5);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_30, 0, 0, 1, 2);

        label_24 = new QLabel(gridLayoutWidget_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_24, 0, 2, 1, 2);

        label_25 = new QLabel(gridLayoutWidget_5);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignCenter);
        label_25->setWordWrap(true);

        gridLayout_5->addWidget(label_25, 1, 2, 1, 1);

        spbSegmentNumber = new QSpinBox(gridLayoutWidget_5);
        spbSegmentNumber->setObjectName(QString::fromUtf8("spbSegmentNumber"));
        spbSegmentNumber->setMaximum(11);

        gridLayout_5->addWidget(spbSegmentNumber, 2, 5, 1, 1);

        label_22 = new QLabel(gridLayoutWidget_5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_22, 2, 4, 1, 1);

        label_29 = new QLabel(gridLayoutWidget_5);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_29, 0, 4, 1, 2);

        spbFlashAbonentNumber = new QSpinBox(gridLayoutWidget_5);
        spbFlashAbonentNumber->setObjectName(QString::fromUtf8("spbFlashAbonentNumber"));
        spbFlashAbonentNumber->setMinimum(1);
        spbFlashAbonentNumber->setMaximum(5);
        spbFlashAbonentNumber->setValue(1);

        gridLayout_5->addWidget(spbFlashAbonentNumber, 1, 5, 1, 1);

        lblFileCRC = new QLabel(gridLayoutWidget_5);
        lblFileCRC->setObjectName(QString::fromUtf8("lblFileCRC"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        lblFileCRC->setFont(font);
        lblFileCRC->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lblFileCRC, 2, 3, 1, 1);

        label_33 = new QLabel(gridLayoutWidget_5);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_33, 1, 4, 1, 1);

        lblHwCRC = new QLabel(gridLayoutWidget_5);
        lblHwCRC->setObjectName(QString::fromUtf8("lblHwCRC"));
        lblHwCRC->setFont(font);
        lblHwCRC->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lblHwCRC, 1, 3, 1, 1);

        btnFlashCheck = new QPushButton(gridLayoutWidget_5);
        btnFlashCheck->setObjectName(QString::fromUtf8("btnFlashCheck"));

        gridLayout_5->addWidget(btnFlashCheck, 1, 1, 1, 1);

        btnFlashErase = new QPushButton(gridLayoutWidget_5);
        btnFlashErase->setObjectName(QString::fromUtf8("btnFlashErase"));

        gridLayout_5->addWidget(btnFlashErase, 2, 1, 1, 1);

        btnFlashFileOpen = new QPushButton(gridLayoutWidget_5);
        btnFlashFileOpen->setObjectName(QString::fromUtf8("btnFlashFileOpen"));

        gridLayout_5->addWidget(btnFlashFileOpen, 1, 0, 1, 1);

        btnFlashLoad = new QPushButton(gridLayoutWidget_5);
        btnFlashLoad->setObjectName(QString::fromUtf8("btnFlashLoad"));

        gridLayout_5->addWidget(btnFlashLoad, 2, 0, 1, 1);

        label_27 = new QLabel(gridLayoutWidget_5);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setAlignment(Qt::AlignCenter);
        label_27->setWordWrap(true);

        gridLayout_5->addWidget(label_27, 2, 2, 1, 1);

        gbFlashData = new QGroupBox(page_3);
        gbFlashData->setObjectName(QString::fromUtf8("gbFlashData"));
        gbFlashData->setGeometry(QRect(5, 2, 725, 240));
        ftable = new QTableView(gbFlashData);
        ftable->setObjectName(QString::fromUtf8("ftable"));
        ftable->setGeometry(QRect(11, 17, 705, 215));
        toolBox->addItem(page_3, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 flash"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 738, 345));
        groupBox_7 = new QGroupBox(page_4);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(5, 240, 725, 105));
        gridLayoutWidget_4 = new QWidget(groupBox_7);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(20, 21, 685, 80));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_32 = new QLabel(gridLayoutWidget_4);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_32, 0, 0, 1, 2);

        btnRamOpen = new QPushButton(gridLayoutWidget_4);
        btnRamOpen->setObjectName(QString::fromUtf8("btnRamOpen"));

        gridLayout_4->addWidget(btnRamOpen, 1, 0, 1, 1);

        btnRamLoad = new QPushButton(gridLayoutWidget_4);
        btnRamLoad->setObjectName(QString::fromUtf8("btnRamLoad"));

        gridLayout_4->addWidget(btnRamLoad, 2, 0, 1, 1);

        btnRamErase = new QPushButton(gridLayoutWidget_4);
        btnRamErase->setObjectName(QString::fromUtf8("btnRamErase"));

        gridLayout_4->addWidget(btnRamErase, 1, 1, 1, 1);

        btnRamSave = new QPushButton(gridLayoutWidget_4);
        btnRamSave->setObjectName(QString::fromUtf8("btnRamSave"));

        gridLayout_4->addWidget(btnRamSave, 2, 1, 1, 1);

        rbtFillRamPattern = new QRadioButton(gridLayoutWidget_4);
        rbtFillRamPattern->setObjectName(QString::fromUtf8("rbtFillRamPattern"));

        gridLayout_4->addWidget(rbtFillRamPattern, 1, 2, 1, 1);

        rbtFillRamRandom = new QRadioButton(gridLayoutWidget_4);
        rbtFillRamRandom->setObjectName(QString::fromUtf8("rbtFillRamRandom"));
        rbtFillRamRandom->setChecked(true);

        gridLayout_4->addWidget(rbtFillRamRandom, 1, 3, 1, 1);

        lePatternValue = new QSpinBox(gridLayoutWidget_4);
        lePatternValue->setObjectName(QString::fromUtf8("lePatternValue"));
        lePatternValue->setMaximum(31);

        gridLayout_4->addWidget(lePatternValue, 2, 2, 1, 1);

        btnFillRam = new QPushButton(gridLayoutWidget_4);
        btnFillRam->setObjectName(QString::fromUtf8("btnFillRam"));

        gridLayout_4->addWidget(btnFillRam, 2, 3, 1, 1);

        label_34 = new QLabel(gridLayoutWidget_4);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_34, 0, 2, 1, 2);

        label_16 = new QLabel(gridLayoutWidget_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_16, 1, 4, 1, 1);

        spbRamStepValue = new QSpinBox(gridLayoutWidget_4);
        spbRamStepValue->setObjectName(QString::fromUtf8("spbRamStepValue"));
        spbRamStepValue->setMinimum(1);
        spbRamStepValue->setMaximum(31);

        gridLayout_4->addWidget(spbRamStepValue, 2, 4, 1, 1);

        btnIncRamValue = new QPushButton(gridLayoutWidget_4);
        btnIncRamValue->setObjectName(QString::fromUtf8("btnIncRamValue"));

        gridLayout_4->addWidget(btnIncRamValue, 1, 5, 1, 1);

        btnDecRamValue = new QPushButton(gridLayoutWidget_4);
        btnDecRamValue->setObjectName(QString::fromUtf8("btnDecRamValue"));

        gridLayout_4->addWidget(btnDecRamValue, 2, 5, 1, 1);

        label_31 = new QLabel(gridLayoutWidget_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_31, 0, 4, 1, 2);

        label_35 = new QLabel(gridLayoutWidget_4);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_35, 1, 6, 1, 1);

        spbRamAbonentNumber = new QSpinBox(gridLayoutWidget_4);
        spbRamAbonentNumber->setObjectName(QString::fromUtf8("spbRamAbonentNumber"));
        spbRamAbonentNumber->setMinimum(1);
        spbRamAbonentNumber->setMaximum(5);

        gridLayout_4->addWidget(spbRamAbonentNumber, 2, 6, 1, 1);

        label_36 = new QLabel(gridLayoutWidget_4);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_36, 0, 6, 1, 1);

        gbRamData = new QGroupBox(page_4);
        gbRamData->setObjectName(QString::fromUtf8("gbRamData"));
        gbRamData->setGeometry(QRect(6, 0, 725, 240));
        rtable = new QTableView(gbRamData);
        rtable->setObjectName(QString::fromUtf8("rtable"));
        rtable->setGeometry(QRect(11, 17, 705, 215));
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
        verticalLayoutWidget_6->setGeometry(QRect(40, 25, 145, 300));
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
        btnShowView->setCheckable(false);

        verticalLayout_6->addWidget(btnShowView);

        toolBox->addItem(page_5, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260\320\274\320\270"));

        verticalLayout->addWidget(toolBox);

        horizontalLayoutWidget = new QWidget(sul_monitorClass);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(4, 567, 746, 21));
        barLayout = new QHBoxLayout(horizontalLayoutWidget);
        barLayout->setSpacing(6);
        barLayout->setContentsMargins(11, 11, 11, 11);
        barLayout->setObjectName(QString::fromUtf8("barLayout"));
        barLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(sul_monitorClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 460, 75, 105));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(6, 18, 60, 80));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
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

        groupBox_11 = new QGroupBox(sul_monitorClass);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(85, 459, 525, 105));
        gridLayoutWidget_2 = new QWidget(groupBox_11);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(5, 16, 515, 85));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        btnDraw = new QPushButton(gridLayoutWidget_2);
        btnDraw->setObjectName(QString::fromUtf8("btnDraw"));

        gridLayout_2->addWidget(btnDraw, 0, 0, 1, 1);

        btnSysCtrl = new QPushButton(gridLayoutWidget_2);
        btnSysCtrl->setObjectName(QString::fromUtf8("btnSysCtrl"));
        btnSysCtrl->setCheckable(false);

        gridLayout_2->addWidget(btnSysCtrl, 1, 0, 1, 1);

        label_14 = new QLabel(gridLayoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_14, 0, 5, 1, 2);

        label_10 = new QLabel(gridLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 0, 2, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_15, 0, 3, 1, 1);

        label_21 = new QLabel(gridLayoutWidget_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_21, 0, 4, 1, 1);

        spbLowLevel = new QSpinBox(gridLayoutWidget_2);
        spbLowLevel->setObjectName(QString::fromUtf8("spbLowLevel"));
        spbLowLevel->setMinimum(0);
        spbLowLevel->setMaximum(255);
        spbLowLevel->setValue(60);

        gridLayout_2->addWidget(spbLowLevel, 1, 6, 1, 1);

        spbTopLevel = new QSpinBox(gridLayoutWidget_2);
        spbTopLevel->setObjectName(QString::fromUtf8("spbTopLevel"));
        spbTopLevel->setMaximum(255);
        spbTopLevel->setValue(80);

        gridLayout_2->addWidget(spbTopLevel, 1, 5, 1, 1);

        spbPauseDuration = new QSpinBox(gridLayoutWidget_2);
        spbPauseDuration->setObjectName(QString::fromUtf8("spbPauseDuration"));
        spbPauseDuration->setMinimum(5);
        spbPauseDuration->setMaximum(20);
        spbPauseDuration->setValue(20);

        gridLayout_2->addWidget(spbPauseDuration, 1, 4, 1, 1);

        spbResetDuration = new QSpinBox(gridLayoutWidget_2);
        spbResetDuration->setObjectName(QString::fromUtf8("spbResetDuration"));
        spbResetDuration->setMinimum(25);
        spbResetDuration->setMaximum(50);
        spbResetDuration->setValue(40);

        gridLayout_2->addWidget(spbResetDuration, 1, 3, 1, 1);

        spbScaleValue = new QSpinBox(gridLayoutWidget_2);
        spbScaleValue->setObjectName(QString::fromUtf8("spbScaleValue"));
        spbScaleValue->setMinimum(1);
        spbScaleValue->setMaximum(20);
        spbScaleValue->setValue(6);

        gridLayout_2->addWidget(spbScaleValue, 1, 2, 1, 1);

        btnGridArray = new QPushButton(gridLayoutWidget_2);
        btnGridArray->setObjectName(QString::fromUtf8("btnGridArray"));

        gridLayout_2->addWidget(btnGridArray, 2, 0, 1, 1);

        btnSetScale = new QPushButton(gridLayoutWidget_2);
        btnSetScale->setObjectName(QString::fromUtf8("btnSetScale"));

        gridLayout_2->addWidget(btnSetScale, 2, 2, 1, 5);

        groupBox_19 = new QGroupBox(sul_monitorClass);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        groupBox_19->setGeometry(QRect(615, 459, 130, 105));
        gridLayoutWidget_3 = new QWidget(groupBox_19);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(5, 18, 120, 80));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(5);
        gridLayout_3->setVerticalSpacing(6);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(gridLayoutWidget_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_23, 0, 0, 1, 1);

        lbActiveAbonents = new QLabel(gridLayoutWidget_3);
        lbActiveAbonents->setObjectName(QString::fromUtf8("lbActiveAbonents"));
        lbActiveAbonents->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbActiveAbonents, 0, 1, 1, 1);

        spbAbonentIndex = new QSpinBox(gridLayoutWidget_3);
        spbAbonentIndex->setObjectName(QString::fromUtf8("spbAbonentIndex"));
        spbAbonentIndex->setEnabled(true);
        spbAbonentIndex->setMinimum(1);
        spbAbonentIndex->setMaximum(5);

        gridLayout_3->addWidget(spbAbonentIndex, 1, 0, 1, 1);

        lbAbonentAddr = new QLabel(gridLayoutWidget_3);
        lbAbonentAddr->setObjectName(QString::fromUtf8("lbAbonentAddr"));
        lbAbonentAddr->setEnabled(true);
        lbAbonentAddr->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbAbonentAddr, 1, 1, 1, 1);

        btnRestartSystem = new QPushButton(gridLayoutWidget_3);
        btnRestartSystem->setObjectName(QString::fromUtf8("btnRestartSystem"));

        gridLayout_3->addWidget(btnRestartSystem, 2, 0, 1, 2);


        retranslateUi(sul_monitorClass);

        toolBox->setCurrentIndex(0);
        toolBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(sul_monitorClass);
    } // setupUi

    void retranslateUi(QWidget *sul_monitorClass)
    {
        sul_monitorClass->setWindowTitle(QApplication::translate("sul_monitorClass", "sul_monitor", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("sul_monitorClass", "\320\236\321\201\321\214 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        rbtAxisX->setText(QApplication::translate("sul_monitorClass", "X", 0, QApplication::UnicodeUTF8));
        rbtAxisY->setText(QApplication::translate("sul_monitorClass", "Y", 0, QApplication::UnicodeUTF8));
        rbtAxisXY->setText(QApplication::translate("sul_monitorClass", "XY", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\263\320\276\320\273 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217, \302\260", 0, QApplication::UnicodeUTF8));
        groupBox_18->setTitle(QApplication::translate("sul_monitorClass", "\320\227\320\276\320\275\320\260", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("sul_monitorClass", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 X", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 Y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\270\320\276\320\264, \320\274\321\201", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("sul_monitorClass", "\320\241\320\265\320\272\321\202\320\276\321\200, \302\260", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("sul_monitorClass", "\320\250\320\260\320\263", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        btnSetBeam->setText(QApplication::translate("sul_monitorClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("sul_monitorClass", "\320\242\320\265\320\272\321\203\321\211\320\270\320\265 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("sul_monitorClass", "X:", 0, QApplication::UnicodeUTF8));
        currentX->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\264", 0, QApplication::UnicodeUTF8));
        currentXcode->setText(QApplication::translate("sul_monitorClass", "0x0", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("sul_monitorClass", "Y:", 0, QApplication::UnicodeUTF8));
        currentY->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\264", 0, QApplication::UnicodeUTF8));
        currentYcode->setText(QApplication::translate("sul_monitorClass", "0x0", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\202\321\203\321\201 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("sul_monitorClass", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\260\321\217 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\270\321\201\321\202\320\265\320\274\321\213", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_15), QApplication::translate("sul_monitorClass", " \320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \321\204\320\260\320\271\320\273\320\260 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\241\320\243\320\233", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_17), QApplication::translate("sul_monitorClass", " \320\237\320\276\320\264\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\273\321\203\321\207\320\260 (\320\262\320\260\321\200\320\270\320\260\320\275\321\202 1)", 0, QApplication::UnicodeUTF8));
        btnNewConfig->setText(QApplication::translate("sul_monitorClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        toolBox_2->setItemText(toolBox_2->indexOf(page_16), QApplication::translate("sul_monitorClass", " \320\237\320\276\320\264\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\273\321\203\321\207\320\260 (\320\262\320\260\321\200\320\270\320\260\320\275\321\202 2)", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\273\321\203\321\207\320\276\320\274", 0, QApplication::UnicodeUTF8));
        groupBox_21->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\265\320\271 FLASH", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("sul_monitorClass", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("sul_monitorClass", "CRC \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\276\320\262:", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("sul_monitorClass", "\320\235\320\276\320\274\320\265\321\200 \321\201\320\265\320\263\320\274\320\265\320\275\321\202\320\260 ", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\262\320\270\320\263\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        lblFileCRC->setText(QApplication::translate("sul_monitorClass", "0x0000", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        lblHwCRC->setText(QApplication::translate("sul_monitorClass", "0x0000", 0, QApplication::UnicodeUTF8));
        btnFlashCheck->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\275\321\202\321\200\320\276\320\273\321\214", 0, QApplication::UnicodeUTF8));
        btnFlashErase->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\270\321\200\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        btnFlashFileOpen->setText(QApplication::translate("sul_monitorClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnFlashLoad->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("sul_monitorClass", "CRC \321\204\320\260\320\271\320\273\320\260:", 0, QApplication::UnicodeUTF8));
        gbFlashData->setTitle(QString());
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 flash", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\265\320\271 RAM", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213", 0, QApplication::UnicodeUTF8));
        btnRamOpen->setText(QApplication::translate("sul_monitorClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnRamLoad->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", 0, QApplication::UnicodeUTF8));
        btnRamErase->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\270\321\200\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        btnRamSave->setText(QApplication::translate("sul_monitorClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        rbtFillRamPattern->setText(QApplication::translate("sul_monitorClass", "\320\247\320\270\321\201\320\273\320\276\320\262\320\276\320\265", 0, QApplication::UnicodeUTF8));
        rbtFillRamRandom->setText(QApplication::translate("sul_monitorClass", "\320\241\320\273\321\203\321\207\320\260\320\271\320\275\320\276\320\265", 0, QApplication::UnicodeUTF8));
        btnFillRam->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\277\320\276\320\273\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("sul_monitorClass", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("sul_monitorClass", "\320\250\320\260\320\263", 0, QApplication::UnicodeUTF8));
        btnIncRamValue->setText(QApplication::translate("sul_monitorClass", "\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        btnDecRamValue->setText(QApplication::translate("sul_monitorClass", "\320\224\320\265\320\272\321\200\320\265\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\262\320\270\320\263\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        gbRamData->setTitle(QString());
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 ram", 0, QApplication::UnicodeUTF8));
        groupBox_13->setTitle(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\265\320\264\320\260\321\207\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        groupBox_12->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\320\275\321\213\320\271 \320\261\320\273\320\276\320\272", 0, QApplication::UnicodeUTF8));
        groupBox_14->setTitle(QApplication::translate("sul_monitorClass", "\320\237\321\200\320\270\320\265\320\274 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        groupBox_17->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("sul_monitorClass", "\320\242\320\270\320\277 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        abonentCmd->clear();
        abonentCmd->insertItems(0, QStringList()
         << QApplication::translate("sul_monitorClass", "host_eeprom_data", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "host_ram_data", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "host_scale", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_scale_return", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_eeprom_to_plm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_ram_to_plm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_eeprom_clear", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_ram_clear", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_eeprom_data", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_ram_data", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_eeprom_crc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_ram_crc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_ctrl_impulse", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_impulse_return", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_ctrl_channel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_channel_return", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_ctrl_calc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_calc_return", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "host_to_target", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_to_host", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_address", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("sul_monitorClass", "target_reset", 0, QApplication::UnicodeUTF8)
        );
        label_17->setText(QApplication::translate("sul_monitorClass", "\320\235\320\276\320\274\320\265\321\200 \320\261\320\273\320\276\320\272\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\260\320\271\321\202 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\270\320\276\320\264 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271, \320\274\321\201", 0, QApplication::UnicodeUTF8));
        btnSend->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        btnShowView->setText(QApplication::translate("sul_monitorClass", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260\320\274\320\270", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("sul_monitorClass", "\320\230\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201", 0, QApplication::UnicodeUTF8));
        rbtCOM1->setText(QApplication::translate("sul_monitorClass", "\320\241OM1", 0, QApplication::UnicodeUTF8));
        rbtCOM2->setText(QApplication::translate("sul_monitorClass", "COM2", 0, QApplication::UnicodeUTF8));
        rbtRS4851->setText(QApplication::translate("sul_monitorClass", "COM3", 0, QApplication::UnicodeUTF8));
        rbtRS4852->setText(QApplication::translate("sul_monitorClass", "COM4", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("sul_monitorClass", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \321\201\320\270\321\201\321\202\320\265\320\274\320\276\320\271", 0, QApplication::UnicodeUTF8));
        btnDraw->setText(QApplication::translate("sul_monitorClass", "\320\233\321\203\321\207", 0, QApplication::UnicodeUTF8));
        btnSysCtrl->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\275\321\202\321\200\320\276\320\273\321\214", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("sul_monitorClass", "\320\224\320\270\320\260\320\277\320\260\320\267\320\276\320\275 \320\263\321\200\320\260\320\275\320\270\321\206", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("sul_monitorClass", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("sul_monitorClass", "\320\241\320\261\321\200\320\276\321\201, \320\274\320\272\321\201", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("sul_monitorClass", "\320\237\320\260\321\203\320\267\320\260, \320\274\320\272\321\201", 0, QApplication::UnicodeUTF8));
        btnGridArray->setText(QApplication::translate("sul_monitorClass", "\320\240\320\265\321\210\320\265\321\202\320\272\320\260", 0, QApplication::UnicodeUTF8));
        btnSetScale->setText(QApplication::translate("sul_monitorClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_19->setTitle(QApplication::translate("sul_monitorClass", "\320\220\320\272\321\202\320\270\320\262\320\275\321\213\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("sul_monitorClass", "\320\222\321\201\320\265\320\263\320\276:", 0, QApplication::UnicodeUTF8));
        lbActiveAbonents->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        lbAbonentAddr->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        btnRestartSystem->setText(QApplication::translate("sul_monitorClass", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class sul_monitorClass: public Ui_sul_monitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUL_MONITOR_H
