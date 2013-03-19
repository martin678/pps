#include <cstdlib>
#include <iostream>
#include <fileUtils.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	// Présentations d'usage...
	writeFile("/dev/serusb1", " ");
	std::cout << readLine("/dev/serusb1") << std::endl;

	writeFile("/dev/serusb1", "f");
	std::cout << readLine("/dev/serusb1") << std::endl;

	// Lecture de la température
	writeFile("/dev/serusb1", "b5528FF11C80300003844\r"); // ou \n?
	std::cout << readLine("/dev/serusb1") << std::endl; // consomme le output
	sleep(1);

	writeFile("/dev/serusb1", "r");
	std::cout << readLine("/dev/serusb1") << std::endl; // consomme le output

	writeFile("/dev/serusb1", "b5528FF11C803000038BE");
	// ici, ça bloque... PK?
	std::cout << readLine("/dev/serusb1") << std::endl; // consomme le output

	writeFile("/dev/serusb1", "FF");
	string result1 = readLine("/dev/serusb1");
	writeFile("/dev/serusb1", "FF");
	string result2 = readLine("/dev/serusb1");

	std::cout << "0x" << result2 << result1 << std::endl;

	return EXIT_SUCCESS;
}
