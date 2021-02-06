#include <GLFW/glfw3.h>
//#include <glad/glad.h>
#include <assert.h>

#define WIN_WID 800
#define WIN_HEIGHT 600
#define WIN_TITLE "Hello OpenGL"

#define VIEW_BEGIN_X 0
#define VIEW_BEGIN_Y 0
#define VIEW_WID WIN_WID
#define VIEW_HEIGHT WIN_HEIGHT



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, 1);
}

int main()
{
    // 初始化OpenGL
    glfwInit();

    // 配置OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(WIN_WID, WIN_HEIGHT, WIN_TITLE, 0, 0);
    assert(window != 0);
    glfwMakeContextCurrent(window);

    // 设置视口
    glViewport(VIEW_BEGIN_X, VIEW_BEGIN_Y, VIEW_WID, VIEW_HEIGHT);

    // 设置窗口大小改变事件的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 设置颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // 渲染循环
    while(!glfwWindowShouldClose(window)) {
        // 清空屏幕的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        // 若按下ESC，则关闭窗口
        processInput(window);

        // 交换颜色缓冲，即绘制窗口
        glfwSwapBuffers(window);

        // 检查是否有事件触发，并调用相应回调函数
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
