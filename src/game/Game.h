#pragma once

#include "../include/Renderer.h"
#include "../include/Shader.h"
#include "../include/VertexArray.h"
#include "../include/IndexBuffer.h"
#include "../include/Texture.h"

#include <GLFW/glfw3.h>

#include "Grid.h"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

struct KeyMap{
    bool a = false;
    bool d = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool up = false;
};

class Game{
    public:
        Game();
        ~Game();

        void onUpdate(float deltaTime, GLFWwindow *window);
        void onRender();
        void left();
        void keyHandler(GLFWwindow *window);

    private:
        KeyMap mKeyMap;
        
        double timeLast = glfwGetTime();
        double timeNow = glfwGetTime();
        float mClearColor[4];
        Renderer mRenderer;

        Grid mGrid;
        
};
