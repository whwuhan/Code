# 源文件配置文件
#include config/dir_config.mk#注意这里是要写最顶层makefile，也就是生成最终可执行文件的makefile的位置为基准
# 基础结构体源文件
POINT3D_SRC := $(BASIC_DIR)/point3d.cpp
POINT_CLOUD_SRC := $(BASIC_DIR)/point_cloud.cpp
CUBE_SRC:=$(BASIC_DIR)/cube.cpp
POLYGON_MESH_SRC:=$(BASIC_DIR)/polygon_mesh.cpp
EDGE_SRC:=$(BASIC_DIR)/edge.cpp
FACE_SRC:=$(BASIC_DIR)/face.cpp
LOP_SRC:=$(ALG_DIR)/LOP.cpp
# 功能源文件
IO_OBJ_SRC := $(UTILS_DIR)/io/io_obj.cpp
STRING_LIB_SRC := $(UTILS_DIR)/string_lib.cpp


