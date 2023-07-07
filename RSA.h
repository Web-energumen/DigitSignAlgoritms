#pragma once
#ifndef RSALIB
#define RSALIB

#include <string>
#include <vector>

class RSA {
private:
	int powMod(int x, int y, int p);
	bool millerTest(int d, int n);
	bool checkPrime(int n, int k);
	int gcd(int a, int h);
	long encrypt(double message, const int& n, const int& publicKey);
	long decrypt(int encrpyted_text, const int& n, const int& privateKey);

public:
	void readTxtFile(std::string path, std::string& text);
	void generateRandomPrimeNumber(int& n);
	void setKeys(int P, int Q, int& n, int& publicKey, int& privateKey);
	void encoder(std::string message, const int& n, const int& publicKey, std::vector<int>& c);
	void decoder(std::vector<int> encoded, const int& n, const int& privateKey, std::string& d);
};
#endif // !RSALIB

