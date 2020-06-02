
#include <cstdio>

#include "buffer.h"


GLuint make_buffer( const GLenum target, const size_t data_size, const void *data, const GLenum usage )
{
    if(data_size == 0)
    {
        printf("[error] 0B buffer...\n");
        return 0;
    }

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, data_size, data, usage);
    return buffer;
}


GLuint create_vertex_format( )
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

void release_vertex_format( const GLuint vao )
{
    if(vao == 0)
        return;

    glBindVertexArray(vao);

    GLint n= 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);

    // recupere les vertex buffers associes au vao
    GLuint buffer= 0;
    for(int i= 0; i < n; i++)
    {
        glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, (GLint *) &buffer);
        if(buffer > 0)
            glDeleteBuffers(1, &buffer);
    }

    // et l'index buffer
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint *) &buffer);
    if(buffer > 0)
        glDeleteBuffers(1, &buffer);

    glDeleteVertexArrays(1, &vao);
}


GLuint make_vertex_buffer( const GLuint vao, const GLint attribute,
    const int size, const GLenum type, const size_t data_size, const void *data )
{
    if(attribute < 0)
        return 0;

#ifndef GK_RELEASE
    // verifie que le vertex array est selectionne
    GLuint current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *) &current);
    if(current != vao)
    {
        printf("[error] wrong vertex array %u...\n", current);
        glBindVertexArray(vao);
    }
#endif

    GLuint buffer= make_buffer(GL_ARRAY_BUFFER, data_size, data);
    if(buffer > 0)
    {
        // configure l'utilisation du buffer
        glVertexAttribPointer(attribute, size, type, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(attribute);
    }
    return buffer;
}

GLuint make_index_buffer( const GLuint vao, const size_t data_size, const void *data )
{
#ifndef GK_RELEASE
    // verifie que le vertex array est selectionne
    GLuint current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *) &current);
    if(current != vao)
    {
        printf("[error] wrong vertex array %u...\n", current);
        glBindVertexArray(vao);
    }
#endif

    GLuint buffer= make_buffer(GL_ELEMENT_ARRAY_BUFFER, data_size, data);
    return buffer;
}


bool update_buffer( const GLenum target, const size_t data_size, const void *data )
{
#ifndef GK_RELEASE
    GLint buffer_size= 0;
    glGetBufferParameteriv(target, GL_BUFFER_SIZE, &buffer_size);
    if((size_t) buffer_size < data_size)
    {
        printf("[error] updating small buffer %d < %d...\n", (int) buffer_size, (int) data_size);
        glBufferData(target, data_size, data, GL_STATIC_DRAW);
        return false;
    }
#endif
    
    glBufferSubData(target, 0, data_size, data);
    return true;
}

bool update_vertex_buffer( const GLuint vao, const GLint attribute, const size_t data_size, const void *data )
{
#ifndef GK_RELEASE
    // verifie que le vertex array est selectionne
    GLuint current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *) &current);
    if(current != vao)
    {
        printf("[error] wrong vertex array %u...\n", current);
        glBindVertexArray(vao);
    }
#endif

    GLuint buffer= 0;
    glGetVertexAttribiv(attribute, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, (GLint *) &buffer);
    if(buffer == 0)
        return false;
    
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    return update_buffer(GL_ARRAY_BUFFER, data_size, data);
}

bool update_index_buffer( const GLuint vao, const size_t data_size, const void *data )
{
#ifndef GK_RELEASE
    // verifie que le vertex array est selectionne
    GLuint current;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *) &current);
    if(current != vao)
    {
        printf("[error] wrong vertex array %u...\n", current);
        glBindVertexArray(vao);
    }
#endif

    // recupere l'index buffer
    GLuint buffer;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint *) &buffer);    
    if(buffer == 0)
        return false;
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    return update_buffer(GL_ELEMENT_ARRAY_BUFFER, data_size, data);
}


