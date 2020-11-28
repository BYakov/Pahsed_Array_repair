#include "array_antenna.h"

//-----------------------------------------------------------------------------

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

array_antenna::array_antenna(const std::vector<double>& X, const std::vector<double>& Y, QWidget *parent) :
    QWidget(parent)
{
    std::cout << "array_antenna::array_antenna()" << endl;

    m_param = NULL;
    m_P.clear();
    m_maxX = 0;
    m_maxY = 0;
    m_Radius = 10;
    m_w = 0;
    m_h = 0;
    m_w0 = 0;
    m_h0 = 0;
    m_R0 = 0;
    m_xs = 0;
    m_ys = 0;
    m_dx = 0;
    m_dy = 0;
    memset(&m_channel,0,sizeof(struct channel_t));
    m_channel.entry.N = -1;
    m_pressedX = -1;
    m_pressedY = -1;

    if(X.size() != Y.size()) {
        std::cout << "array_antenna::array_antenna() - invalid vectors size" << endl;
        return;
    }

    for(unsigned i=0; i<X.size(); i++) {

        m_P.push_back(QPointF(X.at(i), Y.at(i)));

        if(X.at(i) > m_maxX)
            m_maxX = X.at(i);

        if(Y.at(i) > m_maxY)
            m_maxY = Y.at(i);
    }

    m_text_show = false;
}

//---------------------------------------------------------------------------------------

array_antenna::~array_antenna()
{
    std::cout << "array_antenna::~array_antenna()" << endl;
    m_P.clear();
}

//---------------------------------------------------------------------------------------

void array_antenna::paintEvent(QPaintEvent *event)
{
    QRectF r = event->rect();
    QPainter p(this);

    paintParamters(p, r);
}

//---------------------------------------------------------------------------------------

void array_antenna::mousePressEvent(QMouseEvent *event)
{
    m_pressedX = (event->x()-m_dx-0.25*m_Radius)/m_xs;
    m_pressedY = (event->y()-m_dy-0.25*m_Radius)/m_ys;

    std::cout << "array_antenna::mousePressEvent(): " << m_pressedX << " , " << m_pressedY << endl;

    emit mousePressed(m_pressedX, m_pressedY, event);
}

//---------------------------------------------------------------------------------------

void array_antenna::elementSizeChange(int newSize)
{
    if(newSize > 0)
        m_Radius = newSize;
    repaint();
}

//---------------------------------------------------------------------------------------

void array_antenna::selectedChannelChange(struct channel_t info)
{
    m_channel = info;
    repaint();
}

//---------------------------------------------------------------------------------------

void array_antenna::paintParamters(QPainter& p, QRectF& r)
{
    m_w = r.width()-2;
    m_h = r.height()-2;
    m_w0 = m_w/2;
    m_h0 = m_h/2;
    m_R0 = min(m_w0,m_h0);
    m_xs = (2*m_R0-m_Radius)/(m_maxX);
    m_ys = (2*m_R0-m_Radius)/(m_maxY);
    m_dx = (m_w0-m_R0);
    m_dy = (m_h0-m_R0);

    p.fillRect(0,0,m_w,m_h,QBrush(QColor(Qt::lightGray)));

    QBrush b(QColor(Qt::gray));
    QBrush b1(QColor(Qt::gray));
    QColor c;

    for(unsigned i=0; i<m_P.size(); i++) {

        if(m_channel.entry.x_grid == m_P.at(i).x() && m_channel.entry.y_grid == m_P.at(i).y()) {
            p.setBrush(b1);
        } else {
            if(m_param) {
                p.setBrush(c.fromHsv(m_param->at(i),255,255));
            } else {
                p.setBrush(b);
            }
        }

        p.drawEllipse(m_dx+(m_P.at(i).x())*m_xs, m_dy+(m_P.at(i).y())*m_ys, m_Radius, m_Radius);
        if(m_param && m_text_show) {

            int x = m_dx+(m_P.at(i).x())*m_xs;
            int y = m_dy+(m_P.at(i).y())*m_ys;

            p.drawText( x, y, m_Radius, m_Radius,
                        Qt::AlignHCenter | Qt::AlignVCenter,
                        QString::number(int(m_param->at(i))));
        }
    }
}

//---------------------------------------------------------------------------------------

void array_antenna::setParameters(std::vector<double> *newParam)
{
    if(!newParam) return;
    if(newParam->empty()) return;

    m_param = newParam;

    repaint();
}

//---------------------------------------------------------------------------------------

QColor array_antenna::xyToColor(int X, int Y)
{
    QColor c;
    return c.fromHsv(((20*Y)%259),255,255);
}

//---------------------------------------------------------------------------------------

void array_antenna::setShowTextFlag(bool flag)
{
    m_text_show = flag;
    repaint();
}

//---------------------------------------------------------------------------------------

void array_antenna::repaintWidget()
{
    repaint();
}
