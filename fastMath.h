#ifndef FASTMATH_H
#define FASTMATH_H


#define tanMaxIndex  17
//#define acosMaxIndex 31
#define acosMaxIndex 15
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>


#define matherr 0.0F


namespace fmath {

#ifdef Arduino_h

#include <avr/pgmspace.h>

	//results of cos_fn 
	const float CosArray[] PROGMEM = { 1.0, 0.999848, 0.999391, 0.998630, 0.997564,
		0.996195, 0.994522, 0.992546, 0.990268, 0.987688,
		0.984808, 0.981627, 0.978148, 0.974370, 0.970297,
		0.965926, 0.961262, 0.956305, 0.951057, 0.945519,
		0.939693, 0.933580, 0.927184, 0.920505, 0.913545,
		0.906308, 0.898794, 0.891007, 0.882948, 0.874620,
		0.866025, 0.857167, 0.848048, 0.838671, 0.829038,
		0.819152, 0.809017, 0.798636, 0.788011, 0.777146,
		0.766044, 0.754710, 0.743145, 0.731354, 0.719340,
		0.707107, 0.694658, 0.681998, 0.669131, 0.656059,
		0.642788, 0.629320, 0.615661, 0.601815, 0.587785,
		0.573576, 0.559193, 0.544639, 0.529919, 0.515038,
		0.500000, 0.484810, 0.469472, 0.453990, 0.438371,
		0.422618, 0.406737, 0.390731, 0.374607, 0.358368,
		0.342020, 0.325568, 0.309017, 0.292372, 0.275637,
		0.258819, 0.241922, 0.224951, 0.207912, 0.190809,
		0.173648, 0.156434, 0.139173, 0.121869, 0.104528,
		0.087156, 0.069756, 0.052336, 0.034899, 0.017452,
		0.000000 };

	//array to select right element of atanValues
	const unsigned short atanLimits[tanMaxIndex] PROGMEM = { 0, 324,       726,      1000,     1376,      1962,     2414,     3077,      4165,      6313,      8448,       12705,      16956,      25450,      28635,      38186,       57290 };

	/*atan = m x +n,
	m - second row
	n - first row*/
	const float atanValues[2][tanMaxIndex] PROGMEM = { { 0, 0.0202666, 0.15279,  0.285398, 0.466948,  0.695047, 0.824542, 0.962743,  1.10818,   1.25921,   1.33626,    1.41404,    1.45312,    1.49229,    1.50101,    1.51845,     1.55334 },
											 { 1, 0.904509,  0.654509, 0.50000,  0.345492,  0.206108, 0.146447, 0.0954921, 0.0544972, 0.0244721, 0.0138153,  0.00615603, 0.00346592, 0.00154143, 0.00121807, 0.000685301, 0 } };


	//array to select right element of acosValues
	/*const unsigned short acosLimits[acosMaxIndex] PROGMEM = { 0x4000, 0x2000, 0x6000, 0x1000, 0x3000, 0x5000, 0x7000, 0x0800, 0x1800, 0x2800, 0x3800, 0x4800, 0x5800, 0x6800, 0x7800,
															0x0400, 0x0c00, 0x1400, 0x1c00, 0x2400, 0x2c00, 0x3400, 0x3c00, 0x4400, 0x4c00, 0x5400, 0x5c00, 0x6400, 0x6c00, 0x7400, 0x7c00 };*/

	const unsigned char acosLimits[acosMaxIndex] = { 0x40, 0x20, 0x60, 0x10, 0x30, 0x50, 0x70, 0x08, 0x18, 0x28, 0x38, 0x48, 0x58, 0x68, 0x78/*,
													 0x04, 0x0c, 0x14, 0x1c, 0x24, 0x2c, 0x34, 0x3c, 0x44, 0x4c, 0x54, 0x5c, 0x64, 0x6c, 0x74, 0x7c*/ };

	/*acos = m x +n,
	m - second row
	n - first row*/
	const float acosValues[2][acosMaxIndex] PROGMEM = { { 1.624, 1.576, 1.875, 1.571, 1.636, 1.557, 2.313, 1.571, 1.573, 1.582, 1.605, 1.653, 1.760, 2.015, 3.0490/*,
														 1.5708, 1.5745, 1.5721, 1.574, 1.5729, 1.5860, 1.597, 1.6138, 1.6377, 1.6729, 1.7247, 1.8026, 1.9257, 2.1386, 2.5802, 4.1563*/ },
														 { 1.158, 1.033, 1.512, 1.008, 1.057, 1.058, 2.066, 1.002, 1.018, 1.053, 1.112, 1.209, 1.377, 1.715, 2.874/*,
														 1.000, 1.0044, 1.0124, 1.0248, 1.0421, 1.0649, 1.0944, 1.1321, 1.1803, 1.2428, 1.3253, 1.4383, 1.6020, 1.8631, 2.3655, 4.0316*/ } };

#else

	const float PI = 3.1415926535897932384626433832795F;

