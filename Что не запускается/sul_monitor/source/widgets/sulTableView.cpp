#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#include "sulTableView.h"

using namespace std;

//-----------------------------------------------------------------------------

SpinBoxDelegate::SpinBoxDelegate(QObject *parent, int minValue, int maxValue, int stepValue)
     : QItemDelegate(parent)
 {
    offset = 0;

    min = minValue;
    max = maxValue;
    step = stepValue;

    connect(this,SIGNAL(editorCreated(int)),this,SLOT(offsetChanged(int)));

    //cout << "SpinBoxDelegate::SpinBoxDelegate()" << endl;
 }

//-----------------------------------------------------------------------------

 QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem &option,
     const QModelIndex &index) const
 {
     //cout << "SpinBoxDelegate::createEditor()" << endl;

     QSpinBox *editor = new QSpinBox(parent);

     editor->setMaximum(max);
     editor->setMinimum(min);
     editor->setSingleStep(step);

     connect(editor,SIGNAL(valueChanged(int)),this,SLOT(valueChanged(int)));

     int colNumber = index.model()->columnCount();
     int off = index.row()*colNumber + index.column();

     emit editorCreated(off);

     return editor;
 }

 //-----------------------------------------------------------------------------

 void SpinBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
     //cout << "SpinBoxDelegate::setEditorData()" << endl;

     int value = index.model()->data(index, Qt::DisplayRole).toInt();

     QSpinBox *spinBox = static_cast<QSpinBox*>(editor);

     spinBox->setValue(value);
 }

 //-----------------------------------------------------------------------------

 void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
     //cout << "SpinBoxDelegate::setModelData()" << endl;

     QSpinBox *spinBox = static_cast<QSpinBox*>(editor);

     spinBox->interpretText();

     int value = spinBox->value();

     model->setData(index, value, Qt::EditRole);
 }

 //-----------------------------------------------------------------------------

 void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &index ) const
 {
     //cout << "SpinBoxDelegate::updateEditorGeometry()" << endl;
     editor->setGeometry(option.rect);
 }

 //-----------------------------------------------------------------------------

 void SpinBoxDelegate::valueChanged(int value)
 {
     //cout << "SpinBoxDelegate::valueChanged(): value = " << value << endl;
     emit itemChanged(value, offset);
 }

 //-----------------------------------------------------------------------------

 void SpinBoxDelegate::offsetChanged(int off)
 {
     //cout << "SpinBoxDelegate::offsetChanged(): offset = " << off << endl;
     offset = off;
 }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

SulTableView::SulTableView(QWidget * parent) : QTableView( parent )
{
    SpinBoxDelegate *delegate = new SpinBoxDelegate(this);
    setItemDelegate(delegate);
    setSelectionMode( QAbstractItemView::SingleSelection );
    setEditTriggers( QAbstractItemView::AllEditTriggers );

    send_ok = false;

    connect(delegate,SIGNAL(itemChanged(int,int)),this,SLOT(itemChanged(int,int)));

    //cout << "SulTableView::SulTableView()" << endl;
}

//-----------------------------------------------------------------------------

SulTableView::~SulTableView()
{
}

//-----------------------------------------------------------------------------

void SulTableView::itemChanged(int value, int offset)
{
    //cout << "SulTableView::itemChanged()" << endl;
    emit cellChanged(value, offset);
}

//-----------------------------------------------------------------------------

void SulTableView::dataChanged( const QModelIndex &current, const QModelIndex &previous )
{
    //cout << "SulTableView::dataChanged()" << endl;

    QTableView::dataChanged( current, previous );

    if(send_ok) {
	cout << "SulTableView::dataChanged(): col = " << current.column() << " row = " << current.row() <<
		" current = " << current.data().toInt() << endl;
        emit cellChanged(current);
    }
}

//-----------------------------------------------------------------------------

void SulTableView::currentChanged( const QModelIndex &current, const QModelIndex &previous )
{
    //cout << "SulTableView::currentChanged(): col = " << current.column() << " row = " << current.row() <<
//	    " current = " << current.data().toInt() << endl;
    QTableView::currentChanged( current, previous );
}

//-----------------------------------------------------------------------------

void SulTableView::changeSignal(bool enable)
{
   // cout << "SulTableView::changeSignal()" << endl;
    send_ok = enable;
}

//-----------------------------------------------------------------------------
