include config/mac_dir.mk


test : 
	$(CC) $(MAIN_DIR)main.cpp $(UTILS_DIR)string_lib.cpp -o $(DES_DIR)test


.PHONY : clean
clean :  
	-rm -rf $(DES_DIR)test
