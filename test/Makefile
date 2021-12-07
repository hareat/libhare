run: tmp test
	./test

tmp:
	mkdir tmp
	chmod -w data/readonly.txt

test: main.cpp test.h hare/TestAlgorithm.h hare/TestCstdio.h hare/TestCstdlib.h \
		hare/TestCstring.h hare/TestFstream.h hare/TestFunctional.h hare/TestIconv.h hare/TestLeakyBucket.h \
		hare/TestMacSz.h hare/TestMemory.h hare/TestNumeric.h hare/TestPwd.h hare/TestSignal.h hare/TestStrprintf.h \
		hare/throws/TestCstdio.h hare/throws/TestCstdlib.h hare/throws/TestCurl.h \
		hare/throws/TestDirent.h hare/throws/TestIconv.h hare/throws/TestStat.h \
		hare/wrap/TestCstdio.h hare/wrap/TestCstdlib.h hare/wrap/TestDirent.h
	g++ -DBACKTRACE_SIZE=16 -DBACKTRACE_ADDR2LINE -I. -I../include main.cpp -g -o test -lcurl
