#ifndef MESH_H
#define MESH_H
#ifdef WIN32
  #include <Windows.h> // must be before gl.h include
#endif

#if defined (__linux__) || defined (WIN32)
    #include <GL/gl.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#endif

class Mesh
{
  public :
    static void bullet(float _scale);
    static void cube(GLfloat _w, GLfloat _h, GLfloat _d);
    static void shipTest(float _scale);
    static void ship1(float _scale);
    static void ship2(float _scale);
    static void ship3(float _scale);
    static void asteroid(float _scale); //temp
    static void asteroid1(float _scale); //not ready
    static void asteroid2(float _scale); //not ready
    //make class abstract as we don't need it to be constructed
    virtual double getVolume() = 0;
};
#endif // MESH_H
