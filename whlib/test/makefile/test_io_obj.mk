include config/config.mk

test_io_obj :
	$(CC) $(TEST_MAIN_DIR)test_io_obj.cpp $(UTILS_DIR)io.cpp $(UTILS_DIR)string_lib.cpp $(BASIC_DIR)point_cloud.cpp $(BASIC_DIR)point3d.cpp -o $(TEST_DES_DIR)test_io_obj

.PHONY : clean
clean :  
	-rm $(DES_DIR)test_io_obj