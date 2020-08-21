include config/*.mk

SRC :=  $(POINT3D_SRC) $(TEST_MAIN_DIR)/test_curve.cpp $(STRING_LIB_SRC)
test_curve:
	$(CC) -o $(TEST_DES_DIR)/$@  $(SRC)