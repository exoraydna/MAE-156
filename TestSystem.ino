#define TC_PIN A0 // set to ADC pin used
#define AREF 5.0 // set to AREF, typically board voltage like 3.3 or 5.0
#define ADC_RESOLUTION 10 // set to ADC bit resolution, 10 is default
#define HC_PIN 3 // set heating catridge pin used
#define TD_PIN A1 // set inlet transducer pin used
#define PSU_GND A5// set PSU ground voltage pin used

float readingTC, readingTD, voltageTC, voltageTD, temperature, pressureTD;
int percent = 0; // set default PWM percentage
int dutycycle;
float step = 0.005; // Set transducer step size in V/psi

float get_voltage(int raw_adc) {
return raw_adc * (AREF / (pow(2, ADC_RESOLUTION)-1));
}

float get_temperature(float voltage) {
return (voltage-1.25) / 0.005;
}

void setup() {
Serial.begin(9600);
pinMode(3, OUTPUT);
}

void loop() {
// Read and output analog temperature
readingTC = analogRead(TC_PIN);
voltageTC = get_voltage(readingTC);
temperature = (readingTC-255)*0.976;
//temperature = get_temperature(voltageTC);
Serial.print("Temperature = ");
Serial.print(temperature);
Serial.println(" C");
Serial.println(voltageTC);

readingTD = analogRead(TD_PIN);
voltageTD = get_voltage(readingTD);
pressureTD = (readingTD-511)*(AREF / (pow(2, ADC_RESOLUTION)-1));
Serial.print("Head Loss = ");
Serial.print(pressureTD);
Serial.println(" Pa");

delay(500);
}
