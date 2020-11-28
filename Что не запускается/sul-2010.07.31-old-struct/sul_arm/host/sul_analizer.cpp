#include "sul_analizer.h"

///////////////////////////////////////////////////////////////////////
//	    Класс для рисования состояния каналов
///////////////////////////////////////////////////////////////////////

data_plot::data_plot(unsigned short *data, QWidget *parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
    setWindowTitle(tr("Анализтор каналов"));
    setWindowIcon(QIcon("icon\\chan_icon.png"));
    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    square_size = 6;
    X = 0;
    N = 0;
    buffer = data;
    bar->showMessage(tr("КУ!"));
}

//----------------------------------------------------------------------------------------------

data_plot::~data_plot()
{
}

//----------------------------------------------------------------------------------------------

void data_plot::paintEvent(QPaintEvent *event)
{
    int size = 128;

    QRectF r = event->rect();

    float w = r.width();
    float h = r.height();
    float xs = w/size;

    QPainter p(this);
    QLinearGradient g(0.7*w,h,0,0);
    g.setSpread(QGradient::ReflectSpread);

    QColor c(Qt::green);
    int val = 0;

    p.fillRect(0,0,w,h,QBrush(g));
    p.setPen(Qt::red);
    c = Qt::green;
    for(int i=0; i<128; i++) {

        val = buffer[i];

        p.fillRect(xs*i,
		   0.9*h-val,
                   square_size,
                   square_size,
                   QBrush(c,Qt::SolidPattern));
    }
}

//----------------------------------------------------------------------------------------------

void data_plot::mousePressEvent(QMouseEvent *event)
{
}

//----------------------------------------------------------------------------------------------

void data_plot::show_data()
{
    show();
    repaint();
}

//----------------------------------------------------------------------------------------------
