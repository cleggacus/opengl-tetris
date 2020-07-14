#include "include/VertexBufferLayout.h"

template<>
void VertexBufferLayout::push<float>(unsigned int count){
    mElements.push_back({GL_FLOAT, count, GL_FALSE});
    mStride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count){
    mElements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    mStride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count){
    mElements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    mStride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}