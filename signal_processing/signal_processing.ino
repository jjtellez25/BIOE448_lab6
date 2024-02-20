// declaring variables
const int sensor_pin = 0;
int pulse_signal = 0;
float BPM = 0;
int pulse_period = 0;

// declaring flags and time storing variables (true = placing flag, false = picking up flag)
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
  Serial.println(pulse_signal);

  // adding checkpoint
  delay(100);
  // creating upper threshold flag
  if (pulse_signal > upper_threshold && any_peak_detected == false) {
    // placing any peak flag
    any_peak_detected = true;
    if (first_peak_detected == true) {
      // recording first checkpoint
      first_pulse_time = millis();
    }
    else {
      // recording second checkpoint
      second_pulse_time = millis();
      // calculating pulse period
      pulse_period = second_pulse_time - first_pulse_time;
      // calculating BPM from pulse period
      BPM = 60000/pulse_period;
      // placing first peak flag
      first_peak_detected = true;
      //picking up any peak flag
      any_peak_detected = false;
      // printing BPM values
      Serial.print("BPM: ");
      Serial.println(float(BPM));
    }
  }
  
  // creating lower threshold flag
  if (pulse_signal < lower_threshold) {
    // picking up any peak flag
    any_peak_detected = false;
    // picking up first peak flag
    first_peak_detected = false;
  }

}
