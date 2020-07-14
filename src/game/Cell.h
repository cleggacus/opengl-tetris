#pragma once

#include <iostream>
#include <array>

#include "../include/VertexBuffer.h"

using namespace std;

struct Vertex{
    float positionX;
    float positionY;
    float texCoordX;
    float texCoordY;
    float color;
};

enum BlockType {
    none, I, J, L, O, S, T, Z
};

class Cell{
    private:
        unsigned int mX;
        unsigned int mY;
        float mCellW;
        float mCellH;
        BlockType mColor;

    public:
        Cell(unsigned int x = 0, unsigned int y = 0, float w = 0, float h = 0);
        ~Cell();
        void updateColor(BlockType c);
        array<Vertex, 4> getQuadVertices();
        void setPosition(unsigned int x, unsigned int y);

        inline BlockType getColor() const {return mColor;};
        inline unsigned int getX() const {return mX;};
        inline unsigned int getY() const {return mY;};
        inline unsigned int getCellWidth() const {return mCellW;};
        inline unsigned int getCellHeight() const {return mCellH;};
};