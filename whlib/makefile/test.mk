include win_dir.mk


test : 
	$(CC) $(MAIN_DIR)main.cpp $(UTILS_DIR)string_lib.cpp -o $(DES_DIR)test



