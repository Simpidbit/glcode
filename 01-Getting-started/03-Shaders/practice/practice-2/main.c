#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <simpidbit.h>
#include <assert.h>
#include <math.h>
#include <spshader.h>

#define WIN_WID 800
#define WIN_HEIGHT 600
#define WIN_TITLE "Hello Shader Object"

#define VIEW_BEGIN_X 0
#define VIEW_BEGIN_Y 0
#define VIEW_WID WIN_WID
#define VIEW_HEIGHT WIN_HEIGHT

#define VS_FNAME "./vertex.glsl"
#define FS_FNAME "./frag.glsl"

typedef unsigned int uint;
static float vertices1[] = {
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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

    // 初始化glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // 设置视口
    glViewport(VIEW_BEGIN_X, VIEW_BEGIN_Y, VIEW_WID, VIEW_HEIGHT);

    // 设置窗口大小改变事件的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 设置颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    // 创建 顶点数组对象
    unsigned int VAO1;
    glGenVertexArrays(1, &VAO1);

    // 创建 1 个顶点缓冲对象
    uint VBO1;
    glGenBuffers(1, &VBO1);

    // 绑定VAO
    glBindVertexArray(VAO1);

    // 绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);

    // 将顶点数据复制到顶点缓冲对象里面
    // @GL_STATIC_DRAW: 顶点数据不会或几乎不会改变
    //  GL_DYNAMIC_DRAW：数据会被改变很多
    //  GL_STREAM_DRAW ：数据每次绘制时都会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // 解析顶点数据
    glVertexAttribPointer(
            0,                      /* 对应顶点着色器里的location */
            3,                      /* 顶点属性大小为3 */
            GL_FLOAT,               /* 指定数据类型 */
            GL_FALSE,               /* 是否希望数据被标准化 */
            6 * sizeof(float),      /* 步长 */
            (void*)0                /* 数据偏移量 */
            );
    // 以顶点属性位置 (Location) 值为参数，启用顶点属性
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1,                      /* 对应顶点着色器里的location */
            3,                      /* 顶点属性大小为3 */
            GL_FLOAT,               /* 指定数据类型 */
            GL_FALSE,               /* 是否希望数据被标准化 */
            6 * sizeof(float),      /* 步长 */
            (void*)(3 * sizeof(float))      /* 数据偏移量 */
            );
    // 以顶点属性位置 (Location) 值为参数，启用顶点属性
    glEnableVertexAttribArray(1);

    /* ------------------------------------------ */

    struct SPShader shader;
    spinit_shader(&shader, VS_FNAME, FS_FNAME);

    // 渲染循环
    while(!glfwWindowShouldClose(window)) {
        // 清空屏幕的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
 
        // 使用着色器程序
        spuse_shader(&shader);
        set_uniform_1f(&shader, "offset", 0.5f);

        // 绑定VAO1，绘制左下三角形
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

       // 交换颜色缓冲，即绘制窗口
        glfwSwapBuffers(window);

        // 检查是否有事件触发，并调用相应回调函数
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
