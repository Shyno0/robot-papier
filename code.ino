//*******************************************
// Module L298N pour commander un
// Moteur 2 phases pas à pas (4 fils)
//============================================
//Câblage du steper, utilise 6 broches
int ENA = 3; // Arduino Pin 3
int IN1 = 2; // Arduino Pin 2
int IN2 = 4; // Arduino Pin 4
int ENB = 5; // Arduino Pin 5
int IN3 = 6; // Arduino Pin 6
int IN4 = 7; // Arduino Pin 7
int servoPin = 9; // déclare la broche de contrôle du servo
int temps = 1000; // valeur servo de base
#define ServoClose  1500
// Position pince fermer
#define ServoOpen   2500
// Position pince ouvert

char commande;    // Variable commande pour lire ensuite lire le Moniteur serie
char receiveData; // Variable pour comparer une information reçus

#include <Wire.h> // Librairie pour la communication I2C

#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur
Servo ServoMoteur;  // on crée l'objet monServo

void setup()
{
  Serial.begin(9600);                        // Ouvre le port série
  ServoMoteur.attach(servoPin);              // on définit le Pin utilisé par le servomoteur
  ServoMoteur.writeMicroseconds(ServoClose); // position pince fermé

  pinMode(ENA, OUTPUT); // Les 6 pins configurées en sorties
  pinMode(ENB, OUTPUT); //
  pinMode(IN1, OUTPUT); //
  pinMode(IN2, OUTPUT); //
  pinMode(IN3, OUTPUT); //
  pinMode(IN4, OUTPUT); //

  //Enable A et B, utilise les 2 ponts en H bloque les deux roues
  digitalWrite(ENA, LOW); // Activer pont A
  digitalWrite(ENB, LOW); // Activer pont B

  Wire.begin(8);                // Rejoindre l'autre carte
  Wire.onReceive(receiveEvent); // Preparer une fonction spécifique a la reception de donnee
  receiveData = 0;              // On initialise receiveData a 0
}
void loop() {

  if (receiveData != 0) // si le caractère reçus est different de zero
  {
    Serial.print(" Donnée reçue via I2C : "); 
    Serial.println(receiveData); // afficher le caractère sur l'interface serie

    if (receiveData == 'A') // si le robot reçoit "A"
    {
      Serial.print("position pince fermé  : ");  // ecrit dans le moniteur : position pince fermé  :
      Serial.println(ServoClose);
      ServoMoteur.writeMicroseconds(ServoClose); // le robot ferme la pince lorsqu'il reçoit "A"
    }

    else if (receiveData == 'B') // si le robot reçoit "B"
    {
      Serial.print("position pince ouvert : "); // ecrit dans le moniteur : position pince ouvert :
      Serial.println(ServoOpen);
      ServoMoteur.writeMicroseconds(ServoOpen); // le robot ouvre la pince lorsqu'il reçoit "B"
    }

    else if (receiveData == 'C') // si le robot reçoit "C"
    {
      avant();                           // le robot avance lorsqu'il reçoit "C"
      Serial.println("Le Robot avance"); // ecrit dans le moniteur : Le Robot avance
      delay(10);                         // ajout d'un délai
    }

    else if (receiveData == 'D') // si le robot reçoit "D"
    {
      arriere();                         // le robot recule lorsqu'il reçoit "D"
      Serial.println("Le Robot recule"); // ecrit dans le moniteur : Le Robot recule
      delay(10);                         // ajout d'un délai
    }

    else if (receiveData == 'E') // si le robot reçoit "E"
    {
      gauche();                                   // le robot tourne a gauche lorsqu'il reçoit "E"
      Serial.println("Le Robot tourne a gauche"); // ecrit dans le moniteur : Le Robot tourne a gauche
      delay(10);                                  // ajout d'un délai
    }

    else if (receiveData == 'F') // si le robot reçoit "F"
    {
      droite();                                   // le robot tourne a droite lorsqu'il reçoit "F"
      Serial.println("Le Robot tourne a droite"); // ecrit dans le moniteur : Le Robot tourne a droite
      delay(10);                                  // ajout d'un délai
    }
    else // si le robot reçoit rien ne rien faire
    {
      stop1();                                 // le robot se stop lorsqu'il reçoit autre chose
      Serial.println("Le Robot ne bouge pas"); // ecrit dans le moniteur : Le Robot ne bouge pas
      delay(10);                               // ajout d'un délai
    }
  }
}

