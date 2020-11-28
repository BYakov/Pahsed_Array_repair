#ifndef SET_CHANNEL_PHASE_H
    #include "setChannelPhase.h"
#endif

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

set_channel_phase::set_channel_phase(sul_base *system, QWidget *parent, Qt::WindowFlags flags):
        QWidget(parent,flags)
{
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    m_sul = system;

    QGridLayout *gl = new QGridLayout();

    QLabel *ltmp1 = new QLabel(QString::fromUtf8("Модуль:"));
    m_lm = new QLabel(tr(""));

    QLabel *ltmp2 = new QLabel(QString::fromUtf8("Канал:"));
    m_lc = new QLabel(tr(""));

    QLabel *ltmp3 = new QLabel(QString::fromUtf8("Код фазы:"));
    m_spbPhase = new QSpinBox();
    m_spbPhase->setMinimum(0);
    m_spbPhase->setMaximum(255);

    QLabel *ltmp4 = new QLabel(QString::fromUtf8("Фаза:"));
    m_lp = new QLabel(tr(""));

    m_pbSetup = new QPushButton(QString::fromUtf8("Установить"));

    // отображение основных параметров канала
    gl->addWidget(ltmp1,0,0);
    gl->addWidget(ltmp2,1,0);
    gl->addWidget(ltmp3,2,0);
    gl->addWidget(ltmp4,3,0);

    gl->addWidget(m_lm,0,1);
    gl->addWidget(m_lc,1,1);
    gl->addWidget(m_spbPhase,2,1);
    gl->addWidget(m_lp,3,1);

    gl->addWidget(m_pbSetup,4,0,1,2);

    setLayout(gl);

    connect(m_pbSetup,SIGNAL(clicked()),this,SLOT(setup_phase()));

    std::cout << "set_channel_phase::set_channel_phase()" << std::endl;
}

//-----------------------------------------------------------------------------

set_channel_phase::~set_channel_phase()
{
    std::cout << "set_channel_phase::~set_channel_phase()" << std::endl;
}

//-----------------------------------------------------------------------------

void set_channel_phase::updateScreen(struct channel_t& channel)
{
    m_channel = channel;
    m_lm->setText(QString::number(m_channel.entry.M));
    m_lc->setText(QString::number(m_channel.entry.number_on_module));
    repaint();
}

//-----------------------------------------------------------------------------

void set_channel_phase::setup_phase()
{
    if(!m_sul) return;

    unsigned char data = 0;
    unsigned char phase = m_spbPhase->value();

    int res = m_sul->sul_set_channel_phase(m_channel.entry.M-1,
                                           m_channel.entry.number_on_module,phase,&data);
    if(res < 0) {
        std::cout << "set_channel_phase::setup_phase() - error" << std::endl;
        m_lp->setText(QString::fromUtf8("Ошибка"));
        return;
    }

    std::cout << "data (raw) = " << int(data) << std::endl;

    if(data <= 7) {
        data = 0;
    } else {
        data -= 7;
    }

    std::cout << "data (corr) = " << int(data) << std::endl;

    double scv = 1.0;
    double scale = 1.0;
    double ss[] = { 27.78, 31.75, 35.72 };

    int m_scale = m_sul->sul_get_scale(m_channel.entry.M-1);

    std::cout << "m_scale = " << m_scale << std::endl;

    switch(m_scale) {
        case 6: scv = ss[0];
            break;
        case 7: scv = ss[1];
            break;
        case 8: scv = ss[2];
            break;
        default:
            scv = 27.78;
    }

    scale = 127.0/scv;

    std::cout << "scale = " << scale << std::endl;

    data *= scale;

    std::cout << "data = " << int(data) << std::endl;

    std::cout << "set_channel_phase::setup_phase() - channel phase = " << int(data) << std::endl;
    m_lp->setText(QString::number(int(data)));
    emit update_phase_image(data);
}

//-----------------------------------------------------------------------------
