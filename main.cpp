#include <iostream>
#include <chrono>
#include "Vector.h"
#include <vector>
#define start_time auto start = std::chrono::system_clock::now();
#define end_time {\
auto end = std::chrono::system_clock::now();\
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);\
std::cout << "»¨·ÑÁË"<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den << "Ãë" << std::endl;}

using namespace std;


int main() {
	
	
	start_time
	MiniSTL::Vector<int> v;

	std::vector<int> V;


	for (int i = 0; i < 1e7; i++) {
		v.push_back(i);
		//V.push_back(i);
	}
	auto it = MiniSTL::find(v.begin(), v.end(), 12000000);
	
	printf("%d\n", v.size());


	end_time
		//	system("pause");
		float c;
	cin >> c;
	return 0;
}

