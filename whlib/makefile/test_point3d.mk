include config/win_dir.mk


test.exe : 
	$(CC) $(MAIN_DIR)test_point3d.cpp $(BASIC_DIR)point3d.cpp -o $(DES_DIR)test_point3d.exe


.PHONY : clean
clean :  
	-rm $(DES_DIR)test_point3d.exe
