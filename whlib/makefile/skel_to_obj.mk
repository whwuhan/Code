include config/*.mk
FLAGS := -std=c++11
EXC_NAME:=skel_to_obj_main

SRC := $(MAIN_DIR)/$(EXC_NAME).cpp $(STRING_LIB_SRC) $(IO_OBJ_SRC) $(POINT3D_SRC) $(POINT_CLOUD_SRC) $(CUBE_SRC) $(EDGE_SRC) $(FACE_SRC) \
$(POLYGON_MESH_SRC) $(LOP_SRC)


$(EXC_NAME) :
	$(CC) $(SRC) -o $(MAC_DES_DIR)/$@ -I$(INCLUDE_DIR) -I$(DEPS_EIGEN_INCLUDE_DIR) $(FLAGS)
.PHONY : clean
clean :  
	-rm $(DES_DIR)$(EXC_NAME)