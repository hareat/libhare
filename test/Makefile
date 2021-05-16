run: test
	./test

test: main.cpp test.h hare/TestAlgorithm.h hare/TestNumeric.h hare/TestStrprintf.h \
		hare/throws/TestStdio.h hare/wrap/TestStdio.h
	g++ -I. -I../include main.cpp -o test
