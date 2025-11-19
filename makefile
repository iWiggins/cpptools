testall: teststringutils testitertools testcxtools

teststringutils: tests/bin/stringutilstests
	./tests/bin/stringutilstests

debugstringutils: tests/bin/stringutilstests_d
	@echo Ready for debugging.

tests/bin/stringutilstests: tests/src/stringutilstests.cpp Include/stringutils.h Include/cxtools.h | tests/bin
	g++ -std=c++23 -o tests/bin/stringutilstests -I Include tests/src/stringutilstests.cpp

tests/bin/stringutilstests_d: tests/src/stringutilstests.cpp Include/stringutils.h Include/cxtools.h | tests/bin
	g++ -std=c++23 -o tests/bin/stringutilstests_d -I Include -g -Og tests/src/stringutilstests.cpp

testitertools: tests/bin/itertoolstests
	./tests/bin/itertoolstests

debugitertools: tests/bin/itertoolstests_d
	@echo Ready for debugging.

tests/bin/itertoolstests: tests/src/itertoolstests.cpp Include/itertools.h | tests/bin
	g++ -std=c++23 -o tests/bin/itertoolstests -I Include tests/src/itertoolstests.cpp

tests/bin/itertoolstests_d: tests/src/itertoolstests.cpp Include/itertools.h | tests/bin
	g++ -std=c++23 -o tests/bin/itertoolstests_d -I Include -g -Og tests/src/itertoolstests.cpp

testcxtools: tests/bin/cxtoolstests
	./tests/bin/cxtoolstests

debugcxtools: tests/bin/cxtoolstests_d
	@echo Ready for debugging.

tests/bin/cxtoolstests: tests/src/cxtoolstests.cpp Include/cxtools.h | tests/bin
	g++ -std=c++23 -o tests/bin/cxtoolstests -I Include tests/src/cxtoolstests.cpp

tests/bin/cxtoolstests_d: tests/src/cxtoolstests.cpp Include/cxtools.h | tests/bin
	g++ -std=c++23 -o tests/bin/cxtoolstests_d -I Include -g -Og tests/src/cxtoolstests.cpp

tests/bin:
	mkdir tests/bin

clean:
	rm -r tests/bin