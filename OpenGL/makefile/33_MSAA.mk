# glfw静态库编译
# skybox
include config/*.mk
EXC_NAME := 33_MSAA
$(EXC_NAME) : 
	$(CC) $(CXX_FLAGS) \
	$(SRC_DIR)/$(EXC_NAME).cpp \
	/Users/wuhan/wuhan/CodingSpace/Code/opengl/utils/src/Mesh_wh.cpp \
	/Users/wuhan/wuhan/CodingSpace/Code/opengl/utils/src/stb_image.cpp \
	-I$(INCLUDE_DIR) \
	-I$(UTILS_INCLUDE_DIR) \
	-L$(LIB_MAC_DIR) -lglad -lglfw3 -lassimp \
	-L$(UTILS_LIB_MAC_DIR) -lcamera \
	-Wl,-rpath ./ \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	-o $(DES_MAC_DIR)/$@ 
	

.PHONY : clean
clean : 
	rm -rf $(DES_MAC_DIR)/$@