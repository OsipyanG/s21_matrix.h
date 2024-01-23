SRC=$(wildcard s21_*.c)
TEST_SRC=$(wildcard tests/s21_*test.c) unit_tests.c

OBJ=$(patsubst %.c,%.o,$(SRC))
TEST_OBJ=$(patsubst tests/%.c,%.o,$(TEST_SRC))
GCOV_TEST_OBJ=$(patsubst %, gcov_%, $(OBJ))

CFLAGS=-Wall -Werror -Wextra -std=c11   -g3
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
TEST_FLAGS=-lcheck
OPEN=open
else ifeq ($(shell hostnamectl | grep -o 'Ubuntu'), Ubuntu)
TEST_FLAGS=-lpthread -lcheck   -lm -lsubunit
OPEN=open
else
TEST_FLAGS=-lpthread -lm -lcheck
OPEN=xdg-open
endif
GCOV_FLAGS=-ftest-coverage --coverage
CC=gcc

.PHONY: all clean clang-format test

all: s21_matrix.a

s21_matrix.a: clang-format $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

test: s21_matrix.a $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ)  s21_matrix.a -o ./unit_tests $(TEST_FLAGS)
	./unit_tests

gcov_report: s21_matrix.a $(GCOV_TEST_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(GCOV_TEST_OBJ) $(TEST_OBJ) -o ./gcov_unit_tests $(TEST_FLAGS)
	./gcov_unit_tests
	lcov -t "s21_matrix_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN) report/index.html

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: tests/%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(TEST_FLAGS)

gcov_%.o: %.c
	$(CC) -c $(CFLAGS) $(GCOV_FLAGS) $< -o ./$@ $(TEST_FLAGS)

clang-format:
	clang-format -i *.c *.h ./tests/*.c ./tests/*.h

clean:
	rm -rf report/
	rm -rf *.o *.a *.gcno *.gcda unit_tests gcov_unit_tests *.info

