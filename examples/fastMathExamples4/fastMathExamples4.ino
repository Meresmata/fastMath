#include <fastMath.h>


void mathBench(float(*fn_ptr)(float), float x) {
	unsigned long time = micros();
	int d = static_cast<int>(degrees((*fn_ptr)(x) * 100));
	time = micros() - time;
	char buf[59];
	snprintf(buf, sizeof(buf), "Fkt. %d.%2d degrees in %ld microseconds.", d / 100, d % 100, time);
	Serial.println(buf);
}

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Start acos math: ");
	int offset = 1;
	for(int i = 0; i <= 100; i = i + offset){
			//mathBench((acosf), (static_cast<float>(i)/100.0));
			mathBench((fmath::acos), (static_cast<float>(i)/100.0));
	}
	Serial.println("End acos math");
	Serial.println();
}

void loop() {
	// put your main code here, to run repeatedly:

}



