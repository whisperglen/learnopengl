// learnopengl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad33/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "helpers.h"

extern int run_tests();
extern int call_loop_unit1(int &selection);

extern int call_loop_unit100(int& selection);

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);

static int selection = INT_MAX;
static int unit = INT_MAX;

static bool firstMouse = true;
static float deltaTime = 0.0f;	// Time between current frame and last frame
static float lastFrame = 0.0f;

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

int main()
{
    int retcode = 0;
    std::cout << "Hello World!\n";

    run_tests();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //used for apple
    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); //requests debug context

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << " OGL v." << glGetString(GL_VERSION) << std::endl;

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    std::cout << "GL context flags: 0x" << std::hex << flags << std::dec << std::endl;
#ifdef GL_DEBUG_OUTPUT
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // rendering commands here

        switch (unit)
        {
        default:
        case 1:
            retcode = call_loop_unit1(selection);
            break;
        case 100:
            retcode = call_loop_unit100(selection);
            break;
        }
        glCheckError();

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
        unit = 1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        unit = 2;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        unit = 3;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        unit = 4;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        unit = 5;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        unit = 6;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        unit = 7;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        unit = 8;
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        unit = 9;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        unit = 0;

    static int tab_pressed = 0;
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tab_pressed)
    {
        tab_pressed++;
        selection--;
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
    {
        tab_pressed = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        unit--;
        if (unit < 0) unit = INT_MAX;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        unit++;
        if (unit < 0) unit = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        processKeyboard(0, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        processKeyboard(1, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        processKeyboard(2, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        processKeyboard(3, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        firstMouse = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, 0);
    }
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static double lastX, lastY;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = float(xpos - lastX);
    float yoffset = float(lastY - ypos); // Reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    processMouseMovement(xoffset, yoffset);
}

static int g_width = SCR_WIDTH;
static int g_height = SCR_HEIGHT;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    g_width = width;
    g_height = height;
    glViewport(0, 0, width, height);
}

const glm::mat4 getProjMatrix()
{
    return glm::perspective(glm::radians(45.0f), (float)g_width / (float)g_height, 0.1f, 100.0f);
}

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
#if defined GL_STACK_OVERFLOW && defined GL_STACK_UNDERFLOW
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
#endif
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

#ifdef GL_DEBUG_OUTPUT
void APIENTRY glDebugOutput(GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}
#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
