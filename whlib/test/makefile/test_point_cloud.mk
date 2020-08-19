include config/*.mk

test_point_cloud : 
	$(CC) $(TEST_MAIN_DIR)test_point_cloud.cpp $(BASIC_DIR)point_cloud.cpp $(BASIC_DIR)point3d.cpp -o $(TEST_DES_DIR)test_point_cloud

.PHONY : clean
clean :  
	-rm $(DES_DIR)test_point_cloud
