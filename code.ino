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

char commande; // Variable commande pour lire ensuite lire le Moniteur serie

#include <Wire.h> // Librairie pour la communication I2C

#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur
Servo ServoMoteur;  // on crée l'objet monServo

void setup() {
  Serial.begin(9600);
  ServoMoteur.attach(servoPin); // on définit le Pin utilisé par le servomoteur
  ServoMoteur.writeMicroseconds(ServoClose); // position pince fermé

  pinMode(ENA, OUTPUT); // Les 6 pins configurées en sorties
  pinMode(ENB, OUTPUT); //
  pinMode(IN1, OUTPUT); //
  pinMode(IN2, OUTPUT); //
  pinMode(IN3, OUTPUT); //
  pinMode(IN4, OUTPUT); //
  //Enable A et B, utilise les 2 ponts en H bloque les deux roues
  digitalWrite(ENA, HIGH); // Activer pont A
  digitalWrite(ENB, HIGH); // Activer pont B
}
void loop() {
  //des données sur la liaison série (lorsque l'on appuie sur '1' ou '2')
  if (Serial.available())
  {
    commande = Serial.read(); //on lit
    
    if (commande == '1') // le robot ferme la pince lorsqu'il recoit 1
    {
      Serial.print("position pince fermé  : "); // écrit le texte " "
      Serial.println(ServoClose); // écrit " la valeur de ServoClose "
      ServoMoteur.writeMicroseconds(ServoClose); // la pince se ferme
    }
    else if (commande == '2') // le robot ouvre la pince lorsqu'il reçoit 2
    {
      Serial.print("position pince ouvert : "); // écrit le texte " "
      Serial.println(ServoOpen); // écrit " La valeur de ServoOpen "
      ServoMoteur.writeMicroseconds(ServoOpen); // la pince s'ouvre
    }
    else if (commande == '3') // le robot avance lorsqu'il reçoit "3"
    {
      avant();   // le robot avance
      Serial.println("Robot avance"); // écrit le texte " "
      delay(10); // délai de 10 microseconde
    }
    else if (commande == '4') // le robot recule lorsqu'il reçoit "4"
    {
      arriere(); // le robot recule
      Serial.println("Robot recule"); // écrit le texte " "
      delay(10); // délai de 10 microseconde
    }
    else if (commande == '5') // le robot tourne a gauche lorsqu'il reçoit "5"
    {
      gauche();  // le robot tourne a gauche 
      Serial.println("Robot tourne a gauche"); // écrit le texte " "
      delay(10); // délai de 10 microseconde
    }
    else if (commande == '6') // le robot tourne a droite lorsqu'il reçoit "6"
    {
      droite();  // le robot tourne a droite
      Serial.println("Robot tourne a droite"); // écrit le texte " "
      delay(10); // délai de 10 microseconde
    }
    else if (commande == '7') // le robot se stop lorsqu'il ne reçoit rien ( 7 pour les test)
    {
      stop1();  // le robot se stop
      Serial.println("Robot ne bouge pas");
      delay(10); // délai de 10 microseconde
    }
  }
}

void avant () // programme pour que le robot avance
{
  digitalWrite(IN1, HIGH); //broche IN1 alimenté
  digitalWrite(IN2, LOW);  //broche IN2 pas alimenté
  digitalWrite(IN3, HIGH); //broche IN3 alimenté
  digitalWrite(IN4, LOW);  //broche IN4 pas alimenté
}

void arriere () // programme pour que le robot recule
{
  digitalWrite(IN1, LOW);  //broche IN1 pas alimenté
  digitalWrite(IN2, HIGH); //broche IN2 alimenté
  digitalWrite(IN3, LOW);  //broche IN3 pas alimenté
  digitalWrite(IN4, HIGH); //broche IN4 alimenté
}

void stop1 () // programme pour que le robot se stop
{
  digitalWrite(IN1, HIGH); //broche IN1 alimenté
  digitalWrite(IN2, HIGH); //broche IN2 alimenté
  digitalWrite(IN3, HIGH); //broche IN3 alimenté
  digitalWrite(IN4, HIGH); //broche IN4 alimenté
}

void gauche () // programme pour que le robot tourne a gauche
{
  digitalWrite(IN1, HIGH); // vitesse A CHANGER ET RAJOUTER
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // vitesse A CHANGER ET RAJOUTER
  digitalWrite(IN4, LOW);
}

void droite () // programme pour que le robot tourne a gauche
{
  digitalWrite(IN1, HIGH); // vitesse A CHANGER ET RAJOUTER
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // vitesse A CHANGER ET RAJOUTER
  digitalWrite(IN4, LOW);
}

// A RETIRER POTENTIELLEMENT

void stop2 () // second programme pour que le robot se stop
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void mesureDirection () // ecrit les mouvement du robot
{

  if      (commande == '3')   // le robot avance lorsqu'il reçoit "3"
  {
    Serial.println("Robot avance");
    delay(10);
  }

  else if (commande == '4')   // le robot recule lorsqu'il reçoit "4"
  {
    Serial.println("Robot recule");
    delay(10);
  }

  else if (commande == '5')    // le robot s'arrete lorsqu'il reçoit "5"
  {
    Serial.println("Robot tourne a gauche");
    delay(10);
  }

  else if (commande == '6')   // le robot tourne a gauche lorsqu'il reçoit "6"
  {
    Serial.println("Robot tourne a droite");
    delay(10);
  }

  else if (commande == '7') // le robot tourne a droite droite lorsqu'il ne reçoit rien
  {
    Serial.println("Robot ne bouge pas");
    delay(10);
  }
}

// RETIRER POTENTIELLEMENT

//*******************************************
// Commentaire programme
// - Le moteur 2 ne fonctionne pas
// - Faire I2C
// - Voir code a retirer potentiellement
//============================================

// code I2C ?

// Fonction qui s execute si quelque chose est present sur l interface
void receiveEvent()
{
int x = Wire.read(); // recevoir un chiffre
Serial.println(x); // afficher ce chiffre sur l'interface serie
if(x == 1)
{
      Serial.print("position pince fermé  : ");
      Serial.println(ServoClose);
      ServoMoteur.writeMicroseconds(ServoClose);
}
  
else if(x == 2)
{      
      Serial.print("position pince ouvert : ");
      Serial.println(ServoOpen);
      ServoMoteur.writeMicroseconds(ServoOpen);
}
  
else if(x == 3)
{
      avant();   // le robot avance lorsqu'il reçoit "3"
      Serial.println("Robot avance");
      delay(10);
}
  
else if(x == 4)
{
      arriere(); // le robot recule lorsqu'il reçoit "4"
      Serial.println("Robot recule");
      delay(10);
}
  
else if(x == 5)
{
      gauche();  // le robot tourne a gauche lorsqu'il reçoit "5"
      Serial.println("Robot tourne a gauche");
      delay(10);
}
else if(x == 6)
{
      droite();  // le robot tourne a droite lorsqu'il reçoit "6"
      Serial.println("Robot tourne a droite");
      delay(10);
}
else if(x == 7)
{
      stop1();  // le robot se stop lorsqu'il ne reçoit rien
      Serial.println("Robot ne bouge pas");
      delay(10);
}
  
}

//code setup

//Wire.begin(4); // Rejoindre le bus à l'adresse #4
//Wire.onReceive(receiveEvent); // Preparer une fonction spécifique a la reception de donnee
//pinMode(L1, OUTPUT); // L1 est une broche de sortie

// code setup
// code I2C

