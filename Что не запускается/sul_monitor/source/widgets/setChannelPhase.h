#ifndef SET_CHANNEL_PHASE_H
#define SET_CHANNEL_PHASE_H

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#else
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#endif
#include <QSettings>


#ifndef _SUL_BASE_H_
    #include "sul_base.h"
#endif
#ifndef SUL_CHANNEL_DATA_H
    #include "sul_channel_data.h"
#endif

class set_channel_phase : public QWidget
{
        Q_OBJECT

private:
        sul_base            *m_sul;
        QLabel              *m_lm;
        QLabel              *m_lc;
        QLabel              *m_lp;
        QSpinBox            *m_spbPhase;
        QPushButton         *m_pbSetup;
        struct channel_t     m_channel;

private slots:
        void setup_phase();

public:
        set_channel_phase(sul_base *system, QWidget *parent = 0, Qt::WindowFlags flags = 0);
        virtual ~set_channel_phase();
        void updateScreen(struct channel_t& channel);

signals:
        void update_phase_image(unsigned char code);
};

#endif // SET_CHANNEL_PHASE_H
