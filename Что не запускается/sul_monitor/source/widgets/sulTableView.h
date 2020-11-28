#ifndef _SUL_TABLE_VIEW_H_
#define _SUL_TABLE_VIEW_H_

//-----------------------------------------------------------------------------

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QSpinBox>
#else
#include <QTableView>
#include <QStatusBar>
#include <QItemDelegate>
#include <QSpinBox>
#include <QtGui/QWidget>
#endif
#include <QSettings>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QObject>
#include <QSize>

//-----------------------------------------------------------------------------

class SpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT

private:
    int offset;
    int min;
    int max;
    int step;

public:
    SpinBoxDelegate(QObject *parent = 0, int minValue = 0, int maxValue = 360, int stepValue = 1);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
    void valueChanged(int value);
    void offsetChanged(int off);

signals:
    void itemChanged(int value, int offset);
    void editorCreated(int off) const;
};

//-----------------------------------------------------------------------------

class SulTableView : public QTableView {

    Q_OBJECT

private:
    bool        send_ok;

public:
                SulTableView(QWidget * parent = 0);
    virtual     ~SulTableView();
    void        changeSignal(bool enable);

public slots:
    void itemChanged( int value, int offset );
    void dataChanged( const QModelIndex &current, const QModelIndex &previous );
    void currentChanged( const QModelIndex &current, const QModelIndex &previous );

signals:
    void cellChanged( const QModelIndex &current );
    void cellChanged( int value, int offset );
};

//-----------------------------------------------------------------------------

#endif // _SUL_TABLE_VIEW_H_
