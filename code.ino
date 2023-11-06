// Pont en H L298N

//Ports de commande du moteur B
#define borneIN3  7  // On associe la borne "IN3" du L298N à la pin D7 de l'Arduino
#define borneIN4  6  // On associe la borne "IN4" du L298N à la pin D6 de l'Arduino
#define borneENB  5  // On associe la borne "ENB" du L298N à la pin D5 de l'Arduino (PWM possible sur cette broche)

// Ports de commande moteur A
#define borneENA  10 // On associe la borne "ENA" du L298N à la pin D10 de l'Arduino (PWM possible sur cette broche)
#define borneIN1  9  // On associe la borne "IN1" du L298N à la pin D9 de l'Arduino
#define borneIN2  8  // On associe la borne "IN2" du L298N à la pin D8 de l'Arduino

// Vitesse du moteur
int state = 0;
void setup() {
  // Configuration de toutes les pins de l'Arduino en "sortie" (car elles attaquent les entrées du module L298N)
  pinMode(borneENA, OUTPUT);
  pinMode(borneIN1, OUTPUT);
  pinMode(borneIN2, OUTPUT);
  pinMode(borneIN3, OUTPUT);
  pinMode(borneIN4, OUTPUT);
  pinMode(borneENB, OUTPUT);

    // Initialisation du port série
    Serial.begin(9600);
}
 
void loop() {
    if (Serial.available() &gt; 0)
    {
      // Lecture de l'entier passé au port série
      state = Serial.parseInt();
      //
      // Sens du mouvement
      //
      if (state &gt; 0) // avant
      {
        digitalWrite(motorPin1B, HIGH); 
        digitalWrite(motorPin2B, LOW);
        Serial.print("Avant ");
        Serial.println(state);
      }
      else if (state &lt; 0) // arrière
      {
        digitalWrite(motorPin1B, LOW); 
        digitalWrite(motorPin2B, HIGH);
        Serial.print("Arriere ");
        Serial.println(state);
      }
      else // Stop (freinage)
      {
        digitalWrite(motorPin1B, HIGH); 
        digitalWrite(motorPin2B, HIGH);
        Serial.println("Stop");
      }
      //
      // Vitesse du mouvement
      //
      analogWrite(enablePinB, abs(state));
    }
    delay(100);
}
