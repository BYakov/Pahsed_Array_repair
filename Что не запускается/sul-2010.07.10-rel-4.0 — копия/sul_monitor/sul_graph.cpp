#include "sul_graph.h"

///////////////////////////////////////////////////////////////////////
//		Класс для рисования положения луча (на плоскости)
///////////////////////////////////////////////////////////////////////

sul_graph::sul_graph(scanner *Scan, QWidget *parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
        setWindowTitle(tr("Сканирование лучом"));
        scan = Scan;
        //setFixedSize(geometry().width(),geometry().height());
}

//---------------------------------------------------------------------------------------

sul_graph::~sul_graph()
{
}

//---------------------------------------------------------------------------------------

void sul_graph::repaint()
{
        QWidget::repaint();
        if(!scan) return;
}

//---------------------------------------------------------------------------------------

void sul_graph::paintEvent(QPaintEvent *event)
{
        if(!scan)
                return;

        QRectF r = event->rect();

        float D = 8;
        float R = 0.5*D;

        float w = r.width();
        float h = r.height();
        float w0 = w/2;
        float h0 = h/2;

        float sc = w0/scan->get_rm();
        float xp = w0+sc*scan->get_x();
        float yp = h0-sc*scan->get_y();

        QPainter p(this);
        p.fillRect(0,0,w,h,QBrush(QLinearGradient(0,0,w,h)));
        p.setPen(Qt::black);
        p.drawLine(0,h/2,w,h/2);
        p.drawLine(w/2,0,w/2,h);
        p.drawEllipse(r);
        QBrush b(Qt::green);
        p.setBrush(b);
        p.drawEllipse(xp-R,yp-R,D,D);
}

//---------------------------------------------------------------------------------------

void sul_graph::mousePressEvent(QMouseEvent *event)
{
    float w = geometry().width();
    float h = geometry().height();

    float w0 = w/2;
    float h0 = h/2;

    float x = event->x();
    float y = event->y();

    float ScaleX = w0/scan->get_rm();
    float ScaleY = h0/scan->get_rm();

    float X = (x-w0)/ScaleX;
    float Y = (h0-y)/ScaleY;

    if((X*X + Y*Y) > scan->get_rm()*scan->get_rm())
	return;

    scan->set_x(X);
    scan->set_y(Y);

    emit set_beam_position(X, Y);

    repaint();
}

//---------------------------------------------------------------------------------------
