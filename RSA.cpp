#include "RSA.h"

#include <iostream>
#include <fstream>
#include <random>

void RSA::readTxtFile(std::string path, std::string& text) {
	std::ifstream fileRead;
	try {
		fileRead.open(path);

		std::string temp;
		if (!fileRead.is_open()) {
			throw std::exception("File can not be open");
		}
		else {
			while (!fileRead.eof()) {
				std::getline(fileRead, temp);
				text += temp + "\n";
			}
		}
		fileRead.close();
	}
	catch (const std::exception& EXEPT) {
		std::cout << EXEPT.what() << std::endl;
		fileRead.close();
	}
}

int RSA::powMod(int x, int y, int p) {
	int res = 1;
	x = x % p;

	while (y > 0) {
		if (y & 1) {
			res = (res * x) % p;
		}
		y = y >> 1;
		x = (x * x) % p;
	}
	return res;
}

bool RSA::millerTest(int d, int n) {
	std::mt19937 randomGen32(time(nullptr));
	int a = 2 + randomGen32() % (n - 4);
	int x = powMod(a, d, n);

	if (x == 1 || x == n - 1) {
		return true;
	}
	while (d != n - 1) {
		x = (x * x) % n;
		d *= 2;

		if (x == 1) {
			return false;
		}
		if (x == n - 1) {
			return true;
		}
	}
	return false;
}

bool RSA::checkPrime(int n, int k) {
	if (n <= 1 || n == 4) {
		return false;
	}
	if (n <= 3) {
		return true;
	}

	int d = n - 1;
	while (d % 2 == 0) {
		d = d >> 1;
	}

	for (int i = 0; i < k; i++) {
		if (!millerTest(d, n)) {
			return false;
		}
	}
	return true;
}

void RSA::generateRandomPrimeNumber(int& n) {
	std::mt19937 randomGen32(time(nullptr));
	int prime;
	bool isPrime = false;
	do {
		prime = randomGen32();
		if (checkPrime(prime, 12)) {
			n = prime;
			isPrime = true;
		}
	} while (isPrime != true);

}

int RSA::gcd(int a, int h)
{
	int temp;
	while (true) {
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
}

void RSA::setKeys(int P, int Q, int& n, int& publicKey, int& privateKey) {
	n = P * Q;
	int fi = (P - 1) * (Q - 1);
	int e = 2;
	while (true) {
		if (gcd(e, fi) == 1) {
			break;
		}
		e++;
	} // d = (k * fi(n) + 1) / e
	publicKey = e;

	int d = 2;
	while (true) {
		if ((d * e) % fi == 1) {
			break;
		}
		d++;
	}
	privateKey = d;
}

long RSA::encrypt(double message, const int& n, const int& publicKey) {
	int e = publicKey;
	long long int encryptedText = 1;
	while (e--) {
		encryptedText *= message;
		encryptedText %= n;
	}
	return encryptedText;
}

void RSA::encoder(std::string message, const int& n, const int& publicKey, std::vector<int>& c) {
	std::vector<int> form;
	for (auto& letter : message) {
		form.push_back(encrypt((int)letter, n, publicKey));
	}
	c = form;
}

long RSA::decrypt(int encrpyted_text, const int& n, const int& privateKey) {
	int d = privateKey;
	long long int decrypted = 1;
	while (d--) {
		decrypted *= encrpyted_text;
		decrypted %= n;
	}
	return decrypted;
}

void RSA::decoder(std::vector<int> encoded, const int& n, const int& privateKey, std::string& d) {
	std::string s;
	for (auto& num : encoded) {
		s += decrypt(num, n, privateKey);
	}
	d = s;
}
