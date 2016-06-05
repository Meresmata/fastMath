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

void mathBench(float(*fn_ptr)(float, float), const float x, const float y) {
	int d = static_cast<int>(fmath::toDeg((*fn_ptr)(x, y)) * 100);
	char buf[51];
	snprintf(buf, sizeof(buf), "Fkt. %d.%2d degrees", d / 100, d % 100);
	cout << buf <<endl;
}


int main() {



    for (i=0;i < 360; i++ ) {
		ii = static_cast<float>(i - 180);
		diff = abs(cosf(fmath::toRad(ii)) - fmath::cos(fmath::toRad(ii)));
		sumdiff += diff;
		if (diff > maxdiff)
			maxdiff = diff;

    }
	avediff = sumdiff / 65000;

	cout << "Cosine test" << endl;
	cout << maxdiff << avediff << endl;

	for (i = 0; i < 350; i++) {
		ii = static_cast<float>(i-175) / 10.0F;
		float libArc = fmath::toDeg(atanf(ii));
		float ownArc = fmath::toDeg(fmath::atan(ii));
		diff = abs(libArc - ownArc);
		sumdiff += diff;
		if (diff > maxdiff){
			maxdiff = diff;
			maxDiffArc = ii;
		}
	}
	avediff = sumdiff / 350;

	cout << "atan() test" << endl;
	cout << maxdiff << avediff << maxDiffArc << endl;


	for (i = 0; i < 350; i++) {
		ii = static_cast<float>(i - 175) / 1;
		for (int j = 0; j < 35; j++) {
			float jj = static_cast<float>(i - 175) / 1;
			mathBench((atan2f), (ii), (jj));
			mathBench((fmath::atan2), (ii), (jj));
			/*double libArc = fastToDeg(atan2(ii, jj));
			double ownArc = fastToDeg(fastAtan2(ii, jj));
			diff = abs(libArc - ownArc);
			sumdiff += diff;

			if (diff > maxdiff) {
				maxdiff = diff;
				maxDiffArc = ii;
			}*/
		}
	}
	avediff = sumdiff / (350*350);

	cout << "atan2() test" << endl;
	cout << maxdiff << avediff << maxDiffArc << endl;



}
