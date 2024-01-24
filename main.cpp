#include <iostream>

#include "src/models/3DObject.h"
#include "src/file_loader/stl.h"
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
// Include GLFW
#include <GLFW/glfw3.h>
#include <fstream>
#include <streambuf>

std::optional<GLFWwindow *> initWindow()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return {};
    }

    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    GLFWwindow *window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return {};
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return window;
};

std::optional<std::string> loadShaderFromFile(std::string filename)
{
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Cannot load shader " << filename;
        return {};
    }

    return std::string(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>());
}

std::optional<GLuint> compileShader(std::string filename, GLenum shaderType)
{
    auto shader = loadShaderFromFile(filename);
    if (!shader)
    {
        return {};
    }
    std::cout << *shader;
    auto shaderId = glCreateShader(shaderType);
    auto src = (*shader).c_str();
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);
    GLint isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::string errorLog(maxLength, '\0');
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
        std::cout << errorLog;

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(shaderId); // Don't leak the shader.
        return {};
    }
    return shaderId;
}

std::optional<GLuint> loadBasicProgram()
{
    auto vertexShaderId = compileShader("./shaders/vertex.shader", GL_VERTEX_SHADER);
    if (!vertexShaderId)
        return {};

    auto fragementShaderId = compileShader("./shaders/fragment.shader", GL_FRAGMENT_SHADER);
    if (!fragementShaderId)
    {
        glDeleteShader(*vertexShaderId);
        return {};
    }

    auto programId = glCreateProgram();
    glAttachShader(programId, *vertexShaderId);
    glAttachShader(programId, *fragementShaderId);

    glLinkProgram(programId);

    GLint isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::string infoLog(maxLength, '\0');
        glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

        std::cout << infoLog;

        // We don't need the program anymore.
        glDeleteProgram(programId);
        // Don't leak shaders either.
        glDeleteShader(*vertexShaderId);
        glDeleteShader(*fragementShaderId);

        return {};
    }

    // Always detach shaders after a successful link.
    glDetachShader(programId, *vertexShaderId);
    glDetachShader(programId, *fragementShaderId);

    return programId;
}

int main()
{
    auto objectResult = Stl::load("./files/cube_ascii.stl");
    if (!objectResult)
        return 0;

    auto windowResult = initWindow();
    if (!windowResult)
        return 0;

    auto programResult = loadBasicProgram();
    if (!programResult)
        return 0;
    // glUseProgram(*programResult);

    auto &object = *objectResult;
    auto window = *windowResult;

    do
    {
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw nothing, see you in tutorial 2 !

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
    return 0;
}
