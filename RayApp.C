/*************************************************************************
 *    NAME: Nong Li
 *    USER: nli
 *    FILE: RayApp.C
 *    DATE: Thu May 10 16:30:58 2007
 *************************************************************************/
#include "RayApp.H"
#include "RayCanvas.H"
#include <RenderThread.H>
#include <SceneviewCanvas.H>
#include <QtGui>
#include <iostream>
using namespace std;

/*************************************************************************
 * Function Name: RayApp::RayApp
 * Parameters: 
 * Effects: 
 *************************************************************************/
RayApp::RayApp() : QMainWindow(), 
    m_noCanvas(0), m_selectedCombo(-1)
{
    QPalette plastique;
    QApplication::setStyle("plastique");

    QColor brightText, base, highlight, button, mid,
	   text, windowText, buttonText, window, 
	   highlightedText;

    highlightedText.setRgb(255,255,255);
    base.setRgb(255,255,255);
    highlight.setRgb(0,0,100);
    button.setRgb(240,240,240);
    mid.setRgb(75,75,75);
    brightText.setRgb(0,0,0);
    text.setRgb(0,0,0);
    windowText.setRgb(0,0,0);
    buttonText.setRgb(0,0,0);
    window.setRgb(255,255,255);

    plastique.setBrush(QPalette::HighlightedText, highlightedText);
    plastique.setBrush(QPalette::BrightText, brightText);
    plastique.setBrush(QPalette::Base, base);
    plastique.setBrush(QPalette::Highlight, highlight);
    plastique.setBrush(QPalette::Button, button);
    plastique.setBrush(QPalette::Mid, mid);
    plastique.setBrush(QPalette::Text, text);
    plastique.setBrush(QPalette::WindowText, windowText);
    plastique.setBrush(QPalette::ButtonText, buttonText);
    plastique.setBrush(QPalette::Window, window);

    QApplication::setPalette(plastique);

    setWindowTitle(tr("Ray"));
    setDockOptions(dockOptions() | QMainWindow::ForceTabbedDocks);

    QMenu* file = menuBar()->addMenu(QString("&File"));
    QMenu* ray_options = menuBar()->addMenu(QString("Ray &Options"));

    file->addAction(QString("&Load"), this, SLOT(loadPressed()));
    file->addAction(QString("&Save"), this, SLOT(savePressed()));
    file->addAction(QString("&Quit"), qApp, SLOT(quit()));

    ray_options->addAction(QString("&Render"), this, SLOT(render()));

    QPalette palette(qApp->palette());
    palette.setColor(QPalette::Highlight, QColor(157, 187, 227));
    qApp->setPalette(palette);

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    show();
}


/*************************************************************************
 * Function Name: RayApp::~RayApp
 * Parameters: 
 * Effects: 
 *************************************************************************/
RayApp::~RayApp() {
}

/*************************************************************************
 * Function Name: RayApp::addCanvas
 * Parameters: CS123Canvas* canvas, const char* title
 * Returns: void
 * Effects: 
 *************************************************************************/
void RayApp::addCanvas(RayCanvas* canvas, const char* title) {
    // all dockwidgets must go into same area if you want them to be tabbed
    Qt::DockWidgetArea area = Qt::RightDockWidgetArea;

    setUpdatesEnabled(false);

    CS123CanvasContainer *container = new CS123CanvasContainer(canvas, title);
    addDockWidget(area, container);
    if (!m_canvases.isEmpty())
	tabifyDockWidget(m_canvases.top(), container);

    if (!m_glcanvases.isEmpty())
	tabifyDockWidget(m_glcanvases.top(), container);

    m_canvases.push(container);

    setUpdatesEnabled(true);
    ++m_noCanvas;
    
    connect(canvas, SIGNAL(selectionChanged(int, int, int, int)), this,
		SLOT(selectionChanged(int, int, int, int)));
}


/*************************************************************************
 * Function Name: RayApp::addCanvas
 * Parameters: CS123Canvas* canvas
 * Returns: void
 * Effects: 
 *************************************************************************/
void RayApp::addCanvas(RayCanvas* canvas) {
    addCanvas(canvas, "Canvas");
}

void RayApp::addCanvas(SceneviewCanvas* canvas, const char* title) {
    // all dockwidgets must go into same area if you want them to be tabbed
    Qt::DockWidgetArea area = Qt::RightDockWidgetArea;

    setUpdatesEnabled(false);
    CS123OpenGLCanvasContainer *container = new CS123OpenGLCanvasContainer(canvas, title);
    addDockWidget(area, container);
    if (!m_canvases.isEmpty())
	tabifyDockWidget(m_canvases.top(), container);

    if (!m_glcanvases.isEmpty())
	tabifyDockWidget(m_glcanvases.top(), container);

    m_glcanvases.push(container);
    setUpdatesEnabled(true);

    connect(canvas, SIGNAL(selectionChanged(int, int, int, int)), this,
		SLOT(selectionChanged(int, int, int, int)));
}

