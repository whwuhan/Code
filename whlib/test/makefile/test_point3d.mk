include config/*.mk


test : 
	$(CC) $(TEST_MAIN_DIR)test_point3d.cpp $(BASIC_DIR)point3d.cpp -o $(TEST_DES_DIR)test_point3d


.PHONY : clean
clean :  
	-rm $(DES_DIR)test_point3d
