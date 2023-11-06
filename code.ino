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
 Serial.begin(9600);

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

void avant ()
{

digitalWrite(IN1,LOW);  
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
}

void arriere ()
{

digitalWrite(IN1,LOW);  
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
}

void stop ()
{

digitalWrite(IN1,LOW);  
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
}

void gauche ()
{

digitalWrite(IN1,LOW);  
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
}

void droite ()
{

digitalWrite(IN1,LOW);  
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
 
}