	//results of cos_fn 
	const float CosArray[] = { 1.0F, 0.999848F, 0.999391F, 0.998630F, 0.997564F,
	0.996195F, 0.994522F, 0.992546F, 0.990268F, 0.987688F,
	0.984808F, 0.981627F, 0.978148F, 0.974370F, 0.970297F,
	0.965926F, 0.961262F, 0.956305F, 0.951057F, 0.945519F,
	0.939693F, 0.933580F, 0.927184F, 0.920505F, 0.913545F,
	0.906308F, 0.898794F, 0.891007F, 0.882948F, 0.874620F,
	0.866025F, 0.857167F, 0.848048F, 0.838671F, 0.829038F,
	0.819152F, 0.809017F, 0.798636F, 0.788011F, 0.777146F,
	0.766044F, 0.754710F, 0.743145F, 0.731354F, 0.719340F,
	0.707107F, 0.694658F, 0.681998F, 0.669131F, 0.656059F,
	0.642788F, 0.629320F, 0.615661F, 0.601815F, 0.587785F,
	0.573576F, 0.559193F, 0.544639F, 0.529919F, 0.515038F,
	0.500000F, 0.484810F, 0.469472F, 0.453990F, 0.438371F,
	0.422618F, 0.406737F, 0.390731F, 0.374607F, 0.358368F,
	0.342020F, 0.325568F, 0.309017F, 0.292372F, 0.275637F,
	0.258819F, 0.241922F, 0.224951F, 0.207912F, 0.190809F,
	0.173648F, 0.156434F, 0.139173F, 0.121869F, 0.104528F,
	0.087156F, 0.069756F, 0.052336F, 0.034899F, 0.017452F,
	0.000000F };

	//array to select right element of atanValues
	const unsigned short atanLimits[tanMaxIndex] = { 0, 324,       726,      1000,     1376,     1962,     2414,     3077,      4165,      6313,      8448,      12705,      16956,      25450,      28635,      38186,       57290 };

	/*atan = m x +n,
	m - second row
	n - first row*/
	const float atanValues[2][tanMaxIndex] = { { 0.0F, 0.0202666F, 0.15279F,  0.285398F, 0.466948F, 0.695047F, 0.824542F, 0.962743F,  1.10818F,   1.25921F,   1.33626F,   1.41404F,    1.45312F,    1.49229F,    1.50101F,    1.51845F,     1.55334F },
											 { 1.0F, 0.904509F,  0.654509F, 0.50000F,  0.345492F, 0.206108F, 0.146447F, 0.0954921F, 0.0544972F, 0.0244721F, 0.0138153F, 0.00615603F, 0.00346592F, 0.00154143F, 0.00121807F, 0.000685301F, 0.0F } };

	//array to select right element of acosValues
	/*const unsigned short acosLimits[acosMaxIndex] = { 0x4000, 0x2000, 0x6000, 0x1000, 0x3000, 0x5000, 0x7000, 0x0800, 0x1800, 0x2800, 0x3800, 0x4800, 0x5800, 0x6800, 0x7800,
													0x0400, 0x0c00, 0x1400, 0x1c00, 0x2400, 0x2c00, 0x3400, 0x3c00, 0x4400, 0x4c00, 0x5400, 0x5c00, 0x6400, 0x6c00, 0x7400, 0x7c00};*/

	const unsigned char acosLimits[acosMaxIndex] = { 0x40, 0x20, 0x60, 0x10, 0x30, 0x50, 0x70, 0x08, 0x18, 0x28, 0x38, 0x48, 0x58, 0x68, 0x78/*,
													0x04, 0x0c, 0x14, 0x1c, 0x24, 0x2c, 0x34, 0x3c, 0x44, 0x4c, 0x54, 0x5c, 0x64, 0x6c, 0x74, 0x7c*/ };


	/*acos = m x +n,
	m - second row
	n - first row*/
	const float acosValues[2][acosMaxIndex] = { {1.624F, 1.576F, 1.875F, 1.571F, 1.636F, 1.557F, 2.313F, 1.571F, 1.573F, 1.582F, 1.605F, 1.653F, 1.760F, 2.015F, 3.0490F/*,
												1.5708F, 1.5745F, 1.5721F, 1.574F, 1.5729F, 1.5860F, 1.597F, 1.6138F, 1.6377F, 1.6729F, 1.7247F, 1.8026F, 1.9257F, 2.1386F, 2.5802F, 4.1563F*/},
											 {  1.158F, 1.033F, 1.512F, 1.008F, 1.057F, 1.058F, 2.066F, 1.002F, 1.018F, 1.053F, 1.112F, 1.209F, 1.377F, 1.715F, 2.874F/*,
												1.000F, 1.0044F, 1.0124F, 1.0248F, 1.0421F, 1.0649F, 1.0944F, 1.1321F, 1.1803F, 1.2428F, 1.3253F, 1.4383F, 1.6020F, 1.8631F, 2.3655F, 4.0316F*/} };

#endif
	const float HALFPI = PI / 2;

	//faster but less precise calculation of cosine
	//max error of 0.5° 
	float cos(const float inAngle);

	//faster but less precise calculation of sin
	float inline sin(float angle) { return fmath::cos((angle - HALFPI)); };


	float acos(const float arcAngle);
	
	float inline asin(float arcAngle){ return (HALFPI - fmath::acos(arcAngle));}
	
	//faster but less precise calculation of tangens
	//average error: 0.08°
	//max. error: 0.6°
	float atan(float arcAngle);

	//faster but less precise calculation of tan2
	//average error: 0.2%°
	//max. error: 0.6°
	//if x and y nearly zero returns zero
	// if ownly y nearly zero returns +/- PI/2
	float atan2(const float x, const float y);

#ifndef abs
	//computes the absolute of any value, using templates
	template<typename inType = short>
	inType abs(inType x){
		if (x >= 0)
			return x;
		else
			return (-x);
	};
#endif

	//computes degrees in RAD from DEG
	float inline toRad(const float deg) { return (1.7453292519943295769e-2F/*  PI/180  */)*deg; };

	//computes degrees in DEG from RAD
	float inline toDeg(const float rad) { return  57.2957795130823208767F /*  180/PI   */ *rad; };
	
	float inline sqr(const float inNumber) { return inNumber * inNumber; }
}//namespace fastmath
#endif // FASTMATH_H






