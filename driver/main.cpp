#include ".\..\fastMath.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;


int i = 0;
float ii = 0.0;
float diff = 0.0;
float maxdiff = 0.0;
float sumdiff = 0.0;
float avediff = 0.0;
float maxDiffArc = 0.0;

/*
void mathBench(float(*fn_ptr)(float, float), const float x, const float y) {
	int d = static_cast<int>(fmath::toDeg((*fn_ptr)(x, y)) * 100);
	char buf[51];
	snprintf(buf, sizeof(buf), "Fkt. %d.%2d degrees", d / 100, d % 100);
	cout << buf <<endl;
}*/

void mathBench(float(*fn_ptr)(float), const float x) {
	int d = static_cast<int>(fmath::toDeg((*fn_ptr)(x)) * 100);
	char buf[51];
	snprintf(buf, sizeof(buf), "Fkt. %d.%2d degrees", d / 100, d % 100);
	cout << buf << endl;
}

int main() {


	//test cos
    for (i=0;i < 360; i++ ) {
		ii = static_cast<float>(i - 180);
		diff = abs(cosf(fmath::toRad(ii)) - fmath::cos(fmath::toRad(ii)));
		sumdiff += diff;
		if (diff > maxdiff)
			maxdiff = diff;

    }
	avediff = sumdiff / 65000;

	cout << "Cosine test" << endl;
	cout << maxdiff << " " << avediff << endl << endl;

	//atan test

	//setting to zero
	maxdiff = 0;
	maxDiffArc = 0;
	sumdiff = 0;
	avediff = 0;

	for (i = 0; i < 350; i++) {
		ii = static_cast<float>(i-175) / 10.0F;
		float libArc = fmath::toDeg(atanf(ii));
		float ownArc = fmath::toDeg(fmath::atan(ii));
		diff = abs(libArc - ownArc);
		sumdiff += diff;
		if (diff > maxdiff){
			maxdiff = diff;
			maxDiffArc = ii;
		}//end if
	}//end for
	avediff = sumdiff / 350;

	cout << "atan() test" << endl;
	cout << maxdiff << " " << avediff << " " << maxDiffArc << endl << endl;;

	//atan2 test

	//setting to zero
	maxdiff = 0;
	maxDiffArc = 0;
	sumdiff = 0;
	avediff = 0;

	for (i = 0; i < 35; i++) {
		ii = static_cast<float>(i - 17.5F) / 1.0F;
		for (int j = 0; j < 35; j++) {
			float jj = static_cast<float>(j - 17.5F) / 1.0F;
			//mathBench((atan2f), (ii), (jj));
			//mathBench((fmath::atan2), (ii), (jj));
			float libArc = fmath::toDeg(atan2f(ii, jj));
			float ownArc = fmath::toDeg(fmath::atan2(ii, jj));
			diff = abs(libArc - ownArc);
			sumdiff += diff;
			if (diff > maxdiff) {
				maxdiff = diff;
				maxDiffArc = ii;
			}//end if
		}//end for
	}//end for
	avediff = sumdiff / (35*35);

	cout << "atan2() test" << endl;
	cout << maxdiff << " " << avediff << " " << maxDiffArc << endl << endl;


	//test acos

	//setting to zero
	maxdiff = 0;
	maxDiffArc = 0;
	sumdiff = 0;
	avediff = 0;

	
	for (i = 0; i <= 320; i++) {
		ii = static_cast<float>(i) / 320.0F;
		float libArc = fmath::toDeg(acosf(ii));
		float ownArc = fmath::toDeg(fmath::acos(ii));
		diff = abs(libArc - ownArc);
		sumdiff += diff;
		if (diff > maxdiff) {
			maxdiff = diff;
			maxDiffArc = ii;
		}//end if
	}//end for
	avediff = sumdiff / (320 + 1);

	cout << "acos() test" << endl;
	cout << maxdiff << " " << avediff << " " << maxDiffArc << endl << endl;

	
	cout << "Test ends!" << endl;
}
