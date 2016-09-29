#pragma once
#ifndef _BIGINT_H_
#define _BIGINT_H_
#define BIT 10000

class BigInt {

private:
	
	std::vector<int> digits;// get the bigint from integers

	int operator [] (const int& k) const;//get digit

	void Assign(const int& k, const int& value);//assignment

	
	int size() const {// length
		return digits.size();
	}
	
	void resize() {// smoothing
		while (digits.size() > 1 && digits.back() == 0) {
			digits.pop_back();
		}
	}

	void resize(int length) {// set length of vector
		digits.resize(length);
	}

public:
	BigInt() {}

	BigInt(const int& value);//int to bigint

	operator int() const;//bigint to int

	BigInt operator = (const int& value);//assignment

	BigInt operator + (const BigInt& add) const;//addition
	BigInt operator - (const BigInt& sub) const;//subtraction
	BigInt operator * (const BigInt& mul) const;//multiplication
	BigInt operator % (const BigInt& mod) const;//modulo operation
																	//operator overload
	bool operator == (const BigInt& comp) const;//equal to
	bool operator != (const BigInt& comp) const;//unequal to 
	bool operator < (const BigInt& comp) const;//less than
	bool operator <= (const BigInt& comp) const;//less than or equal to
	bool operator > (const BigInt& comp) const;//bigger than
	bool operator >= (const BigInt& comp) const;//bigger than or equal to

	BigInt& operator ++ ();//self increment
	BigInt operator ++ (int);
	BigInt& operator -- ();//self decrement
	BigInt operator -- (int);

	void Print();//print

};

#endif