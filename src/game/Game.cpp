#include "Game.h"

Game::Game() :
    mClearColor { 0.01f, 0.03f, 0.095f, 1.0f },
    mGrid(10, 20, 400, 800),
    mRenderer()
{
    
}

Game::~Game()
{
}

void Game::onUpdate(float deltaTime, GLFWwindow *window){
    keyHandler(window);

    timeNow = glfwGetTime();

    if(timeNow - timeLast >= 0.7){
        timeLast = timeNow;
        mGrid.moveDown();
    }
}

void Game::keyHandler(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_A) == 1 && !mKeyMap.a){
        mKeyMap.a = true;
        mGrid.rotateLeft();
    }else if(glfwGetKey(window, GLFW_KEY_A) == 0){
        mKeyMap.a = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == 1 && !mKeyMap.d){
        mKeyMap.d = true;
        mGrid.rotateRight();
    }else if(glfwGetKey(window, GLFW_KEY_D) == 0){
        mKeyMap.d = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_DOWN) == 1 && !mKeyMap.down){
        mKeyMap.down = true;
        mGrid.moveDown();
    }else if(glfwGetKey(window, GLFW_KEY_DOWN) == 0){
        mKeyMap.down = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == 1 && !mKeyMap.up){
        mKeyMap.up = true;
        mGrid.moveUp();
    }else if(glfwGetKey(window, GLFW_KEY_UP) == 0){
        mKeyMap.up = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT) == 1 && !mKeyMap.left){
        mKeyMap.left = true;
        mGrid.moveLeft();
    }else if(glfwGetKey(window, GLFW_KEY_LEFT) == 0){
        mKeyMap.left = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == 1 && !mKeyMap.right){
        mKeyMap.right = true;
        mGrid.moveRight();
    }else if(glfwGetKey(window, GLFW_KEY_RIGHT) == 0){
        mKeyMap.right = false;
    }
}

void Game::onRender()
{
    mRenderer.clear();
    glCall(glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], mClearColor[3]));
    
    mGrid.onRender(mRenderer);
}