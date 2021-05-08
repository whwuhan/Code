# glfw静态库编译
# 聚光SpotLight 新增平滑边缘
include config/*.mk
EXC_NAME := 18_model
$(EXC_NAME) : 
	$(CC) $(CXX_FLAGS) \
	$(SRC_DIR)/$(EXC_NAME).cpp \
	/Users/wuhan/wuhan/coding_space/Code/opengl/utils/src/Camera.cpp \
	/Users/wuhan/wuhan/coding_space/Code/opengl/utils/src/Mesh_wh.cpp \
	/Users/wuhan/wuhan/coding_space/Code/opengl/utils/src/stb_image.cpp \
	-I$(INCLUDE_DIR) \
	-I$(UTILS_INCLUDE_DIR) \
	-L$(LIB_MAC_DIR) -lglad -lglfw3 -lassimp \
	-Wl,-rpath ./ \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	-o $(DES_MAC_DIR)/$@ 
	

.PHONY : clean
clean : 
	rm -rf $(DES_MAC_DIR)/$@