#include <HX711.h>
#include <ESP32Servo.h>
Servo myservo;

int pos=0;
float aa=0.0;
float rho=1.189;
float v=6.3;
float l=0.55;
float c=0.15;


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN_1 = 27;
const int LOADCELL_SCK_PIN_1 = 14;

const int LOADCELL_DOUT_PIN_4 = 18;
const int LOADCELL_SCK_PIN_4 = 19;

const int LOADCELL_DOUT_PIN_3 = 25;
const int LOADCELL_SCK_PIN_3 = 26;

const int LOADCELL_DOUT_PIN_2 = 22;
const int LOADCELL_SCK_PIN_2 = 23;

const int LOADCELL_DOUT_PIN_5 = 32;
const int LOADCELL_SCK_PIN_5 = 33;



int flag1; //Zero load calibration indicator
int flag2; //Zero load calibration indicator
int flag3;
int flag4;
int flag5;
float L;
float D;
float M;
float CL;
float CD;
float CM;
float celulasL;
float celulasD;
float celulaM;


float zero_load1;
float zero_load2;
float zero_load3;
float zero_load4;
float zero_load5;

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;
HX711 scale5;


void setup() {
  Serial.begin(115200);
  myservo.attach(4);
  myservo.write(0);              
  delay(50);
  myservo.write(aa); 
  
  Serial.println("CL CD CM");
    flag1=0;
    flag2=0;
    flag3=0;
    flag4=0;
    flag5=0;
  scale1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN_1);
  scale2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN_2);
  scale3.begin(LOADCELL_DOUT_PIN_3, LOADCELL_SCK_PIN_3);
  scale4.begin(LOADCELL_DOUT_PIN_4, LOADCELL_SCK_PIN_4);
  scale5.begin(LOADCELL_DOUT_PIN_5, LOADCELL_SCK_PIN_5);

}

void loop() {

celulasL=(GetScale1(scale1)-GetScale2(scale2));
celulasD=(GetScale3(scale3)-GetScale4(scale4));
celulaM=GetScale5(scale5);

 L=((-0.00125006706802622)*celulasL+(-3.05184585681753e-05)*celulasD+(1.97794018692644e-11)*celulasL*celulasD)*0.001*9.81;//a0=1.35302050820960
 //Serial.print("AOA: ");
 //Serial.print(aa,2);
 CL=L/(rho*(v*v)*l*c*0.5);
 //Serial.print("° ; ");
 //Serial.print("SUSTENTAÇÃO: ");
 Serial.print(CL,5);
 Serial.print(" ");
 D=((-1.96346319551432e-05)*celulasL+(0.00111725111792471)*celulasD+(-3.50640462506972e-11)*celulasL*celulasD)*0.001*9.81;//a0=-1.14463914988820
 CD=D/(rho*(v*v)*l*c*0.5);
 //Serial.print("ARRASTO: ");
 Serial.print(CD,5);
 Serial.print(" ");
 M=((celulaM*(0.00000228075))-0.00143191);//calibração g/m
 CM=M/(rho*(v*v)*l*c*c*0.5);
 //Serial.print("MOMENTO: ");
 Serial.print(CM,5);
 //Serial.print("N*m");
 Serial.println("");
  delay(100);
 //incertezas L=0.140703414 D=0.143606279 M=0.007750947
}

float GetScale1(HX711 scale) {
  if (scale.is_ready()) {
    if (flag1 == 0) {
      zero_load1 = (scale.read());
      flag1 = 1;
    }
    
    float reading1 = (scale.read());
    reading1 = reading1 - zero_load1;

    return reading1;
  } else {

  }
}

float GetScale2(HX711 scale) {
  if (scale.is_ready()) {
    if (flag2 == 0) {
      zero_load2 = (scale.read());
      flag2 = 1;
    }
    
    float reading2 = (scale.read());
    reading2 = reading2 - zero_load2;

    return reading2;
  } else {

  }
}

float GetScale3(HX711 scale) {
  if (scale.is_ready()) {
    if (flag3 == 0) {
      zero_load3 = (scale.read());
      flag3 = 1;
    }
    
    float reading3 = (scale.read());
    reading3 = reading3 - zero_load3;

    return reading3;
  } else {

  }
}

float GetScale4(HX711 scale) {
  if (scale.is_ready()) {
    if (flag4 == 0) {
      zero_load4 = (scale.read());
      flag4 = 1;
    }
    
    float reading4 = (scale.read());
    reading4 = reading4 - zero_load4;

    return reading4;
  } else {

  }
}

float GetScale5(HX711 scale) {
  if (scale.is_ready()) {
    if (flag5 == 0) {
      zero_load5 = (scale.read());
      flag5 = 1;
    }
    
    float reading5 = (scale.read());
    reading5 = reading5 - zero_load5;

    return reading5;
  } else {

  }
}
