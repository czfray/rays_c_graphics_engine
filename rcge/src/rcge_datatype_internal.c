//RCGE Internal
#include <glfw/glfw3.h>
#include <rcge/internal/rcge_datatype_internal.h>

unsigned int rcge_datatype_to_gl(rcge_datatype datatype)
{
    switch(datatype)
    {
        case DATATYPE_BYTE:
            return (unsigned int)(GL_BYTE);
        case DATATYPE_UNSIGNED_BYTE:
            return (unsigned int)(GL_UNSIGNED_BYTE);
        case DATATYPE_SHORT:
            return (unsigned int)(GL_SHORT);
        case DATATYPE_UNSIGNED_SHORT:
            return (unsigned int)(GL_UNSIGNED_SHORT);
        case DATATYPE_INT:
            return (unsigned int)(GL_INT);
        case DATATYPE_UNSIGNED_INT:
            return (unsigned int)(GL_UNSIGNED_INT);
        case DATATYPE_FLOAT:
            return (unsigned int)(GL_FLOAT);
        case DATATYPE_DOUBLE:
            return (unsigned int)(GL_DOUBLE);
    }
    return (unsigned int)(GL_FLOAT);
}

unsigned int rcge_datatype_size(rcge_datatype datatype)
{
    switch(datatype)
    {
        case DATATYPE_BYTE:
            return sizeof(char);
        case DATATYPE_UNSIGNED_BYTE:
            return sizeof(unsigned char);
        case DATATYPE_SHORT:
            return sizeof(short);
        case DATATYPE_UNSIGNED_SHORT:
            return sizeof(unsigned short);
        case DATATYPE_INT:
            return sizeof(int);
        case DATATYPE_UNSIGNED_INT:
            return sizeof(unsigned int);
        case DATATYPE_FLOAT:
            return sizeof(float);
        case DATATYPE_DOUBLE:
            return sizeof(double);
    }
    return sizeof(float);
}