#ifndef __RENDER_THREAD_H__
#define __RENDER_THREAD_H__

#include <QThread>
#include <CS123Common.H>

class RayCanvas;

class RenderThread : public QThread {

   public:
      RenderThread(RayCanvas* canvas);
      RenderThread(RayCanvas* canvas, const CS123Rectangle& region);
      virtual ~RenderThread();

   protected:
      virtual void run();

   private:
      RayCanvas* m_canvas;
      CS123Rectangle m_region;
      bool m_regionEnabled;
};

// this class acts as a signal emitter in the current thread
// its intended to be created, used once, then destroyed
// it's only purpose in life is to get around the fact that
//    the SyscallListener is a) not always called in the same thread
//                       and b) not always called from the thread it belongs to
class LocalSyscallProxy : public QObject {
    
    Q_OBJECT

    public:
        LocalSyscallProxy(RayCanvas *canvas, QObject *mainProxy = NULL);
        void repaint(int x1, int y1, int w, int h);
        void connectTo(QObject *mainProxy);
        
    signals:
        void sig_repaint(void*, int x1, int y1, int w, int h);

    private:
        RayCanvas *m_canvas;
};

// all instances of this class will push themselves into the main thread
// otherwise it is simply an adaptor to run syscall, undoSyscall and reset on the given handler
class MainSyscallProxy : public QObject {
    Q_OBJECT
    
    public:
        MainSyscallProxy();
        
    public slots:
        void slot_repaint(void *target, int x1, int y1, int w, int h);
};

#endif

