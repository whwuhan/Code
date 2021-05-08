/**
 * 画一个三角形
 * 顶点缓冲对象(Vertex Buffer Objects, VBO)
 * 顶点数组对象(Vertex Array Object, VAO)
 * 
*/
#include <iostream>
#include <glad/glad.h> //glad需要在GLFW之前包含
#include <GLFW/glfw3.h>
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//顶点着色器
const char *vertexShaderSource =
"#version 330 core\n"
//in表示输入顶点属性 vec3表示数据类型(对象)，它有x,y,z三个属性 aPos是变量名
//layout (location = 0)表示该变量的位置
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
    //把位置属性赋值给预定义的gl_Position，注意gl_Position是预定义的
    //且gl_Position是vec4类型的变量，有x,y,z,w四个变量
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

//片段着色器
const char *fragmentShaderSource =
"#version 330 core\n"
//out关键字表示这是一个输出变量，vec4表示这是一个4分量的向量，FragColor是输出的变量名
//注意这里是输出，而上面的顶点着色器是输入
//同时这里的FragColor不是预定义的变量，而是自定义的变量
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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
    //--------------------------初始化部分结束--------------------------

    // -----------------着色器编译-------------------
    // build and compile our shader program
    // 编译着色器程序
    // vertex shader 顶点着色器
    //创建着色器对象，参数为着色器类型，得到的是一个着色器的int类型的编号
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::cout << "vertexShaderID = " <<vertexShader << std::endl;
    //将着色器源码附加到着色器上（将着色器源码，绑定到着色器编号上）
    //参数：着色器对象，着色器源码字符串数量，字符串源码，第四个参数不管，先设为NULL
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    std::cout<<"vertexShaderSource"<<&vertexShaderSource<<std::endl;
    //编译着色器
    glCompileShader(vertexShader);

    //-------------检查着色器是否编译成功---------------
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
        
    // fragment shader 片段着色器，片段是OpenGL渲染一个像素的所需要的所有数据
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::cout << "fragmentShaderID = " << fragmentShader << std::endl;
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // link shaders
    //将编译好的着色器链接成程序
    //创建程序对象
    int shaderProgram = glCreateProgram();
    std::cout<< "shaderProgramID = " << shaderProgram << std::endl;
    //附加着色器到程序
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    //链接着色器
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //链接完成后删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //------------------着色器编译部分结束------------------

    // ---------------------------输入顶点数据-----------------------------------
    // 顶点数据
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f // top
    };
    //创建顶点数组对象VAO和顶点缓冲对象VBO
    unsigned int VBO, VAO;
    //第一个参数是数量，表示创建1个VBO或者1个VAO对象
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    std::cout<< "VBOID = " << VBO << std::endl;
    std::cout<< "VAOID = " << VAO << std::endl;
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //绑定一个VAO
    glBindVertexArray(VAO);
    //绑定VBO，第一个参数是类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将顶点数据传入当前VBO管理的显存中
    //参数：1类型 2所有数据的大小 3数据 4指定显卡如何管理这些数据
    //GL_STATIC_DRAW：数据几乎不变 GL_DYNAMIC_DRAW：数据会改变很多 GL_STREAM_DRAW：数据每次绘制都会改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //顶点属性指针，告诉OpenGL怎么解析VBO所管理的显存，并存储到当前绑定的VAO中 
    //参数：
    //1要配置的顶点属性（顶点着色器中指的是 layout(location = 0) ） 
    //2顶点属性的大小 顶点的位置属性是vec3类型有3个值，所以是3   
    //3指定顶点坐标的类型
    //4否希望数据被标准化(Normalize)   
    //5步长（顶点有多长）  
    //6这个顶点属性相对起始位置的偏移量，注意是一个void*类型
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //启用顶点数组对象 参数：顶点属性的位置（在顶点着色器中 顶点着色器中指的是 layout(location = 0) 所以这里是0）
    glEnableVertexAttribArray(0);
    
    
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //解绑VAO 因为参数是0
    glBindVertexArray(0);
    //--------------------顶点输入部分结束-------------------

    // uncomment this call to draw in wireframe polygons.
    // 允许绘制多边形 否则是实心图像 参数：1应用到三角形的正面和背面  2告诉我们用线进行绘制 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) 将其设置回默认模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) //将其设置回默认模式，即填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //---------------------渲染循环部分-----------------------
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // 调用输入函数，判断是否按下键盘
        processInput(window);

        // render
        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清除颜色（背景颜色）
        glClear(GL_COLOR_BUFFER_BIT);//清除缓存

        // draw our first triangle
        // 使用着色器程序
        glUseProgram(shaderProgram);
        
        //绑定VAO因为上面解绑了VAO
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //绘制图元 参数：1绘制类型 2顶点数组起始索引 3绘制多少个顶点
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time
     
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //可选部分删除VAO,VBO和着色器程序
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
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


