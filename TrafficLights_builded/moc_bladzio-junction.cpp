/****************************************************************************
** Meta object code from reading C++ file 'bladzio-junction.h'
**
** Created: Sun Apr 29 16:19:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/TrafficLights_manager/bladzio-junction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bladzio-junction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BladzioJunction[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      33,   16,   16,   16, 0x08,
      50,   16,   16,   16, 0x08,
      66,   16,   16,   16, 0x08,
      83,   16,   16,   16, 0x08,
     103,   16,   16,   16, 0x08,
     124,   16,   16,   16, 0x08,
     144,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BladzioJunction[] = {
    "BladzioJunction\0\0firstSubcycle()\0"
    "secondSubcycle()\0thirdSubcycle()\0"
    "fourthSubcycle()\0holdFirstSubcycle()\0"
    "holdSecondSubcycle()\0holdThirdSubcycle()\0"
    "holdFourthSubcycle()\0"
};

const QMetaObject BladzioJunction::staticMetaObject = {
    { &Junction::staticMetaObject, qt_meta_stringdata_BladzioJunction,
      qt_meta_data_BladzioJunction, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BladzioJunction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BladzioJunction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BladzioJunction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BladzioJunction))
        return static_cast<void*>(const_cast< BladzioJunction*>(this));
    return Junction::qt_metacast(_clname);
}

int BladzioJunction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Junction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: firstSubcycle(); break;
        case 1: secondSubcycle(); break;
        case 2: thirdSubcycle(); break;
        case 3: fourthSubcycle(); break;
        case 4: holdFirstSubcycle(); break;
        case 5: holdSecondSubcycle(); break;
        case 6: holdThirdSubcycle(); break;
        case 7: holdFourthSubcycle(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
