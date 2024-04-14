CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
CFLAGS_GCOV =-Wall -Werror -Wextra --coverage
CFLAGS_TEST =-lgtest -pthread -lgmock -fprofile-arcs -ftest-coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  CFLAGS_TEST += -lm -lsubunit
  OPEN=xdg-open
else
  OPEN=open
endif

LEAKS_RUN = CK_FORK=no leaks -atExit -- ./tests

SOURCES = ./model/affine.cc ./model/parser.cc ./controller/controller.cc
HEADERS = ./model/model.h ./model/affine.h ./model/parser.h ./controller/controller.h
SOURCES_TEST = ./tests/test.cc

DVI_DIR = ./"doc_3DViewer_v2.0"
BUILD_DIR = ../build
OUTFILE_TEST = test

all: install

install:
	qmake CONFIG+=release -o $(BUILD_DIR)/Makefile 3DViewer.pro 
	-cd $(BUILD_DIR); make
	-cd $(BUILD_DIR); make clean  

uninstall:
	rm -rf ../build

dist:
	mkdir CPP4_3DViewer_v2.0
	cp -rf ./model ./controller ./view *.cpp *.pro *.texi Makefile CPP4_3DViewer_v2.0
	tar -cf CPP4_3DViewer_v2.0.tar CPP4_3DViewer_v2.0
	rm -rf CPP4_3DViewer_v2.0

dvi:
	makeinfo -o $(DVI_DIR) --html --no-warn --force ./3DViewer_v2.0_info.texi
	$(OPEN) $(DVI_DIR)/index.html

test:
	$(CC) -c $(HEADERS) $(CFLAGS)
	$(CC) $(SOURCES_TEST) $(SOURCES) -o $(OUTFILE_TEST) $(CFLAGS_TEST) $(CFLAGS)
	./$(OUTFILE_TEST)

gcov_report: test
	lcov -t "s21_3dviewer_test" -o s21_3dviewer_test.info -c -d .
	genhtml -o report s21_3dviewer_test.info
	open report/index.html

google_style:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format --verbose -i ./model/*.h ./model/*.cc ./controller/*.h ./controller/*.cc ./view/*.h ./view/*.cpp
	rm .clang-format

clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format --verbose -n ./model/*.h ./model/*.cc ./controller/*.h ./controller/*.cc ./view/*.h ./view/*.cpp
	rm .clang-format

leaks: test
	$(LEAKS_RUN)

clean:
	rm -rf ./lcov_report
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.info *.html *.css report doc_3DViewer_v2.0 ./model/*.gch ./controller/*.gch ./view/*.gch .qmake.stash $(BUILD_DIR)/$(OUTFILE_TEST)