//使用相同的VAO绘制两个三角形
int practiceTriangle(){
    //初始化
    glfwInit();
    //设置参数
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    //创建窗口
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Practice Triangle",NULL,NULL);
    if(window == NULL){
        std::cerr<<"窗口创建失败！"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr<<"初始化GLAD失败！"<<std::endl;
        return -1;
    }
    
    //编译着色器，生成着色器程序
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cerr<<"顶点着色器编译失败！错误信息："<<infoLog<<std::endl;
    }
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cerr<<"片段着色器编译失败！错误信息："<<infoLog<<std::endl;
    }
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout<<"着色器程序链接失败！错误信息："<<infoLog<<std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //顶点
    float vertices[]={
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f, // top
        // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };
    unsigned int VBO,VAO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //先暂时解绑
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    //渲染
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

//使用不同VAO和VBO绘制图像
int practiceTriangle1(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //编译着色器，链接成着色器程序
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };
    unsigned int VBOs[2],VAOs[2];
    glGenBuffers(2,VBOs);
    glGenVertexArrays(2,VAOs);
    //----------------重点，绑定不同的VBO,VAO------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //glBindVertexArray(0); //解绑VAO，下面直接绑定另一个VAO，所以这里不需要解绑
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0); //注意这里第5的参数是0，因为之前步长已经打包过了,可以设置为0
    glEnableVertexAttribArray(0);
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        //------重点绑定不同的VAO绘制不同的三角形--------
        //第一个三角形
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES,0,3);
        //第二个三角形
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2,VAOs);
    glDeleteBuffers(2,VBOs);
    glDeleteShader(shaderProgram);
    glfwTerminate();
    return 0;
}
//第二个片段着色器
const char *fragment_shader_source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{"
    "FragColor = vec4(1.0f,1.0f,0.0f,0.5f);\n"
"}\n\0";


//使用不同的VAO和不同的着色器绘制两个不同的三角形
int practiceTriangle2(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    //创建窗口
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Practice Triangle",NULL,NULL);
    if(window == NULL){
        std::cerr<<"窗口创建失败！"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr<<"初始化GLAD失败！"<<std::endl;
        return -1;
    }
    //着色器
    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader,1,&vertexShaderSource,NULL);
    glCompileShader(vertex_shader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertex_shader,512,NULL,infoLog);
        std::cerr<<"顶点着色器编译失败！错误信息："<<infoLog<<std::endl;
    }
    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader,1,&fragment_shader_source,NULL);
    glGetShaderiv(fragment_shader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragment_shader,512,NULL,infoLog);
        std::cerr<<"片段着色器编译失败！错误信息："<<infoLog<<std::endl;
    }
    int shader_program = glCreateProgram();
    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program,GL_LINK_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(shader_program,512,NULL,infoLog);
        std::cout<<"着色器程序链接失败！错误信息："<<infoLog<<std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    //顶点
    float vertices[]={
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f, // top
        // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };
    unsigned int VBOs[2],VAOs[2];
    glGenBuffers(2,VBOs);
    glGenVertexArrays(2,VAOs);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
    //没有写完
    return 0;
}
