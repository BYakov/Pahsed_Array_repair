#include "grid_array.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

grid_array::grid_array(sul_base *Sul, QWidget *parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
    setWindowTitle(tr("Антенная решетка"));

    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);

    sul = Sul;

    int N = sul->sul_total_channels();

    x = new u8[N];
    y = new u8[N];
    R = new float[N];

    memset(x,0,N);
    memset(y,0,N);
    memset(R,0,N);

    maxX = 1;
    maxY = 1;
    Rmax = 1;

    // заполним координаты для быстрого поиска
    float x0 = 0;
    float y0 = 0;
    float xc = 0;
    float yc = 0;

    for(int i=0; i<N; i++) {

        sul->sul_flash_get_element(9,0,i,x[i]);
        sul->sul_flash_get_element(10,0,i,y[i]);

        if(x[i] > maxX) maxX = x[i];
        if(y[i] > maxY) maxY = y[i];
    }

    xc = maxX/2.0;
    yc = maxY/2.0;

    for(int i=0; i<N; i++) {

        x0 = (x[i]-xc)*7.2;
        y0 = (y[i]-yc)*4.5;
        R[i]  = sqrt(x0*x0 + y0*y0);

        if(R[i] > Rmax) { Rmax = R[i]; }
    }


    cS = 1;

    memset(&shifter, 0, sizeof(struct phase_shifter));
    Radius = 20;
    abonent = 1;
    type = processing_grids;
    fi0 = false;
}

//---------------------------------------------------------------------------------------

grid_array::~grid_array()
{
    close();

    if(x) delete [] x;
    if(y) delete [] y;
    if(R) delete [] R;
}

//---------------------------------------------------------------------------------------

void grid_array::paint_grid(QPaintEvent *event)
{
    float ScaleX = 0;
    float ScaleY = 0;

    //перерасчет масштабного коэффициента
    cS = 255.0/Rmax;

    float w = geometry().width()-3.0*Radius;
    float h = geometry().height()-3.0*Radius;

    ScaleX = w/maxX;
    ScaleY = h/maxY;

    QPainter p(this);
    QLinearGradient g(2.0*geometry().width(),geometry().height(),0,0);
    g.setSpread(QGradient::ReflectSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));

    for(int i=0; i<sul->sul_total_channels(); i++) {

        if((x[i] == 0) && (y[i] == 0))
            continue;

        if(sul->sul_phase_shifter_info(i,shifter) < 0)
            continue;

        //заполнение зеленым цветом
        QColor c;
        QBrush b(c.fromRgb(0,255.0-R[i]*cS,0));
        p.setBrush(b);
        p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
    }
}

//---------------------------------------------------------------------------------------

void grid_array::paint_grid_channels(QPaintEvent *event)
{
    float ScaleX = 0;
    float ScaleY = 0;

    float w = geometry().width()-3.0*Radius;
    float h = geometry().height()-3.0*Radius;

    ScaleX = w/maxX;
    ScaleY = h/maxY;

    QPainter p(this);
    QLinearGradient g(2.0*geometry().width(),geometry().height(),0,0);
    g.setSpread(QGradient::ReflectSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));

    for(int i=0; i<sul->sul_total_channels(); i++) {

        if((x[i] == 0) && (y[i] == 0))
            continue;

        if(sul->sul_phase_shifter_info(i,shifter) < 0)
            continue;

        switch(shifter.state) {
        case channel_operational: {
                QBrush b(Qt::green);
                p.setBrush(b);
                p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
            } break;
        case channel_open_fault: {
                QBrush b(Qt::red);
                p.setBrush(b);
                p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
            } break;
        case channel_short_circuit: {
                QBrush b(Qt::blue);
                p.setBrush(b);
                p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
            } break;
        case channel_untested:
        case channel_unconnected: {
                QBrush b(Qt::gray);
                p.setBrush(b);
                p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
            } break;
        }
    }
}

//---------------------------------------------------------------------------------------

void grid_array::paint_grid_calculators(QPaintEvent *event)
{
    float ScaleX = 0;
    float ScaleY = 0;

    float w = geometry().width()-3.0*Radius;
    float h = geometry().height()-3.0*Radius;

    ScaleX = w/maxX;
    ScaleY = h/maxY;

    QPainter p(this);
    QLinearGradient g(2.0*geometry().width(),geometry().height(),0,0);
    g.setSpread(QGradient::ReflectSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));

    int code = 0;

    for(int i=0; i<sul->sul_total_channels(); i++) {

        if((x[i] == 0) && (y[i] == 0))
            continue;

        if(sul->sul_phase_shifter_info(i,shifter) < 0)
            continue;

        // fi0 == true - полный код с учетом начальной фазы
	code = fi0 ? shifter.calc_code : shifter.calc_code + shifter.fi0_code;

        //заполнение непрерывным цветом (0 - красный)
        QColor c;
        QBrush b(c.fromHsv(code,255,255));
        p.setBrush(b);
        p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
    }
}

//---------------------------------------------------------------------------------------

