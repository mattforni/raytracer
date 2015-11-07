/****************************************************************************
** Meta object code from reading C++ file 'RenderThread.H'
**
** Created: Fri Oct 19 17:17:03 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RenderThread.H"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderThread.H' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_LocalSyscallProxy[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      30,   19,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_LocalSyscallProxy[] = {
    "LocalSyscallProxy\0\0,x1,y1,w,h\0"
    "sig_repaint(void*,int,int,int,int)\0"
};

const QMetaObject LocalSyscallProxy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LocalSyscallProxy,
      qt_meta_data_LocalSyscallProxy, 0 }
};

const QMetaObject *LocalSyscallProxy::metaObject() const
{
    return &staticMetaObject;
}

void *LocalSyscallProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalSyscallProxy))
	return static_cast<void*>(const_cast< LocalSyscallProxy*>(this));
    return QObject::qt_metacast(_clname);
}

int LocalSyscallProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sig_repaint((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void LocalSyscallProxy::sig_repaint(void * _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_MainSyscallProxy[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      35,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainSyscallProxy[] = {
    "MainSyscallProxy\0\0target,x1,y1,w,h\0"
    "slot_repaint(void*,int,int,int,int)\0"
};

const QMetaObject MainSyscallProxy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainSyscallProxy,
      qt_meta_data_MainSyscallProxy, 0 }
};

const QMetaObject *MainSyscallProxy::metaObject() const
{
    return &staticMetaObject;
}

void *MainSyscallProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainSyscallProxy))
	return static_cast<void*>(const_cast< MainSyscallProxy*>(this));
    return QObject::qt_metacast(_clname);
}

int MainSyscallProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slot_repaint((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        }
        _id -= 1;
    }
    return _id;
}
