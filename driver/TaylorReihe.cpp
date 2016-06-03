#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = 3.14159;

double tangens = 0;
double firstExp = 0, m_Value = 0;
double xDeg = 0;
double xRad = 0;


double factor = 8;

int i = 0;
int max_Value = 89*factor;
int step = 9;

ofstream TaylorFile("tanTaylor.txt");

int main(){
	
	if (TaylorFile.is_open()){
		
		TaylorFile << "Tangens: \n\n";
		for(i = 0; i< max_Value; i = i + step){
		
			xDeg = i / factor;
			xRad = xDeg /180 * PI;
	
			tangens = tan(xRad);
	
			/*zeroExp= atan(tangens);	== xRad
			firstExp = 1/(tangens*tangens + 1);
	
			m_Value = xRad - firstExp * tangens;
	
			cout << "Die Taylor-Entwicklung um " << tangens << "ist: " << m_Value << " + " << firstExp << "* X." << endl;*/
			TaylorFile << setw(12) <<(int)(tangens*1000) << ", ";
		}//for1
		
		TaylorFile << "\n\n zeroth element:\n";
		
		for(i = 0; i< max_Value; i = i + step){
		
			xDeg = i / factor;
			xRad = xDeg /180 * PI;
	
			tangens = tan(xRad);
	
			//zeroExp= atan(tangens);	== xRad
			firstExp = 1/(tangens*tangens + 1);
	
			m_Value = xRad - firstExp * tangens;
	
			//cout << "Die Taylor-Entwicklung um " << tangens << "ist: " << m_Value << " + " << firstExp << "* X." << endl;
			TaylorFile << setw(12) << m_Value << ", ";
		}//for2
		
		TaylorFile << "\n\n First Element:\n";
		
		
		for(i = 0; i< max_Value; i = i + step){
		
			xDeg = i / factor;
			xRad = xDeg /180 * PI;
	
			tangens = tan(xRad);
	
			//zeroExp= atan(tangens);	== xRad
			firstExp = 1/(tangens*tangens + 1);
	
			m_Value = xRad - firstExp * tangens;
	
			//cout << "Die Taylor-Entwicklung um " << tangens << "ist: " << m_Value << " + " << firstExp << "* X." << endl;*/
			TaylorFile << setw(12) << firstExp << ", ";
		}//for1
		TaylorFile.close();
	}//if
	
	else
		cout <<"Could not open File.";
}
