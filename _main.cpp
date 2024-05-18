// learnopengl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad33/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

extern int run_tests();
extern int call_loop_unit1(int &selection);

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

static int selection = INT_MAX;

int main()
{
    int retcode = 0;
    std::cout << "Hello World!\n";

    run_tests();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here


        retcode = call_loop_unit1(selection);

        if (retcode != 0)
            break;

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    std::cout << std::endl;
    system("pause");

    return retcode;
}

static void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        selection = 1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        selection = 2;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        selection = 3;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        selection = 4;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        selection = 5;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        selection = 6;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        selection = 7;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        selection = 8;
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        selection = 9;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        selection = 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
