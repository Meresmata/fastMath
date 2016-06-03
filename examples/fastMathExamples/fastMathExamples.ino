#include <fastMath.h>


void mathBench(double(*fn_ptr)(double), int x) {
	unsigned long time = micros();
	int d = degrees((*fn_ptr)(x)) * 100;
	time = micros() - time;
	char buf[51];
	snprintf(buf, sizeof(buf), "Fkt. %d.%2d degrees in %ld microseconds", d / 100, d % 100, time);
	Serial.println(buf);
}

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Begin cosine math:");
	for (int i = 0; i <= 100; i++) {
		mathBench((cos), i);
		mathBench((fastmath::cos), i);
	}
	Serial.println("Ende cosine math");
	Serial.println();

}

void loop() {
	// put your main code here, to run repeatedly:

}