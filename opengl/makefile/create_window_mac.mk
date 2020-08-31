# glfw静态库编译
include config/*.mk
create_window : 
	$(CC) $(CXX_FLAGS) \
	$(SRC_DIR)/create_window.cpp \
	-I$(DEP_DIR) \
	-L$(LIB_MAC_DIR) -lglad -lglfw3 \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
	-o $(DES_MAC_DIR)/$@ 
	

.PHONY : clean
clean : 
	-rm -rf $(DES_MAC_DIR)/$@