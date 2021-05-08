#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 创建着色器程序
    std::string vertex_shader_path = 
    "/Users/wuhan/wuhan/coding_space/Code/opengl/shader/06/6.1.coordinate_system_vs.glsl";
    std::string fragment_shader_path = 
    "/Users/wuhan/wuhan/coding_space/Code/opengl/shader/06/6.1.coordinate_system_fs.glsl";
    Shader ourShader(vertex_shader_path.c_str(), fragment_shader_path.c_str());

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // 点坐标和纹理坐标
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };

    // 索引
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //绑定VAO
    glBindVertexArray(VAO);
    //绑定VAO和VBO
    //传递数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //启动顶点属性指针
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);//0是着色器中的location
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //创建加载纹理
    unsigned int texture1,texture2;
    //生成纹理对象
    glGenTextures(1,&texture1);
    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D,texture1);
    //设置纹理环绕参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置纹理过滤参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载图片，创建纹理图像，生成多级渐远纹理
    int width,height,nrChannels;//nrChannels是颜色通道的个数
    stbi_set_flip_vertically_on_load(true);//翻转图片
    //读取图片信息
    std::string texture1_path = 
    "/Users/wuhan/wuhan/coding_space/Code/opengl/img/container.jpg";
    unsigned char *data =
    stbi_load(texture1_path.c_str(),&width,&height,&nrChannels,0);
    if(data)
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
    glGenTextures(1,&texture2);
    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D,texture2);
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
    stbi_load(texture2_path.c_str(),&width,&height,&nrChannels,0);
    if(data)
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

    //激活着色器程序
    ourShader.use();
    //告诉采样器对应的纹理
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    //渲染循环
    while(!glfwWindowShouldClose(window))
    {   
        //处理键盘鼠标输入
        processInput(window);
        //设置背景颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //绑定纹理到对应的纹理单元
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //激活着色器
        ourShader.use();

        //创建变换矩阵
        //模型矩阵
        glm::mat4 model(1.0f);
        model = glm::rotate(model,glm::radians(-55.0f),glm::vec3(1.0f, 0.0f, 0.0f));
        //观察矩阵
        glm::mat4 view(1.0f);
        view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
        //投影矩阵
        glm::mat4 projection(1.0f);
        //参数
        //1 视角FOV(Field of View)
        //2 宽高比
        //3 近平面
        //4 远平面
        projection = 
        glm::perspective(glm::radians(45.0f), 
        (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //获取着色器中矩阵uniform的位置
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID,"model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID,"view");
        unsigned int projectionLoc = glGetUniformLocation(ourShader.ID,"projection");
        //传递矩阵值给着色器（三种方法）
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, 
        //but since the projection matrix rarely changes 
        //it's often best practice to set it outside the main loop only once.
        //一般在渲染循环外面设置投影矩阵，因为一般它不会改变
        ourShader.setMat4("projection", projection);
        
        //绘制图像
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //交换缓存
        glfwSwapBuffers(window);
        //轮询io事件
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}