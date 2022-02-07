main.o : main.cpp skiplist.hpp skiplist.cpp
	g++ main.cpp skiplist.cpp -O3 -o skiplist.x
	echo "operation succesfully done!\n"
	echo "you can call as ./skiplist.x SIZE default SIZE is 100"
clean :
	rm skiplist.x
