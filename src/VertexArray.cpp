#include "include/VertexArray.h"
#include "include/Renderer.h"

VertexArray::VertexArray(){
    glCall(glGenVertexArrays(1, &mRendererId));
}

VertexArray::~VertexArray(){
    glCall(glDeleteVertexArrays(1, &mRendererId));
}

void VertexArray::bind() const{
    glCall(glBindVertexArray(mRendererId));
}

void VertexArray::unBind() const{
    glCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
    bind();
    vb.bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;

    for(unsigned int i = 0; i < elements.size(); i++){
        const auto& element = elements[i];
        glCall(glEnableVertexAttribArray(i));
        glCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }

}