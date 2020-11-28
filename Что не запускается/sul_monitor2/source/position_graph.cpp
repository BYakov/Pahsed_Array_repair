#include "position_graph.h"

///////////////////////////////////////////////////////////////////////
//		Класс для рисования положения луча (на плоскости)
///////////////////////////////////////////////////////////////////////

position_graph::position_graph(scanner *s, QWidget *parent, Qt::WindowFlags flags)
: QWidget(parent, flags)
{
        setWindowTitle(tr("Текущие координаты"));
        scan = s;
}

//---------------------------------------------------------------------------------------

position_graph::position_graph(QWidget *parent, Qt::WindowFlags flags)
: QWidget(parent, flags)
{
        setWindowTitle(tr("Текущие координаты"));
        scan = NULL;
}

//---------------------------------------------------------------------------------------

position_graph::~position_graph()
{
}

//---------------------------------------------------------------------------------------

void position_graph::set_scanner(scanner *s)
{
    if((s != scan) && s)
        scan = s;
}

//---------------------------------------------------------------------------------------

void position_graph::repaint()
{
        QWidget::repaint();
        if(!scan) return;
}

//---------------------------------------------------------------------------------------

void position_graph::paintEvent(QPaintEvent *event)
{
        if(!scan) return;

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

void position_graph::mousePressEvent(QMouseEvent *event)
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

    emit new_position(X, Y);

    repaint();
}

//---------------------------------------------------------------------------------------
