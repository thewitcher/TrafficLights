/****************************************************************************
** Meta object code from reading C++ file 'simple-junction.h'
**
** Created: Wed May 2 09:17:48 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/TrafficLights_manager/simple-junction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simple-junction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimpleJunction[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      32,   15,   15,   15, 0x08,
      49,   15,   15,   15, 0x08,
      65,   15,   15,   15, 0x08,
      85,   15,   15,   15, 0x08,
     106,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimpleJunction[] = {
    "SimpleJunction\0\0firstSubcycle()\0"
    "secondSubcycle()\0thirdSubcycle()\0"
    "holdFirstSubcycle()\0holdSecondSubcycle()\0"
    "holdThirdSubcycle()\0"
};

const QMetaObject SimpleJunction::staticMetaObject = {
    { &Junction::staticMetaObject, qt_meta_stringdata_SimpleJunction,
      qt_meta_data_SimpleJunction, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimpleJunction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimpleJunction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimpleJunction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleJunction))
        return static_cast<void*>(const_cast< SimpleJunction*>(this));
    return Junction::qt_metacast(_clname);
}

int SimpleJunction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Junction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: firstSubcycle(); break;
        case 1: secondSubcycle(); break;
        case 2: thirdSubcycle(); break;
        case 3: holdFirstSubcycle(); break;
        case 4: holdSecondSubcycle(); break;
        case 5: holdThirdSubcycle(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
