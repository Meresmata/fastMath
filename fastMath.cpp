#include "fastMath.h"


#ifndef FASTMATH_CPP
#define FASTMATH_CPP

float fmath::cos(float angle){
	signed char factor = 1;
	float result = 0.0;

	//using the integer instead of double causes
	//about 0.3% deviation, so it's acceptable
	unsigned int intAngleDeg = static_cast<unsigned>(fAbs<float>(toDeg(angle)));

	if (intAngleDeg > 360)
	{
		intAngleDeg = intAngleDeg % 360;
	}

	if (intAngleDeg > 180) {
		factor *= -1;
		intAngleDeg -= 180;
	}
	if (intAngleDeg > 90) {
		factor *= -1;
		intAngleDeg = 180 - intAngleDeg;
	}
	if (factor == 1)
		result = CosArray[intAngleDeg];

	else
		result = -CosArray[intAngleDeg];



    return result;
};

float fmath::atan(float arcAngle){
	const float maxAngle = static_cast<float>(UINT_MAX) / 1000;

	if (arcAngle >= maxAngle)
		return 1.555538F;
	else if ((-arcAngle) >= maxAngle)
		return (-1.555538F);
	else {

			unsigned int leftCompare = 0;
			unsigned int rightCompare = 0;
			signed char factor = 1;
			const int lastIndex = tanMaxIndex - 1;

			if (arcAngle < 0){
				arcAngle = -arcAngle;
				factor = -1;
			}

			unsigned int arcInt = static_cast<unsigned>(arcAngle * 1000);
			unsigned char index = 0;

			//use taylor-polynom with factors saved in the atanValues array

			//only special case inVale exceeds every limit for every Taylor-Polynome
			if (arcInt >57290)//atanLimits[(tanMaxIndex - 1)]
				return factor *1.55334F; //atanValues[0][tanMaxIndex - 1]


			//can't be smaller than zero
			else {	//find the right Taylor-Polynome (linear fit) using the value the Taylor-Polynome is expended around
				while (arcInt > atanLimits[index])
					index++;

				//chose the best fitting Taylor-Polynome
				if (arcInt != atanLimits[index]) {
					leftCompare = arcInt - atanLimits[index - 1];
					rightCompare = atanLimits[index] - arcInt;

					if (leftCompare < rightCompare)
						--index;
				}
			}

			if (factor == 1){
				//special case for expansion around zero, a bit faster:
				if (index == 0)
					return arcAngle;
				//special case case cut off
				else if (index == lastIndex)
					return 1.55334F;
				else
					return (atanValues[0][index] + atanValues[1][index] * arcAngle);
			}
			//negative arctan
			else{
				//special case for expension around zero, a bit faster:
				if (index == 0)
					return  (-arcAngle);
				//special case case cut off
				else if (index == lastIndex)
					return (-1.55334F);
				else
				return (-atanValues[0][index] - atanValues[1][index] * arcAngle);
			}
	}
}

float fmath::atan2(const float x, const float y){

	//speeding up with integer is not used, because of the creation of special cases...
	//first has to check, where integer applicable and then where it is not
	//doppels the code... and creates extra checks with doubles

		if ((y <= 0.00001) && (y >= -0.0001)) {
			if ((x >= 0.00001))
				return 1.555538F;
			else if (x <= -0.00001)
				return 1.555538F;
			else
				return 0.0F;
		
	}
	else {

		const float slope = x / y;

		if (x >= 0) {
			if (y >= 0)
				return atan(slope);
			else
				return atan(slope) + 1.5707963268F /*  PI/2  */;
		}
		else {
			if (y >= 0)
				return atan(slope) + 4.7123889804F /*3* PI /2*/;
			else
				return atan(slope) + PI;
		}
	}

}


#endif //FASTMATH_CPP
