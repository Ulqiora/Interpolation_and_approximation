CC=g++
BD=../build
GCOV_REPORT_FOLDER=$(BD)
CXX_FLAGS=-c -std=c++17 -O2#-Wall -Werror -Wextra -Wfloat-equal -Warray-bounds -Wshadow -pedantic
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lrt
endif

all: clean start

./$(BD)/%.o:%.cc
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o:*/%.cc
	$(CC) $(CXX_FLAGS) $< -o $@
 
./$(BD)/%.o: */*/%.cc
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o: */*/*/%.cc
	$(CC) $(CXX_FLAGS) $< -o $@

#              Файлы для основного проекта
PROJECT_FILES_SOURCES=$(shell find $(PWD)   -iname '*.cc')
PROJECT_FILES_FILENAMES=$(shell basename -a $(PROJECT_FILES_SOURCES))
PROJECT_FILES_OBJECTS=$(addprefix $(BD)/,$(PROJECT_FILES_FILENAMES:.cc=.o))


run: tests
	./$(BD)/tests

start:$(PROJECT_FILES_OBJECTS)
	$(CC) -g  $^ -o $(BD)/$@ 
	./$(BD)/$@

gcov_report: clean
	g++ --coverage $(TESTS_FILES_SOURCES) -o test -lgtest -std=c++17
	./test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open ./report/index.html

check: clean tests
	 cp -f ../materials/linters/.clang-format .clang-format
	clang-format -i $(PROJECT_FILES_SOURCES)
	 clang-format -n $(PROJECT_FILES_SOURCES)
	 cppcheck --language=c++ --enable=all --suppressions-list=suppresionlist.cfg $(PROJECT_FILES_SOURCES)
	 rm -rf .clang-format
	 CK_FORK=no leaks --atExit -- ./../build/tests

clean:
	rm -rf $(BD)/*
	rm -rf $(BD)/*.*
	rm -rf run test *.a *.o
	rm -rf *.gcda *.gcno *.info
	rm -rf ./report
	rm -rf Tests/Examples/out.txt