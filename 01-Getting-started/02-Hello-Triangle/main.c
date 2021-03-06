#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <simpidbit.h>
#include <spshader.h>
#include <assert.h>

#define WIN_WID 800
#define WIN_HEIGHT 600
#define WIN_TITLE "Hello Texture"

#define VIEW_BEGIN_X 0
#define VIEW_BEGIN_Y 0
#define VIEW_WID WIN_WID
#define VIEW_HEIGHT WIN_HEIGHT

#define VS_FNAME "./vertex.glsl"
#define FS_FNAME "./frag.glsl"

typedef unsigned int uint;
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void check_shader_complie(uint shader)
{
    int  success;
    char infolog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, 0, infolog);
        sperr(5, "Shader compile error!\n%s\n", infolog);
    }
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
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // 创建顶点缓冲对象
    uint VBO;
    glGenBuffers(1, &VBO);

    // 创建索引缓冲对象
    uint EBO;
    glGenBuffers(1, &EBO);

    // 绑定VAO
    glBindVertexArray(VAO);

    // 绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // 绑定索引缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // 将顶点数据复制到顶点缓冲对象里面
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 将顶点数据复制到索引缓冲对象里面
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 解析顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // 以顶点属性位置值为参数，启用顶点属性
    glEnableVertexAttribArray(0);


    struct SPShader shader;
    spinit_shader(&shader, VS_FNAME, FS_FNAME);

    // 渲染循环
    while(!glfwWindowShouldClose(window)) {
        // 清空屏幕的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
 
        // 使用着色器程序
        spuse_shader(&shader);

        // 绑定VAO3, 绘制中间矩形
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

       // 交换颜色缓冲，即绘制窗口
        glfwSwapBuffers(window);

        // 检查是否有事件触发，并调用相应回调函数
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
