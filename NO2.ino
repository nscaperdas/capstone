float IotVgas;
float IotVref;
float IotVtemp;

float Vgas;
float Vref;
float Vtemp;
float VgasAVG;
float VrefAVG;

float Cx;
float M;
float T;
float Vgas0 = 0;    //We can calibrate this in a clean air environment and use it forever
int NumOfSamples = 0;

const float Sf1 = -22.07;  //Sensitivity code (nA/ppm)   LOOK AT BACK OF SENSOR  NO2 = -22.07     SO2 = 42.47     CO = 4.05
const float Gain = 499;    // TIA Gain (kV/A)            LOOK AT ULPSM           NO2 = 499        SO2 = 100       CO = 100

void setup() {
  Serial.begin(9600);
}

void loop() {
  IotVgas = 0;
  IotVref = 0;

 for(int i = 0; i <= 0; i++) {      // For loop is here so you can make each data point the average of an interval
  Vgas = analogRead(A0);            // 
  Vref = analogRead(A1);
  Vref = Vref/2;

  IotVgas += Vgas;
  IotVref += Vref;
  delay(1000);
 }

VgasAVG = IotVgas / 1;
VrefAVG = IotVref / 1;

  Serial.println("Vgas = " + String(Vgas)); // + " Average Vgas = " + String(VgasAVG));
  Serial.println("Vref = " + String(Vref)); // + " Average Vref = " + String(VrefAVG));
  

  M = (Sf1*Gain)*(10^(-6));                       // Sensor calibration factor (depends on target gas)
  Cx = ((1/M) * (VgasAVG - VrefAVG))*1000;        //*1000 for ppb
  Serial.println("Concentration = " + String(Cx));
  Serial.println(" ");
  delay(100);
}