void grid_array::paint_grid_phases(QPaintEvent *event)
{
    float ScaleX = 0;
    float ScaleY = 0;

    //перерасчет масштабного коэффициента
    cS = float(359.0/Rmax);

    float w = geometry().width()-3.0*Radius;
    float h = geometry().height()-3.0*Radius;

    ScaleX = w/maxX;
    ScaleY = h/maxY;

    QPainter p(this);
    QLinearGradient g(2.0*geometry().width(),geometry().height(),0,0);
    g.setSpread(QGradient::ReflectSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));

    for(int i=0; i<sul->sul_total_channels(); i++) {

        if((x[i] == 0) && (y[i] == 0))
            continue;

        if(sul->sul_phase_shifter_info(i,shifter) < 0)
            continue;

        //заполнение непрерывным цветом
        QColor c;
	QBrush b(c.fromHsv(shifter.fi0_code,255,255));
        p.setBrush(b);
        p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
    }
}

//---------------------------------------------------------------------------------------

void grid_array::paint_grid_pulses(QPaintEvent *event)
{
    float ScaleX = 0;
    float ScaleY = 0;

    //перерасчет масштабного коэффициента
    cS = float(359.0/Rmax);

    float w = geometry().width()-3.0*Radius;
    float h = geometry().height()-3.0*Radius;

    ScaleX = w/maxX;
    ScaleY = h/maxY;

    QPainter p(this);
    QLinearGradient g(2.0*geometry().width(),geometry().height(),0,0);
    g.setSpread(QGradient::ReflectSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));

    for(int i=0; i<sul->sul_total_channels(); i++) {

	if((x[i] == 0) && (y[i] == 0))
	    continue;

	if(sul->sul_phase_shifter_info(i,shifter) < 0)
	    continue;

	//заполнение непрерывным цветом
	QColor c;
	QBrush b(c.fromHsv(shifter.pulse_code,255,255));
	p.setBrush(b);
	p.drawEllipse(ScaleX*x[i]+Radius,ScaleY*y[i]+Radius,Radius,Radius);
    }
}

//---------------------------------------------------------------------------------------


void grid_array::paintEvent(QPaintEvent *event)
{
    switch(type) {
    case processing_channels: {
            paint_grid_channels(event);
        } break;
    case processing_calculators: {
            paint_grid_calculators(event);
        } break;
    case processing_phases: {
            paint_grid_phases(event);
        } break;
    case processing_grids: {
            paint_grid(event);
        } break;
    case processing_pulses: {
	    paint_grid_pulses(event);
	} break;
    }
}

//---------------------------------------------------------------------------------------

void grid_array::mousePressEvent(QMouseEvent *event)
{
    float w = geometry().width()-3.0*Radius;
    float h = geometry().height()-3.0*Radius;

    float ScaleX = w/maxX;
    float ScaleY = h/maxY;

    int x = (event->x()-Radius)/ScaleX;
    int y = (event->y()-Radius)/ScaleY;

    QString s;

    if(sul->sul_phase_shifter_info(x,y,shifter) < 0) {
        s = tr("Канал не выбран");
        bar->setGeometry(2,geometry().height()-15,geometry().width()-2,15);
        bar->showMessage(s);
        repaint();
        return;
    }

    QString state;

    switch(shifter.state) {
    case channel_operational: {
            state = tr(" исправен");
        } break;
    case channel_open_fault: {
            state = tr(" обрыв");
        } break;
    case channel_short_circuit: {
            state = tr(" замыкание");
        } break;
    case channel_untested:
    case channel_unconnected: {
            state = tr(" ?");
        } break;
    }

    s = tr("Канал: ") + QString::number(shifter.channel_number + 1) +
        tr(", Состояние: ") + state +
        tr(", Линейка: ") + QString::number(shifter.line) +
        tr(", Модуль: ") + QString::number(shifter.abonent + 1) +
	tr(", Соединитель: X") + QString::number(shifter.connector + 1);

    switch(type) {
    case processing_channels:
	s += tr(" код канала: ") + QString::number(shifter.chan_code);
	break;
    case processing_calculators:
	s += tr(" код вычислителя: ") + QString::number(shifter.calc_code);
	break;
    case processing_phases:
	s += tr(" код фазы: ") + QString::number(shifter.fi0_code);
	break;
    case processing_pulses:
	s += tr(" код импульса: ") + QString::number(shifter.pulse_code);
	break;
    case processing_grids:
	s += tr(" x: ") + QString::number(shifter.x);
	s += tr(" y: ") + QString::number(shifter.y);
	break;
    }

    bar->setGeometry(2,geometry().height()-15,geometry().width()-2,15);
    bar->showMessage(s);
    repaint();
}

//---------------------------------------------------------------------------------------

void grid_array::set_abonent_number(int devn)
{
    abonent = devn;
}

//---------------------------------------------------------------------------------------

void grid_array::show_grid()
{
    type = processing_grids;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void grid_array::show_channels()
{
    type = processing_channels;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void grid_array::show_calculators(bool Fi0)
{
   fi0 = Fi0;
   type = processing_calculators;
   show();
   repaint();
}

//---------------------------------------------------------------------------------------

void grid_array::show_pulses()
{
    type = processing_pulses;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------


void grid_array::show_fi0()
{
    type = processing_phases;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------
