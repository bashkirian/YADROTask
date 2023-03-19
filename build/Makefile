CC=g++
CFLAGS=-Wall -std=c++14

tapesort:
	mkdir tmp;
	$(CC) $(CFLAGS) ..\src\main.cpp ..\src\Sorter\sorter.cpp ..\src\Tape\tape.cpp -o sorttape
unittests: 
	mkdir tmp;
	$(CC) $(CFLAGS) ..\src\Sorter\sorter.cpp ..\src\Tape\tape.cpp ..\src\UnitTests\unit_tests.cpp -o runtests
clean: 
	rmdir /s /q tmp;
	del .\*.exe;

# FOR LINUX
# tapesort:
# 	mkdir tmp;
# 	$(CC) $(CFLAGS) ../src/main.cpp ../src/Sorter/sorter.cpp ../src/Tape/tape.cpp -o sorttape
# unittests: 
# 	mkdir tmp;
# 	$(CC) $(CFLAGS) ../src/Sorter/sorter.cpp ../src/Tape/tape.cpp ../src/UnitTests/unit_tests.cpp -o runtests
# clean: 
# 	rm -rf tmp;
# 	rm ./*.exe;
