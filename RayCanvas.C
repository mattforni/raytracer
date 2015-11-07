/*************************************************************************
 *    NAME: Nong Li
 *    USER: nli
 *    FILE: RayCanvas.C
 *    DATE: Thu May 10 17:25:24 2007
 *************************************************************************/
#include <QApplication>
#include "RayCanvas.H"
#include <iostream>
#include <RenderThread.H>
using namespace std;

/*************************************************************************
 * Function Name: RayCanvas::RayCanvas
 * Parameters: 
 * Effects: 
 *************************************************************************/

RayCanvas::RayCanvas(int width , int height) : CS123Canvas(width, height)
{
   m_mainProxy = new MainSyscallProxy();
   enableMarquee();
}


/*************************************************************************
 * Function Name: RayCanvas::~RayCanvas
 * Parameters: 
 * Effects: 
 *************************************************************************/

RayCanvas::~RayCanvas()
{
}


/*************************************************************************
 * Function Name: RayCanvas::mousePressed
 * Parameters: int x, int y
 * Returns: void
 * Effects: 
 *************************************************************************/
void
RayCanvas::mousePressed(int x, int y) {
   cout << "Mouse Pressed (" << x << ", " << y << ")" << endl;
}


/*************************************************************************
 * Function Name: RayCanvas::mouseReleased
 * Parameters: int x, int y
 * Returns: void
 * Effects: 
 *************************************************************************/
void
RayCanvas::mouseReleased(int x, int y) {
   cout << "Mouse Released (" << x << ", " << y << ")" << endl;
}


/*************************************************************************
 * Function Name: RayCanvas::mouseDragged
 * Parameters: int x, int y
 * Returns: void
 * Effects: 
 *************************************************************************/
void
RayCanvas::mouseDragged(int x, int y) {
   cout << "Mouse Dragged (" << x << ", " << y << ")" << endl;
}

void RayCanvas::repaint(int x, int y, int w, int h) {
   LocalSyscallProxy(this, m_mainProxy).repaint(x, y, w, h);
}

void RayCanvas::repaintPrivate(int x, int y, int w, int h) {
   QWidget::repaint(x, y, w, h);
}

