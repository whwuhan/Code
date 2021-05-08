/**
 * 相机实现类
*/
#include <Camera.h>
#include <iostream>
//构造方法
Camera::Camera(glm::vec3 position,glm::vec3 up,float yaw,float pitch):
Front(glm::vec3(0.0f,0.0f,-1.0f)),
MovementSpeed(SPEED),
MouseSensitivity(SENSITIVITY),
Zoom(ZOOM){
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    std::cout<<"Camera init information:"<<std::endl;
    std::cout<<"position:["<<position.x<<","<<position.y<<","<<position.z<<"]"<<std::endl;
    std::cout<<"up:["<<up.x<<","<<up.y<<","<<up.z<<"]"<<std::endl;
    std::cout <<"Yaw:"<<Yaw<<"°"<<std::endl;
    std::cout <<"Pitch:"<<Pitch<<"°"<<std::endl;
    updateCameraVectors();
}

Camera::Camera(
float posX,
float posY,
float posZ,
float upX,
float upY,
float upZ,
float yaw,
float pitch):
Front(glm::vec3(0.0f, 0.0f, -1.0f)),
MovementSpeed(SPEED),
MouseSensitivity(SENSITIVITY),
Zoom(ZOOM){
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

//获取观察矩阵，也就是loocAt矩阵
glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(Position, Position + Front, Up);
}

//响应键盘
void Camera::ProcessKeyboard(Camera_Movement direction,float deltaTime){
    float velocity = MovementSpeed * deltaTime;
    //向前
    if(direction == FORWARD){
        Position += Front * velocity;
    }
    //向后
    if(direction == BACKWARD){
        Position -= Front * velocity;
    }
    //向左
    if(direction == LEFT){
        Position -= Right * velocity;
    }
    //向右
    if(direction == RIGHT){
        Position += Right * velocity;
    }
    //向上（世界上方，不是相机上方）
    if(direction == UPWARD){
        Position += WorldUp * velocity;
    }
}

//响应鼠标
void Camera::ProcessMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch){
    //xy的偏移量
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;//偏航角
    Pitch += yoffset;//俯仰角

    //判断是否锁定俯仰角
    if(constrainPitch){
        if(Pitch > 89.0f){
            Pitch = 89.0f;
        }
        if(Pitch < -89.0f){
            Pitch = -89.0f;
        }
    }
    //更新相机前向角
    updateCameraVectors();
}

//响应滚轮，yoffset表示竖直滚动的大小
void Camera::ProcessMouseScroll(float yoffset){
    Zoom -= (float)yoffset;//Zoom就是视角fov
    if(Zoom < 1.0f)
    {
        Zoom = 1.0f;
    }
    if(Zoom > 45.0f)
    {
        Zoom = 45.0f;
    }
}

//计算相机前向角
void Camera::updateCameraVectors(){
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    //更新相机右向量和上向量
    Right = glm::normalize(glm::cross(Front,WorldUp));
    Up = glm::normalize(glm::cross(Right,Front));
}

//显示相机信息
void Camera::showInf(){
    std::cout<<"-----------------------------------------"<<std::endl;
    std::cout<<"Camera information:"<<std::endl;
    std::cout<<"Position:["<<Position.x<<","<<Position.y<<","<<Position.z<<"]"<<std::endl;
    std::cout<<"Up:["<<Up.x<<","<<Up.y<<","<<Up.z<<"]"<<std::endl;
    std::cout<<"Front:["<<Front.x<<","<<Front.y<<","<<Front.z<<"]"<<std::endl;
    std::cout<<"Right:["<<Right.x<<","<<Right.y<<","<<Right.z<<"]"<<std::endl;
    std::cout<<"Yaw:"<<Yaw<<"°"<<std::endl;
    std::cout<<"Pitch:"<<Pitch<<"°"<<std::endl;
    std::cout<<"MovementSpeed:"<<MovementSpeed<<std::endl;
    std::cout<<"MouseSensitivity:"<<MouseSensitivity<<std::endl;
    std::cout<<"Zoom:"<<Zoom<<"°"<<std::endl;
}