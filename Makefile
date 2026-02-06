TEST_DIR := tests
TEST_BUILD := $(TEST_DIR)/build

.PHONY: build clean tests

build:
	mkdir -p build
	cmake -S . -B build
	cmake --build build
	./build/computer_club test.txt

clean:
	rm -rf build
	rm -rf ${TEST_BUILD}

tests:
	mkdir -p $(TEST_BUILD)
	cmake -S $(TEST_DIR) -B $(TEST_BUILD)
	cmake --build $(TEST_BUILD)
	./$(TEST_BUILD)/Project_tests