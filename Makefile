CC=g++
CFLAGS=-Wall -std=c++14

tapesort:
# mkdir .\src\Sorter\tmp;
	$(CC) $(CFLAGS) src\main.cpp src\Sorter\sorter.cpp src\Tape\tape.cpp -o sorttape
unittests: 
	make tapesort;
	$(CC) $(CFLAGS) src\UnitTests src\unit_tests.cpp -o runtests
clean: 
	rmdir .\src\Sorter\tmp;
	del .\*.exe;