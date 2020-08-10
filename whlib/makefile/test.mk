include config/win_dir.mk


test.exe : 
	$(CC) $(MAIN_DIR)test.cpp $(UTILS_DIR)string_lib.cpp -o $(DES_DIR)test.exe


.PHONY : clean
clean :  
	-rm $(DES_DIR)test.exe
