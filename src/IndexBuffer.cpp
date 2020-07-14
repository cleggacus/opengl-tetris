#include "include/IndexBuffer.h"
#include "include/Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : mCount(count){
    glCall(glGenBuffers(1, &mRendererId));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer(){
    glCall(glDeleteBuffers(1, &mRendererId));
}

void IndexBuffer::bind() const{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId));
}

void IndexBuffer::unBind() const{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}