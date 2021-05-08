# glfw静态库编译
# 链接camera静态库有问题
include config/*.mk
EXC_NAME := 07_camera_move_camera
$(EXC_NAME) : 
	$(CC) $(CXX_FLAGS) \
	$(SRC_DIR)/$(EXC_NAME).cpp \
	-I$(DEP_DIR) \
	-I$(UTILS_INCLUDE_DIR) \
	-L$(LIB_MAC_DIR) -lglad -lglfw3 \
	-L$(UTILS_LIB_MAC_DIR) -lcamera \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	-o $(DES_MAC_DIR)/$@ 
	

.PHONY : clean
clean : 
	rm -rf $(DES_MAC_DIR)/$(EXC_NAME)