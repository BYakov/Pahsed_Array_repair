#ifndef ARRAY_ANTENNA_H
#define ARRAY_ANTENNA_H

#include <QPaintEvent>
#include <QPainter>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include "sul_channel_data.h"

//----------------------------------------------------------------------

class array_antenna : public QWidget
{
    Q_OBJECT
public:
    explicit array_antenna(const std::vector<double>& X, const std::vector<double>& Y, QWidget *parent = 0);
    virtual ~array_antenna();

private:
    std::vector<double>         *m_param;
    std::vector<QPointF>        m_P;
    double                      m_maxX;
    double                      m_maxY;
    double                      m_Radius;
    double                      m_w;
    double                      m_h;
    double                      m_w0;
    double                      m_h0;
    double                      m_R0;
    double                      m_xs;
    double                      m_ys;
    double                      m_dx;
    double                      m_dy;
    struct channel_t            m_channel;
    int                         m_pressedX;
    int                         m_pressedY;
    bool                        m_text_show;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintParamters(QPainter& p, QRectF& r);

signals:
    void mousePressed(int X, int Y, QMouseEvent *event);

public slots:
    void elementSizeChange(int newSize);
    void selectedChannelChange(struct channel_t info);
    void setParameters(std::vector<double> *newParam);
    void setShowTextFlag(bool flag);
    QColor xyToColor(int X, int Y);
    void repaintWidget();

};

#endif // ARRAY_ANTENNA_H
