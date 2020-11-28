#include "sul_analizer.h"

///////////////////////////////////////////////////////////////////////
//	    Класс для рисования состояния каналов
///////////////////////////////////////////////////////////////////////

sul_channel_analizer::sul_channel_analizer(sul_base *Sul, QWidget *parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
    setWindowTitle(tr("Анализтор каналов"));
    setWindowIcon(QIcon("icon\\chan_icon.png"));
    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    square_size = 6;
    fi0 = false;
    type = processing_channels;
    X = 0;
    N = 0;
    sul = Sul;
    abonent = 1;
    bar->showMessage(tr("Выбор канала"));
}

//----------------------------------------------------------------------------------------------

sul_channel_analizer::~sul_channel_analizer()
{
}

//----------------------------------------------------------------------------------------------

void sul_channel_analizer::paintEvent(QPaintEvent *event)
{
    if(!sul) return;

    struct phase_shifter shifter = {0};
    int size = sul->sul_total_channels(abonent);
    int offset = size*(abonent-1);

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

    int start_line = 0;

    for(int i=0; i<sul->sul_total_channels(abonent); i++) {

        if( sul->sul_phase_shifter_info(offset+i, shifter) < 0 )
            continue;

        if(i==0) {
            start_line = shifter.line;
        }

        switch(type) {
        case processing_channels: {

                //вывод информации о состоянии каналов
                switch(shifter.state) {
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
                    case channel_unconnected:
                            c = Qt::gray;
                    break;
                }
                val = shifter.chan_code;

            }; break;
        case processing_calculators: {

                //вывод информации о коде вычислителей
                val = fi0 ? shifter.calc_code : shifter.calc_code - shifter.fi0_code;

            }; break;
        case processing_phases: {

                //вывод информации о начальной фазе канала
                val = shifter.fi0_code;

            }; break;
	case processing_pulses: {

		//вывод информации о коде импульса
		val = shifter.pulse_code;
	    }; break;
        case processing_grids: {
            }; break;
        }

        p.fillRect(xs*i,
		   0.9*h-val,
                   square_size,
                   square_size,
                   QBrush(c,Qt::SolidPattern));

        if(start_line != shifter.line) {
            p.drawLine(xs*i,0,xs*i,h);
            start_line = shifter.line;
        }
    }
}

//----------------------------------------------------------------------------------------------

void sul_channel_analizer::mousePressEvent(QMouseEvent *event)
{
    struct phase_shifter shifter = {0};
    QString status;

    if(!sul) return;

    int offset = (abonent-1)*sul->sul_total_channels(abonent);

    X = event->x();
    N = offset + 128*X/geometry().width() + 1;

    bar->setGeometry(5,geometry().height()-15,geometry().width()-5,15);

    if( sul->sul_phase_shifter_info(N-1, shifter) < 0 ) {
        bar->showMessage(tr("Неправильный номер канала."));
        return;
    }

    switch(type) {
    case processing_channels: {

            //вывод информации о состоянии каналов
            switch(shifter.state) {
                case channel_operational: status = tr("исправен"); break;
                case channel_open_fault: status = tr("обрыв"); break;
                case channel_short_circuit: status = tr("замыкание"); break;
                case channel_untested:
                case channel_unconnected:
                            status = tr("канал не проверен/подключен");
                break;
            }

            bar->showMessage(tr("Линейка: ") + QString::number(shifter.line) +
                             tr(" Канал: ") + QString::number(shifter.channel_number + 1) + " - " + status);
			     tr(" Код: ") + QString::number(shifter.chan_code);

        }; break;
    case processing_calculators: {

            int code = fi0 ? shifter.calc_code : shifter.calc_code - shifter.fi0_code;

            //вывод информации о коде вычислителей
            bar->showMessage(tr("Линейка: ") + QString::number(shifter.line) +
                             tr(" Канал: ") + QString::number(shifter.channel_number + 1) +
                             tr(" Код: ") + QString::number(code));

        }; break;
    case processing_phases: {

            int code = shifter.fi0_code;

            //вывод информации о коде вычислителей
            bar->showMessage(tr("Линейка: ") + QString::number(shifter.line) +
                             tr(" Канал: ") + QString::number(shifter.channel_number + 1) +
                             tr(" Код: ") + QString::number(code));

        }; break;
    case processing_grids: {
        }; break;
    case processing_pulses: {

	    int code = shifter.pulse_code;

	    //вывод информации о коде вычислителей
	    bar->showMessage(tr("Линейка: ") + QString::number(shifter.line) +
			     tr(" Канал: ") + QString::number(shifter.channel_number + 1) +
			     tr(" Код: ") + QString::number(code));
	}; break;
    }

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
    type = processing_pulses;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_channels()
{
    type = processing_channels;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_calculators(bool Fi0)
{
    fi0 = Fi0;
    type = processing_calculators;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------

void sul_channel_analizer::show_fi0()
{
    type = processing_phases;
    show();
    repaint();
}

//---------------------------------------------------------------------------------------
