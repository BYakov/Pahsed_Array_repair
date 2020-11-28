
#include "sul_array.h"

using namespace std;

sul_array::sul_array(sul_base *Sul, QWidget *parent, Qt::WindowFlags flags)
: QWidget(parent, flags)
{
    setWindowTitle(tr("Антенная решетка"));
    setWindowIcon(QIcon("config\\icon\\array_icon.png"));

    sul = Sul;
    legend1 = new sul_legend_widget1(Sul,NULL,Qt::Popup);
    legend2 = new sul_legend_widget2(Sul,NULL,Qt::Popup);

    int N = sul->sul_total_channels();

    x = new unsigned short[N];
    y = new unsigned short[N];
    R = new float[N];

    memset(x,0,N);
    memset(y,0,N);
    memset(R,0,N);

    Rmax = 1;
    maxX = 1;
    maxY = 1;
    minX = 0;
    minY = 0;

    // заполним координаты для быстрого поиска
    float x0 = 0;
    float y0 = 0;
    float xc = 0;
    float yc = 0;

    int x_segment = sul->sul_flash_find_segment("X");
    int y_segment = sul->sul_flash_find_segment("Y");

    const vector<double> &x_data = sul->sul_flash_segment(x_segment);
    const vector<double> &y_data = sul->sul_flash_segment(y_segment);

    int channel_counter = 0;
    for(unsigned i=0; i<sul->sul_total_abonents(); i++) {

        int module_channels = sul->sul_abonent_channels(i);
        int flash_offset = sul->sul_flash_block_size()*i;

        //cout << "Module " << i << " module_channels " << module_channels << " flash_offset " << flash_offset << endl;

        for(int j=0; j<module_channels; j++) {

            x[channel_counter] = x_data.at(flash_offset+j);
            y[channel_counter] = y_data.at(flash_offset+j);

            if(x[channel_counter] > maxX) maxX = x[channel_counter];
            if(y[channel_counter] > maxY) maxY = y[channel_counter];
            if(x[channel_counter] < minX) minX = x[channel_counter];
            if(y[channel_counter] < minY) minY = y[channel_counter];

            channel_counter++;
        }
    }

    xc = 0.5*(maxX-minX);
    yc = 0.5*(maxY-minY);

    for(int i=0; i<N; i++) {

        x0 = (x[i]-xc);
        y0 = (y[i]-yc);
        R[i]  = sqrt(x0*x0 + y0*y0);

        if(R[i] > Rmax) { Rmax = R[i]; }
    }

    cS = 1;

    memset(&channel, 0, sizeof(struct channel_info));
    elementSize = 10;
    abonent = 1;
    fi0 = false;

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

    sul->sul_channel_info(0,channel);

    numberOfPhases = channel.phase0.size();
    numberOfGains = channel.gain0.size();
    numberOfExtras = channel.extra.size();

    selectedChannel = -1;
    viewParameter = -1;
    viewSpaceParameter = -1;

    //m_param = NULL;

    cout << "sul_array::sul_array()" <<  endl;
    cout << "sul_array::N = " << N << endl;
    cout << "sul_array::maxX = " << maxX << endl;
    cout << "sul_array::maxY = " << maxY << endl;
    cout << "sul_array::scaleScreenX = " << scaleScreenX << endl;
    cout << "sul_array::scaleScreenY = " << scaleScreenY << endl;
    cout << "sul_array::numberOfPhases = " << numberOfPhases << endl;
    cout << "sul_array::numberOfExtras = " << numberOfExtras << endl;
}

//---------------------------------------------------------------------------------------

sul_array::~sul_array()
{
    close();

    if(x) delete [] x;
    if(y) delete [] y;
    if(R) delete [] R;

    if(legend1) delete legend1;
    if(legend2) delete legend2;

    cout << "sul_array::~sul_array()" <<  endl;
}

//---------------------------------------------------------------------------------------

void sul_array::paint_grid(QPaintEvent *event)
{
    int W = (maxX*scaleScreenX + 3)*elementSize;
    int H = (maxY*scaleScreenY + 3)*elementSize;
    int R = sqrt(W*W + H*H);

    QWidget::setGeometry(geometry().x(),geometry().y(),W,H);

    QPainter p(this);
    //QLinearGradient g(geometry().width(),geometry().height(),0,0);
    QRadialGradient g(0.5*geometry().width(),0.5*geometry().height(),R);
    //g.setSpread(QGradient::ReflectSpread);
    g.setSpread(QGradient::RepeatSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));

    QColor c;

    int color_step = 350/sul->sul_total_abonents();

    for(int i=0; i<sul->sul_total_channels(); i++) {

        if(sul->sul_channel_info(i,channel) < 0)
            continue;

        if(channel.state == channel_untested) {

            //заполнение цветом в зависимости от модуля
            //QBrush b1(QColor(Qt::gray));
            QBrush b1(c.fromHsv(channel.module*color_step, 255, 255));
            p.setBrush(b1);

        } else {

            if(channel.state != channel_operational) {

                //заполнение красным цветом
                QBrush b2(QColor(Qt::red));
                p.setBrush(b2);
            } else {

                //заполнение зеленым цветом
                QBrush b3(QColor(Qt::green));
                p.setBrush(b3);
            }
        }

        if(selectedChannel == i) {
            QBrush b1(QColor(Qt::yellow));
            p.setBrush(b1);
        }

        p.drawEllipse((x[i]+1)*elementSize*scaleScreenX,(y[i]+1)*elementSize*scaleScreenY,elementSize,elementSize);

        QPoint point((x[i]+1)*elementSize*scaleScreenX,(y[i]+1)*elementSize*scaleScreenY);

        //p.drawText(point, QString::number(channel.number));
        //p.drawText((x[i]+1)*elementSize*scaleScreenX,(y[i]+1.1)*elementSize*scaleScreenY,elementSize,elementSize,Qt::AlignCenter,QString::number(channel.module));
        p.drawText((x[i]+1)*elementSize*scaleScreenX,(y[i]+1.1)*elementSize*scaleScreenY,elementSize,elementSize,Qt::AlignCenter,QString::number(channel.number_on_module));
    }
}

