/****************************************************************************
** Meta object code from reading C++ file 'RayCanvas.H'
**
** Created: Fri Oct 19 17:17:02 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RayCanvas.H"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RayCanvas.H' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RayCanvas[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RayCanvas[] = {
    "RayCanvas\0\0sceneFile\0loadScene(const char*)\0"
};

const QMetaObject RayCanvas::staticMetaObject = {
    { &CS123Canvas::staticMetaObject, qt_meta_stringdata_RayCanvas,
      qt_meta_data_RayCanvas, 0 }
};

const QMetaObject *RayCanvas::metaObject() const
{
    return &staticMetaObject;
}

void *RayCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RayCanvas))
	return static_cast<void*>(const_cast< RayCanvas*>(this));
    return CS123Canvas::qt_metacast(_clname);
}

int RayCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CS123Canvas::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadScene((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
