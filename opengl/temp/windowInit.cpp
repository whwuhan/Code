//
//  windowInit.cpp
//  HelloOpenGL
//
//  Created by wuhan on 2020/2/19.
//  Copyright © 2020 wuhan. All rights reserved.
//

#include "../include/windowInit.hpp"

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
