/****************************************************************************
** Meta object code from reading C++ file 'graphics-view.h'
**
** Created: Sun Apr 29 15:25:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/Root_window/graphics-view.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphics-view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphicsView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      26,   13,   13,   13, 0x08,
      54,   13,   13,   13, 0x08,
      73,   13,   13,   13, 0x08,
      87,   13,   13,   13, 0x08,
     130,  114,   13,   13, 0x08,
     170,  159,   13,   13, 0x28,
     197,  191,   13,   13, 0x28,
     213,   13,   13,   13, 0x08,
     237,   13,   13,   13, 0x08,
     262,  257,   13,   13, 0x08,
     291,   13,   13,   13, 0x28,
     316,   13,   13,   13, 0x08,
     325,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GraphicsView[] = {
    "GraphicsView\0\0initScene()\0"
    "createDeployTrafficLights()\0"
    "initGraphicsView()\0createItems()\0"
    "createCheckpointsManager()\0speed,dark,type\0"
    "addVehicle(int,bool,QString)\0speed,dark\0"
    "addVehicle(int,bool)\0speed\0addVehicle(int)\0"
    "createJunctionManager()\0createConnections()\0"
    "dark\0changeBackgroundPixmap(bool)\0"
    "changeBackgroundPixmap()\0setDay()\0"
    "setNight()\0"
};

const QMetaObject GraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphicsView,
      qt_meta_data_GraphicsView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphicsView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsView))
        return static_cast<void*>(const_cast< GraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: initScene(); break;
        case 1: createDeployTrafficLights(); break;
        case 2: initGraphicsView(); break;
        case 3: createItems(); break;
        case 4: createCheckpointsManager(); break;
        case 5: addVehicle((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 6: addVehicle((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: addVehicle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: createJunctionManager(); break;
        case 9: createConnections(); break;
        case 10: changeBackgroundPixmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: changeBackgroundPixmap(); break;
        case 12: setDay(); break;
        case 13: setNight(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
