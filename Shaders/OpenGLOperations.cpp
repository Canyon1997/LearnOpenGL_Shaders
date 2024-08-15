#include "OpenGLOperations.h"
#include <fstream>
#include <iostream>
#include <sstream>


GLFWwindow* InitializeOpenGL()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    return window;
}

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

std::string GetVertexShaderSource(std::string vertexFile)
{
    std::ifstream vertexSource(vertexFile);

    if (!vertexSource.is_open())
    {
        std::cout << "Failed to open vertex source file" << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << vertexSource.rdbuf();
    vertexSource.close();

    return ss.str();
}

std::string GetFragmentShaderSource(std::string fragmentFile)
{
    std::ifstream fragmentSource(fragmentFile);

    if (!fragmentSource.is_open())
    {
        std::cout << "Failed to open fragment source file" << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << fragmentSource.rdbuf();
    fragmentSource.close();

    return ss.str();
}

unsigned int CreateVertexShader(const std::string& vertexSource)
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char* vertexSourceConversion = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceConversion, NULL);
    glCompileShader(vertexShader);

    return vertexShader;
}

unsigned int CreateFragmentShader(const std::string& fragmentSource)
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentSourceConversion = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceConversion, NULL);
    glCompileShader(fragmentShader);

    return fragmentShader;
}

unsigned int CreateCompleteShader(const unsigned int& vertexShaderID, const unsigned int& fragmentShaderID)
{
    unsigned int completeShader;
    completeShader = glCreateProgram();

    glAttachShader(completeShader, vertexShaderID);
    glAttachShader(completeShader, fragmentShaderID);
    glLinkProgram(completeShader);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return completeShader;
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
