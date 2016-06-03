#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const double PI = 3.14159;
double tangens = 0, x_Rad = 0;
int offset = 2;


int main() {
	ofstream tanfile("tangens.txt");
	
	if (tanfile.is_open()) {
		for (int i = 0; i < 90; i = i + offset){
			x_Rad = ((double)i)/180*PI;
			tangens = tan(x_Rad);
	
			//cout << "Bei" << i <<" Grad" <<"(" << x_Rad << ") liegt" << tangens <<"." << endl;
			tanfile << x_Rad << " ,";
			if (i % 5 == 0)
				tanfile << "\n";
		}
	tanfile.close();
	}
	else 
		cout << "Datei konnte nicht geöffnet werden."<< endl;
}
