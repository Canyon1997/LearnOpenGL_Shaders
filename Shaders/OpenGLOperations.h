#pragma once


#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <string>


GLFWwindow* InitializeOpenGL();

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

std::string GetVertexShaderSource(std::string vertexFile);

std::string GetFragmentShaderSource(std::string fragmentFile);

unsigned int CreateVertexShader(const std::string& vertexSource);

unsigned int CreateFragmentShader(const std::string& fragmentSource);

unsigned int CreateCompleteShader(const unsigned int& vertexShaderID, const unsigned int& fragmentShaderID);

void ProcessInput(GLFWwindow* window);