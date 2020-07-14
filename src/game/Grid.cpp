#include "Grid.h"

#include <math.h>

Grid::Grid(unsigned int width, unsigned int height, unsigned int widthMap, unsigned int heightMap) :
    mWidth(width), mHeight(height),
    mWidthMap(widthMap), mHeightMap(heightMap),
    mProj(glm::ortho(0.0f, 400.0f, 0.0f, 800.0f, -1.0f, 1.0f)),
    mTranslation(0, 0, 0),
    mVa(),
    mIb({}, 400*6),
    mVb(nullptr, 5 * 4 * 400 * sizeof(float), false),
    mLayout(),
    mShader("res/shaders/basic.shader"),
    mTexture("res/textures/block.png"),
    mBlock(5, 10, L, widthMap / width, heightMap / height)
{
    float cellWidth = widthMap / width;
    float cellHeight = heightMap / height;

    for(unsigned int i = 0; i < width * height; i++){
        unsigned int y = floor(i / width);
        unsigned int x = floor(i - width * floor(i / width));

        Cell cell(x, y, cellWidth, cellHeight);
        mCells.push_back(cell);

        int indices[6] = {
            i*4, i*4+ 1, i*4+ 2,
            i*4+ 2, i*4+ 3, i*4
        };

        for(unsigned int j = 0; j < 6; j++){
            mIndices[i*6 +j] = (indices[j]);
        }
    }
    
    mLayout.push<float>(2);
    mLayout.push<float>(2);
    mLayout.push<float>(1);
    mVa.addBuffer(mVb, mLayout);

    mTexture.bind();

    mShader.bind();
    mShader.setUniform1i("uTexture", 0);
    srand((unsigned int)time(NULL));
    initBlock();
    onUpdate();
}

Grid::~Grid(){

}

void Grid::initBlock(){
    BlockType blockType((BlockType)round(rand()%7+1));
    mBlock = Block(round(rand()%(mWidth-6)), mHeight-5, blockType, mWidthMap / mWidth, mHeightMap / mHeight);
    for(unsigned int i = 0; i < 5; i++)
        moveUp();
    
    onUpdate();
}

void Grid::commitBlock(){
    for(unsigned int i = 0; i < 25; i ++){
        if(mBlock.mCells[i].getColor() != none){
            bool check;
            int cellCheck;

            tie(check, cellCheck) = getCell(mBlock.mCells[i].getX(), mBlock.mCells[i].getY());

            if(check){
                mCells[cellCheck].updateColor(mBlock.mCells[i].getColor());
            }
        }
    }
    
    onUpdate();
}

tuple<bool, int> Grid::getCell(unsigned int x, unsigned int y){
    unsigned int index (x+(mWidth*y));
    if(x >= 0 && x < mWidth && y >= 0 && y < mHeight)
        return {true, (x+(mWidth*y))};

    return {false, NULL};
}

void Grid::updateGrid(){
    int rowCheckCount = 0;
    vector<int> removeList;

    for(unsigned int i = 0; i < mWidth * mHeight; i++){
        array<Vertex, 4> quad(mCells[i].getQuadVertices());

        if(i%mWidth == 0)
            rowCheckCount = 0;

        if(mCells[i].getColor() != none)
            rowCheckCount++;

        if(rowCheckCount == mWidth){
            removeList.push_back(round(i/mHeight));
        }

        for(unsigned int j = 0; j < 4; j++){
            mVb.populateData(&quad[j], 5 * sizeof(float), (j + i * 4) * 5 * sizeof(float));
        }
    }

    for(unsigned int i = 0; i < removeList.size(); i++){
        removeRow(removeList[i]);
    }
}

void Grid::removeRow(int row){
    for(unsigned int i = (row+1)*mWidth; i < mWidth * mHeight; i++){
        mCells[i-mWidth] = mCells[i];
        mCells[i-mWidth].setPosition(mCells[i-mWidth].getX(), mCells[i-mWidth].getY()-1);

        if(i >= mWidth*(mHeight-1))
            mCells[i].updateColor(none);
    }
}

