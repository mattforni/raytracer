#ifndef __RAY_CANVAS_H__
#define __RAY_CANVAS_H__

#include <CS123Canvas.H>

class MainSyscallProxy;

enum RayOptions {
    RAY_OPTION_RECURSION_DEPTH,
    RAY_OPTION_SUPERSAMPLING
};

class RayCanvas : public CS123Canvas {

    Q_OBJECT

    public:
	/* No need to worry about this - this is to get concurrent rendering */
	friend class MainSyscallProxy;

	//! Create a canvas with the given dimensions
	RayCanvas(int width, int height);
	virtual ~RayCanvas();
    
	//! Option method for handling mouse press events
	virtual void mousePressed(int x, int y);
	//! Option method for handling mouse released events
	virtual void mouseReleased(int x, int y);
	//! Option method for handling mouse dragged events
	virtual void mouseDragged(int x, int y);

	//! This is overrided to handle concurrent rendering 
	virtual void repaint(int x, int y, int w, int h);

	/* You must implement these methods */
	//! Render the entire canvas
	virtual void render() = 0;
	//! Render the portion of the canvas specified by the rectangle
	virtual void render(const CS123Rectangle&) = 0;
	//! This method can be used to control render settings 
	virtual void setRenderSetting(RayOptions option, int value) = 0;

	//! Override this method to load scenes.  
	/* When you override it, do NOT make it a slot.  Simply declare it
	 * as being a public method */
	public slots:
	    virtual void loadScene(const char* sceneFile) = 0;

    private:
	//! Don't worry about this - this is for concurrent rendering
	void repaintPrivate(int x, int y, int w, int h);
	MainSyscallProxy *m_mainProxy;
};

#endif

