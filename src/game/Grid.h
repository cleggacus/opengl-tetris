#pragma once

#include <iostream>
#include <vector>
#include <array>

#include "../include/Renderer.h"
#include "../include/Shader.h"
#include "../include/VertexArray.h"
#include "../include/IndexBuffer.h"
#include "../include/Texture.h"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "Cell.h"
#include "Block.h"

using namespace std;

class Grid{
    private:
        Shader mShader;
        Texture mTexture;
        glm::mat4 mProj;
        glm::vec3 mTranslation;

        IndexBuffer mIb;
        VertexBuffer mVb;
        VertexArray mVa;
        VertexBufferLayout mLayout;

        unsigned int mHeight;
        unsigned int mWidth;
        unsigned int mHeightMap;
        unsigned int mWidthMap;
        Block mBlock;
        vector<Cell> mCells;
        unsigned int mIndices[6*400];
    public:
        Grid(unsigned int width, unsigned int height, unsigned int widthMap, unsigned int heightMap);
        ~Grid();
        void onUpdate();
        void onRender(Renderer renderer);
        void initBlock();
        void commitBlock();
        void updateBlock();
        void moveLeft();
        void moveRight();
        void moveDown();
        void moveUp();
        void rotateLeft();
        void rotateRight();
        void updateGrid();
        void removeRow(int row);
        void setBlockPosition(unsigned int x, unsigned int y);
        bool cellCollidingLeft(Cell cell);
        bool cellCollidingRight(Cell cell);
        bool cellCollidingDown(Cell cell);
        bool cellCollidingUp(Cell cell);
        tuple<bool, int>  getCell(unsigned int x, unsigned int y);
        //void setBlock(unsigned int x, unsigned int y, color);
        
        IndexBuffer getIndexbuffer();
};