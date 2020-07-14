#pragma once

#include <iostream>
#include <vector>
#include <array>

#include "../include/VertexBuffer.h"
#include "Cell.h"

using namespace std;

class Block{
    private:
        BlockType mBlockType;
        bool blockLayouts[8][25] = {
            {},
            {
                false,false,false,false,false,
                false,false,false,false,false,
                false,true,true,true,true,
                false,false,false,false,false,
                false,false,false,false,false
            },
            {
                false,false,false,false,false,
                false,true,false,false,false,
                false,true,true,true,false,
                false,false,false,false,false,
                false,false,false,false,false
            },
            {
                false,false,false,false,false,
                false,false,false,true,false,
                false,true,true,true,false,
                false,false,false,false,false,
                false,false,false,false,false
            },
            {
                false,false,false,false,false,
                false,false,true,true,false,
                false,false,true,true,false,
                false,false,false,false,false,
                false,false,false,false,false
            },
            {
                false,false,false,false,false,
                false,false,true,true,false,
                false,true,true,false,false,
                false,false,false,false,false,
                false,false,false,false,false
            },
            {
                false,false,false,false,false,
                false,false,true,false,false,
                false,true,true,true,false,
                false,false,false,false,false,
                false,false,false,false,false
            },
            {
                false,false,false,false,false,
                false,true,true,false,false,
                false,false,true,true,false,
                false,false,false,false,false,
                false,false,false,false,false
            }
        };

        int blockOffsetsJLSTZ[40] = {
            0,0, 0,0, 0,0, 0,0, 0,0,
            0,0, 1,0, 1,-1, 0,2, 1,2,
            0,0, 0,0, 0,0, 0,0, 0,0,
            0,0, -1,0, -1,-1, 0,2, -1,2
        };

        int blockOffsetsI[40] = {
            0,0, -1,0, 2,0, -1,0, 2,0,
            -1,0, 0,0, 0,0, 0,1, 0,-2,
            -1,1, 1,1, -2,1, 1,0, -2,0,
            0,1, 0,1, 0,1, 0,-1, 0,2
        };

        int blockOffsetsO[8] = {
            0,0,
            0,-1,
            -1,-1,
            -1,0,
        };

        bool mBlockLayout[25];
        int mR = 0;

    public:
        int mX;
        int mY;
        Cell mCells[25];
        Block(int x, int y, BlockType type, float cw, float h);
        ~Block();
        void update();
        void rotateLeft(Cell grid[]);
        void rotateRight(Cell grid[]);
        bool testOffset(Cell grid[], int testBlock[], int x, int y);
        array<int, 2> offset(bool isLeft, int testBlock[], Cell grid[]);
        vector<array<Vertex, 4>> getQuadsVertices();
        void setPosition(int x, int y);

        inline BlockType getColor() const {return mBlockType;};
};