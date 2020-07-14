#include "Block.h"
#include <math.h>

Block::Block(int x, int y,  BlockType type, float cw, float ch):
    mX(x), mY(y),
    mBlockType(type)
{

    copy(begin(blockLayouts[type]), end(blockLayouts[type]), begin(mBlockLayout));

    unsigned int scale = 5;
    
    for(unsigned int i = 0; i < 25; i++){
        unsigned int cy = mY + floor(i / scale);
        unsigned int cx = mX + i%scale;

        Cell cell(cx, cy, cw, ch);

        if(mBlockLayout[i])
            cell.updateColor(mBlockType);

        mCells[i] = cell;
    }
}

Block::~Block(){

}

void Block::setPosition(int x, int y){
    mX = x;
    mY = y;
    update();
}

void Block::update(){
    unsigned int scale = 5;
    
    for(unsigned int i = 0; i < 25; i++){
        int cy = mY + floor(i / scale);
        int cx = mX + i%scale;
        mCells[i].setPosition(cx, cy);
        mCells[i].updateColor(mBlockLayout[i] == none ? none : mBlockType);
    }
}

array<int, 2> Block::offset(bool isLeft, int testBlock[], Cell grid[]){
    int r = mR + (isLeft ? -1 : 1);
    r = r == -1 ? 3 : r == 4 ? 0 : r;

    if(mBlockType == I){
        for(unsigned int i = 0; i < 5; i++){
            int rIndex = 10 * r;
            int mRIndex = 10 * mR;

            int x = blockOffsetsI[mRIndex+i*2] - blockOffsetsI[rIndex+i*2];
            int y = (blockOffsetsI[mRIndex+i*2+1] - blockOffsetsI[rIndex+i*2+1]);
            
            if(testOffset(grid, testBlock, -x, y))
                return {-x, y};
        }
    }else if(mBlockType == O){
        for(unsigned int i = 0; i < 1; i++){
            int rIndex = 2 * r;
            int mRIndex = 2 * mR;

            int x = blockOffsetsO[mRIndex+i*2] - blockOffsetsO[rIndex+i*2];
            int y = (blockOffsetsO[mRIndex+i*2+1] - blockOffsetsO[rIndex+i*2+1]);
            
            if(testOffset(grid, testBlock, -x, y)){
                return {-x, y};
            }
        }
    }else{
        for(unsigned int i = 0; i < 5; i++){
            int rIndex = 10 * r;
            int mRIndex = 10 * mR ;

            int x = blockOffsetsJLSTZ[mRIndex+i*2] - blockOffsetsJLSTZ[rIndex+i*2];
            int y = (blockOffsetsJLSTZ[mRIndex+i*2+1] - blockOffsetsJLSTZ[rIndex+i*2+1]);
            
            if(testOffset(grid, testBlock, -x, y)){
                return {-x, y};
            }
        }
    }

    return{1000, 1000};
}

bool Block::testOffset(Cell grid[], int testBlock[], int x, int y){
    y += mY;
    x += mX;

    unsigned int scale = 5;

    for(unsigned int i; i < 25; i++){
        int cy = y + floor(i / scale);
        int cx = x + i%scale;
        int index = cy*10 + cx;

        if((grid[index].getColor() != none || cy < 0 || cx < 0 || cx >= 10 || cy >= 20) && testBlock[i] != none)
            return false;
    }

    return true;
}

void Block::rotateRight(Cell grid[]){
    unsigned int scale = 5;

    int temp[25];

    for(unsigned int i = 0; i < 25; i++){
        int cy = floor(i / scale);
        int cx = i%scale;

        temp[i] = mBlockLayout[cx*scale + cy];
    }

    int temp1[25];

    for(unsigned int i = 0; i < 25; i++){
        int cy = floor(i / scale);
        int cx = i%scale;

        temp1[i] = temp[24 - scale*cy + 1 - scale + cx];
    }
    
    array<int, 2> offsetTest = offset(false, temp1, grid);

    if(offsetTest[0] != 1000 && offsetTest[1] != 1000){
        copy(begin(temp1), end(temp1), begin(mBlockLayout));
        mX += offsetTest[0];
        mY += offsetTest[1];
        mR = mR +1 == 4 ? 0 : mR +1;
    }
}

void Block::rotateLeft(Cell grid[]){
    unsigned int scale = 5;

    int temp[25];

    for(unsigned int i = 0; i < 25; i++){
        int cy = floor(i / scale);
        int cx = i%scale;

        temp[i] = mBlockLayout[cx*scale + cy];
    }

    int temp1[25];

    for(unsigned int i = 0; i < 25; i++){
        int cy = floor(i / scale);
        int cx = i%scale;

        temp1[i] = temp[scale - 1 - cx + scale*cy];
    }
    
    array<int, 2> offsetTest = offset(true, temp1, grid);

    if(offsetTest[0] != 1000 && offsetTest[1] != 1000){
        copy(begin(temp1), end(temp1), begin(mBlockLayout));
        mX += offsetTest[0];
        mY += offsetTest[1];
        mR = mR -1 == -1 ? 3 : mR -1;
    }
}

vector<array<Vertex, 4>> Block::getQuadsVertices(){
    vector<array<Vertex, 4>> quads;

    for(unsigned int i = 0; i < 25; i++){
        quads.push_back(mCells[i].getQuadVertices());
    }

    return quads;
}