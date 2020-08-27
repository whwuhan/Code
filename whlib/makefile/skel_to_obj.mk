include config/*.mk
SRC := $(IO_OBJ_SRC) $(STRING_LIB_SRC) $(MAIN_DIR)/skel_to_obj_main.cpp $(POINT3D_SRC) $(POINT_CLOUD_SRC)
skel_to_obj :
	$(CC) $(SRC) -o $(WIN_DES_DIR)/$@
.PHONY : clean
clean :  
	-rm $(DES_DIR)skel_to_obj