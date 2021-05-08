/**
 * 使用封装好的相机类改变视角
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <Camera.h>
#include <iostream>
#include <string>
#include <iostream>


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
//新增鼠标和鼠标滚轮回调函数
void mouse_callback(GLFWwindow *window, double xpos, double ypos);// xpos,ypos当前鼠标的xy坐标位置
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);// xoffset,yoffset

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 新增相机类
Camera camera(glm::vec3(0.0f,0.0f,3.0f));

//初始化上一次的鼠标位置
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;//鼠标是否是第一次进入window
//时间差
float deltaTime = 0.0f;//lastFrame和currentFrame的时间间隔
float lastFrame = 0.0f;//上一帧


int main()
{   
    std::cout << "new camera" << std::endl;
    Camera newCamera(glm::vec3(0.0f,0.0f,3.0f));

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //新增监听鼠标和鼠标滚轮事件
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);
    //告诉GLFW选中窗口不显示鼠标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 创建着色器程序
    std::string vertex_shader_path =
        "/Users/wuhan/wuhan/coding_space/Code/opengl/shader/07/7.3.camera.vs.glsl";
    std::string fragment_shader_path =
        "/Users/wuhan/wuhan/coding_space/Code/opengl/shader/07/7.3.camera.fs.glsl";
    Shader ourShader(vertex_shader_path.c_str(), fragment_shader_path.c_str());

     //开始配置全局opengl
    //glEnable和glDisable函数允许我们启用或禁用某个OpenGL功能。
    //这个功能会一直保持启用/禁用状态，直到另一个调用来禁用/启用它。
    glEnable(GL_DEPTH_TEST); //开启深度测试，保证在后面被遮挡的物体不会显示到前面

    //坐标信息，绘制一个立方体要36顶点
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
    // world space positions of our cubes
    //模型矩阵，将物体摆放到世界坐标系中的合适位置
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    //VAO VBO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //纹理
    //创建加载纹理
    unsigned int texture1, texture2;
    //生成纹理对象
    glGenTextures(1, &texture1);
    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, texture1);
    //设置纹理环绕参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置纹理过滤参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载图片，创建纹理图像，生成多级渐远纹理
    int width, height, nrChannels;          //nrChannels是颜色通道的个数
    stbi_set_flip_vertically_on_load(true); //翻转图片
    //读取图片信息
    std::string texture1_path =
        "/Users/wuhan/wuhan/coding_space/Code/opengl/img/container.jpg";
    unsigned char *data =
        stbi_load(texture1_path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // 第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
        // 第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
        // 第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
        // 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
        // 下个参数应该总是被设为0（历史遗留的问题）。
        // 第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
        // 最后一个参数是真正的图像数据。
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // 自动生成多级渐远纹理的级别
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放图像资源
    stbi_image_free(data);

    //创建第二个纹理
    //生成纹理对象
    glGenTextures(1, &texture2);
    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, texture2);
    //设置纹理环绕参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置纹理过滤参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载图片，创建纹理图像，生成多级渐远纹理
    //读取图片信息
    std::string texture2_path =
        "/Users/wuhan/wuhan/coding_space/Code/opengl/img/awesomeface.png";

    data =
        stbi_load(texture2_path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // 第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
        // 第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
        // 第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
        // 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
        // 下个参数应该总是被设为0（历史遗留的问题）。
        // 第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
        // 最后一个参数是真正的图像数据。
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // 自动生成多级渐远纹理的级别
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放图像资源
    stbi_image_free(data);

    //使用着色器
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    //透视投影矩阵，一般不会改变，在渲染循环外设置
    // 但是在如果需要按照滚轮进行缩放，需要在渲染循环中设置投影矩阵
    // glm::mat4 projection(1.0f); //投影矩阵
    // projection = glm::perspective(glm::radians(45.0f),
    //                     (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // ourShader.setMat4("projection", projection);

    //开始渲染
    while (!glfwWindowShouldClose(window))
    {
        //获取每一帧的间隔时间
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //处理输入
        processInput(window);

        //设置清空颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //清空缓存，注意这里也要清空每一帧的深度信息
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        //激活纹理单元，绑定纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //激活着色器
        ourShader.use();

        //因为要缩放，所以在渲染循环中设置投影矩阵，调整fov
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
        //获取lookAt矩阵
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view",view);

        //渲染箱子
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            //模型矩阵
            glm::mat4 model(1.0f);
            //位移，改变箱子的位置
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            //旋转，改变箱子的朝向
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            //获取变换矩阵在着色器中的位置，设置变换矩阵
            ourShader.setMat4("model", model);
            //绘制图像
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    //监听esc，退出程序
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    //相机移动封装到了camera中
    //移动相机
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    {
        //向前移动
        camera.ProcessKeyboard(FORWARD,deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
        //向后移动
        camera.ProcessKeyboard(BACKWARD,deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        //向左移动
        camera.ProcessKeyboard(LEFT,deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
        //向右移动
        camera.ProcessKeyboard(RIGHT,deltaTime);
    }
        
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//鼠标回调函数
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    //判断鼠标是否是第一次进入窗口
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    //计算鼠标偏移量
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;//之所以是反过来是因为俯仰角正向是往y轴负向
    lastX = xpos;
    lastY = ypos;

    //视角的变换封装到了Camera类里面
    camera.ProcessMouseMovement(xoffset,yoffset);
}

//鼠标滚轮回调函数
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
