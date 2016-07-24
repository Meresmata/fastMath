#include "fastMath.h"


#ifndef FASTMATH_CPP
#define FASTMATH_CPP

float fmath::cos(const float inAngle){
	signed char factor = 1;
	float result = 0.0F;

	//using the integer instead of double causes
	//about 0.3% deviation, so it's acceptable
	unsigned short intAngleDeg = static_cast<unsigned short>(fmath::abs<float>(toDeg(inAngle)));

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

float fmath::acos(const float arcAngle){
	float inAngle;
	unsigned long integer;
	unsigned char significant;//7 bit of the significand + number 1, but normed to [-2,2]
	//unsigned short significant;//15 bit of the significand + number 1, but normed to [-2,2]
	unsigned char exp;
	bool isNegative = false;
	inAngle = arcAngle;
	integer = *(long*) &inAngle;//copy float bitwise in a long, to do some bitwise logic

	//calc the abs of the float
	long positiveInteger = (integer & 0x7FFFFFFF);
	inAngle = *(float*) &positiveInteger;
	
	//the arcAngle negative?
	if(integer & 0x80000000)
		isNegative = true;
	
	//extract significand and normalise
	exp = static_cast<unsigned char>((integer & 0x7F800000)>>23);//now shift right to fit into an short
	if (exp < 111)
		significant = 0;
	else {
		//significant = (static_cast<unsigned short>((integer & 0x007FFFFF) >> 8) | 0x8000);
		significant = (static_cast<unsigned char>((integer & 0x007FFFFF) >> 16) | 0x80);
		
		if(exp < 119/*for siginifant uint16_t 111*/)
			significant = 0;
		//we only need to values in the interval [-1,1]
		else if (exp < 127)
			significant = significant  >> (127 - exp);
		else if (exp > 127)
			return matherr;
		if (significant > 0x80/*0x8000 for uint16_t*/)
			return matherr;
	}	

	//now lets start the calculation
	
	
	//2. using point symmetrie to further limit the interval
	//hence lowest value HalfPI
	//highest value PI
	//get normal erg
	
	//use the balanced binary sorted tree (array) to find the result quickly
	//unsigned short interval = 0x0400;//equals +/- 1/32 als intervall around each number
	unsigned char interval = 0x04;//equals +/- 1/32 als intervall around each number
	float result = 0;

	//special chases zero
	if (significant < interval) {
		result = 1.57080F - 1.00012F * inAngle;
		//result = 1.5708F - inAngle;
	}
	//special chase nearly exact zero
	else if (significant > 0x7f/*0x7ff0 for uint16_t*/) {
		result = 0.0F;
	}
	//special case quite nearly one
	else if ((significant >= 0x7e/*0x7e00 for uint16_t*/)) {
		//result = 8.0782F - 8.0157F * inAngle;
		result = 6.62766F - 6.55119F * inAngle;
		//result = 5.76734F - 5.67908F * inAngle;
	}
	//general case
	else {
		bool isFound = false;
		unsigned char index = 0;
		unsigned char childIndex = 0;
		//unsigned short parentCompare = 0;
		unsigned char parentCompare = 0;

		//start searching the binary tree
		while (!isFound) {
			childIndex = (index + 1) * 2;
			parentCompare = acosLimits[index];

			//if last leave of that path or signicant found
			if (((significant >= parentCompare - interval) && (significant <= parentCompare + interval)) || (childIndex >= acosMaxIndex)) {
				isFound = true;
			}
			//try left child
			else if (significant < parentCompare) {
				childIndex -= 1;
				//go further
				index = childIndex;
			}//else if --end left child

			//try right child
			else {
				//go further
				index = childIndex;
			}//else  -- end right child
		}//end binary tree search

		result = acosValues[0][index] - acosValues[1][index] * inAngle;
	}//end general case
	
	
	if(isNegative){
		result = PI - result;
	}
	return result;
}


float fmath::atan(float arcAngle){
	const float maxAngle = static_cast<float>(UINT_MAX) / 1000;

	if (arcAngle >= maxAngle)
		return 1.555538F;
	else if ((-arcAngle) >= maxAngle)
		return (-1.555538F);
	else {

			unsigned short leftCompare = 0;
			unsigned short rightCompare = 0;
			signed char factor = 1;
			const short lastIndex = tanMaxIndex - 1;

			if (arcAngle < 0){
				arcAngle = -arcAngle;
				factor = -1;
			}

			unsigned short arcInt = static_cast<unsigned>(arcAngle * 1000);
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

float fmath::atan2(const float y, const float x){

	//speeding up with integer is not used, because of the creation of special cases...
	//first has to check, where integer applicable and then where it is not
	//doppels the code... and creates extra checks with doubles

		if ((x >= -0.000001F) && (x <= 0.000001F)) {
			if ((y >= 0.00001))
				return HALFPI;
			else if (x <= -0.00001)
				return -HALFPI;
			else
				return 0.0F;
	}
	else {

		const float slope = y / x;

		if (x >= 0.0F) {
				return atan(slope);
		}
		else {
			if (y >= 0)
				return atan(slope) + PI;
			else
				return atan(slope) - PI;
		}
	}

}//atan2


#endif //FASTMATH_CPP
