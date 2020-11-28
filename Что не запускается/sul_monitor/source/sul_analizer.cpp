#include "sul_analizer.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
//	    Класс для рисования состояния каналов
///////////////////////////////////////////////////////////////////////

sul_channel_analizer::sul_channel_analizer(sul_base *Sul, QWidget *parent, Qt::WindowFlags flags)
: QWidget(parent, flags)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    setWindowTitle(QString::fromUtf8("Анализтор каналов"));
    setWindowIcon(QIcon("config\\icon\\chan_icon.png"));
    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    square_size = 3;
    fi0 = false;
    //type = processing_channels;
    X = 0;
    N = 0;
    sul = Sul;
    abonent = 1;
    data_ = NULL;
    bar->showMessage(QString::fromUtf8("Выбор канала"));
}

//----------------------------------------------------------------------------------------------

sul_channel_analizer::~sul_channel_analizer()
{
}

//----------------------------------------------------------------------------------------------

void sul_channel_analizer::paintEvent(QPaintEvent *event)
{
    if(!sul)
        return;

    struct channel_t channel;
    int size = sul->sul_abonent_channels(abonent);
    int offset = size*(abonent-1);

    QRectF r = event->rect();

    float w = r.width();
    float h = r.height();
    float xs = w/size;

    QPainter p(this);

    //QLinearGradient g(0.7*w,h,0,0);
    //g.setSpread(QGradient::ReflectSpread);
    //p.fillRect(0,0,w,h,QBrush(g));
    //p.fillRect(0,0,w,h,QBrush(Qt::lightGray));

    QColor c(Qt::darkBlue);
    //int val = 0;
    //int start_line = 0;

    p.drawRect(0,0,w-1,h-1);
    p.setPen(Qt::red);

    if(data_) {

        xs = w/data_->size();

        for(unsigned i=0; i<data_->size(); i++) {

            p.fillRect(xs*i,
                       0.8*h-1.2*data_->at(i),
                       square_size,
                       square_size,
                       QBrush(c,Qt::SolidPattern));
        }

        return;
    }

    for(int i=0; i<sul->sul_abonent_channels(abonent); i++) {

        if( sul->sul_channel_info(offset+i, channel) < 0 )
            continue;

        //if(i==0) {
        //    start_line = channel.entry.line_number;
        //}
/*
        switch(type) {
        case processing_phases: {

                //вывод информации о начальной фазе канала
                val = channel.phase0.at(0);

            }; break;
        case processing_channels: {

                //вывод информации о состоянии каналов
                switch(channel.state) {
                    case channel_operational:
                        c = Qt::green;
                    break;
                    case channel_open_fault:
                        c = Qt::red;
                    break;
                    case channel_short_circuit:
                        c = Qt::blue;
                    break;
                    case channel_untested:
                            c = Qt::gray;
                    break;
                }
                val = channel.number;

            }; break;
        case processing_calculators: {

                //вывод информации о коде вычислителей
                val = channel.extra.at(0);

            }; break;
        case processing_pulses: {

                //вывод информации о коде импульса
                val = channel.extra.at(3);
            }; break;
        case processing_grids: {
            }; break;
        }

        p.fillRect(xs*i,
                   0.8*h-1.2*val,
                   square_size,
                   square_size,
                   QBrush(c,Qt::SolidPattern));

        if(start_line != channel.line) {
            p.drawLine(xs*i,0,xs*i,h);
            start_line = channel.line;
        }
*/
    }
}

//----------------------------------------------------------------------------------------------

void sul_channel_analizer::mousePressEvent(QMouseEvent *event)
{
    struct channel_t channel;
    QString status;

    if(!sul) return;

    int offset = (abonent-1)*sul->sul_abonent_channels(abonent);

    X = event->x();
    N = offset + 128*X/geometry().width() + 1;

    bar->setGeometry(5,geometry().height()-15,geometry().width()-5,15);

    if(!data_ || (N >= (int)data_->size())) return;
    /*
    if( sul->sul_channel_info(N-1, channel) < 0 ) {
        bar->showMessage(tr("Неправильный номер канала."));
        return;
    }


    if(data_) {

        //вывод информации о коде вычислителей
        bar->showMessage(tr(" Канал: ") + QString::number(channel.entry.N) +
                         tr(" Код: ") + QString::number(data_->at(channel.entry.N-1)));

        repaint();
        return;
    }
    */

    //вывод информации о коде вычислителей
    bar->showMessage(QString::fromUtf8(" Канал: ") + QString::number(N) +
                     QString::fromUtf8(" Код: ") + QString::number(data_->at(N-1)));

/*
    switch(type) {
    case processing_channels: {

            //вывод информации о состоянии каналов
            switch(channel.state) {
                case channel_operational: status = tr("исправен"); break;
                case channel_open_fault: status = tr("обрыв"); break;
                case channel_short_circuit: status = tr("замыкание"); break;
                case channel_untested:
                            status = tr("канал не проверен");
                break;
            }

            bar->showMessage(tr("Линейка: ") + QString::number(channel.line) +
                             tr(" Канал: ") + QString::number(channel.number+1) + " - " + status);
                             tr(" Код: ") + QString::number(channel.extra.at(0));

        }; break;
    case processing_calculators: {

            int code = fi0 ? channel.phase0.at(0) : channel.phase0.at(0) - channel.phase0.at(0);

            //вывод информации о коде вычислителей
            bar->showMessage(tr("Линейка: ") + QString::number(channel.line) +
                             tr(" Канал: ") + QString::number(channel.number+1) +
                             tr(" Код: ") + QString::number(code));

        }; break;
    case processing_phases: {

            int code = channel.phase0.at(0);

            //вывод информации о коде вычислителей
            bar->showMessage(tr("Линейка: ") + QString::number(channel.line) +
                             tr(" Канал: ") + QString::number(channel.number+1) +
                             tr(" Код: ") + QString::number(code));

        }; break;
    case processing_grids: {
        }; break;
    case processing_pulses: {

            int code = channel.phase0.at(0);

            //вывод информации о коде вычислителей
            bar->showMessage(tr("Линейка: ") + QString::number(channel.line) +
                             tr(" Канал: ") + QString::number(channel.number+1) +
                             tr(" Код: ") + QString::number(code));
        }; break;
    }
*/
    repaint();
}

//----------------------------------------------------------------------------------------------

void sul_channel_analizer::set_abonent_number(int devn)
{
    abonent = devn;
}

//----------------------------------------------------------------------------------------------

void sul_channel_analizer::show_pulses()
{
    cout << "sul_channel_analizer::show_pulses()" << endl;
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_channels()
{
    cout << "sul_channel_analizer::show_channels()" << endl;
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_calculators(bool Fi0)
{
    cout << "sul_channel_analizer::show_calculators()" << endl;
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_fi0()
{
    cout << "sul_channel_analizer::show_fi0()" << endl;
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_abonent_test(int test_number)
{
    cout << "sul_channel_analizer::show_abonent_test( " << test_number << " )" << endl;
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_abonent_test()
{
    cout << "sul_channel_analizer::show_abonent_test()" << endl;
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::paint_user_data(const vector<double> *data)
{
    data_ = data;
    cout << "data_->size()" << data_->size() << endl;
}

//---------------------------------------------------------------------------------------
