#include <IRremote.h>
#include <Servo.h>

#define plus 0xFF18E7 // tlačidlo hore
#define minus 0xFF4AB5  // tlačidlo dole


Servo servo;

//int RECV_PIN = 2; // snímač ovládača
IRrecv irrecv(2); // ovládač na pine 2
decode_results results; // signál z ovládača

int svetelnySenzor; // hodnota svetelného senzoru

int uhol = 90; // hodnota uhla, o ktorý sa má otočiť servo
bool rotaciaplus; // ???
bool rotaciaminus;

void setup() {
  Serial.begin(9600); // zapnutie sériového portu
  irrecv.enableIRIn(); // zapnutie senzoru na ovládač

  pinMode(zltaLed, OUTPUT);
  pinMode(modraLed, OUTPUT);
  pinMode(cervenaLed, OUTPUT);
  
  servo.attach(9);  // zapnutie serva na 9. pine
}

// funkcia na nastavenie uhlu podľa ovládača
void ir(){
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // ďalšie info prijme

    if (results.value == plus)
    {
      rotaciaplus = !rotaciaplus;      //pohyb do rotacie
      rotaciaminus = false;         //zakaže pohyb
    }

    if (results.value == minus)
    {
      rotaciaminus = !rotaciaminus;   //prepina hodnotu
      rotaciaplus = false;            //zakaže pohyb
    }
  }
  if (rotaciaplus && (uhol != 180))  {
    uhol++;                         //do rotacie
  }
  if (rotaciaminus && (uhol != 0))  {
    uhol--;                         //proti rotacii
  }
}

// funkcia na nastavenie uhlu podľa svetelného senzoru
void ls(){
  svetelnySenzor = analogRead(A0);
  if(svetelnySenzor > 0)
  {
    if(svetelnySenzor < 50)
    {
      //digitalWrite(zltaLed, HIGH);
      if(uhol < 180)
      { uhol++; }
    }  
    else if(svetelnySenzor > 100)
    {
      if(uhol > 0)
      { uhol--; }
    }
  }
}

void loop() {
  ir();
  ls();
  servo.write(uhol);    
  delay(20);
}
