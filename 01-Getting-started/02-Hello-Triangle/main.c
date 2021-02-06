#include <GLFW/glfw3.h>
//#include <glad/glad.h>
#include <simpidbit.h>
#include <assert.h>

#define WIN_WID 800
#define WIN_HEIGHT 600
#define WIN_TITLE "Hello OpenGL"

#define VIEW_BEGIN_X 0
#define VIEW_BEGIN_Y 0
#define VIEW_WID WIN_WID
#define VIEW_HEIGHT WIN_HEIGHT

#define VS_FNAME "./vertex.glsl"
#define FS_FNAME "./frag.glsl"

typedef unsigned int uint;
static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

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

    // 设置颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    // 创建 顶点数组对象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // 创建 1 个顶点缓冲对象
    uint VBO;
    glGenBuffers(1, &VBO);

    // 绑定VAO
    glBindVertexArray(VAO);

    // 绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 将顶点数据复制到顶点缓冲对象里面
    // @GL_STATIC_DRAW: 顶点数据不会或几乎不会改变
    //  GL_DYNAMIC_DRAW：数据会被改变很多
    //  GL_STREAM_DRAW ：数据每次绘制时都会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


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

    // 解析顶点数据
    glVertexAttribPointer(
            0,                      /* 对应顶点着色器里的location */
            3,                      /* 顶点属性大小为3 */
            GL_FLOAT,               /* 指定数据类型 */
            GL_FALSE,               /* 是否希望数据被标准化 */
            3 * sizeof(float),      /* 步长 */
            (void*)0                /* 数据偏移量 */
            );

    glEnableVertexAttribArray(0);

    // 使用此着色器
    glUseProgram(shaderpg);


    // 渲染循环
    while(!glfwWindowShouldClose(window)) {
        // 清空屏幕的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换颜色缓冲，即绘制窗口
        glfwSwapBuffers(window);

        // 检查是否有事件触发，并调用相应回调函数
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
