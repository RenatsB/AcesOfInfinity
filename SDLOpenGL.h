#ifndef SDLOPENGL_H_
#define SDLOPENGL_H_
#include <SDL.h>
#include <string>

/// \brief SDL Opengl context creator
/// \author Jonathan Macey
/// \brief Taken from an existing project. Was kept intact ever since.
/// Jonathan Macey (February 22, 2016). SDLOpenGL Project [online].
/// [Accessed 2017]. Available from: "https://github.com/jmacey/-SDLOpenGL".
/// \class SDLOpenGL
/// \brief SDL Opengl context creator

class SDLOpenGL
{
  public :
    SDLOpenGL(const std::string &_name, int _x, int _y, int _width, int _height);

    void makeCurrent() { SDL_GL_MakeCurrent(m_window,m_glContext);}
    void swapWindow() { SDL_GL_SwapWindow(m_window); }

    void pollEvent(SDL_Event &_event);

  private :
    /// @brief width of screen
    int m_width;
    /// @brief height of screen
    int m_height;
    // xpos of window
    int m_x;
    // ypos of window
    int m_y;
    // name of window
    std::string m_name;

    void init();

    SDL_GLContext m_glContext;
    void createGLContext();

    void ErrorExit(const std::string &_msg) const;

    SDL_Window *m_window;

}; //end of class

#endif
