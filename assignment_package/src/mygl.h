#ifndef MYGL_H
#define MYGL_H

#include <openglcontext.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cube.h>
#include <scene/worldaxes.h>
#include "camera.h"
#include <terrains.h>
#include "texture.h"
#include <scene/quad.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <smartpointerhelp.h>

using namespace std;
using namespace glm;

class MyGL : public OpenGLContext
{
    Q_OBJECT
private:
    uPtr<Cube> mp_geomCube;// The instance of a unit cube we can use to render any cube. Should NOT be used in final version of your project.
    uPtr<WorldAxes> mp_worldAxes; // A wireframe representation of the world axes. It is hard-coded to sit centered at (32, 128, 32).
    uPtr<ShaderProgram> mp_progLambert;// A shader program that uses lambertian reflection
    uPtr<ShaderProgram> mp_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)
    uPtr<ShaderProgram> mp_sky;
    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    uPtr<Camera> mp_camera;
    uPtr<Terrain> mp_terrain;
    uPtr<Terrain> mp_terrainTrans;
    uPtr<Texture> mp_texture;
    uPtr<Quad> mp_geomQuad;
    int m_time;

    /// Timer linked to timerUpdate(). Fires approx. 60 times per second
    QTimer timer;
int count;
    void MoveMouseToCenter(); // Forces the mouse position to the screen's center. You should call this
                              // from within a mouse move event after reading the mouse movement so that
                              // your mouse stays within the screen bounds and is always read.


public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void GLDrawScene();
    void removeblock();
    void addblock();
    float dis(vec3 p1, vec3 p2);
    void boundcheck();
    void performPostprocessRenderPass();
    void createRenderBuffers();
    GLuint m_frameBuffer;
    GLuint m_renderedTexture;
    GLuint m_depthRenderBuffer;
    //Quad m_geomQuad;
    //PostProcessShader* m_postProcessNoop;
protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);

private slots:
    /// Slot that gets called ~60 times per second
    void timerUpdate();
};


#endif // MYGL_H
