# glfw动态库编译
include config/*.mk
create_window : 
	$(CC) $(CXX_FLAGS) \
	$(SRC_DIR)/create_window.cpp \
	-I$(DEP_DIR) \
	-L$(LIB_MAC_DIR) -lglad -lglfw.3 \
	-Wl,-rpath $(LIB_MAC_DIR) \
	-o $(DES_MAC_DIR)/$@

.PHONY : clean
clean : 
	-rm -rf $(DES_MAC_DIR)/$@