/****************************************************************************
** Meta object code from reading C++ file 'histogram_view.h'
**
** Created: Sun Dec 18 19:00:28 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "histogram_view.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'histogram_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HistogramView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      25,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HistogramView[] = {
    "HistogramView\0\0enlarge()\0shrink()\0"
};

void HistogramView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HistogramView *_t = static_cast<HistogramView *>(_o);
        switch (_id) {
        case 0: _t->enlarge(); break;
        case 1: _t->shrink(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData HistogramView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HistogramView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HistogramView,
      qt_meta_data_HistogramView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HistogramView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HistogramView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HistogramView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HistogramView))
        return static_cast<void*>(const_cast< HistogramView*>(this));
    return QWidget::qt_metacast(_clname);
}

int HistogramView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
