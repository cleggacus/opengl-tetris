#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include "include/Renderer.h"
#include "include/VertexBuffer.h"
#include "include/IndexBuffer.h"
#include "include/VertexArray.h"
#include "include/Shader.h"
#include "include/Texture.h"

#include "game/Game.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

using namespace std;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    unsigned int width = 400;
    unsigned int height = 800;

    window = glfwCreateWindow(width, height, "GLFW-Dev", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); 
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK){
        cout << "error\n";
        return 0;
    }

    Game game;

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    while (!glfwWindowShouldClose(window))
    {
        game.onUpdate(0.0f, window);
        game.onRender();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}