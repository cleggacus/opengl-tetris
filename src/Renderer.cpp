#include "include/Renderer.h"
#include <iostream> 

using namespace std;

void glClearError(){
    while(glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line){
    while(GLenum error = glGetError()){
        cout << "Error: [OpenGL] (" << error << ") : at function " << function << " at file " << file << " : at line " << line << "\n";
        return false;
    }
    
    return true;
}

void Renderer::clear() const{
    glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
    shader.bind();
    va.bind();
    ib.bind();
    
    glCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
} 