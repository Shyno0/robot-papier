//*******************************************
// Module L298N pour commander un
// Moteur 2 phases pas à pas (4 fils)
//============================================
//Câblage du steper, utilise 6 broches
int ENA=2; // Arduino Pin 2
int IN1=3; // Arduino Pin 3
int IN2=4; // Arduino Pin 4
int ENB=5; // Arduino Pin 5
int IN3=6; // Arduino Pin 6
int IN4=7; // Arduino Pin 7

void setup() {
 pinMode(ENA,OUTPUT);  //Les 6 pins configurées en sorties
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 //Enable A et B, utilise les 2 ponts en H
 digitalWrite(ENA,HIGH);// Activer pont A
 digitalWrite(ENB,HIGH);// Activer pont B
}
void loop(){
 // Un moteur Pas-à-pas se contrôle à l'aide de 4 battements
 // Séquences AB   A-B   A-B-  AB-  ou séquence  AB   AB-   A-B-   A-B
 
 int tps = 20;  //Délai en ms entre deux commandes de changement de pas (vitesse du moteur)

}

 digitalWrite(IN1,LOW);  //0110  A-B
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 
 digitalWrite(IN1,LOW);  //0101  A-B-
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);

 digitalWrite(IN1,HIGH); //1001  AB-
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 
 digitalWrite(IN1,HIGH);  //1010  AB
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 
