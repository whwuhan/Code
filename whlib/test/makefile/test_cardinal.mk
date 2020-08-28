include config/*.mk
FLAGS := -std=c++11

test : 
	$(CC) $(FLAGS) $(TEST_MAIN_DIR)/test_cardinal.cpp \
	$(BASIC_DIR)/point_cloud.cpp \
	$(IO_OBJ_SRC) \
	$(STRING_LIB_SRC) \
	$(BASIC_DIR)/point3d.cpp -o \
	$(TEST_DES_DIR)/test_cardinal


.PHONY : clean
clean :  
	-rm $(DES_DIR)test_point3d
