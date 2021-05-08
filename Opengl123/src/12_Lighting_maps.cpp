/**
 * 基础光照
 * 环境光照
 * 漫反射
 * 镜面高光
 * 新增材质（主要是在着色器中添加材质信息）
 * 新增光照贴图（新增贴图加载函数）
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
unsigned int loadTexture(const char* path);                                 //新增贴图加载函数

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

//光照初始位置
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
    ="/Users/wuhan/wuhan/coding_space/Code/opengl/shader/12/12.lighting_maps.vs.glsl";
    std::string colors_fragment_path
    ="/Users/wuhan/wuhan/coding_space/Code/opengl/shader/12/12.lighting_maps.fs.glsl";

    //光源着色器
    std::string light_cube_vertex_path
    ="/Users/wuhan/wuhan/coding_space/Code/opengl/shader/12/12.light_cube.vs.glsl";
    std::string light_cube_fragment_path
    ="/Users/wuhan/wuhan/coding_space/Code/opengl/shader/12/12.light_cube.fs.glsl";

    Shader lightingShader(colors_vertex_path.c_str(),colors_fragment_path.c_str());
    Shader lightCubeShader(light_cube_vertex_path.c_str(),light_cube_fragment_path.c_str());

    //顶点坐标和顶点的法线
    float vertices[] = {
        // 位置                //法线               // 纹理坐标
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
    //设置顶点属性，除了位置坐标，现在还有顶点的法线坐标，和贴图坐标
    //1.着色器中的location 2.该location有几个分量(vec3有3个分量) 3.类型 
    //4.是否希望标准化 5 一个顶点多长 6.偏移量
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);       //启用顶点位置属性，0对应着色器中的location
    //设置顶点的法线属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);       //启用顶点法线属性，1对应着色器中的location
    //设置顶点的光照贴图坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);       //启用顶点的纹理坐标属性，2对应着色器中的location

    //设置光源立方体
    unsigned int lightCubeVAO;
    glGenVertexArrays(1,&lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //注意这里数据还是之前传递的那36个点
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //加载纹理图片
    std::string diffuse_map_path = 
    "/Users/wuhan/wuhan/coding_space/Code/opengl/img/container2.png";
    std::string specular_map_path = 
    "/Users/wuhan/wuhan/coding_space/Code/opengl/img/container2_specular.png";
    unsigned int diffuseMap = loadTexture(diffuse_map_path.c_str());
    unsigned int specularMap = loadTexture(specular_map_path.c_str());

    //着色器配置
    lightingShader.use();                               //激活
    //给纹理采样器分配位置值
    //对应后面的
    // glActiveTexture(GL_TEXTURE0);               //激活贴图单元
    // glBindTexture(GL_TEXTURE_2D, diffuseMap);   //绑定贴图
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);



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

        //激活物体着色器
        lightingShader.use();
        lightingShader.setVec3("light.position", lightPos);     //物体的光照来源
        lightingShader.setVec3("viewPos", camera.Position);     //设置相机位置
        //设置光照信息（现在光照信息不是写在发光物体着色器上的，而是显示物体着色器上）
        lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        //设置材质信息
        lightingShader.setFloat("material.shininess", 64.0f);   //反光度

        //观察矩阵、投影矩阵
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        //模型矩阵
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);
        
        //绑定漫反射贴图
        glActiveTexture(GL_TEXTURE0);               //激活贴图单元
        glBindTexture(GL_TEXTURE_2D, diffuseMap);   //绑定贴图
        //绑定镜面反射贴图
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);



        
        //绘制渲染物体立方体
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //绘制光源立方体
        lightCubeShader.use();//激活对应着色器
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);
        //绘制光源立方体
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        
        //显示相机信息
        //camera.showInf();

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
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //向前移动
        camera.ProcessKeyboard(FORWARD,deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //向后移动
        camera.ProcessKeyboard(BACKWARD,deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //向左移动
        camera.ProcessKeyboard(LEFT,deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        //向右移动
        camera.ProcessKeyboard(RIGHT,deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE)){
        //向上移动
        camera.ProcessKeyboard(UPWARD,deltaTime);
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

//加载纹理图片函数
unsigned int loadTexture(const char* path){
    unsigned int textureID;
    glGenTextures(1, &textureID);//生成纹理对象

    int width, height, nrComponents;
    //加载图片 参数1.路径 2.宽 3.高 4.通道数
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if(data){//加载成功

        GLenum format;      //贴图格式
        if(nrComponents == 1){
            format = GL_RED;
        }else if(nrComponents == 3){
            format = GL_RGB;
        }else if(nrComponents == 4){
            format = GL_RGBA;
        }
        
        glBindTexture(GL_TEXTURE_2D, textureID);        //绑定纹理对象

        //将图片加载到创建的纹理对象上 参数：1加载的纹理目标 2多级渐远纹理级别 
        //3纹理存储成的格式，这里是RGB值 4，5宽高 6总是为0 
        //7原图的格式 8数据类型 9图片数据
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);                //自动生成多级渐远纹理

        //设置纹理环绕方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //设置纹理过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);//释放图片内存
    }else{//加载不成功
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}