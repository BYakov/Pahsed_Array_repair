
#include "sul_array.h"

using namespace std;

sul_array::sul_array(console& log, sul_base *sul_system,
                     QWidget *parent, Qt::WindowFlags flags)
                   : QWidget(parent, flags), tty(log), sul(sul_system)
{
    R.clear();

    Rmax = 1;
    maxX = 1;
    maxY = 1;
    minX = 0;
    minY = 0;

    X = sul->sul_x_data();
    Y = sul->sul_y_data();

    // заполним координаты дл€ быстрого поиска
    for(int i=0; i < sul->sul_total_channels(); i++) {

        double x = X.at(i);
        double y = Y.at(i);

        if(x > maxX) maxX = x;
        if(y > maxY) maxY = y;
        if(x < minX) minX = x;
        if(y < minY) minY = y;
    }

    cS = 1;
    elementSize = 10;

    if(maxX > maxY) {

        scaleScreenX = (maxY / maxX);
        scaleScreenY = 1.0;

        if(scaleScreenX < 0.6)
            scaleScreenX = 0.6;

    } else {

        scaleScreenY = (maxX / maxY);
        scaleScreenX = 1.0;

        if(scaleScreenY < 0.6)
            scaleScreenY = 0.6;
    }

    colorStep = 5;
    userData_ = NULL;
    legend = new legend_widget(NULL,Qt::Popup);

    tty << "sul_array::sul_array()" <<  "\n";
    tty << "sul_array::N = " << X.size() << "\n";
    tty << "sul_array::maxX = " << maxX << "\n";
    tty << "sul_array::maxY = " << maxY << "\n";
    tty << "sul_array::scaleScreenX = " << scaleScreenX << "\n";
    tty << "sul_array::scaleScreenY = " << scaleScreenY << "\n";
}

//---------------------------------------------------------------------------------------

sul_array::~sul_array()
{
    close();

    R.clear();

    userData_ = NULL;

    if(legend) {
        delete legend;
        legend = NULL;
    }

    tty << "sul_array::~sul_array()" <<  "\n";
}

//---------------------------------------------------------------------------------------

void sul_array::paint_grid(QPaintEvent *event)
{
    int W = (maxX*scaleScreenX + 3)*elementSize;
    int H = (maxY*scaleScreenY + 3)*elementSize;
    int R = sqrt(W*W + H*H);

    QWidget::setGeometry(geometry().x(),geometry().y(),W,H);
    QPainter p(this);
    QRadialGradient g(0.5*geometry().width(),0.5*geometry().height(),R);

    g.setSpread(QGradient::RepeatSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));

    QColor c;


    if(!userData_) {

        int color_step = 720/sul->sul_total_abonents();
        int color = color_step;

        for(int i=0; i<sul->sul_total_channels(); i++) {

            struct channel_info info;

            int res = sul->sul_channel_info(i, info);
            if(res < 0)
                continue;

            //заполнение цветом в зависимости от модул€
            color = ((info.module*color_step)%360 + 1);

            QBrush b1(c.fromHsv(color, 255, 255));

            p.setBrush(b1);
            p.drawEllipse((X[i]+1)*elementSize*scaleScreenX,(Y[i]+1)*elementSize*scaleScreenY,elementSize,elementSize);
        }

    } else {

        for(unsigned i=0; i < userData_->size(); i++) {

            //заполнение цветом в зависимости от значени€ в векторе данных
            if(userData_->at(i) >= 0) {
                QBrush b1(c.fromHsv(userData_->at(i), 255, 255));
                p.setBrush(b1);
            } else {
                QBrush b1(Qt::gray);
                p.setBrush(b1);
            }
            p.drawEllipse((X[i]+1)*elementSize*scaleScreenX,(Y[i]+1)*elementSize*scaleScreenY,elementSize,elementSize);
        }
    }
}

//---------------------------------------------------------------------------------------

void sul_array::paintEvent(QPaintEvent *event)
{
    return paint_grid(event);
}

//---------------------------------------------------------------------------------------

void sul_array::mousePressEvent(QMouseEvent *event)
{
    int x = (event->x()/(scaleScreenX*elementSize)) - 1;
    int y = (event->y()/(scaleScreenY*elementSize)) - 1;

    selectedChannel = -1;

    for(unsigned i=0; i<X.size(); i++) {
        if(X[i] == x) {
            if(Y[i] == y) {
                selectedChannel = i;
            }
        }
    }

    if(selectedChannel < 0)
        return;

    if(legend) {
        if(selectedChannel != -1) {
            legend->updateParam(0,tr(" анал:"),QString::number(selectedChannel));
            if(userData_) {
                legend->updateParam(1,tr("‘аза:"),QString::number(userData_->at(selectedChannel)));
            } else {
                legend->updateParam(1,tr("X: ")+QString::number(x),tr("Y: ")+QString::number(y));
            }
            legend->setGeometry(event->globalX(),
                                event->globalY()+20,
                                legend->geometry().width(),
                                legend->geometry().height());
            legend->show();
            legend->adjustSize();
        }
    }

    tty << x << " , " << y << " selectetChannel " << selectedChannel << "\n";

    repaint();
}

//---------------------------------------------------------------------------------------

void sul_array::setArrayElementSize(int size)
{
    elementSize = size;
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_array::setColorStep(int step)
{
    if(step <= 0)
        colorStep = 5;
    else
        colorStep = step;
}

//---------------------------------------------------------------------------------------

void sul_array::setUserData(const std::vector<double> *data)
{
    if(!data) {
        //tty << "sul_array::setUserData(): Invalid data pointer" << "\n";
        userData_ = NULL;
        repaint();
        return;
    }

    if((data->size() != X.size()) || (data->size() != Y.size())) {
        tty << "sul_array::setUserData(): Invalid vector size - " << data->size() << " (need " << X.size() << ")" << "\n";
        return;
    }

    userData_ = data;

    //tty << "sul_array::setUserData(): data updated" << "\n";

    repaint();
}

//---------------------------------------------------------------------------------------
