/********************************************************************************
** Form generated from reading UI file 'sul_monitor.ui'
**
** Created: Sat 24. Jan 14:19:31 2015
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUL_MONITOR_H
#define UI_SUL_MONITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sul_monitorClass
{
public:
    QGridLayout *gridLayout_13;
    QVBoxLayout *verticalLayout;
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout_21;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_16;
    QGridLayout *gridLayout;
    QDoubleSpinBox *value_x0;
    QLabel *label;
    QDoubleSpinBox *value_y0;
    QLabel *label_2;
    QSpinBox *period;
    QLabel *label_3;
    QDoubleSpinBox *scanSectorMax;
    QDoubleSpinBox *step_dr;
    QLabel *label_6;
    QPushButton *btnStart;
    QPushButton *btnSetBeam;
    QLabel *label_5;
    QLabel *label_42;
    QDoubleSpinBox *scanRangeSector;
    QCheckBox *cbTrackMode;
    QCheckBox *cbSphere;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_15;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_18;
    QGridLayout *gridLayout_29;
    QRadioButton *rbtAxisX;
    QRadioButton *rbtAxisY;
    QRadioButton *rbtAxisXY;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_19;
    QGridLayout *gridLayout_30;
    QDoubleSpinBox *scanAngle;
    QGroupBox *groupBox_18;
    QGridLayout *gridLayout_20;
    QComboBox *cbZone;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_17;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLabel *currentX;
    QLabel *label_9;
    QLabel *currentXcode;
    QLabel *label_23;
    QLabel *phaseIncursionX;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *currentY;
    QLabel *label_13;
    QLabel *currentYcode;
    QLabel *label_51;
    QLabel *phaseIncursionY;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_19;
    QProgressBar *progressBar;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_14;
    QToolBox *extTuneBox;
    QWidget *page_15;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_7;
    QLabel *label_37;
    QLabel *label_39;
    QDoubleSpinBox *spbFocusValue;
    QDoubleSpinBox *spbWaveLength;
    QPushButton *pbCalculateCorrectionPhase;
    QPushButton *pbCorrPhaseSaveToFile;
    QPushButton *pbCorrPhaseLoadToSUL;
    QLabel *label_28;
    QCheckBox *cbAddToFile;
    QCheckBox *cbUseFi0;
    QSpacerItem *verticalSpacer;
    QWidget *page_17;
    QGridLayout *gridLayout_22;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_23;
    QGridLayout *gridLayout_9;
    QLabel *label_45;
    QCheckBox *autoMeasureFlag;
    QRadioButton *autoMeasureInc;
    QRadioButton *autoMeasureDec;
    QSpinBox *autoMeasureIncVal;
    QSpinBox *autoMeasureDecVal;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_24;
    QGridLayout *gridLayout_8;
    QLabel *label_44;
    QSpinBox *measureChannel;
    QPushButton *measureSetParam;
    QLabel *label_43;
    QLabel *label_32;
    QSpinBox *spbPhaseAbonentNum;
    QSpinBox *measurePhaseCode;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_16;
    QGridLayout *gridLayout_25;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_27;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_48;
    QLineEdit *leBeamSetupTimerPeriod;
    QCheckBox *cbBeamSetupTimerOn;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_16;
    QGridLayout *gridLayout_28;
    QSpinBox *spbArrayElementSize;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBox_15;
    QGridLayout *gridLayout_26;
    QGridLayout *gridLayout_10;
    QLabel *label_47;
    QLabel *label_46;
    QSpinBox *spbNewAddress;
    QLineEdit *leVendorID;
    QPushButton *btnNewModuleSettings;
    QWidget *page_3;
    QGridLayout *gridLayout_31;
    QGroupBox *gbFlashData;
    QGridLayout *gridLayout_33;
    QVBoxLayout *sul_flash_layout;
    QGroupBox *groupBox_21;
    QGridLayout *gridLayout_32;
    QGridLayout *gridLayout_5;
    QLabel *label_27;
    QPushButton *btnFlashSave;
    QLabel *label_30;
    QLabel *lblFileCRC;
    QLabel *label_25;
    QLabel *label_33;
    QLabel *label_29;
    QLabel *label_22;
    QLabel *lblHwCRC;
    QPushButton *btnFlashLoad;
    QPushButton *btnFlashErase;
    QLabel *label_24;
    QPushButton *btnFlashFileOpen;
    QComboBox *cbFlashSegmentName;
    QSpinBox *spbFlashAbonentNumber;
    QSpacerItem *verticalSpacer_8;
    QWidget *page_4;
    QGridLayout *gridLayout_34;
    QGroupBox *gbRamData;
    QGridLayout *gridLayout_35;
    QVBoxLayout *sul_ram_layout;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_36;
    QGridLayout *gridLayout_4;
    QPushButton *btnRamSaveAll;
    QRadioButton *rbtFillRamPattern;
    QRadioButton *rbtFillRamRandom;
    QSpinBox *patternFixValue;
    QLabel *label_16;
    QSpinBox *spbRamStepValue;
    QPushButton *btnIncRamValue;
    QPushButton *btnDecRamValue;
    QLabel *label_35;
    QSpinBox *spbRamAbonentNumber;
    QLabel *label_36;
    QLabel *label_31;
    QLabel *label_34;
    QPushButton *btnRamErase;
    QPushButton *btnSaveAbonentRamFile;
    QRadioButton *rbtFillRamFlash;
    QPushButton *btnFillRam;
    QSpinBox *patternRndValue;
    QCheckBox *cbUpdateRamAll;
    QPushButton *btnRamLoadAll;
    QPushButton *btnRamOpen;
    QPushButton *btnReadAbonentRamFile;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer_9;
    QWidget *page_5;
    QGridLayout *gridLayout_37;
    QGroupBox *groupBox_17;
    QGridLayout *gridLayout_38;
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
    QSpacerItem *verticalSpacer_11;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_39;
    QVBoxLayout *headerLayout;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_40;
    QVBoxLayout *dataOutLayout;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout_41;
    QVBoxLayout *dataInLayout;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_2;
    QPushButton *btnDraw;
    QLabel *label_14;
    QLabel *label_10;
    QLabel *label_15;
    QLabel *label_21;
    QSpinBox *spbLowLevel;
    QSpinBox *spbTopLevel;
    QSpinBox *spbPauseDuration;
    QSpinBox *spbResetDuration;
    QSpinBox *spbScaleValue;
    QPushButton *btnSetScaleFlash;
    QPushButton *btnSetScaleRam;
    QPushButton *btnGridArray;
    QPushButton *pbInterfaceUpdate;
    QPushButton *pbDebug;
    QGroupBox *groupBox_19;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_3;
    QLabel *label_49;
    QLabel *label_50;
    QLabel *lbAbonentAddr;
    QLabel *lbActiveAbonents;
    QSpinBox *spbAbonentIndex;
    QPushButton *pbRescanModule;
    QLabel *lbCPUVer;
    QLabel *label_26;
    QLabel *lbFPGAVer;
    QHBoxLayout *barLayout;

    void setupUi(QWidget *sul_monitorClass)
    {
        if (sul_monitorClass->objectName().isEmpty())
            sul_monitorClass->setObjectName(QString::fromUtf8("sul_monitorClass"));
        sul_monitorClass->setWindowModality(Qt::WindowModal);
        sul_monitorClass->resize(1022, 801);
        QIcon icon;
        icon.addFile(QString::fromUtf8("monitor_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        sul_monitorClass->setWindowIcon(icon);
        gridLayout_13 = new QGridLayout(sul_monitorClass);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBox = new QToolBox(sul_monitorClass);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 1002, 559));
        gridLayout_21 = new QGridLayout(page);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_16 = new QGridLayout(groupBox_3);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        value_x0 = new QDoubleSpinBox(groupBox_3);
        value_x0->setObjectName(QString::fromUtf8("value_x0"));
        value_x0->setDecimals(4);
        value_x0->setMinimum(-90);
        value_x0->setMaximum(90);

        gridLayout->addWidget(value_x0, 1, 1, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        value_y0 = new QDoubleSpinBox(groupBox_3);
        value_y0->setObjectName(QString::fromUtf8("value_y0"));
        value_y0->setDecimals(4);
        value_y0->setMinimum(-90);
        value_y0->setMaximum(90);

        gridLayout->addWidget(value_y0, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        period = new QSpinBox(groupBox_3);
        period->setObjectName(QString::fromUtf8("period"));
        period->setMaximum(5000);
        period->setSingleStep(10);
        period->setValue(20);

        gridLayout->addWidget(period, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        scanSectorMax = new QDoubleSpinBox(groupBox_3);
        scanSectorMax->setObjectName(QString::fromUtf8("scanSectorMax"));
        scanSectorMax->setDecimals(3);
        scanSectorMax->setMaximum(90);
        scanSectorMax->setValue(60);

        gridLayout->addWidget(scanSectorMax, 3, 1, 1, 1);

        step_dr = new QDoubleSpinBox(groupBox_3);
        step_dr->setObjectName(QString::fromUtf8("step_dr"));
        step_dr->setDecimals(4);
        step_dr->setMinimum(-10);
        step_dr->setMaximum(10);
        step_dr->setSingleStep(0.5);
        step_dr->setValue(0.5);

        gridLayout->addWidget(step_dr, 3, 3, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 2, 3, 1, 1);

        btnStart = new QPushButton(groupBox_3);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout->addWidget(btnStart, 3, 4, 1, 1);

        btnSetBeam = new QPushButton(groupBox_3);
        btnSetBeam->setObjectName(QString::fromUtf8("btnSetBeam"));

        gridLayout->addWidget(btnSetBeam, 1, 4, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        label_42 = new QLabel(groupBox_3);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_42, 2, 2, 1, 1);

        scanRangeSector = new QDoubleSpinBox(groupBox_3);
        scanRangeSector->setObjectName(QString::fromUtf8("scanRangeSector"));
        scanRangeSector->setDecimals(3);
        scanRangeSector->setMaximum(90);
        scanRangeSector->setValue(20);

        gridLayout->addWidget(scanRangeSector, 3, 2, 1, 1);

        cbTrackMode = new QCheckBox(groupBox_3);
        cbTrackMode->setObjectName(QString::fromUtf8("cbTrackMode"));

        gridLayout->addWidget(cbTrackMode, 2, 4, 1, 1);

        cbSphere = new QCheckBox(groupBox_3);
        cbSphere->setObjectName(QString::fromUtf8("cbSphere"));
        cbSphere->setChecked(true);

        gridLayout->addWidget(cbSphere, 0, 4, 1, 1);


        gridLayout_16->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_21->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_15 = new QGridLayout(groupBox_2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_18 = new QGridLayout(groupBox_5);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        gridLayout_29 = new QGridLayout();
        gridLayout_29->setSpacing(6);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        rbtAxisX = new QRadioButton(groupBox_5);
        rbtAxisX->setObjectName(QString::fromUtf8("rbtAxisX"));
        rbtAxisX->setChecked(true);

        gridLayout_29->addWidget(rbtAxisX, 0, 0, 1, 1);

        rbtAxisY = new QRadioButton(groupBox_5);
        rbtAxisY->setObjectName(QString::fromUtf8("rbtAxisY"));

        gridLayout_29->addWidget(rbtAxisY, 0, 1, 1, 1);

        rbtAxisXY = new QRadioButton(groupBox_5);
        rbtAxisXY->setObjectName(QString::fromUtf8("rbtAxisXY"));

        gridLayout_29->addWidget(rbtAxisXY, 0, 2, 1, 1);


        gridLayout_18->addLayout(gridLayout_29, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_5, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_19 = new QGridLayout(groupBox_6);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        gridLayout_30 = new QGridLayout();
        gridLayout_30->setSpacing(6);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        scanAngle = new QDoubleSpinBox(groupBox_6);
        scanAngle->setObjectName(QString::fromUtf8("scanAngle"));
        scanAngle->setDecimals(3);
        scanAngle->setMinimum(0);
        scanAngle->setMaximum(180);

        gridLayout_30->addWidget(scanAngle, 0, 0, 1, 1);


        gridLayout_19->addLayout(gridLayout_30, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_6, 0, 1, 1, 1);

        groupBox_18 = new QGroupBox(groupBox_2);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        gridLayout_20 = new QGridLayout(groupBox_18);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        cbZone = new QComboBox(groupBox_18);
        cbZone->setObjectName(QString::fromUtf8("cbZone"));

        gridLayout_20->addWidget(cbZone, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_18, 0, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer_5, 1, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer_6, 1, 1, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer_7, 1, 2, 1, 1);


        gridLayout_21->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_4 = new QGroupBox(page);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_17 = new QGridLayout(groupBox_4);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);

        currentX = new QLabel(groupBox_4);
        currentX->setObjectName(QString::fromUtf8("currentX"));
        currentX->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(currentX);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        currentXcode = new QLabel(groupBox_4);
        currentXcode->setObjectName(QString::fromUtf8("currentXcode"));
        currentXcode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(currentXcode);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout->addWidget(label_23);

        phaseIncursionX = new QLabel(groupBox_4);
        phaseIncursionX->setObjectName(QString::fromUtf8("phaseIncursionX"));

        horizontalLayout->addWidget(phaseIncursionX);


        gridLayout_17->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_4->addWidget(label_11);

        currentY = new QLabel(groupBox_4);
        currentY->setObjectName(QString::fromUtf8("currentY"));
        currentY->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(currentY);

        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_4->addWidget(label_13);

        currentYcode = new QLabel(groupBox_4);
        currentYcode->setObjectName(QString::fromUtf8("currentYcode"));
        currentYcode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(currentYcode);

        label_51 = new QLabel(groupBox_4);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        horizontalLayout_4->addWidget(label_51);

        phaseIncursionY = new QLabel(groupBox_4);
        phaseIncursionY->setObjectName(QString::fromUtf8("phaseIncursionY"));

        horizontalLayout_4->addWidget(phaseIncursionY);


        gridLayout_17->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(2);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        verticalLayout_11->addWidget(label_19);

        progressBar = new QProgressBar(groupBox_4);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout_11->addWidget(progressBar);


        gridLayout_17->addLayout(verticalLayout_11, 2, 0, 1, 1);


        gridLayout_21->addWidget(groupBox_4, 2, 0, 1, 1);

        groupBox_9 = new QGroupBox(page);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setEnabled(true);
        gridLayout_14 = new QGridLayout(groupBox_9);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        extTuneBox = new QToolBox(groupBox_9);
        extTuneBox->setObjectName(QString::fromUtf8("extTuneBox"));
        extTuneBox->setEnabled(true);
        page_15 = new QWidget();
        page_15->setObjectName(QString::fromUtf8("page_15"));
        page_15->setGeometry(QRect(0, 0, 469, 427));
        gridLayout_6 = new QGridLayout(page_15);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_37 = new QLabel(page_15);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_37, 0, 0, 1, 1);

        label_39 = new QLabel(page_15);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_39, 0, 1, 1, 1);

        spbFocusValue = new QDoubleSpinBox(page_15);
        spbFocusValue->setObjectName(QString::fromUtf8("spbFocusValue"));
        spbFocusValue->setDecimals(3);
        spbFocusValue->setMaximum(1e+06);
        spbFocusValue->setValue(225);

        gridLayout_7->addWidget(spbFocusValue, 1, 0, 1, 1);

        spbWaveLength = new QDoubleSpinBox(page_15);
        spbWaveLength->setObjectName(QString::fromUtf8("spbWaveLength"));
        spbWaveLength->setDecimals(4);
        spbWaveLength->setMinimum(0.001);
        spbWaveLength->setMaximum(1000);
        spbWaveLength->setSingleStep(0.1);
        spbWaveLength->setValue(8.817);

        gridLayout_7->addWidget(spbWaveLength, 1, 1, 1, 1);

        pbCalculateCorrectionPhase = new QPushButton(page_15);
        pbCalculateCorrectionPhase->setObjectName(QString::fromUtf8("pbCalculateCorrectionPhase"));

        gridLayout_7->addWidget(pbCalculateCorrectionPhase, 2, 0, 1, 1);

        pbCorrPhaseSaveToFile = new QPushButton(page_15);
        pbCorrPhaseSaveToFile->setObjectName(QString::fromUtf8("pbCorrPhaseSaveToFile"));

        gridLayout_7->addWidget(pbCorrPhaseSaveToFile, 3, 0, 1, 1);

        pbCorrPhaseLoadToSUL = new QPushButton(page_15);
        pbCorrPhaseLoadToSUL->setObjectName(QString::fromUtf8("pbCorrPhaseLoadToSUL"));

        gridLayout_7->addWidget(pbCorrPhaseLoadToSUL, 4, 0, 1, 1);

        label_28 = new QLabel(page_15);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_28, 4, 1, 1, 1);

        cbAddToFile = new QCheckBox(page_15);
        cbAddToFile->setObjectName(QString::fromUtf8("cbAddToFile"));

        gridLayout_7->addWidget(cbAddToFile, 3, 1, 1, 1);

        cbUseFi0 = new QCheckBox(page_15);
        cbUseFi0->setObjectName(QString::fromUtf8("cbUseFi0"));
        cbUseFi0->setChecked(true);

        gridLayout_7->addWidget(cbUseFi0, 2, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_7, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 1, 0, 1, 1);

        extTuneBox->addItem(page_15, QString::fromUtf8(" \320\240\320\260\321\201\321\207\320\265\321\202 \320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\270\321\200\321\203\321\216\321\211\320\270\321\205 \320\272\320\276\320\264\320\276\320\262"));
        page_17 = new QWidget();
        page_17->setObjectName(QString::fromUtf8("page_17"));
        page_17->setGeometry(QRect(0, 0, 235, 237));
        gridLayout_22 = new QGridLayout(page_17);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        groupBox_8 = new QGroupBox(page_17);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout_23 = new QGridLayout(groupBox_8);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_45 = new QLabel(groupBox_8);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_45, 0, 1, 1, 1);

        autoMeasureFlag = new QCheckBox(groupBox_8);
        autoMeasureFlag->setObjectName(QString::fromUtf8("autoMeasureFlag"));

        gridLayout_9->addWidget(autoMeasureFlag, 0, 0, 1, 1);

        autoMeasureInc = new QRadioButton(groupBox_8);
        autoMeasureInc->setObjectName(QString::fromUtf8("autoMeasureInc"));
        autoMeasureInc->setChecked(true);

        gridLayout_9->addWidget(autoMeasureInc, 1, 0, 1, 1);

        autoMeasureDec = new QRadioButton(groupBox_8);
        autoMeasureDec->setObjectName(QString::fromUtf8("autoMeasureDec"));

        gridLayout_9->addWidget(autoMeasureDec, 2, 0, 1, 1);

        autoMeasureIncVal = new QSpinBox(groupBox_8);
        autoMeasureIncVal->setObjectName(QString::fromUtf8("autoMeasureIncVal"));
        autoMeasureIncVal->setMaximum(127);
        autoMeasureIncVal->setValue(1);

        gridLayout_9->addWidget(autoMeasureIncVal, 1, 1, 1, 1);

        autoMeasureDecVal = new QSpinBox(groupBox_8);
        autoMeasureDecVal->setObjectName(QString::fromUtf8("autoMeasureDecVal"));
        autoMeasureDecVal->setMaximum(127);
        autoMeasureDecVal->setValue(1);

        gridLayout_9->addWidget(autoMeasureDecVal, 2, 1, 1, 1);


        gridLayout_23->addLayout(gridLayout_9, 0, 0, 1, 1);


        gridLayout_22->addWidget(groupBox_8, 0, 0, 1, 1);

        groupBox_10 = new QGroupBox(page_17);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        gridLayout_24 = new QGridLayout(groupBox_10);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_44 = new QLabel(groupBox_10);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        label_44->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_44, 0, 1, 1, 1);

        measureChannel = new QSpinBox(groupBox_10);
        measureChannel->setObjectName(QString::fromUtf8("measureChannel"));
        measureChannel->setMinimum(0);
        measureChannel->setMaximum(128);
        measureChannel->setValue(0);

        gridLayout_8->addWidget(measureChannel, 1, 1, 1, 1);

        measureSetParam = new QPushButton(groupBox_10);
        measureSetParam->setObjectName(QString::fromUtf8("measureSetParam"));

        gridLayout_8->addWidget(measureSetParam, 2, 0, 1, 3);

        label_43 = new QLabel(groupBox_10);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_43, 0, 2, 1, 1);

        label_32 = new QLabel(groupBox_10);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_32, 0, 0, 1, 1);

        spbPhaseAbonentNum = new QSpinBox(groupBox_10);
        spbPhaseAbonentNum->setObjectName(QString::fromUtf8("spbPhaseAbonentNum"));
        spbPhaseAbonentNum->setMinimum(0);
        spbPhaseAbonentNum->setMaximum(255);
        spbPhaseAbonentNum->setValue(0);

        gridLayout_8->addWidget(spbPhaseAbonentNum, 1, 0, 1, 1);

        measurePhaseCode = new QSpinBox(groupBox_10);
        measurePhaseCode->setObjectName(QString::fromUtf8("measurePhaseCode"));
        measurePhaseCode->setMaximum(127);
        measurePhaseCode->setValue(0);

        gridLayout_8->addWidget(measurePhaseCode, 1, 2, 1, 1);


        gridLayout_24->addLayout(gridLayout_8, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_24->addItem(verticalSpacer_2, 1, 0, 1, 1);


        gridLayout_22->addWidget(groupBox_10, 1, 0, 1, 1);

        extTuneBox->addItem(page_17, QString::fromUtf8("\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265 \321\204\320\260\320\267\321\213"));
        page_16 = new QWidget();
        page_16->setObjectName(QString::fromUtf8("page_16"));
        page_16->setGeometry(QRect(0, 0, 469, 427));
        gridLayout_25 = new QGridLayout(page_16);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        groupBox = new QGroupBox(page_16);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_27 = new QGridLayout(groupBox);
        gridLayout_27->setSpacing(6);
        gridLayout_27->setContentsMargins(11, 11, 11, 11);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_48 = new QLabel(groupBox);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        horizontalLayout_5->addWidget(label_48);

        leBeamSetupTimerPeriod = new QLineEdit(groupBox);
        leBeamSetupTimerPeriod->setObjectName(QString::fromUtf8("leBeamSetupTimerPeriod"));

        horizontalLayout_5->addWidget(leBeamSetupTimerPeriod);

        cbBeamSetupTimerOn = new QCheckBox(groupBox);
        cbBeamSetupTimerOn->setObjectName(QString::fromUtf8("cbBeamSetupTimerOn"));

        horizontalLayout_5->addWidget(cbBeamSetupTimerOn);


        gridLayout_27->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_27->addItem(verticalSpacer_3, 1, 0, 1, 1);


        gridLayout_25->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_16 = new QGroupBox(page_16);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        gridLayout_28 = new QGridLayout(groupBox_16);
        gridLayout_28->setSpacing(6);
        gridLayout_28->setContentsMargins(11, 11, 11, 11);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        spbArrayElementSize = new QSpinBox(groupBox_16);
        spbArrayElementSize->setObjectName(QString::fromUtf8("spbArrayElementSize"));
        spbArrayElementSize->setMinimum(1);
        spbArrayElementSize->setMaximum(100);
        spbArrayElementSize->setValue(10);

        gridLayout_28->addWidget(spbArrayElementSize, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_28->addItem(verticalSpacer_4, 1, 0, 1, 1);


        gridLayout_25->addWidget(groupBox_16, 1, 1, 1, 1);

        groupBox_15 = new QGroupBox(page_16);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        gridLayout_26 = new QGridLayout(groupBox_15);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_47 = new QLabel(groupBox_15);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_47, 0, 1, 1, 1);

        label_46 = new QLabel(groupBox_15);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(label_46, 0, 0, 1, 1);

        spbNewAddress = new QSpinBox(groupBox_15);
        spbNewAddress->setObjectName(QString::fromUtf8("spbNewAddress"));
        spbNewAddress->setMinimum(1);
        spbNewAddress->setMaximum(255);

        gridLayout_10->addWidget(spbNewAddress, 1, 1, 1, 1);

        leVendorID = new QLineEdit(groupBox_15);
        leVendorID->setObjectName(QString::fromUtf8("leVendorID"));

        gridLayout_10->addWidget(leVendorID, 1, 0, 1, 1);


        gridLayout_26->addLayout(gridLayout_10, 0, 0, 1, 1);

        btnNewModuleSettings = new QPushButton(groupBox_15);
        btnNewModuleSettings->setObjectName(QString::fromUtf8("btnNewModuleSettings"));

        gridLayout_26->addWidget(btnNewModuleSettings, 1, 0, 1, 1);


        gridLayout_25->addWidget(groupBox_15, 0, 0, 1, 2);

        extTuneBox->addItem(page_16, QString::fromUtf8("\320\227\320\260\320\277\320\270\321\201\321\214 \320\267\320\260\320\262\320\276\320\264\321\201\320\272\320\270\321\205 \320\275\320\276\320\274\320\265\321\200\320\276\320\262 \320\270 \320\260\320\264\321\200\320\265\321\201\320\276\320\262"));

        gridLayout_14->addWidget(extTuneBox, 0, 0, 1, 1);


        gridLayout_21->addWidget(groupBox_9, 0, 1, 3, 1);

        toolBox->addItem(page, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\273\321\203\321\207\320\276\320\274"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 426, 217));
        gridLayout_31 = new QGridLayout(page_3);
        gridLayout_31->setSpacing(6);
        gridLayout_31->setContentsMargins(11, 11, 11, 11);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        gbFlashData = new QGroupBox(page_3);
        gbFlashData->setObjectName(QString::fromUtf8("gbFlashData"));
        gbFlashData->setMinimumSize(QSize(0, 0));
        gridLayout_33 = new QGridLayout(gbFlashData);
        gridLayout_33->setSpacing(6);
        gridLayout_33->setContentsMargins(11, 11, 11, 11);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        sul_flash_layout = new QVBoxLayout();
        sul_flash_layout->setSpacing(6);
        sul_flash_layout->setObjectName(QString::fromUtf8("sul_flash_layout"));

        gridLayout_33->addLayout(sul_flash_layout, 0, 0, 1, 1);


        gridLayout_31->addWidget(gbFlashData, 0, 0, 1, 1);

        groupBox_21 = new QGroupBox(page_3);
        groupBox_21->setObjectName(QString::fromUtf8("groupBox_21"));
        gridLayout_32 = new QGridLayout(groupBox_21);
        gridLayout_32->setSpacing(6);
        gridLayout_32->setContentsMargins(11, 11, 11, 11);
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_27 = new QLabel(groupBox_21);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setAlignment(Qt::AlignCenter);
        label_27->setWordWrap(true);

        gridLayout_5->addWidget(label_27, 2, 2, 1, 1);

        btnFlashSave = new QPushButton(groupBox_21);
        btnFlashSave->setObjectName(QString::fromUtf8("btnFlashSave"));

        gridLayout_5->addWidget(btnFlashSave, 2, 1, 1, 1);

        label_30 = new QLabel(groupBox_21);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_30, 0, 0, 1, 2);

        lblFileCRC = new QLabel(groupBox_21);
        lblFileCRC->setObjectName(QString::fromUtf8("lblFileCRC"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        lblFileCRC->setFont(font);
        lblFileCRC->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lblFileCRC, 2, 3, 1, 1);

        label_25 = new QLabel(groupBox_21);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignCenter);
        label_25->setWordWrap(true);

        gridLayout_5->addWidget(label_25, 1, 2, 1, 1);

        label_33 = new QLabel(groupBox_21);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_33, 1, 4, 1, 1);

        label_29 = new QLabel(groupBox_21);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_29, 0, 4, 1, 2);

        label_22 = new QLabel(groupBox_21);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_22, 2, 4, 1, 1);

        lblHwCRC = new QLabel(groupBox_21);
        lblHwCRC->setObjectName(QString::fromUtf8("lblHwCRC"));
        lblHwCRC->setFont(font);
        lblHwCRC->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lblHwCRC, 1, 3, 1, 1);

        btnFlashLoad = new QPushButton(groupBox_21);
        btnFlashLoad->setObjectName(QString::fromUtf8("btnFlashLoad"));

        gridLayout_5->addWidget(btnFlashLoad, 2, 0, 1, 1);

        btnFlashErase = new QPushButton(groupBox_21);
        btnFlashErase->setObjectName(QString::fromUtf8("btnFlashErase"));

        gridLayout_5->addWidget(btnFlashErase, 1, 1, 1, 1);

        label_24 = new QLabel(groupBox_21);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_24, 0, 2, 1, 2);

        btnFlashFileOpen = new QPushButton(groupBox_21);
        btnFlashFileOpen->setObjectName(QString::fromUtf8("btnFlashFileOpen"));

        gridLayout_5->addWidget(btnFlashFileOpen, 1, 0, 1, 1);

        cbFlashSegmentName = new QComboBox(groupBox_21);
        cbFlashSegmentName->setObjectName(QString::fromUtf8("cbFlashSegmentName"));

        gridLayout_5->addWidget(cbFlashSegmentName, 2, 5, 1, 1);

        spbFlashAbonentNumber = new QSpinBox(groupBox_21);
        spbFlashAbonentNumber->setObjectName(QString::fromUtf8("spbFlashAbonentNumber"));
        spbFlashAbonentNumber->setMinimum(0);
        spbFlashAbonentNumber->setMaximum(0);
        spbFlashAbonentNumber->setValue(0);

        gridLayout_5->addWidget(spbFlashAbonentNumber, 1, 5, 1, 1);


        gridLayout_32->addLayout(gridLayout_5, 0, 0, 1, 1);


        gridLayout_31->addWidget(groupBox_21, 1, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_31->addItem(verticalSpacer_8, 2, 0, 1, 1);

        toolBox->addItem(page_3, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 flash"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 668, 187));
        gridLayout_34 = new QGridLayout(page_4);
        gridLayout_34->setSpacing(6);
        gridLayout_34->setContentsMargins(11, 11, 11, 11);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        gbRamData = new QGroupBox(page_4);
        gbRamData->setObjectName(QString::fromUtf8("gbRamData"));
        gridLayout_35 = new QGridLayout(gbRamData);
        gridLayout_35->setSpacing(6);
        gridLayout_35->setContentsMargins(11, 11, 11, 11);
        gridLayout_35->setObjectName(QString::fromUtf8("gridLayout_35"));
        sul_ram_layout = new QVBoxLayout();
        sul_ram_layout->setSpacing(6);
        sul_ram_layout->setObjectName(QString::fromUtf8("sul_ram_layout"));

        gridLayout_35->addLayout(sul_ram_layout, 0, 0, 1, 1);


        gridLayout_34->addWidget(gbRamData, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(page_4);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_36 = new QGridLayout(groupBox_7);
        gridLayout_36->setSpacing(6);
        gridLayout_36->setContentsMargins(11, 11, 11, 11);
        gridLayout_36->setObjectName(QString::fromUtf8("gridLayout_36"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        btnRamSaveAll = new QPushButton(groupBox_7);
        btnRamSaveAll->setObjectName(QString::fromUtf8("btnRamSaveAll"));

        gridLayout_4->addWidget(btnRamSaveAll, 2, 1, 1, 1);

        rbtFillRamPattern = new QRadioButton(groupBox_7);
        rbtFillRamPattern->setObjectName(QString::fromUtf8("rbtFillRamPattern"));

        gridLayout_4->addWidget(rbtFillRamPattern, 1, 2, 1, 1);

        rbtFillRamRandom = new QRadioButton(groupBox_7);
        rbtFillRamRandom->setObjectName(QString::fromUtf8("rbtFillRamRandom"));
        rbtFillRamRandom->setChecked(true);

        gridLayout_4->addWidget(rbtFillRamRandom, 1, 3, 1, 1);

        patternFixValue = new QSpinBox(groupBox_7);
        patternFixValue->setObjectName(QString::fromUtf8("patternFixValue"));
        patternFixValue->setMaximum(255);

        gridLayout_4->addWidget(patternFixValue, 2, 2, 1, 1);

        label_16 = new QLabel(groupBox_7);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_16, 1, 5, 1, 1);

        spbRamStepValue = new QSpinBox(groupBox_7);
        spbRamStepValue->setObjectName(QString::fromUtf8("spbRamStepValue"));
        spbRamStepValue->setMinimum(1);
        spbRamStepValue->setMaximum(31);

        gridLayout_4->addWidget(spbRamStepValue, 2, 5, 1, 1);

        btnIncRamValue = new QPushButton(groupBox_7);
        btnIncRamValue->setObjectName(QString::fromUtf8("btnIncRamValue"));

        gridLayout_4->addWidget(btnIncRamValue, 1, 6, 1, 1);

        btnDecRamValue = new QPushButton(groupBox_7);
        btnDecRamValue->setObjectName(QString::fromUtf8("btnDecRamValue"));

        gridLayout_4->addWidget(btnDecRamValue, 2, 6, 1, 1);

        label_35 = new QLabel(groupBox_7);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_35, 1, 7, 1, 1);

        spbRamAbonentNumber = new QSpinBox(groupBox_7);
        spbRamAbonentNumber->setObjectName(QString::fromUtf8("spbRamAbonentNumber"));
        spbRamAbonentNumber->setMinimum(0);
        spbRamAbonentNumber->setMaximum(0);

        gridLayout_4->addWidget(spbRamAbonentNumber, 2, 7, 1, 1);

        label_36 = new QLabel(groupBox_7);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_36, 0, 7, 1, 1);

        label_31 = new QLabel(groupBox_7);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_31, 0, 5, 1, 2);

        label_34 = new QLabel(groupBox_7);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_34, 0, 2, 1, 2);

        btnRamErase = new QPushButton(groupBox_7);
        btnRamErase->setObjectName(QString::fromUtf8("btnRamErase"));

        gridLayout_4->addWidget(btnRamErase, 0, 1, 1, 1);

        btnSaveAbonentRamFile = new QPushButton(groupBox_7);
        btnSaveAbonentRamFile->setObjectName(QString::fromUtf8("btnSaveAbonentRamFile"));

        gridLayout_4->addWidget(btnSaveAbonentRamFile, 1, 1, 1, 1);

        rbtFillRamFlash = new QRadioButton(groupBox_7);
        rbtFillRamFlash->setObjectName(QString::fromUtf8("rbtFillRamFlash"));

        gridLayout_4->addWidget(rbtFillRamFlash, 1, 4, 1, 1);

        btnFillRam = new QPushButton(groupBox_7);
        btnFillRam->setObjectName(QString::fromUtf8("btnFillRam"));

        gridLayout_4->addWidget(btnFillRam, 2, 4, 1, 1);

        patternRndValue = new QSpinBox(groupBox_7);
        patternRndValue->setObjectName(QString::fromUtf8("patternRndValue"));
        patternRndValue->setMaximum(255);
        patternRndValue->setValue(127);

        gridLayout_4->addWidget(patternRndValue, 2, 3, 1, 1);

        cbUpdateRamAll = new QCheckBox(groupBox_7);
        cbUpdateRamAll->setObjectName(QString::fromUtf8("cbUpdateRamAll"));
        cbUpdateRamAll->setEnabled(true);

        gridLayout_4->addWidget(cbUpdateRamAll, 0, 4, 1, 1);

        btnRamLoadAll = new QPushButton(groupBox_7);
        btnRamLoadAll->setObjectName(QString::fromUtf8("btnRamLoadAll"));

        gridLayout_4->addWidget(btnRamLoadAll, 2, 0, 1, 1);

        btnRamOpen = new QPushButton(groupBox_7);
        btnRamOpen->setObjectName(QString::fromUtf8("btnRamOpen"));

        gridLayout_4->addWidget(btnRamOpen, 1, 0, 1, 1);

        btnReadAbonentRamFile = new QPushButton(groupBox_7);
        btnReadAbonentRamFile->setObjectName(QString::fromUtf8("btnReadAbonentRamFile"));

        gridLayout_4->addWidget(btnReadAbonentRamFile, 0, 0, 1, 1);


        gridLayout_36->addLayout(gridLayout_4, 0, 0, 1, 1);


        gridLayout_34->addWidget(groupBox_7, 2, 0, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_34->addItem(verticalSpacer_10, 1, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_34->addItem(verticalSpacer_9, 3, 0, 1, 1);

        toolBox->addItem(page_4, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 ram"));
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setGeometry(QRect(0, 0, 1002, 559));
        gridLayout_37 = new QGridLayout(page_5);
        gridLayout_37->setSpacing(6);
        gridLayout_37->setContentsMargins(11, 11, 11, 11);
        gridLayout_37->setObjectName(QString::fromUtf8("gridLayout_37"));
        groupBox_17 = new QGroupBox(page_5);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        gridLayout_38 = new QGridLayout(groupBox_17);
        gridLayout_38->setSpacing(6);
        gridLayout_38->setContentsMargins(11, 11, 11, 11);
        gridLayout_38->setObjectName(QString::fromUtf8("gridLayout_38"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_8 = new QLabel(groupBox_17);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_6->addWidget(label_8);

        abonentIndex = new QSpinBox(groupBox_17);
        abonentIndex->setObjectName(QString::fromUtf8("abonentIndex"));
        abonentIndex->setMinimum(0);
        abonentIndex->setMaximum(255);

        verticalLayout_6->addWidget(abonentIndex);

        label_12 = new QLabel(groupBox_17);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_6->addWidget(label_12);

        abonentCmd = new QComboBox(groupBox_17);
        abonentCmd->setObjectName(QString::fromUtf8("abonentCmd"));

        verticalLayout_6->addWidget(abonentCmd);

        label_17 = new QLabel(groupBox_17);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        verticalLayout_6->addWidget(label_17);

        msgBlockNum = new QSpinBox(groupBox_17);
        msgBlockNum->setObjectName(QString::fromUtf8("msgBlockNum"));
        msgBlockNum->setMinimum(0);
        msgBlockNum->setMaximum(16);
        msgBlockNum->setValue(0);

        verticalLayout_6->addWidget(msgBlockNum);

        label_18 = new QLabel(groupBox_17);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        verticalLayout_6->addWidget(label_18);

        msgBlockSize = new QSpinBox(groupBox_17);
        msgBlockSize->setObjectName(QString::fromUtf8("msgBlockSize"));
        msgBlockSize->setMinimum(0);
        msgBlockSize->setMaximum(128);
        msgBlockSize->setValue(128);

        verticalLayout_6->addWidget(msgBlockSize);

        label_20 = new QLabel(groupBox_17);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        verticalLayout_6->addWidget(label_20);

        dbgPeriod = new QSpinBox(groupBox_17);
        dbgPeriod->setObjectName(QString::fromUtf8("dbgPeriod"));
        dbgPeriod->setMaximum(5000);
        dbgPeriod->setSingleStep(10);
        dbgPeriod->setValue(0);

        verticalLayout_6->addWidget(dbgPeriod);

        btnSend = new QPushButton(groupBox_17);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setCheckable(true);

        verticalLayout_6->addWidget(btnSend);

        btnShowView = new QPushButton(groupBox_17);
        btnShowView->setObjectName(QString::fromUtf8("btnShowView"));
        btnShowView->setCheckable(false);

        verticalLayout_6->addWidget(btnShowView);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_11);


        gridLayout_38->addLayout(verticalLayout_6, 0, 0, 1, 1);


        gridLayout_37->addWidget(groupBox_17, 0, 0, 1, 1);

        groupBox_12 = new QGroupBox(page_5);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        gridLayout_39 = new QGridLayout(groupBox_12);
        gridLayout_39->setSpacing(6);
        gridLayout_39->setContentsMargins(11, 11, 11, 11);
        gridLayout_39->setObjectName(QString::fromUtf8("gridLayout_39"));
        headerLayout = new QVBoxLayout();
        headerLayout->setSpacing(6);
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));

        gridLayout_39->addLayout(headerLayout, 0, 0, 1, 1);


        gridLayout_37->addWidget(groupBox_12, 0, 1, 1, 1);

        groupBox_13 = new QGroupBox(page_5);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        gridLayout_40 = new QGridLayout(groupBox_13);
        gridLayout_40->setSpacing(6);
        gridLayout_40->setContentsMargins(11, 11, 11, 11);
        gridLayout_40->setObjectName(QString::fromUtf8("gridLayout_40"));
        dataOutLayout = new QVBoxLayout();
        dataOutLayout->setSpacing(6);
        dataOutLayout->setObjectName(QString::fromUtf8("dataOutLayout"));

        gridLayout_40->addLayout(dataOutLayout, 0, 0, 1, 1);


        gridLayout_37->addWidget(groupBox_13, 0, 2, 1, 1);

        groupBox_14 = new QGroupBox(page_5);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        gridLayout_41 = new QGridLayout(groupBox_14);
        gridLayout_41->setSpacing(6);
        gridLayout_41->setContentsMargins(11, 11, 11, 11);
        gridLayout_41->setObjectName(QString::fromUtf8("gridLayout_41"));
        dataInLayout = new QVBoxLayout();
        dataInLayout->setSpacing(6);
        dataInLayout->setObjectName(QString::fromUtf8("dataInLayout"));

        gridLayout_41->addLayout(dataInLayout, 0, 0, 1, 1);


        gridLayout_37->addWidget(groupBox_14, 0, 3, 1, 1);

        toolBox->addItem(page_5, QString::fromUtf8(" \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260\320\274\320\270"));

        verticalLayout->addWidget(toolBox);


        gridLayout_13->addLayout(verticalLayout, 0, 0, 1, 2);

        groupBox_11 = new QGroupBox(sul_monitorClass);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        gridLayout_12 = new QGridLayout(groupBox_11);
        gridLayout_12->setSpacing(2);
        gridLayout_12->setContentsMargins(2, 2, 2, 2);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(5);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnDraw = new QPushButton(groupBox_11);
        btnDraw->setObjectName(QString::fromUtf8("btnDraw"));

        gridLayout_2->addWidget(btnDraw, 0, 0, 1, 1);

        label_14 = new QLabel(groupBox_11);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_14, 0, 4, 1, 2);

        label_10 = new QLabel(groupBox_11);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox_11);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_15, 0, 2, 1, 1);

        label_21 = new QLabel(groupBox_11);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_21, 0, 3, 1, 1);

        spbLowLevel = new QSpinBox(groupBox_11);
        spbLowLevel->setObjectName(QString::fromUtf8("spbLowLevel"));
        spbLowLevel->setMinimum(0);
        spbLowLevel->setMaximum(255);
        spbLowLevel->setValue(60);

        gridLayout_2->addWidget(spbLowLevel, 1, 5, 1, 1);

        spbTopLevel = new QSpinBox(groupBox_11);
        spbTopLevel->setObjectName(QString::fromUtf8("spbTopLevel"));
        spbTopLevel->setMaximum(255);
        spbTopLevel->setValue(80);

        gridLayout_2->addWidget(spbTopLevel, 1, 4, 1, 1);

        spbPauseDuration = new QSpinBox(groupBox_11);
        spbPauseDuration->setObjectName(QString::fromUtf8("spbPauseDuration"));
        spbPauseDuration->setMinimum(0);
        spbPauseDuration->setMaximum(100);
        spbPauseDuration->setValue(50);

        gridLayout_2->addWidget(spbPauseDuration, 1, 3, 1, 1);

        spbResetDuration = new QSpinBox(groupBox_11);
        spbResetDuration->setObjectName(QString::fromUtf8("spbResetDuration"));
        spbResetDuration->setMinimum(0);
        spbResetDuration->setMaximum(100);
        spbResetDuration->setValue(32);

        gridLayout_2->addWidget(spbResetDuration, 1, 2, 1, 1);

        spbScaleValue = new QSpinBox(groupBox_11);
        spbScaleValue->setObjectName(QString::fromUtf8("spbScaleValue"));
        spbScaleValue->setMinimum(1);
        spbScaleValue->setMaximum(20);
        spbScaleValue->setValue(6);

        gridLayout_2->addWidget(spbScaleValue, 1, 1, 1, 1);

        btnSetScaleFlash = new QPushButton(groupBox_11);
        btnSetScaleFlash->setObjectName(QString::fromUtf8("btnSetScaleFlash"));

        gridLayout_2->addWidget(btnSetScaleFlash, 2, 2, 1, 2);

        btnSetScaleRam = new QPushButton(groupBox_11);
        btnSetScaleRam->setObjectName(QString::fromUtf8("btnSetScaleRam"));

        gridLayout_2->addWidget(btnSetScaleRam, 2, 4, 1, 2);

        btnGridArray = new QPushButton(groupBox_11);
        btnGridArray->setObjectName(QString::fromUtf8("btnGridArray"));

        gridLayout_2->addWidget(btnGridArray, 1, 0, 1, 1);

        pbInterfaceUpdate = new QPushButton(groupBox_11);
        pbInterfaceUpdate->setObjectName(QString::fromUtf8("pbInterfaceUpdate"));

        gridLayout_2->addWidget(pbInterfaceUpdate, 2, 0, 1, 1);

        pbDebug = new QPushButton(groupBox_11);
        pbDebug->setObjectName(QString::fromUtf8("pbDebug"));
        pbDebug->setCheckable(true);

        gridLayout_2->addWidget(pbDebug, 2, 1, 1, 1);


        gridLayout_12->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBox_11, 1, 0, 1, 1);

        groupBox_19 = new QGroupBox(sul_monitorClass);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        groupBox_19->setMaximumSize(QSize(300, 16777215));
        gridLayout_11 = new QGridLayout(groupBox_19);
        gridLayout_11->setSpacing(2);
        gridLayout_11->setContentsMargins(2, 2, 2, 2);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(5);
        gridLayout_3->setVerticalSpacing(6);
        label_49 = new QLabel(groupBox_19);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_49, 0, 0, 1, 1);

        label_50 = new QLabel(groupBox_19);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_50, 0, 1, 1, 1);

        lbAbonentAddr = new QLabel(groupBox_19);
        lbAbonentAddr->setObjectName(QString::fromUtf8("lbAbonentAddr"));
        lbAbonentAddr->setEnabled(true);
        lbAbonentAddr->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbAbonentAddr, 1, 1, 1, 1);

        lbActiveAbonents = new QLabel(groupBox_19);
        lbActiveAbonents->setObjectName(QString::fromUtf8("lbActiveAbonents"));
        lbActiveAbonents->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbActiveAbonents, 2, 1, 1, 1);

        spbAbonentIndex = new QSpinBox(groupBox_19);
        spbAbonentIndex->setObjectName(QString::fromUtf8("spbAbonentIndex"));
        spbAbonentIndex->setEnabled(true);
        spbAbonentIndex->setMinimum(0);
        spbAbonentIndex->setMaximum(0);

        gridLayout_3->addWidget(spbAbonentIndex, 1, 0, 1, 1);

        pbRescanModule = new QPushButton(groupBox_19);
        pbRescanModule->setObjectName(QString::fromUtf8("pbRescanModule"));

        gridLayout_3->addWidget(pbRescanModule, 2, 0, 1, 1);

        lbCPUVer = new QLabel(groupBox_19);
        lbCPUVer->setObjectName(QString::fromUtf8("lbCPUVer"));

        gridLayout_3->addWidget(lbCPUVer, 1, 2, 1, 1);

        label_26 = new QLabel(groupBox_19);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_26, 0, 2, 1, 1);

        lbFPGAVer = new QLabel(groupBox_19);
        lbFPGAVer->setObjectName(QString::fromUtf8("lbFPGAVer"));

        gridLayout_3->addWidget(lbFPGAVer, 2, 2, 1, 1);


        gridLayout_11->addLayout(gridLayout_3, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBox_19, 1, 1, 1, 1);

        barLayout = new QHBoxLayout();
        barLayout->setSpacing(6);
        barLayout->setObjectName(QString::fromUtf8("barLayout"));

        gridLayout_13->addLayout(barLayout, 2, 0, 1, 2);


        retranslateUi(sul_monitorClass);

        toolBox->setCurrentIndex(0);
        extTuneBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(sul_monitorClass);
    } // setupUi

    void retranslateUi(QWidget *sul_monitorClass)
    {
        sul_monitorClass->setWindowTitle(QApplication::translate("sul_monitorClass", "sul_monitor", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("sul_monitorClass", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 X", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\320\260 Y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\270\320\276\320\264, \320\274\321\201", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("sul_monitorClass", "\320\250\320\260\320\263", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        btnSetBeam->setText(QApplication::translate("sul_monitorClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("sul_monitorClass", "\320\223\321\200\320\260\320\275\320\270\321\206\320\260, \302\260", 0, QApplication::UnicodeUTF8));
        label_42->setText(QApplication::translate("sul_monitorClass", "\320\236\320\261\320\273\320\260\321\201\321\202\321\214, \302\260", 0, QApplication::UnicodeUTF8));
        cbTrackMode->setText(QApplication::translate("sul_monitorClass", "\320\241\320\273\320\265\320\264\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cbSphere->setText(QApplication::translate("sul_monitorClass", "\320\241\321\204\320\265\321\200\320\260", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("sul_monitorClass", "\320\236\321\201\321\214 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        rbtAxisX->setText(QApplication::translate("sul_monitorClass", "X", 0, QApplication::UnicodeUTF8));
        rbtAxisY->setText(QApplication::translate("sul_monitorClass", "Y", 0, QApplication::UnicodeUTF8));
        rbtAxisXY->setText(QApplication::translate("sul_monitorClass", "XY", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\263\320\276\320\273 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217, \302\260", 0, QApplication::UnicodeUTF8));
        groupBox_18->setTitle(QApplication::translate("sul_monitorClass", "\320\227\320\276\320\275\320\260", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("sul_monitorClass", "\320\242\320\265\320\272\321\203\321\211\320\270\320\265 \320\272\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("sul_monitorClass", "X:", 0, QApplication::UnicodeUTF8));
        currentX->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\264", 0, QApplication::UnicodeUTF8));
        currentXcode->setText(QApplication::translate("sul_monitorClass", "0x0", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\261\320\265\320\263 \321\204\320\260\320\267\321\213 \302\260", 0, QApplication::UnicodeUTF8));
        phaseIncursionX->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("sul_monitorClass", "Y:", 0, QApplication::UnicodeUTF8));
        currentY->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\264", 0, QApplication::UnicodeUTF8));
        currentYcode->setText(QApplication::translate("sul_monitorClass", "0x0", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\261\320\265\320\263 \321\204\320\260\320\267\321\213 \302\260", 0, QApplication::UnicodeUTF8));
        phaseIncursionY->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\202\321\203\321\201 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("sul_monitorClass", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\260\321\217 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\270\321\201\321\202\320\265\320\274\321\213", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("sul_monitorClass", "\320\244\320\276\320\272\321\203\321\201\320\275\320\276\320\265 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\265, \320\274\320\274", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("sul_monitorClass", "\320\224\320\273\320\270\320\275\320\260 \320\262\320\276\320\273\320\275\321\213, \320\274\320\274", 0, QApplication::UnicodeUTF8));
        pbCalculateCorrectionPhase->setText(QApplication::translate("sul_monitorClass", "\320\240\320\260\321\201\321\207\320\265\321\202", 0, QApplication::UnicodeUTF8));
        pbCorrPhaseSaveToFile->setText(QApplication::translate("sul_monitorClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        pbCorrPhaseLoadToSUL->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\262 \320\241\320\243\320\233", 0, QApplication::UnicodeUTF8));
        label_28->setText(QString());
        cbAddToFile->setText(QApplication::translate("sul_monitorClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203", 0, QApplication::UnicodeUTF8));
        cbUseFi0->setText(QApplication::translate("sul_monitorClass", "\320\243\321\207\320\265\321\202 \320\275\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\271 \321\204\320\260\320\267\321\213", 0, QApplication::UnicodeUTF8));
        extTuneBox->setItemText(extTuneBox->indexOf(page_15), QApplication::translate("sul_monitorClass", " \320\240\320\260\321\201\321\207\320\265\321\202 \320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\270\321\200\321\203\321\216\321\211\320\270\321\205 \320\272\320\276\320\264\320\276\320\262", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("sul_monitorClass", "\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\265 \320\272\320\276\320\264\320\260 \321\204\320\260\320\267\321\213", 0, QApplication::UnicodeUTF8));
        label_45->setText(QApplication::translate("sul_monitorClass", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        autoMeasureFlag->setText(QApplication::translate("sul_monitorClass", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        autoMeasureInc->setText(QApplication::translate("sul_monitorClass", "\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        autoMeasureDec->setText(QApplication::translate("sul_monitorClass", "\320\224\320\265\320\272\321\200\320\265\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("sul_monitorClass", "\320\235\320\276\320\274\320\265\321\200 \320\272\320\260\320\275\320\260\320\273\320\260", 0, QApplication::UnicodeUTF8));
        measureSetParam->setText(QApplication::translate("sul_monitorClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_43->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\264 \321\204\320\260\320\267\321\213", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        extTuneBox->setItemText(extTuneBox->indexOf(page_17), QApplication::translate("sul_monitorClass", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265 \321\204\320\260\320\267\321\213", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("sul_monitorClass", "\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \320\277\320\265\321\200\320\265\321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\273\321\203\321\207\320\260", 0, QApplication::UnicodeUTF8));
        label_48->setText(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\270\320\276\320\264, \320\274\321\201", 0, QApplication::UnicodeUTF8));
        leBeamSetupTimerPeriod->setText(QApplication::translate("sul_monitorClass", "3000", 0, QApplication::UnicodeUTF8));
        cbBeamSetupTimerOn->setText(QApplication::translate("sul_monitorClass", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        groupBox_16->setTitle(QApplication::translate("sul_monitorClass", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\200\320\265\321\210\320\265\321\202\320\272\320\270", 0, QApplication::UnicodeUTF8));
        groupBox_15->setTitle(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\277\320\270\321\201\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 \320\267\320\260\320\262\320\276\320\264\321\201\320\272\320\270\321\205 \320\275\320\276\320\274\320\265\321\200\320\276\320\262 \320\270 \320\260\320\264\321\200\320\265\321\201\320\276\320\262", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\267\320\275\320\260\321\207\320\260\320\265\320\274\321\213\320\271\n"
" \320\260\320\264\321\200\320\265\321\201 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\262\320\276\320\264\321\201\320\272\320\276\320\271 \320\275\320\276\320\274\320\265\321\200 \n"
"\320\274\320\276\320\264\321\203\320\273\321\217", 0, QApplication::UnicodeUTF8));
        leVendorID->setText(QApplication::translate("sul_monitorClass", "0x01010101", 0, QApplication::UnicodeUTF8));
        btnNewModuleSettings->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        extTuneBox->setItemText(extTuneBox->indexOf(page_16), QApplication::translate("sul_monitorClass", "\320\227\320\260\320\277\320\270\321\201\321\214 \320\267\320\260\320\262\320\276\320\264\321\201\320\272\320\270\321\205 \320\275\320\276\320\274\320\265\321\200\320\276\320\262 \320\270 \320\260\320\264\321\200\320\265\321\201\320\276\320\262", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\273\321\203\321\207\320\276\320\274", 0, QApplication::UnicodeUTF8));
        gbFlashData->setTitle(QApplication::translate("sul_monitorClass", "Flash data", 0, QApplication::UnicodeUTF8));
        groupBox_21->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\265\320\271 FLASH", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("sul_monitorClass", "CRC \321\204\320\260\320\271\320\273\320\260:", 0, QApplication::UnicodeUTF8));
        btnFlashSave->setText(QApplication::translate("sul_monitorClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213", 0, QApplication::UnicodeUTF8));
        lblFileCRC->setText(QApplication::translate("sul_monitorClass", "0x0000", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("sul_monitorClass", "CRC \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\276\320\262:", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\262\320\270\320\263\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("sul_monitorClass", "\320\241\320\265\320\263\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        lblHwCRC->setText(QApplication::translate("sul_monitorClass", "0x0000", 0, QApplication::UnicodeUTF8));
        btnFlashLoad->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", 0, QApplication::UnicodeUTF8));
        btnFlashErase->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\270\321\200\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("sul_monitorClass", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        btnFlashFileOpen->setText(QApplication::translate("sul_monitorClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 flash", 0, QApplication::UnicodeUTF8));
        gbRamData->setTitle(QApplication::translate("sul_monitorClass", "RAM data", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("sul_monitorClass", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\265\320\271 RAM", 0, QApplication::UnicodeUTF8));
        btnRamSaveAll->setText(QApplication::translate("sul_monitorClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262\321\201\320\265", 0, QApplication::UnicodeUTF8));
        rbtFillRamPattern->setText(QApplication::translate("sul_monitorClass", "\320\247\320\270\321\201\320\273\320\276\320\262\320\276\320\265", 0, QApplication::UnicodeUTF8));
        rbtFillRamRandom->setText(QApplication::translate("sul_monitorClass", "\320\241\320\273\321\203\321\207\320\260\320\271\320\275\320\276\320\265", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("sul_monitorClass", "\320\250\320\260\320\263", 0, QApplication::UnicodeUTF8));
        btnIncRamValue->setText(QApplication::translate("sul_monitorClass", "\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        btnDecRamValue->setText(QApplication::translate("sul_monitorClass", "\320\224\320\265\320\272\321\200\320\265\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\320\262\320\270\320\263\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("sul_monitorClass", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("sul_monitorClass", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        btnRamErase->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\270\321\200\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        btnSaveAbonentRamFile->setText(QApplication::translate("sul_monitorClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        rbtFillRamFlash->setText(QApplication::translate("sul_monitorClass", "\320\270\320\267 FLASH", 0, QApplication::UnicodeUTF8));
        btnFillRam->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\277\320\276\320\273\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cbUpdateRamAll->setText(QApplication::translate("sul_monitorClass", "\320\262\321\201\320\265\320\274 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260\320\274", 0, QApplication::UnicodeUTF8));
        btnRamLoadAll->setText(QApplication::translate("sul_monitorClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\262\321\201\320\265", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnRamOpen->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        btnRamOpen->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        btnRamOpen->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        btnRamOpen->setText(QApplication::translate("sul_monitorClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnReadAbonentRamFile->setText(QApplication::translate("sul_monitorClass", "\320\237\321\200\320\276\321\207\320\270\321\202\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 ram", 0, QApplication::UnicodeUTF8));
        groupBox_17->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\321\213 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("sul_monitorClass", "\320\242\320\270\320\277 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("sul_monitorClass", "\320\235\320\276\320\274\320\265\321\200 \320\261\320\273\320\276\320\272\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\260\320\271\321\202 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\270\320\276\320\264 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271, \320\274\321\201", 0, QApplication::UnicodeUTF8));
        btnSend->setText(QApplication::translate("sul_monitorClass", "\320\241\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        btnShowView->setText(QApplication::translate("sul_monitorClass", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        groupBox_12->setTitle(QApplication::translate("sul_monitorClass", "\320\232\320\276\320\274\320\260\320\275\320\264\320\275\321\213\320\271 \320\261\320\273\320\276\320\272", 0, QApplication::UnicodeUTF8));
        groupBox_13->setTitle(QApplication::translate("sul_monitorClass", "\320\237\320\265\321\200\320\265\320\264\320\260\321\207\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        groupBox_14->setTitle(QApplication::translate("sul_monitorClass", "\320\237\321\200\320\270\320\265\320\274 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("sul_monitorClass", " \320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260\320\274\320\270", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("sul_monitorClass", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \321\201\320\270\321\201\321\202\320\265\320\274\320\276\320\271", 0, QApplication::UnicodeUTF8));
        btnDraw->setText(QApplication::translate("sul_monitorClass", "\320\233\321\203\321\207", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("sul_monitorClass", "\320\224\320\270\320\260\320\277\320\260\320\267\320\276\320\275 \320\263\321\200\320\260\320\275\320\270\321\206", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("sul_monitorClass", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("sul_monitorClass", "\320\241\320\261\321\200\320\276\321\201/\320\224\320\276\320\261\320\260\320\262\320\272\320\260, \320\274\320\272\321\201", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("sul_monitorClass", "\320\237\320\260\321\203\320\267\320\260, \320\274\320\272\321\201", 0, QApplication::UnicodeUTF8));
        btnSetScaleFlash->setText(QApplication::translate("sul_monitorClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\270\320\267 FLASH", 0, QApplication::UnicodeUTF8));
        btnSetScaleRam->setText(QApplication::translate("sul_monitorClass", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\270\320\267 RAM", 0, QApplication::UnicodeUTF8));
        btnGridArray->setText(QApplication::translate("sul_monitorClass", "\320\240\320\265\321\210\320\265\321\202\320\272\320\260", 0, QApplication::UnicodeUTF8));
        pbInterfaceUpdate->setText(QApplication::translate("sul_monitorClass", "\320\241\320\262\321\217\320\267\321\214/\320\240\320\265\321\201\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        pbDebug->setText(QApplication::translate("sul_monitorClass", "\320\240\320\265\320\263\320\273\320\260\320\274\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        groupBox_19->setTitle(QApplication::translate("sul_monitorClass", "\320\220\320\272\321\202\320\270\320\262\320\275\321\213\320\265 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label_49->setText(QApplication::translate("sul_monitorClass", "\320\220\320\261\320\276\320\275\320\265\320\275\321\202", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("sul_monitorClass", "\320\220\320\264\321\200\320\265\321\201", 0, QApplication::UnicodeUTF8));
        lbAbonentAddr->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        lbActiveAbonents->setText(QApplication::translate("sul_monitorClass", "0", 0, QApplication::UnicodeUTF8));
        pbRescanModule->setText(QApplication::translate("sul_monitorClass", "\320\237\320\276\320\270\321\201\320\272", 0, QApplication::UnicodeUTF8));
        lbCPUVer->setText(QString());
        label_26->setText(QApplication::translate("sul_monitorClass", "\320\222\320\265\321\200\321\201\320\270\321\217", 0, QApplication::UnicodeUTF8));
        lbFPGAVer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sul_monitorClass: public Ui_sul_monitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUL_MONITOR_H
