/**
 * 初始化窗口
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int main()
{
    //----------------------初始化部分----------------------
    glfwInit(); //初始化GLFW
    
    //通过glfwWindowHint()函数来设置参数，前面是参数名称，后面是值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //设置使用核心模式
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //mac用户需要设置，初始化才能有效
    #endif
    //创建一个窗口对象
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    //参数依次是长，宽，名称，后两个参数忽略
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    //将窗口的上下文设置成主线程的上下文
    glfwMakeContextCurrent(window);
    //注册回调函数，告诉GLFW窗口大小调整时，调用这个回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //GLAD是用来管理OpenGL的函数指针
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //glfwGetProcAddress 根据编译的系统给出了正确的函数
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //--------------------------以上为初始化部分--------------------------
    
    //渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 调用输入函数，判断是否按下键盘
        processInput(window);
        
        // 渲染
        // ------
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清除颜色（背景颜色）
        glClear(GL_COLOR_BUFFER_BIT);//清除缓存
        
        //交换颜色缓冲，它存储着GLFW中每一个像素颜色值的缓冲，
        glfwSwapBuffers(window);
        //检查有没有触发什么事件，比如键盘输入，鼠标移动等
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

//回调函数声明，更改窗口大小的时候，更改视口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 声明输入函数，判断是否按下键盘
void processInput(GLFWwindow *window)
{
    //glfwGetKey()函数，它需要一个窗口以及一个按键作为输入。
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //检测是否按下esc，按下就退出窗口
        glfwSetWindowShouldClose(window, true);
}