/****************************************************************************
** Meta object code from reading C++ file 'RayApp.H'
**
** Created: Fri Oct 19 17:17:02 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RayApp.H"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RayApp.H' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RayApp[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      22,    7,    7,    7, 0x08,
      36,    7,    7,    7, 0x08,
      57,   45,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RayApp[] = {
    "RayApp\0\0loadPressed()\0savePressed()\0"
    "render()\0x1,y1,x2,y2\0"
    "selectionChanged(int,int,int,int)\0"
};

const QMetaObject RayApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RayApp,
      qt_meta_data_RayApp, 0 }
};

const QMetaObject *RayApp::metaObject() const
{
    return &staticMetaObject;
}

void *RayApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RayApp))
	return static_cast<void*>(const_cast< RayApp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RayApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadPressed(); break;
        case 1: savePressed(); break;
        case 2: render(); break;
        case 3: selectionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        }
        _id -= 4;
    }
    return _id;
}
