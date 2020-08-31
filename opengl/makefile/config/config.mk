# makefile 配置文件

# 编译器配置
CC := g++
CXX_FLAGS := -std=c++11

# 目录配置
BIN_DIR := ../bin/
BIN_WIN_DIR := ../bin/win
BIN_MAC_DIR := ../bin/mac
INCLUDE_DIR := ../include
LIB_DIR := ../lib
LIB_WIN_DIR := ../lib/win
LIB_MAC_DIR := ../lib/mac
SRC_DIR := ../src
MAKEFILE_DIR := ./
DES_WIN_DIR := ../bin/win#win目标文件夹
DES_MAC_DIR := ../bin/mac#mac目标文件夹
DEP_DIR := ../dep

# 静态库文件配置
LIB_MAC_GLAD_A := $(LIB_MAC_DIR)/glad
LIB_MAC_GLFW3_A := $(LIB_MAC_DIR)/glfw3





