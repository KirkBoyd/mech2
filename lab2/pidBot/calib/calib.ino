#define sharp A2 //sharp sensor

int meas;

void setup() {
    pinMode(sharp, INPUT);
    Serial.begin(115200);
}

void loop() {
    meas = analogRead(sharp);
    Serial.print(meas);
    Serial.print(' ');
    Serial.println(sharp_calib(meas));
    delay(500);
}

// Calibration function mapping the analog input to a distance in inches.
// Params:
//  raw - (int) direct reading from analogRead() of sharp sensor
// Returns:
//  dist - (double) estimated distance i
double sharp_calib(int raw) {
    // obtained these constants by collecting data and using scipy's curve_fit()
    static const double CALIB_A = 2.37092463e+03;
    static const double CALIB_B = -1.39181488e+00;

    return CALIB_A/double(raw) + CALIB_B;
}