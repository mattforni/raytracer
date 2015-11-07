/*************************************************************************
 *    NAME: Nong Li
 *    USER: nli
 *    FILE: RenderThread.C
 *    DATE: Tue Sep  4 15:46:08 2007
 *************************************************************************/
#include "RenderThread.H"
#include "RayCanvas.H"
#include <QApplication>

/*************************************************************************
 * Function Name: RenderThread::RenderThread
 * Parameters: RayCanvas* canvas
 * Effects: 
 *************************************************************************/

RenderThread::RenderThread(RayCanvas* canvas) : QThread() {
    m_canvas = canvas;
    m_regionEnabled = false;
}

RenderThread::RenderThread(RayCanvas* c, const CS123Rectangle& r) : QThread() {
    m_canvas = c;

    if (r.minX >= 0 && r.minY >= 0 &&
	    r.maxX > r.minX && r.maxY > r.minY) {
	m_regionEnabled = true;
	memcpy(&m_region, &r, sizeof(CS123Rectangle));
    }
    else
    {
	printf("Invalid rectangular region. Default to rendering whole image.\n");
	m_regionEnabled = false;
    }
}


/*************************************************************************
 * Function Name: RenderThread::~RenderThread
 * Parameters: 
 * Effects: 
 *************************************************************************/

RenderThread::~RenderThread() {
}


/*************************************************************************
 * Function Name: RenderThread::run
 * Parameters: 
 * Returns: void
 * Effects: 
 *************************************************************************/
void
RenderThread::run() {
    setPriority(NormalPriority);
    if (m_regionEnabled) {
	m_canvas->render(m_region);
    }
    else {
	memset(m_canvas->getData(), 0, 
		    m_canvas->getWidth()*m_canvas->getHeight()*sizeof(int));
	m_canvas->repaint(0, 0, m_canvas->getWidth(), m_canvas->getHeight());
	m_canvas->render();
    }
}


/* Implementation of LocalSyscallProxy */
LocalSyscallProxy::LocalSyscallProxy(RayCanvas *canvas, QObject *mainProxy) :
   m_canvas(canvas) {
   if (mainProxy) // auto-connect to mainProxy
      connectTo(mainProxy);
}

void LocalSyscallProxy::repaint(int x1, int y1, int w, int h) {
   emit sig_repaint((void*)m_canvas, x1, y1, w, h);
}

void LocalSyscallProxy::connectTo(QObject *mainProxy) {
   Qt::ConnectionType connectionKind;


   if (this->thread() != mainProxy->thread()) {
      connectionKind = Qt::BlockingQueuedConnection;
   }
   else {
      connectionKind = Qt::DirectConnection;
   }

   // make the connections between this and the main thread proxy
   connect(this, SIGNAL(sig_repaint(void*,int, int, int, int)),
         mainProxy, SLOT(slot_repaint(void*,int, int, int, int)),
         connectionKind);
}

MainSyscallProxy::MainSyscallProxy() {
   // push myself to the main thread
   moveToThread(qApp->thread());
}

// the following three methods just relay the call to handler
void MainSyscallProxy::slot_repaint(void *t, int x1, int y1, int w, int h) {
   RayCanvas *target = (RayCanvas*)t;
   target->repaintPrivate(x1, y1, w, h);
}
