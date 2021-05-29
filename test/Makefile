run: tmp test
	./test

tmp:
	mkdir tmp
	chmod -w data/readonly.txt

test: main.cpp test.h hare/TestAlgorithm.h hare/TestCstdio.h hare/TestCstdlib.h \
		hare/TestCstring.h hare/TestFunctional.h hare/TestNumeric.h hare/TestStrprintf.h \
		hare/throws/TestCstdio.h hare/throws/TestCstdlib.h hare/throws/TestDirent.h \
		hare/wrap/TestDirent.h hare/wrap/TestCstdio.h
	g++ -I. -I../include main.cpp -o test
