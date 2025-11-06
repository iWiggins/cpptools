

teststringutils: tests/bin/stringutilstests
	./tests/bin/stringutilstests

debugstringutils: tests/bin/stringutilstests_d
	@echo Ready for debugging.

tests/bin/stringutilstests: tests/src/stringutilstests.cpp Include/stringutils.h | tests/bin
	g++ -o tests/bin/stringutilstests -I Include tests/src/stringutilstests.cpp

tests/bin/stringutilstests_d: tests/src/stringutilstests.cpp Include/stringutils.h | tests/bin
	g++ -o tests/bin/stringutilstests_d -I Include -g -Og tests/src/stringutilstests.cpp

tests/bin:
	mkdir tests/bin

clean:
	rm -r tests/bin