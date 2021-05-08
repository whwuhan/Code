/**
 * 基础光照
 * 环境光照
 * 漫反射
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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//相机位置
Camera camera(glm::vec3(0.0f,0.0f,3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//光照位置
glm::vec3 lightPos(1.2f,1.0f,2.0f);

int main(){
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

    //启用深度测试
    glEnable(GL_DEPTH_TEST);

    //创建着色器
    //着色器路径
    //光照场景物体着色器
    std::string colors_vertex_path
    ="/Users/wuhan/wuhan/CodingSpace/Code/OpenGL/shader/09/09.basic_lighting.vs.glsl";
    std::string colors_fragment_path
    ="/Users/wuhan/wuhan/CodingSpace/Code/OpenGL/shader/09/09.basic_lighting.fs.glsl";

    //光源着色器
    std::string light_cube_vertex_path
    ="/Users/wuhan/wuhan/CodingSpace/Code/OpenGL/shader/09/09.light_cube.vs.glsl";
    std::string light_cube_fragment_path
    ="/Users/wuhan/wuhan/CodingSpace/Code/OpenGL/shader/09/09.light_cube.fs.glsl";

    Shader lightingShader(colors_vertex_path.c_str(),colors_fragment_path.c_str());
    Shader lightCubeShader(light_cube_vertex_path.c_str(),light_cube_fragment_path.c_str());

    //顶点坐标和顶点的法线
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    //VAO VBO
    //设置物体
    unsigned int VBO,cubeVAO;
    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&VBO);
    //绑定VBO，传递顶点数据
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    //绑定VAO
    glBindVertexArray(cubeVAO);
    //设置顶点属性，除了位置坐标，现在还有顶点的法线坐标
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    //启用顶点属性，0对应着色器中的location
    glEnableVertexAttribArray(0);
    //设置顶点的法线属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //设置光源立方体
    unsigned int lightCubeVAO;
    glGenVertexArrays(1,&lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //注意这里数据还是之前传递的那36个点
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //渲染循环
    while(!glfwWindowShouldClose(window)){
        //获取每一帧的间隔时间
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //处理输入
        processInput(window);

        //设置清空颜色
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//RGBA
        //清空缓存，注意这里也要清空每一帧的深度信息
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //激活着色器
        lightingShader.use();
        //设置物体的颜色
        lightingShader.setVec3("objectColor",1.0f,0.5f,0.31f);
        //设置照到物体上光的颜色
        lightingShader.setVec3("lightColor",1.0f,1.0f,1.0f);//白光
        //设置物体的在世界坐标新中的位置
        lightingShader.setVec3("lightPos", lightPos);

        //变换矩阵
        //投影矩阵和观察矩阵
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
        glm::mat4 view=camera.GetViewMatrix();
        lightingShader.setMat4("projection",projection);
        lightingShader.setMat4("view",view);
        //模型矩阵
        glm::mat4 model(1.0f);
        lightingShader.setMat4("model",model);
        //渲染物体(注意不是光源)
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        //光源物体
        lightCubeShader.use();
        lightCubeShader.setMat4("view",view);
        lightCubeShader.setMat4("projection",projection);
        //设置光源的位置
        model=glm::mat4(1.0f);
        model=glm::translate(model,lightPos);//平移光源
        model=glm::scale(model,glm::vec3(0.2f));//缩放光源物体
        lightCubeShader.setMat4("model",model);
        //绘制光源物体
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        //显示相机信息
        camera.showInf();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window){
    //监听esc，退出程序
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    //相机移动封装到了camera中
    //移动相机
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        //向前移动
        camera.ProcessKeyboard(FORWARD,deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        //向后移动
        camera.ProcessKeyboard(BACKWARD,deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        //向左移动
        camera.ProcessKeyboard(LEFT,deltaTime);
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        //向右移动
        camera.ProcessKeyboard(RIGHT,deltaTime);
    }
        
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//鼠标回调函数
void mouse_callback(GLFWwindow *window, double xpos, double ypos){
    //判断鼠标是否是第一次进入窗口
    if(firstMouse){
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
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}
