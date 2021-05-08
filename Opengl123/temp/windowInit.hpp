//
//  windowInit.hpp
//  HelloOpenGL
//
//  Created by wuhan on 2020/2/19.
//  Copyright © 2020 wuhan. All rights reserved.
//

#ifndef windowInit_hpp
#define windowInit_hpp

#include <iostream>
#include <glad/glad.h> //glad需要在GLFW之前包含
#include <GLFW/glfw3.h>
// 声明回调函数，更改窗口大小的时候，更改视口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// 声明回输入函数，判断是否按下键盘
void processInput(GLFWwindow *window);


#endif /* windowInit_hpp */
