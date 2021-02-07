#include <GLFW/glfw3.h>
#include <simpidbit.h>
#include <assert.h>
#include <math.h>

#define WIN_WID 800
#define WIN_HEIGHT 600
#define WIN_TITLE "Hello VAO, VBO, EBO"

#define VIEW_BEGIN_X 0
#define VIEW_BEGIN_Y 0
#define VIEW_WID WIN_WID
#define VIEW_HEIGHT WIN_HEIGHT

#define VS_FNAME "./vertex.glsl"
#define FS_FNAME "./frag.glsl"

typedef unsigned int uint;
static float vertices1[] = {
    -1.0f, -1.0f, 0.0f,
    -0.5f,  0.0f, 0.0f,
     0.0f, -1.0f, 0.0f
};      // 左下的三角形

static float vertices2[] = {
     1.0f,  1.0f, 0.0f,
     0.5f,  0.0f, 0.0f,
     0.0f,  1.0f, 0.0f
};      // 右上的三角形

// 中间的正方形
//
float vertices3[] = {
    0.2f, 0.2f, 0.0f,   // 右上角
    0.2f, -0.2f, 0.0f,  // 右下角
    -0.2f, -0.2f, 0.0f, // 左下角
    -0.2f, 0.2f, 0.0f   // 左上角
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
            3 * sizeof(float),      /* 步长 */
            (void*)0                /* 数据偏移量 */
            );

    // 以顶点属性位置值为参数，启用顶点属性
    glEnableVertexAttribArray(0);

    /* ------------------------------------------ */

    // 创建 顶点数组对象
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);

    // 创建 1 个顶点缓冲对象
    uint VBO2;
    glGenBuffers(1, &VBO2);

    // 绑定VAO
    glBindVertexArray(VAO2);

    // 绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);

    // 将顶点数据复制到顶点缓冲对象里面
    // @GL_STATIC_DRAW: 顶点数据不会或几乎不会改变
    //  GL_DYNAMIC_DRAW：数据会被改变很多
    //  GL_STREAM_DRAW ：数据每次绘制时都会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // 解析顶点数据
    glVertexAttribPointer(
            0,                      /* 对应顶点着色器里的location */
            3,                      /* 顶点属性大小为3 */
            GL_FLOAT,               /* 指定数据类型 */
            GL_FALSE,               /* 是否希望数据被标准化 */
            3 * sizeof(float),      /* 步长 */
            (void*)0                /* 数据偏移量 */
            );

    // 以顶点属性位置值为参数，启用顶点属性
    glEnableVertexAttribArray(0);

    /* ------------------------------------------ */

    // 创建 顶点数组对象
    unsigned int VAO3;
    glGenVertexArrays(1, &VAO3);

    // 创建顶点缓冲对象
    uint VBO3;
    glGenBuffers(1, &VBO3);

    // 创建索引缓冲对象
    uint EBO;
    glGenBuffers(1, &EBO);

    // 绑定VAO
    glBindVertexArray(VAO3);

    // 绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    
    // 绑定索引缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // 将顶点数据复制到顶点缓冲对象里面
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

    // 将顶点数据复制到索引缓冲对象里面
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 解析顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // 以顶点属性位置值为参数，启用顶点属性
    glEnableVertexAttribArray(0);



    // 读取顶点着色器代码
    char *vsur = spfile_read_heap(VS_FNAME, SPBUFSIZ);

    // 创建着色器
    uint vshader;
    vshader = glCreateShader(GL_VERTEX_SHADER);

    // 将着色器源码附加到着色器上
    glShaderSource(vshader, 1, &vsur, 0);

    // 编译着色器
    glCompileShader(vshader);

    // 检查是否编译成功
    check_shader_complie(vshader);

    // 一样的过程，创建并编译片段着色器
    char *fsur = spfile_read_heap(FS_FNAME, SPBUFSIZ);
    unsigned int fshader;
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fsur, 0);
    glCompileShader(fshader);
    check_shader_complie(fshader);

    // 创建着色器程序
    uint shaderpg;
    shaderpg = glCreateProgram();

    // 把着色器附加到着色器程序上
    glAttachShader(shaderpg, vshader);
    glAttachShader(shaderpg, fshader);

    // 连接着色器们
    glLinkProgram(shaderpg);

    // 删除着色器对象
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    // 渲染循环
    while(!glfwWindowShouldClose(window)) {
        // 清空屏幕的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
 
        // 使用着色器程序
        glUseProgram(shaderpg);

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderpg, "myColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // 绑定VAO1，绘制左下三角形
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 绑定VAO2，绘制右上三角形
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 绑定VAO3, 绘制中间矩形
        glBindVertexArray(VAO3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

       // 交换颜色缓冲，即绘制窗口
        glfwSwapBuffers(window);

        // 检查是否有事件触发，并调用相应回调函数
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
