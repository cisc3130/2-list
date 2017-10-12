#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <string>

#include "llist.h"
#include "dllist.h"

#define ARRSIZE 1000

template <class Iter, class T>
void sort(Iter begin, Iter end, T& x){
	for(Iter i = begin; i != end; ++i){
		Iter smallest = i;
		for(Iter j = i; j != end; ++j){
			if(*j < *smallest) smallest = j;
		}
		T temp = *i;
		*i = *smallest;
		*smallest = temp;
	}
}

template <class Iter>
void selectionSort(Iter begin, Iter end){
	sort(begin, end, *begin);
}

template <class Container, class T, class Iter>
void insert(Container& c, const T& val, Iter it){
	for(Iter i = c.begin(); i != c.end(); ++i){
		if(*i == val){
			c.insert(++i, val);
			break;
		}
	}
}

template <class Container, class T>
void insertNextToMatch(Container &c, const T& val){
	insert(c, val, c.begin());
}

struct time {
	uint64 start;
	std::string name;
	time(const std::string& str="") : start(GetTimeMs64()), name(str) {}
	void getTimeElapsed() { 
		std::cout << name << "... " << GetTimeMs64() - start << std::endl; 
	}
	void startAgain(const std::string& str="") {
		start = GetTimeMs64();
		name = str;
	}
};

int main(int argc, char** argv) {
	if (argc != 2) { 
		std::cout << "Usage: ./a.out <FILENAME>\n";
		return 0;
	}
	std::ifstream fin;
	fin.open(argv[1]);
	
	std::vector<int> v1, v2;
	int x;
	while (!fin.eof()) {
		fin>>x;
		v1.push_back(x);
		if (v1.size() % 5 > 2) v2.push_back(x);
	}

        struct time counter("filling list");
            List<int> lst;
        for (int i = 0; i < v1.size(); i++) {	lst.push_front(v1[i]); }
            counter.getTimeElapsed();

        counter.startAgain("filling dlist");
            DList<int> dlst;
        for (int i = 0; i < v1.size(); i++) {	dlst.push_front(v1[i]); }
            counter.getTimeElapsed();

        counter.startAgain("filling vector");
            std::vector<int> v;
        for (int i = 0; i < v1.size(); i++) { v.push_back(v1[i]); }
            counter.getTimeElapsed();
    
        counter.startAgain("sorting list");
            List<int>::iterator it(lst.begin());
        for(int i = 0; i<v1.size()-1; i++) ++it;
            selectionSort(lst.begin(), it);
        counter.getTimeElapsed();

        counter.startAgain("sorting dlist");
            selectionSort(dlst.begin(), dlst.end());
        counter.getTimeElapsed();

        counter.startAgain("sorting vector");
            selectionSort(v.begin(), v.end());
        counter.getTimeElapsed();

        counter.startAgain("adding more to list");
            for(int i = 0; i < v2.size(); i++) { insertNextToMatch(lst, v2[i]); }
        counter.getTimeElapsed();

        counter.startAgain("adding more to dlist");
            for(int i = 0; i < v2.size(); i++) { insertNextToMatch(dlst, v2[i]); }
        counter.getTimeElapsed();

        counter.startAgain("adding more to vector");
            for(int i = 0; i < v2.size(); i++) { insertNextToMatch(v, v2[i]); }
        counter.getTimeElapsed();
        fin.close();
}
