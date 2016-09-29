#pragma once
#ifndef _PRIME_H_
#define _PRIME_H_

template<class Type>
class Prime {
private:

public:
	std::vector<Type> FasterFilter(int index) {
		std::vector<Type> results;
		long range = 20 * index;
		long count = 0;
		long i, j;
		bool *primes = new bool[range / 2];
		for (i = 0; i <range / 2; i++) primes[i] = 1;
		for (i = 1; i <= sqrt(range) / 2; i++)
			if (primes[i])
				for (j = 2 * i*i + 2 * i; j < range / 2; j += 2 * i + 1) primes[j] = 0;

		for (i = 0; i < range / 2; i++) {
			if (primes[i]) results.push_back(2 * i + 1);
			if (count == range / 20) break;
		}
		results[0] = 2;
		return results;

	}

	std::vector<Type> Filter(const Type& range) {
		std::set<Type> primes;
		Type current = Type(3);
		while (current <= range) {
			primes.insert(current);
			current = current + Type(2);
		}
		std::vector<Type> results;
		results.push_back(Type(2));
		while (primes.size()) {
			results.push_back(*primes.begin());
			std::vector<Type> trash;
			trash.push_back(results.back());
			for (auto& item : primes) {
				current = results.back() * item;
				if (current > range) break;
				trash.push_back(current);
				current = current + results.back();
			}
			while (trash.size()) {
				primes.erase(trash.back());
				trash.pop_back();
			}
		}
		return results;
	}
};
#endif