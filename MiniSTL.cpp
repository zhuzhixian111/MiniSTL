#include <iostream>
#include <chrono>
#define start_time auto start = std::chrono::system_clock::now();
#define end_time {\
auto end = std::chrono::system_clock::now();\
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);\
std::cout << "花费了"<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den << "秒" << std::endl;}

using namespace std;
#include "Test/VectorTest.h"
#include "Test/Priority_queueTest.h"

int main() {

	MiniSTL::VectorTest::testall();
	MiniSTL::Priority_queueTest::testall();
	system("pause");
	
	return 0;
}

