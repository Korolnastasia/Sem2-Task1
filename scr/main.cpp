#include "buffer.h"
#include <iostream>

int main() {
	CircularBuffer b(4, '3');
	std::cout << b.back() << "\n";
	std::cout << b.back();
}