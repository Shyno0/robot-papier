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
int temps = 1000; // valeur servo de base
#define ServoClose  1500 
// Position pince fermer
#define ServoOpen   2500 
// Position pince ouvert  

char commande; // Variable commande pour lire ensuite lire le Moniteur serie

#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur
Servo ServoMoteur;  // on crée l'objet monServo

void setup() {
 Serial.begin(9600);
 ServoMoteur.attach(servoPin); // on définit le Pin utilisé par le servomoteur
 ServoMoteur.writeMicroseconds(ServoClose); // position pince fermé

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
  //des données sur la liaison série (lorsque l'on appuie sur '1' ou '2')
  if (Serial.available())
  {
    commande = Serial.read(); //on lit

    //on modifie la consigne si c'est un caractère qui nous intéresse
    if (commande == '1')      temps = ServoClose;// Pince position fermé
    else if (commande == '2') temps = ServoOpen; // Pince position ouvert
    //on modifie la consigne du servo
    ServoMoteur.writeMicroseconds(temps);
    //et on fait un retour sur la console pour savoir où on est rendu
    mesurePince();
  }

 {
    
  if      (commande == '3') avant();   // le robot avance lorsqu'il reçoit "3"
  else if (commande == '4') arriere(); // le robot recule lorsqu'il reçoit "4"
  else if (commande == '5') gauche();  // le robot tourne a gauche lorsqu'il reçoit "5"
  else if (commande == '6') droite();  // le robot tourne a droite lorsqu'il reçoit "6"
  else                       stop1();  // le robot se stop lorsqu'il ne reçoit rien
  mesureDirection();
  //int tps = 20;  //Délai en ms entre deux commandes de changement de pas (vitesse du moteur)

 }
}

void mesurePince ()
{

  if (commande == '1') 
  {
    Serial.print("position pince fermé  : ");
    Serial.println(ServoClose);
  }
  else if (commande == '2') 
  {
    Serial.print("position pince ouvert : ");
    Serial.println(ServoOpen);
  }
}

void mesureDirection () // ecrit les mouvement du robot
{

  if      (commande == '3')   // le robot avance lorsqu'il reçoit "3"
 {
    Serial.println("Robot avance");
 }
 
  else if (commande == '4')   // le robot recule lorsqu'il reçoit "4"
 {
    Serial.println("Robot recule");
 }
 
  else if (commande == '5')    // le robot s'arrete lorsqu'il reçoit "5"
 {
    Serial.println("Robot tourne a gauche");
 }
 
  else if (commande == '6')   // le robot tourne a gauche lorsqu'il reçoit "6"
 {
    Serial.println("Robot tourne a droite");
 }
 
  else  // le robot tourne a droite droite lorsqu'il ne reçoit rien
 { 
    Serial.println("Robot ne bouge pas");
 }
}

void avant () // programme pour que le robot avance
{

digitalWrite(IN1,HIGH); //broche IN1 alimenté
digitalWrite(IN2,LOW);  //broche IN2 pas alimenté
digitalWrite(IN3,HIGH); //broche IN3 alimenté
digitalWrite(IN4,LOW);  //broche IN4 pas alimenté
 
}

void arriere () // programme pour que le robot recule
{

digitalWrite(IN1,LOW);  //broche IN1 pas alimenté
digitalWrite(IN2,HIGH); //broche IN2 alimenté
digitalWrite(IN3,LOW);  //broche IN3 pas alimenté
digitalWrite(IN4,HIGH); //broche IN4 alimenté
 
}

void stop1 () // programme pour que le robot se stop
{

digitalWrite(IN1,HIGH); //broche IN1 alimenté
digitalWrite(IN2,HIGH); //broche IN2 alimenté
digitalWrite(IN3,HIGH); //broche IN3 alimenté
digitalWrite(IN4,HIGH); //broche IN4 alimenté
 
}

void stop2 () // second programme pour que le robot se stop
{

digitalWrite(IN1,LOW); 
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
 
}

void gauche () // programme pour que le robot tourne a gauche
{

digitalWrite(IN1,HIGH);  // vitesse A CHANGER ET RAJOUTER 
digitalWrite(IN2,LOW);    
digitalWrite(IN3,HIGH);  // vitesse A CHANGER ET RAJOUTER
digitalWrite(IN4,LOW);   
 
}

void droite () // programme pour que le robot tourne a gauche
{

digitalWrite(IN1,HIGH);  // vitesse A CHANGER ET RAJOUTER
digitalWrite(IN2,LOW);   
digitalWrite(IN3,HIGH);  // vitesse A CHANGER ET RAJOUTER
digitalWrite(IN4,LOW);   
 
}
