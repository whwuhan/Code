include config/*.mk

test_binary_tree : 
	$(CC) $(TEST_MAIN_DIR)/test_binary_tree.cpp -o $(TEST_DES_DIR)/test_binary_tree

.PHONY : clean
clean :  
	-rm $(DES_DIR)test_binary_tree