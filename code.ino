//*******************************************
// Module L298N pour commander un
// Moteur 2 phases pas à pas (4 fils)
//============================================
//Câblage du steper, utilise 6 broches
int ENA = 2; // Arduino Pin 2
int IN1 = 3; // Arduino Pin 3
int IN2 = 4; // Arduino Pin 4
int ENB = 5; // Arduino Pin 5
int IN3 = 6; // Arduino Pin 6
int IN4 = 7; // Arduino Pin 7
int servoPin = 9; // déclare la broche de contrôle du servo
int ServoOpen =  1000; // Position pince ouverte ( valeur a changer )
int ServoClose = 2000; // Position pince fermer  ( valeur a changer )

#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur
Servo ServoMoteur;  // on crée l'objet monServo

void setup() {
 Serial.begin(9600);
 ServoMoteur.attach(servoPin); // on définit le Pin utilisé par le servomoteur

 pinMode(ENA,OUTPUT);  // Les 6 pins configurées en sorties
 pinMode(ENB,OUTPUT);  // 
 pinMode(IN1,OUTPUT);  // 
 pinMode(IN2,OUTPUT);  // 
 pinMode(IN3,OUTPUT);  // 
 pinMode(IN4,OUTPUT);  // 
 //Enable A et B, utilise les 2 ponts en H bloque les deux roues
 digitalWrite(ENA,HIGH);// Activer pont A
 digitalWrite(ENB,HIGH);// Activer pont B
}
void loop(){
 int tps = 20;  //Délai en ms entre deux commandes de changement de pas (vitesse du moteur)
 

}

void mesure ()
{

Serial.print(" test ");

}
void avant ()
{

digitalWrite(IN1,HIGH);  
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
}

void arriere ()
{

digitalWrite(IN1,LOW);  
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
 
}

void stop ()
{

digitalWrite(IN1,HIGH);  
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,HIGH);
 
}

void stop2 ()
{

digitalWrite(IN1,LOW);  
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
 
}

void gauche () 
{

digitalWrite(IN1,HIGH);  // A CHANGER 
digitalWrite(IN2,LOW);   // A CHANGER 
digitalWrite(IN3,HIGH);  // A CHANGER 
digitalWrite(IN4,LOW);   // A CHANGER 
 
}

void droite ()
{

digitalWrite(IN1,HIGH);  // A CHANGER 
digitalWrite(IN2,LOW);   // A CHANGER 
digitalWrite(IN3,HIGH);  // A CHANGER 
digitalWrite(IN4,LOW);   // A CHANGER 
 
}