//---------------------------------------------------------------------------------------

void sul_array::paintEvent(QPaintEvent *event)
{
    if(viewSpaceParameter != -1) {
        return paint_space_param(event);
    }

    //if(m_param) {
    //    paint_paramter(event);
    //} else {
        paint_grid(event);
    //}
}

//---------------------------------------------------------------------------------------

void sul_array::mousePressEvent(QMouseEvent *event)
{
    int x = (event->x()/(scaleScreenX*elementSize)) - 1;
    int y = (event->y()/(scaleScreenY*elementSize)) - 1;

    cout << x << " , " << y << endl;

    if(sul->sul_channel_info(x,y,channel) < 0) {
        selectedChannel = -1;
    } else {

        QWidget *legend = NULL;

        switch(event->button()) {
            case Qt::LeftButton:
                legend1->updateScreen(channel);
                legend = legend1;
                break;
            case Qt::RightButton:
                legend2->updateScreen(channel);
                legend = legend2 ;
                break;
            default:
                legend2->updateScreen(channel);
                legend = legend2 ;
                break;
        }

        selectedChannel = channel.number;

        legend->setGeometry(geometry().x()+event->x(),
                            geometry().y()+event->y()+20,
                            legend->geometry().width(),
                            legend->geometry().height());
        legend->show();
        legend->adjustSize();
    }

    repaint();
}

//---------------------------------------------------------------------------------------

void sul_array::set_abonent_number(int devn)
{
    abonent = devn;
}

//---------------------------------------------------------------------------------------

void sul_array::show_phase_array(int param_number)
{
    cout << "sul_array::show_phase_array( " << param_number << " )" << endl;

    if(param_number > sul->sul_total_parameters()) {
        cout << "sul_array::show_phase_array(): Invalid parametr number" << endl;
        return;
    }

    //m_param = sul->sul_get_parameter(param_number);
    viewSpaceParameter = -1;

    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_array::setArrayElementSize(int size)
{
    elementSize = size;
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_array::show_phase_array()
{
    cout << "sul_array::show_phase_array()" << endl;
    viewParameter = -1;
    viewSpaceParameter = -1;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_array::show_space_array(int spaceParameter)
{
    cout << "sul_array::show_space_array(" << spaceParameter << ")" << endl;
    viewSpaceParameter = spaceParameter;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_array::paint_paramter(QPaintEvent *event)
{
    int W = (maxX*scaleScreenX + 3)*elementSize;
    int H = (maxY*scaleScreenY + 3)*elementSize;

    QWidget::setGeometry(geometry().x(),geometry().y(),W,H);

    QPainter p(this);
    QLinearGradient g(geometry().width(),geometry().height(),0,0);
    g.setSpread(QGradient::ReflectSpread);
    p.fillRect(0,0,geometry().width(),geometry().height(),QBrush(g));
/*
    QColor c;

    for(unsigned i=0; i<m_param->data.size(); i++) {

        double value = m_param->data.at(i);

        QBrush b(c.fromHsv(value, 255, 255));
        p.setBrush(b);
        if(selectedChannel == (int)i) {
            QBrush b1(QColor(Qt::yellow));
            p.setBrush(b1);
        }
        p.drawEllipse((x[i]+1)*elementSize*scaleScreenX,
                      (y[i]+1)*elementSize*scaleScreenY,elementSize,elementSize);
    }
*/
}

//---------------------------------------------------------------------------------------

void sul_array::paint_space_param(QPaintEvent *event)
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

    int current_channel = 0;

    for(unsigned i=0; i<sul->sul_total_abonents(); i++) {

        const std::vector<double>& data = sul->sul_flash_block(viewSpaceParameter, i);

        for(int j=0; j<sul->sul_abonent_channels(i); j++) {

            QBrush b(c.fromHsv(data.at(j), 255, 255));

            p.setBrush(b);

            if(selectedChannel == current_channel) {
                QBrush b1(QColor(Qt::yellow));
                p.setBrush(b1);
            }

            p.drawEllipse((x[current_channel]+1)*elementSize*scaleScreenX,
                          (y[current_channel]+1)*elementSize*scaleScreenY,elementSize,elementSize);

            current_channel++;
        }
    }
}

//---------------------------------------------------------------------------------------
