#ifndef __RAYAPP_H__
#define __RAYAPP_H__

#include <QMainWindow>
#include <QColor>
#include <QStack>

class RayCanvas;
class SceneviewCanvas;
class CS123Canvas;
class CS123CanvasContainer;
class CS123OpenGLCanvasContainer;

class RayApp : public QMainWindow {
    Q_OBJECT

    public:
	RayApp();
	~RayApp();

	void addCanvas(RayCanvas* canvas);
	void addCanvas(RayCanvas* canvas, const char* title);
	void addCanvas(SceneviewCanvas* canvas);
	void addCanvas(SceneviewCanvas* canvas, const char* title);

    private slots:
	void loadPressed();
	void savePressed();
	void render();
	void selectionChanged(int x1, int y1, int x2, int y2);

    protected:
	CS123Canvas *getActiveCanvas(const char *);

    private:
	QStack<CS123CanvasContainer*> m_canvases;
	QStack<CS123OpenGLCanvasContainer*> m_glcanvases;
	int m_noCanvas, m_selectedCombo;
};

#endif

