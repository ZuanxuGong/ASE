#include <bitset>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include "bigint.h"
#include "prime.h"
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <fstream>

int main() {

	clock_t start, finish;
	double runtime;
	int index;

	long long range;
	int judge;
	std::ofstream write;
	write.open("result.txt");
	while (TRUE) {
		std::cout << "Input the index for calculating: (exit with 0)" << std::endl;
		std::cin >> index;
		if (index == 0) break;
		std::cout << "Which algorithm to deploy? 0:Faster Filtering 1:Filtering with BigInt" << std::endl;
		std::cin >> judge;
		if (judge) {
			range = index * 20;
			std::vector<long long> large;
			Prime<long long> large_Prime;
			start = clock();
			large = large_Prime.Filter(BigInt(range));
			finish = clock();
			std::cout << "No." << index << " prime: " << large[index - 1] << std::endl;
			runtime = 1.0 * (finish - start) / CLOCKS_PER_SEC;
			std::cout << "Runtime: " << runtime << "s" << std::endl;
			write << "Deploying algorithm with BigInt..." << "\tNo." << index << " prime: " << large[index - 1] << "\tRuntime: " << runtime << "s" << std::endl << std::endl;
		}
		else {
			std::vector<int> mini;
			Prime<int> mini_Prime;
			start = clock();
			mini = mini_Prime.FasterFilter(index);
			finish = clock();
			std::cout << "No." << index << " prime: " << mini[index - 1] << std::endl;
			runtime = 1.0 * (finish - start) / CLOCKS_PER_SEC;
			std::cout << "Runtime: " << runtime << "s" << std::endl;
			write << "Deploying faster algorithm..." << "\tNo." << index << " prime: " << mini[index - 1] << "\tRuntime: " << runtime << "s" << std::endl << std::endl;
			std::cin.get();
		}
	}
	write.close();
	std::cin.get();

	return 0;
}