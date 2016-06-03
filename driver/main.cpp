#include ".\..\fastMath.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;


int i = 0;
double ii = 0.0;
double diff = 0.0;
double maxdiff = 0.0;
double sumdiff = 0.0;
double avediff = 0.0;
double maxDiffArc = 0.0;

void mathBench(double(*fn_ptr)(double, double), const double x, const double y) {
	int d = static_cast<int>(fastmath::toDeg((*fn_ptr)(x, y)) * 100);
	char buf[51];
	snprintf(buf, sizeof(buf), "Fkt. %d.%2d degrees", d / 100, d % 100);
	cout << buf <<endl;
}


int main() {



    for (i=0;i < 360; i++ ) {
		ii = i - 180;
		diff = abs(cos(fastmath::toRad(ii)) - fastmath::cos(fastmath::toRad(ii)));
		sumdiff += diff;
		if (diff > maxdiff)
			maxdiff = diff;

    }
	avediff = sumdiff / 65000;

	cout << "Cosine test" << endl;
	cout << maxdiff << avediff << endl;

	for (i = 0; i < 350; i++) {
		ii = static_cast<double>(i-175) / 10.0;
		double libArc = fastmath::toDeg(atan(ii));
		double ownArc = fastmath::toDeg(fastmath::atan(ii));
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
		ii = static_cast<double>(i - 175) / 1;
		for (int j = 0; j < 35; j++) {
			double jj = static_cast<double>(i - 175) / 1;
			mathBench((atan2), (ii), (jj));
			mathBench((fastmath::atan2), (ii), (jj));
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
