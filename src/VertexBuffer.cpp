#include "include/VertexBuffer.h"
#include "include/Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, const bool isStatic){
    glCall(glGenBuffers(1, &mRendererId));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer(){
    glCall(glDeleteBuffers(1, &mRendererId));
}

void VertexBuffer::populateData(const void* data, unsigned int size, unsigned int offset){
    glCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
    glCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void VertexBuffer::bind() const{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
}

void VertexBuffer::unBind() const{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}