void Grid::updateBlock(){
    mBlock.update();
    
    vector<array<Vertex, 4>> blockQuads = mBlock.getQuadsVertices();
    
    for(unsigned int i= 0; i < blockQuads.size(); i++){
        if(mBlock.mCells[i].getColor() != none){
            unsigned int y = mBlock.mCells[i].getY();
            unsigned int x = mBlock.mCells[i].getX();
            
            array<Vertex, 4> quad(blockQuads[i]);

            for(unsigned int j = 0; j < 4; j++){
                mVb.populateData(&quad[j], 5 * sizeof(float), (j + (y*mWidth + x) * 4) * 5 * sizeof(float));
            }
        }
    }
}

void Grid::rotateLeft(){
    mBlock.rotateLeft(&mCells[0]);
    onUpdate();
}

void Grid::rotateRight(){
    mBlock.rotateRight(&mCells[0]);
    onUpdate();
}

void Grid::moveLeft(){
    bool canMove = true;
    for(unsigned int i = 0; i < 25; i++)
        if(mBlock.mCells[i].getColor() != none && cellCollidingLeft(mBlock.mCells[i]))
            canMove = false;

    if(canMove)
        mBlock.mX --;

    onUpdate();
}

void Grid::moveRight(){
    bool canMove = true;
    for(unsigned int i = 0; i < 25; i++)
        if(mBlock.mCells[i].getColor() != none && cellCollidingRight(mBlock.mCells[i]))
            canMove = false;

    if(canMove)
        mBlock.mX ++;

    onUpdate();
}

void Grid::moveDown(){
    bool canMove = true;

    for(unsigned int i = 0; i < 25; i++){
        if(mBlock.mCells[i].getColor() != none && cellCollidingDown(mBlock.mCells[i]))
            canMove = false;
    }
    if(canMove)
        mBlock.mY --;

    onUpdate();
}

void Grid::moveUp(){
    bool canMove = true;
    for(unsigned int i = 0; i < 25; i++)
        if(mBlock.mCells[i].getColor() != none && cellCollidingUp(mBlock.mCells[i]))
            canMove = false;

    if(canMove)
        mBlock.mY ++;

    onUpdate();
}

void Grid::setBlockPosition(unsigned int x, unsigned int y){
    mBlock.mX = x;
    mBlock.mY = y;
}

IndexBuffer Grid::getIndexbuffer(){
    for(int i = 0; i < 400; i++){
        int indices[6] = {
            i*4, i*4+ 1, i*4+ 2,
            i*4+ 2, i*4+ 3, i*4
        };

        for(int j = 0; j < 6; j++){
            mIndices[i*6 +j] = (indices[j]);
        }
    }

    IndexBuffer ib(mIndices, 400*6);
    return ib;
}

bool Grid::cellCollidingLeft(Cell cell){
    bool check;
    int cellCheck;

    tie(check, cellCheck) = getCell(cell.getX()-1, cell.getY());

    if(!check)
        return true;

    if(mCells[cellCheck].getColor() != none)
        return true;
    return false;
}

bool Grid::cellCollidingRight(Cell cell){
    bool check;
    int cellCheck;

    tie(check, cellCheck) = getCell(cell.getX()+1, cell.getY());

    if(!check)
        return true;

    if(mCells[cellCheck].getColor() != none)
        return true;
    return false;
}

bool Grid::cellCollidingDown(Cell cell){
    bool check;
    int cellCheck;

    tie(check, cellCheck) = getCell(cell.getX(), cell.getY()-1);

    if(!check){
        onUpdate();
        commitBlock();
        initBlock();
        return true;
    }

    if(mCells[cellCheck].getColor() != none){
        onUpdate();
        commitBlock();
        initBlock();
        return true;
    }
    
    return false;
}

bool Grid::cellCollidingUp(Cell cell){
    bool check;
    int cellCheck;

    tie(check, cellCheck) = getCell(cell.getX(), cell.getY()+1);

    if(!check)
        return true;
        
    if(mCells[cellCheck].getColor() != none)
        return true;
    return false;
}

void Grid::onUpdate(){
    updateGrid();
    updateBlock();
}

void Grid::onRender(Renderer renderer){
    IndexBuffer ib(getIndexbuffer());
    glm::mat4 model = glm::translate(glm::mat4(1.0f), mTranslation);
    glm::mat4 mvp = mProj * model;
    mShader.bind();
    mShader.setUniformMat4f("uMVP", mvp);
    renderer.draw(mVa, ib, mShader);
}