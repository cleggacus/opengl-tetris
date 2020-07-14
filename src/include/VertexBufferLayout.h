#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream> 

using namespace std;

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static unsigned int getSizeOfType(unsigned int type ){
        switch(type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }

        return 0;
    };
};

class VertexBufferLayout{
    private: 
        vector<VertexBufferElement> mElements;
        unsigned int mStride;
    public:
        template<typename T>
        void push(unsigned int count){
            cout << "bad\n";
        }       

        VertexBufferLayout() : mStride(0){};

        inline const vector<VertexBufferElement> getElements() const{ return mElements; }
        inline unsigned int getStride() const{ return mStride; }
};