void avant () // programme pour que le robot avance
{
  digitalWrite(IN1, HIGH); // broche IN1 alimenté 
  digitalWrite(IN2, LOW);  // broche IN2 pas alimenté
  digitalWrite(IN3, HIGH); // broche IN3 alimenté 
  digitalWrite(IN4, LOW);  // broche IN4 pas alimenté
  delay(1);
  digitalWrite(ENA, HIGH); // Activer pont A
  digitalWrite(ENB, HIGH); // Activer pont B
}

void arriere () // programme pour que le robot recule
{
  digitalWrite(IN1, LOW);  // broche IN1 pas alimenté
  digitalWrite(IN2, HIGH); // broche IN2 alimenté 
  digitalWrite(IN3, LOW);  // broche IN3 pas alimenté
  digitalWrite(IN4, HIGH); // broche IN4 alimenté 
  delay(1);
  digitalWrite(ENA, HIGH); // Activer pont A
  digitalWrite(ENB, HIGH); // Activer pont B
}

void stop1 () // programme pour que le robot se stop
{
  digitalWrite(ENA, LOW); // Désactiver pont A
  digitalWrite(ENB, LOW); // Désactiver pont B
}

void gauche () // programme pour que le robot tourne a gauche
{
  digitalWrite(IN3, HIGH); // broche IN3 alimenté
  digitalWrite(IN4, LOW);  // broche IN4 pas alimenté
  delay(1);
  digitalWrite(ENA, LOW);  // Désactiver pont A
  digitalWrite(ENB, HIGH); // Activer pont B
}

void droite () // programme pour que le robot tourne a droite
{
  digitalWrite(IN1, HIGH); // broche IN1 alimenté
  digitalWrite(IN2, LOW);  // broche IN2 pas alimenté
  delay(1);
  digitalWrite(ENA, HIGH); // Activer pont A
  digitalWrite(ENB, LOW);  // Désactiver pont B
}

// Fonction qui s execute si quelque chose est present sur l interface
void receiveEvent(int nb)
{
  //do{
    receiveData = Wire.read(); // recevoir une lettre est égale a receiveData
}

//*******************************************
// Commentaire programme
// - L'un des moteurs est moins rapide
// - I2C normalement finit
//============================================

void CommandeRobot()
{
  if (Serial.available())  // si données disponibles sur le port
  {
    commande = Serial.read(); //on lit

    if (commande == '1') // si l'on envoie un "1" dans le moniteur serie
    {
      Serial.print("position pince fermé  : ");  // ecrit dans le moniteur : position pince fermé  :
      Serial.println(ServoClose);
      ServoMoteur.writeMicroseconds(ServoClose); // La pince ce ferme
    }
    else if (commande == '2') // si l'on envoie un "2" dans le moniteur serie
    {
      Serial.print("position pince ouvert : "); // ecrit dans le moniteur : position pince ouvert  :
      Serial.println(ServoOpen);
      ServoMoteur.writeMicroseconds(ServoOpen); // La pince s'ouvre
    }
    else if (commande == '3') // si l'on envoie un "3" dans le moniteur serie
    {
      avant();                        // le robot avance lorsqu'il reçoit "3"
      Serial.println("Robot avance"); // ecrit dans le moniteur : Robot avance
      delay(10);                      // ajout d'un délai
    }
    else if (commande == '4') // si l'on envoie un "4" dans le moniteur serie
    {
      arriere();                      // le robot recule lorsqu'il reçoit "4"
      Serial.println("Robot recule"); // ecrit dans le moniteur : Robot recule 
      delay(10);                      // ajout d'un délai
    }
    else if (commande == '5') // si l'on envoie un "5" dans le moniteur serie
    {
      gauche();                                // le robot tourne a gauche lorsqu'il reçoit "5"
      Serial.println("Robot tourne a gauche"); // ecrit dans le moniteur : Robot tourne a gauche 
      delay(10);                               // ajout d'un délai
    }
    else if (commande == '6') // si l'on envoie un "6" dans le moniteur serie
    {
      droite();                                // le robot tourne a droite lorsqu'il reçoit "6"
      Serial.println("Robot tourne a droite"); // ecrit dans le moniteur : Robot tourne a droite
      delay(10);                               // ajout d'un délai
    }
    else if (commande == '7') // si l'on envoie un "7" dans le moniteur serie
    {
      stop1();                              // le robot se stop lorsqu'il reçoit "7"
      Serial.println("Robot ne bouge pas"); // ecrit dans le moniteur : Robot ne bouge pas
      delay(10);                            // ajout d'un délai
    }
  }
}
