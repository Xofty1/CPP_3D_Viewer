QT_DIR = /usr/lib/x86_64-linux-gnu
QT_INC = -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtOpenGL

QT_LIB = -L$(QT_DIR) -lQt5Widgets -lQt5Gui -lQt5Core -lQt5OpenGL -lGL
FILE_TO_CHECK = Model/model.cc
CC = g++ -std=c++17 -g
CFLAGS = $(QT_INC) $(QT_LIB) -Wall -Werror -Wextra
TESTSFLAGS = -lgtest -lgtest_main -lpthread
VALGRIND_FLAGS_v2 = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full
UNAME = $(shell uname)
LINUX_FLAGS=-lgtest -lgtest_main -pthread
LFLAGS = -fprofile-arcs -ftest-coverage
OPEN :=

ifeq ($(UNAME), Linux)
	OPEN += xdg-open
endif

ifeq ($(UNAME), Darwin)
	OPEN += open
endif

all: build

gcov: gcov_report

tests: s21_viewer_v2.a
	$(CC) $(CFLAGS) $(LFLAGS) ./tests/tests_model.cc ./Model/*.cc $(TESTSFLAGS) -o test $(LINUX_FLAGS)
	@./test


build:
	@mkdir -p 3DView_v2
	@cd 3DView_v2/ && qmake ../Viewer.pro && make

stylemake:
	clang-format -style=google -i ./Model/*.cc ./Model/*.h ./Controller/*.cc ./Controller/*.h ./View/*.cc ./View/*.h *.cc *.h ./tests/*.cc

stylecheck:
	clang-format -style=google -n ./Model/*.cc ./Model/*.h ./Controller/*.cc ./Controller/*.h ./View/*.cc ./View/*.h *.cc *.h ./tests/*.cc

dvi:
	@cd docs && doxygen Doxyfile && $(OPEN) ./html/index.html

open:
	@$(OPEN) 3DView_v2/Viewer

uninstall:
	@rm -rf 3DView_v2

dist:
	mkdir -p Viewer
	@cp -r ./Model/*.cc ./Model/*.h ./Controller/*.cc ./Controller/*.h ./View/*.cc ./View/*.h *.cc *.h ./View/*.ui *.pro Makefile tests/ Doxyfile Viewer
	@tar -cvzf dist.tar.gz Viewer
	@rm -rf Viewer


s21_viewer_v2.a: 
	g++ -Wall -Wextra -Werror $(FILE_TO_CHECK)  -c
	ar rc s21_viewer_v2.a *.o
	ranlib s21_viewer_v2.a
	rm *.o


gcov_report: tests
	gcov -o . ./tests/tests_model.cc
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	genhtml coverage.info --output-directory coverage-html
	rm -rf *.gcda *.gcno
	xdg-open coverage-html/index.html


# Компиляция и запуск тестов

clean:
	@rm -rf *.o test 3DView_v2 dist.tar.gz Viewer
	rm -rf *.o
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.gcda
	rm -rf *.a
	rm -rf *.info
	rm -rf *.a_check
	rm -rf gcov
	rm -rf coverage
	rm -rf coverage-html
	rm -rf test
	rm -rf memory_test
	rm -rf valgrind.txt


rebuild: clean all

clang:
	find . -type f \( -name '*.cc' -o -name '*.h' \) | xargs clang-format -i

valgrind: tests
	valgrind $(VALGRIND_FLAGS_v2) ./test
	grep -n "ERROR SUMMARY" valgrind.txt


.PHONY: all build install stylemake stylecheck dvi open uninstall dist tests clean rebuild clang
