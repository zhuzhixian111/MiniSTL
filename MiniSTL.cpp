#include <iostream>
#include <chrono>
#include "Vector.h"
#include <vector>
#include "List.h"
#include <list>
#include "Deque.h"
#include "Stack.h"

#define start_time auto start = std::chrono::system_clock::now();
#define end_time {\
auto end = std::chrono::system_clock::now();\
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);\
std::cout << "花费了"<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den << "秒" << std::endl;}

using namespace std;


#include <deque>
#include "Queue.h"
#include <queue>
#include "VectorTest.h"


int main() {


	MiniSTL::VectorTest::testall();

	
	
	system("pause");
	
	return 0;
}