void RayApp::addCanvas(SceneviewCanvas* canvas) {
    addCanvas(canvas, "Opengl Render");
}

void RayApp::selectionChanged(int x1, int y1, int x2, int y2) {
    CS123Rectangle r;
    r.minX = MIN(x1, x2);
    r.minY = MIN(y1, y2);
    r.maxX = MAX(x1, x2);
    r.maxY = MAX(y1, y2);

    foreach(CS123CanvasContainer * container, m_canvases) {
	if (container != NULL) {
	    CS123Canvas* canvas = container->getCanvas();
	    canvas->setSelection(r);
	}
    }
    foreach(CS123OpenGLCanvasContainer* container, m_glcanvases) {
	if (container != NULL) {
	    CS123OpenGLCanvas* canvas = container->getCanvas();
	    canvas->setSelection(r);
	}
    }
}

void RayApp::render() {
    printf("Render\n");

    RenderThread* threads[m_noCanvas];
    int i = 0;

    CS123Rectangle region = {-1, -1, -1, -1};
    bool regionEnabled = false;

    foreach(CS123OpenGLCanvasContainer* container, m_glcanvases) {
	CS123OpenGLCanvas* canvas = container->getCanvas();

	if (canvas->hasMarquee()) {
	    regionEnabled = true;
	    region = canvas->getSelection();
	    break;
	}
    }

    foreach(CS123CanvasContainer* container, m_canvases) {
	RayCanvas* c = (RayCanvas*)container->getCanvas();
	if (regionEnabled)
	    threads[i] = new RenderThread(c, region);
	else
	    threads[i] = new RenderThread(c);
	i++;
    }

    for (i = 0; i < m_noCanvas; i++)
	threads[i]->start();

    /*
    for (i = 0; i < m_noCanvas; i++) {
	delete threads[i];
    }
    */
}

void RayApp::loadPressed() {
    const QString &fileName = QFileDialog::getOpenFileName(
	    this, 
	    "Choose a file to open",
	    "/course/cs123/data/scenes",
	    "Images (*.xml)");

    if (fileName.isEmpty())
	return;    
    
    foreach(CS123OpenGLCanvasContainer* container, m_glcanvases) {
	SceneviewCanvas* canvas = (SceneviewCanvas*)container->getCanvas();
	canvas->loadScene(fileName.toAscii().data());
    }    
    
    foreach(CS123CanvasContainer* container, m_canvases) {
	RayCanvas* canvas = (RayCanvas*)container->getCanvas();
	canvas->loadScene(fileName.toAscii().data());
    }
    
}

void RayApp::savePressed() {
    const QString &fileName = QFileDialog::getSaveFileName(
	    this,
	    "Choose a filename to save to",
	    "./",
	    "Images (*.png, *.jpg *.tiff");

    if (fileName.isEmpty())
	return;

    CS123Canvas *active = getActiveCanvas("Select the canvas you would like to save:");

    bool success = (active ? active->save(fileName.toAscii().data()) : false);
    if (!success && active)
	QMessageBox::warning(this, "Error", QString("Could not save to file '%1'").arg(fileName));
}

CS123Canvas *RayApp::getActiveCanvas(const char *text) {
    CS123Canvas *visible = NULL;

    QComboBox *available = new QComboBox(this);
    foreach(CS123CanvasContainer *container, m_canvases) {
	if (container != NULL)
	    available->addItem(container->getTitle());
    }

    connect(available, SIGNAL(currentIndexChanged(int)), this, SLOT(selectComboBox(int)));

    QDialog *d = new QDialog(this);
    d->setModal(true);
    QGridLayout *l = new QGridLayout(d);
    QLabel *label = new QLabel(QString(text), this);
    l->addWidget(label, 0, 0);
    l->addWidget(available, 1, 0);
    QPushButton *okay = new QPushButton(tr("Okay"), this);
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);

    l->addWidget(okay, 2, 0);
    l->addWidget(cancel, 2, 1);

    d->setLayout(l);

    connect(okay, SIGNAL(released()), d, SLOT(accept()));
    connect(cancel, SIGNAL(released()), d, SLOT(reject()));

    m_selectedCombo = 0;
    int res = d->exec();

    if (res == QDialog::Rejected)
	return NULL;

    int i = 0;
    foreach(CS123CanvasContainer *container, m_canvases) {
	if (i++ == m_selectedCombo) {
	    visible = container->getCanvas();
	    break;
	}
    }

    return visible;
}

