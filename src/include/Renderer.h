#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "signal.h"

#define ASSERT(x) if(!(x)) raise(SIGTRAP)
#define glCall(x) glClearError();\
    x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();
bool glLogCall(const char* function, const char* file, int line);

class Renderer{
    private: 
    public: 
        void clear() const;
        void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};