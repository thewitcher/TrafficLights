/****************************************************************************
** Meta object code from reading C++ file 'checkpoint.h'
**
** Created: Sun Apr 29 15:26:10 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/Checkpoints_manager/checkpoint.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkpoint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Checkpoint[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Checkpoint[] = {
    "Checkpoint\0\0flags,checkpointId,vehicle\0"
    "checkpointReached(uint,int,Vehicle*)\0"
};

const QMetaObject Checkpoint::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Checkpoint,
      qt_meta_data_Checkpoint, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Checkpoint::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Checkpoint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Checkpoint::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Checkpoint))
        return static_cast<void*>(const_cast< Checkpoint*>(this));
    return QObject::qt_metacast(_clname);
}

int Checkpoint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkpointReached((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< Vehicle*(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Checkpoint::checkpointReached(uint _t1, int _t2, Vehicle * _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
