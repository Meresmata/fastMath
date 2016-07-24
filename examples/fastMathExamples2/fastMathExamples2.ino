#include <fastMath.h>

void mathBench(float(*fn_ptr)(float), int x) {
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
  for(int i = 0; i <= 100; i++){
    //mathBench((atanf),i);
    mathBench((fmath::atan), i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

