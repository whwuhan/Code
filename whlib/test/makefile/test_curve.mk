include config/*.mk
FLAGS := -std=c++11

SRC := $(TEST_MAIN_DIR)/test_curve.cpp $(STRING_LIB_SRC) $(IO_OBJ_SRC) $(POINT3D_SRC) $(POINT_CLOUD_SRC)
test_curve:
	$(CC) -o $(TEST_DES_DIR)/$@  $(FLAGS) $(SRC) -I$(DEPS_EIGEN_INCLUDE_DIR) -I$(INCLUDE_DIR)