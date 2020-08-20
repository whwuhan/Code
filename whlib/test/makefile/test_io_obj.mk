include config/*.mk

test_io_obj :
	$(CC) $(TEST_MAIN_DIR)/test_io_obj.cpp $(IO_OBJ_SRC) $(STRING_LIB_SRC) $(POINT_CLOUD_SRC) $(POINT3D_SRC) -o $(TEST_DES_DIR)/test_io_obj

.PHONY : clean
clean :  
	-rm $(DES_DIR)test_io_obj