include config/*.mk
SRC := $(IO_OBJ_SRC) $(STRING_LIB_SRC) $(POINT_CLOUD_SRC) $(POINT3D_SRC)
test_graph : 
	$(CC) $(TEST_MAIN_DIR)/test_graph.cpp $(SRC) -o $(TEST_DES_DIR)/test_graph