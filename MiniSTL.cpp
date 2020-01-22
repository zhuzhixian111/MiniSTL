#include <iostream>
#include <chrono>
#include "Vector.h"
#include <vector>
#include "List.h"
#include <list>
#define start_time auto start = std::chrono::system_clock::now();
#define end_time {\
auto end = std::chrono::system_clock::now();\
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);\
std::cout << "花费了"<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den << "秒" << std::endl;}

using namespace std;


int main() {


	//start_time

		MiniSTL::Vector<int> v;
	MiniSTL::List<int> l;
	std::list<int> stdl;
	
	srand((unsigned)time(NULL));
	for (int i = 0; i < 100; i++) {
		l.push_back(i);
	}
	l.reverse();
	for (auto it = l.begin(); it != l.end(); it++) {
		cout << *it << endl;
	}


	//end_time
	//	system("pause");

	return 0;
}

