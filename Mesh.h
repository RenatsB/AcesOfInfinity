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

/// \brief Geometry container
/// \author Renats Bikmajevs

/// \class Mesh
/// \brief A container of all game geometry (ABC)

class Mesh
{
  public :
    /// \brief method to draw bullet shape
    /// \param[in] _scale scale of the drawn geometry
    static void bullet(float &_scale);
    /// \brief method to draw Simple Ship shape (for testing)
    /// \param[in] _scale scale of the drawn geometry
    static void shipTest(float &_scale);
    /// \brief method to draw a Terran Interceptor shape
    /// \param[in] _scale scale of the drawn geometry
    static void ship1(float &_scale);
    /// \brief method to draw a Pirate Interceptor shape
    /// \param[in] _scale scale of the drawn geometry
    static void ship2(float &_scale);
    /// \brief method to draw an Alien Interceptor shape
    /// \param[in] _scale scale of the drawn geometry
    static void ship3(float &_scale);
    /// \brief method to draw an Asteroid shape
    /// \param[in] _scale scale of the drawn geometry
    static void asteroid(float &_scale);
    //make class abstract as we don't need it to be constructed
    virtual double getVolume() = 0;
}; //end of class
#endif // MESH_H
