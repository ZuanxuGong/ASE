#include <cstdio>
#include <vector>
#include <algorithm>
#include "bigint.h"

BigInt::BigInt(const int& value) { //transformation from int
	digits.clear();
	int tmp = value;
	while (tmp) {
		digits.push_back(tmp % BIT);
		tmp /= BIT;
	}
}

int BigInt::operator [] (const int& k) const {//getting digit
	if (k < (int)digits.size()) return digits[k];
	else return 0;
}

BigInt::operator int() const {//transformation to int
	int result = 0;
	for (int i = digits.size() - 1; i >= 0; i--) {
		result = result * BIT + digits[i];
	}
	return result;
}

void BigInt::Assign(const int& k, const int & value) {
	if (k >= (int)digits.size()) {
		digits.resize(k + 1);
	}
	digits[k] = value;
}

BigInt BigInt::operator = (const int& value) {//assignment
	digits.clear();
	int tmp = value;
	while (tmp) {
		digits.push_back(tmp % BIT);
		tmp /= BIT;
	}
	return *this;
}

BigInt BigInt::operator + (const BigInt& add) const {//addtion
	int length = std::max((*this).digits.size(), add.digits.size());
	BigInt result;
	result.resize(length);
	int x, y = 0;
	for (int i = 0; i < length; i++) {
		x = (*this)[i] + add[i] + y;
		if (x >= BIT) {
			x -= BIT;
			y = 1;
		}
		else {
			y = 0;
		}
		result.Assign(i, x);
	}
	if (y) {
		result.Assign(length, y);
	}
	result.resize();
	return result;
}

BigInt BigInt::operator - (const BigInt& sub) const {//subtraction
	int length = std::max((*this).size(), sub.size());
	BigInt result;
	result.resize(length);
	int x, y = 0;
	for (int i = 0; i < length; i++) {
		x = (*this)[i] - sub[i] - y;
		if (x < 0) {
			x += BIT;
			y = 1;
		}
		else {
			y = 0;
		}
		result.Assign(i, x);
	}
	if (y) {
		result.Assign(length, result[length] - 1);
	}
	result.resize();
	return result;
}

BigInt BigInt::operator * (const BigInt& mul) const {//multiplication
	int len1 = (*this).size();
	int len2 = mul.size();
	int length = len1 + len2;
	BigInt result;
	result.resize(length);
	int x, y;
	for (int i = 0; i < len1; i++) {
		y = 0;
		for (int j = 0; j < len2; j++) {
			x = (*this)[i] * mul[j] + result[i + j] + y;
			y = x / BIT;
			x = x - y * BIT;
			result.Assign(i + j, x);
		}
		if (y > 0) {
			result.Assign(i + len2, y);
		}
	}
	result.resize();
	return result;
}

BigInt BigInt::operator % (const BigInt& mod) const {//modulo operation
	std::vector<BigInt> result;
	result.push_back(mod);
	while (result.back() <= *this) {
		result.push_back(result.back() * BigInt(2));
	}
	result.pop_back();
	if (result.size() == 0) {
		return *this;
	}
	BigInt rem = *this;
	while (result.size()) {
		if (rem >= result.back()) {
			rem = rem - result.back();
		}
		result.pop_back();
	}
	return rem;
}

bool BigInt::operator == (const BigInt& comp) const {//equal sign
	if ((*this).size() != comp.size()) return false;
	for (int i = (*this).size() - 1; i >= 0; i--)
		if ((*this)[i] != comp[i]) return false;
	return true;
}

bool BigInt::operator != (const BigInt& comp) const {//unequal
	return !((*this) <= comp);
}

bool BigInt::operator < (const BigInt& comp) const {//less than
	if ((*this).size() < comp.size()) return true;
	if ((*this).size() > comp.size()) return false;
	for (int i = (*this).size() - 1; i >= 0; i--) {
		if ((*this)[i] < comp[i]) return true;
		if ((*this)[i] > comp[i]) return false;
	}
	return false;
}

bool BigInt::operator <= (const BigInt& comp) const {//less than or equal to
	if ((*this).size() < comp.size()) return true;
	if ((*this).size() > comp.size()) return false;
	for (int i = (*this).size() - 1; i >= 0; i--) {
		if ((*this)[i] < comp[i]) return true;
		if ((*this)[i] > comp[i]) return false;
	}
	return true;
}

bool BigInt::operator > (const BigInt& comp) const {//bigger than
	return !((*this) <= comp);
}

bool BigInt::operator >= (const BigInt& comp) const {//bigger than or equal to
	return !((*this) < comp);
}

BigInt& BigInt::operator ++ () {// self increment
	digits[0]++;
	for (int i = 0; i < (int)digits.size(); i++) {
		if (digits[i] == BIT) {
			digits[i] = 0;
			if (i == (int)digits.size() - 1) {
				digits.push_back(1);
				break;
			}
			else digits[i + 1]++;
		}
		else break;
	}
	return (*this);
}

BigInt BigInt::operator ++ (int) {//self increment by given step
	BigInt tmp = *this;
	++*this;
	return tmp;
}

BigInt& BigInt::operator -- () {//self decrement
	digits[0]--;
	for (int i = 0; i < (int)digits.size(); i++) {
		if (digits[i] < 0) {
			digits[i] = BIT - 1;
			digits[i + 1]--;
		}
		else break;
	}
	(*this).resize();
	return (*this);
}

BigInt BigInt::operator -- (int) {//self decrement by given step
	BigInt tmp = *this;
	--*this;
	return tmp;
}

void BigInt::Print() {//print
	int tmp, cnt;
	std::vector<int> bits;
	if (digits.size() > 0) {
		printf("%d", digits.back());
	}
	for (int i = digits.size() - 2; i >= 0; i--) {
		cnt = BIT / 10;
		tmp = digits[i];
		while (cnt) {
			bits.push_back(tmp % 10);
			tmp /= 10;
			cnt /= 10;
		}
		while (bits.size()) {
			std::printf("%d", bits.back());
			bits.pop_back();
		}
	}
	std::printf("\n");
}