#include <QApplication>
#include "RayApp.H"
#include "RayCanvas.H"
#include <MyRayCanvas.H>
#include <TAIntersectCanvas.H>
#include <TARayCanvas.H>
#include <TASceneviewCanvas.H>
#include <string.h>

/* This is the entry point to your application.  You should add
 * functionality to parse command line parameters to control your
 * render settings 
 */
int main(int argc, char** argv) {
    QApplication qApplication(argc, argv);
    RayApp app;

    /* Default width and height */
    int width = 500;
    int height = 500;

    /* Default scene to render 
     * When you get started, you should probably change to a much simpler scene 
     */
    const char* scene = "/course/cs123/data/scenes/ray/sphere_texture_test.xml";

    /* Start up a sceneview canvas to preview the scene quickly before
     * rendering.  Feel free to replace this with your implementation of
     * sceneview.
     */
    TASceneviewCanvas taSceneviewCanvas(width, height);
    taSceneviewCanvas.enableMarquee();
    app.addCanvas(&taSceneviewCanvas, "GL Preview");

    /* Starts up an intersect canvas - this is an implementation of the basic
     * ray tracing algorithm 
     */
    TAIntersectCanvas taCanvas(width, height);
    app.addCanvas(&taCanvas, "Intersect Demo");

    MyRayCanvas myRayCanvas(width, height);
    app.addCanvas(&myRayCanvas, "My Ray");

    /* Starts up a TASceneviewCanvas with default width 500 and height 500 
     * Here are two examples on how to set render settings.  You can find the
     * the possible setting options in RayCanvas.H */
    TARayCanvas taRayCanvas(width, height);
    taRayCanvas.setRenderSetting(RAY_OPTION_RECURSION_DEPTH, 6);
    taRayCanvas.setRenderSetting(RAY_OPTION_SUPERSAMPLING, 3);
    app.addCanvas(&taRayCanvas, "Ray Demo");

    /* Load scene in each canvas */
    taSceneviewCanvas.loadScene(scene);
    taCanvas.loadScene(scene);
    myRayCanvas.loadScene(scene);
    taRayCanvas.loadScene(scene);

    /* Start up your Canvas and add it to the app. */

    return qApplication.exec();
}

