// declaring variables
const int sensor_pin = 0;
int pulse_signal = 0;
float BPM = 0;
int pulse_period = 0;

// declaring flags and time storing variables
bool any_peak_detected = false;
bool first_peak_detected = true;
unsigned long first_pulse_time = 0;
unsigned long second_pulse_time = 0;

// declaring upper and lower threshold
int upper_threshold = 820;
int lower_threshold = 800;

void setup() {
  // initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // collect pulse signal and print
  pulse_signal = analogRead(sensor_pin);
  //Serial.println(pulse_signal);

  // adding checkpoint
  delay(100);
  // creating upper threshold flag
  if (pulse_signal > upper_threshold && any_peak_detected == false) {
    any_peak_detected = true;
    if (first_peak_detected == true) {
      first_pulse_time = millis();
    }
    else {
      second_pulse_time = millis();
      pulse_period = second_pulse_time - first_pulse_time;
      BPM = 60000/pulse_period;
      first_peak_detected = true;
      any_peak_detected = false;
      Serial.print("BPM: ");
      Serial.println(float(BPM));
    }
  }
  
  // creating lower threshold flag
  if (pulse_signal < lower_threshold) {
    any_peak_detected = false;
    first_peak_detected = false;
  }

}
