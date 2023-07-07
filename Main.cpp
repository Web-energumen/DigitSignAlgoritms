#include <iostream>
#include "RSA.h"

int main() {
	int n, e, d;
	int p, q;
	int publicKey, privateKey;

	RSA rsa;
	rsa.generateRandomPrimeNumber(p);
	rsa.generateRandomPrimeNumber(q);
	printf("P = %u\n", p);
	printf("Q = %u\n", q);

	std::string text;
	rsa.readTxtFile("Document.txt", text);

	rsa.setKeys(p, q, n, publicKey, privateKey);

	std::vector<int> c;
	rsa.encoder(text, n, publicKey, c);
	printf("Encrypted text\n");
	for (auto& i : c) {
		printf("%u", i);
	}

	std::string decrypM;
	rsa.decoder(c, n, privateKey, decrypM);
	printf("\nDecrypted text:\n");
	std::cout << decrypM << "\n";

	return 0;
}