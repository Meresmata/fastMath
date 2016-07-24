#include <iostream>

//calculate significant
int main(){
float inNumber = (9/32.0);
	unsigned short erg = 0;
	float remainder = 0;

	for (int i = 0; i < 16; ++i) {
		remainder = (static_cast<float>(1) / static_cast<float>(1<<(i)));
		erg = erg << 1;
		if (inNumber >= remainder) {
			inNumber = inNumber  - remainder;
			erg += 1;
		}//if
	}//for
	std::cout << std::hex << erg << std::endl;
return 0;
}//main
