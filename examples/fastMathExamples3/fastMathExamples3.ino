#include <fastMath.h>
#include <math.h>

void mathBench(float(*fn_ptr)(float, float),const float x, const float y) {
	unsigned long time = micros();
	int d = static_cast<int>(degrees((*fn_ptr)(x, y) * 100));
	time = micros() - time;
	char buf[59];
	snprintf(buf, sizeof(buf), "Fkt. %d.%2d degrees in %ld microseconds.", d / 100, d % 100, time);
	Serial.println(buf);
}

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Start atan2 math: ");
	int offset = 20;
	for(int i = 0; i <= 100; i = i + offset){
		for (int j = 0; j <= 100; j = j + offset) {
			//mathBench((atan2), static_cast<double>(i), static_cast<double>(j));
			mathBench((fmath::atan2), static_cast<float>(i), static_cast<float>(j));
		}
	}
	Serial.println("End atan2 math");
	Serial.println();
}

void loop() {
	// put your main code here, to run repeatedly:

}



