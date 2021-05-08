# glfw静态库编译
include config/*.mk
EXC_NAME := 01_create_window
$(EXC_NAME) : 
	$(CC) $(CXX_FLAGS) \
	$(SRC_DIR)/$(EXC_NAME).cpp \
	-I$(DEP_DIR) \
	-L$(LIB_MAC_DIR) -lglad -lglfw3 \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	-o $(DES_MAC_DIR)/$@ 
	

.PHONY : clean
clean : 
	-rm -rf $(DES_MAC_DIR)/$@