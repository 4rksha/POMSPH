
#include "app.h"
#include "glcore.h"
#include <cstdio>
#include <cstring>

App::App( const int width, const int height, const int major, const int minor )
    : m_window(nullptr), m_context(nullptr)
{
    m_window= create_window(width, height);
    m_context= create_context(m_window, major, minor);
}

App::~App( )
{
    if(m_context)
        release_context(m_context);
    if(m_window)
        release_window(m_window);
}

int App::run( )
{
    if(init() < 0)
        return -1;

    // configure openGL
    glViewport(0, 0, window_width(), window_height());

    // utiliser SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency() si la precision n'est pas suffisante
    m_time= SDL_GetTicks();
    while(events(m_window))
    {
        m_delta= SDL_GetTicks() - m_time;
        if(update(global_time(), delta_time()) < 0)
            break;
        if(render() < 1)
            break;

        m_time= SDL_GetTicks();

        // presenter le resultat
        SDL_GL_SwapWindow(m_window);
    }

    if(quit() < 0)
        return -1;
    return 0;
}

float App::global_time( )
{
    return (float) m_time;
}

float App::delta_time( )
{
    return (float) m_delta;
}
