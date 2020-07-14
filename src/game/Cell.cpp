#include "Cell.h"


Cell::Cell(unsigned int x, unsigned int y, float w, float h):
    mX(x), mY(y),
    mCellW(w), mCellH(h),
    mColor(none)
{
    
}

Cell::~Cell(){

}

void Cell::setPosition(unsigned int x, unsigned int y){
    mX = x;
    mY = y;
}

void Cell::updateColor(BlockType c){
    mColor = c;
}

array<Vertex, 4> Cell::getQuadVertices(){
    float x(mX*mCellW);
    float y(mY*mCellH);

    Vertex v0{x, y, 0.0f, 0.0f, mColor};
    Vertex v1{x+mCellW, y, 1.0f, 0.0f, mColor};
    Vertex v2{x+mCellW, y+mCellH, 1.0f, 1.0f, mColor};
    Vertex v3{x, y+mCellH, 0.0f, 1.0f, mColor};

    return {v0, v1, v2, v3};
}