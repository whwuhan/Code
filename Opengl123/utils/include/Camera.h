/**
 * 封装相机功能
*/
#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

//照相机移动方向枚举
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD
};

//默认照相机数值
const float YAW         = -90.0f;   //偏航角
const float PITCH       = 0.0f;     //俯仰角
const float SPEED       = 2.5f;     //速度
const float SENSITIVITY = 0.1f;     //鼠标灵敏度
const float ZOOM        = 45.0f;    //fov视角

//相机抽象类
class Camera
{
public:
    //相机属性
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    //欧拉角
    float Yaw;//偏航角
    float Pitch;//俯仰角
    //相机选项
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    //构造方法
    Camera(
        glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),//相机位置
        glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f),
        float yaw = YAW,
        float pitch = PITCH
    );
    Camera(
        float posX,
        float posY,
        float posZ,
        float upX,
        float upY,
        float upZ,
        float yaw,
        float pitch
    );
    //获取观察矩阵，也就是loocAt矩阵
    glm::mat4 GetViewMatrix();
    //响应键盘
    void ProcessKeyboard(Camera_Movement direction,float deltaTime);
    //响应鼠标，最后一个参数表示是否限制俯仰角角度
    void ProcessMouseMovement(float xoffset,float yoffset,GLboolean constrainPitch=true);
    //响应鼠标滚轮
    void ProcessMouseScroll(float yoffset);
    //显示Camera信息
    void showInf();
private:
    //计算前向向量
    void updateCameraVectors();

};
#endif
