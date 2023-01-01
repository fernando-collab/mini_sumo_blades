/*
Descripcion:Codigo para controlar un robot mini sumo mediante
            el uso de los sensores "tcrt 5000" y "fc-51" y dos servos
Desarrollador:Fernando sanchez 
Github:fernando-collab
*/

//declaramos las librerias
#include<Arduino.h>
#include <Servo.h>
#include<control_robot.h>

//definimos los servos
Servo servo_drch;
Servo servo_izq;

//declaramos variables
boolean modo_combate = false;//el robot comienza parado
int estado_boton = digitalRead(boton);  //lee el estado del boton
//almacena estado de los sensores
int estado_s_iqz;
int estado_s_drch;
int estado_s_at_izq;
int estado_s_at_cnt;
int estado_s_at_drch;


void setup() {
	//configuramos los pines  
	pinMode(boton , INPUT_PULLUP);
	pinMode(s_izq , INPUT);
	pinMode(s_drch , INPUT);
  pinMode(s_at_izq , INPUT);
  pinMode(s_at_cnt , INPUT);
  pinMode(s_at_drch , INPUT);
	//configuramos los servos
  servo_izq.attach(motor_izq);
  servo_drch.attach(motor_drch);
	//puerto serie 
 	Serial.begin(9600);

}

void loop() {
  //delay(50);
  leer_boton();
  leer_sensores_ataque();
  leer_sensores_line();
  
  if (modo_combate == false)
  {  
    parado();
  }else{


    //modificar para integrar los menus de ataque!!!!!!


    if (estado_s_drch == LOW ||estado_s_iqz == LOW ){
      Serial.println("NEGRO");
      evasion();
    }else{
      if ( estado_s_at_cnt == LOW || estado_s_at_izq == LOW || estado_s_at_drch == LOW ){
        Serial.println("MALO");
        adelante();
      }else{ 
        girar_derecha();
      }  
    }
  }
delay(50);
}

void leer_boton() {
  if (estado_boton == LOW) {
    modo_combate = !modo_combate; 
    delay(500); 
    if (modo_combate == true){   
      Serial.println("ENTRANDO EN MODO COMBATE");
      delay(4500);
    }
    if(modo_combate == false){
       Serial.println("ENTRANDO EN MODO REPOSO");
    }
  }
}
//lee los sensores de ataque
void leer_sensores_ataque(){
  estado_s_at_izq = digitalRead(s_at_izq);  
  estado_s_at_cnt = digitalRead(s_at_cnt);
  estado_s_at_drch = digitalRead(s_at_drch);
 //codigo para comprobar el funcionamiento de los sensores de ataque 
  Serial.print("SENSORES DE ATAQUE");
  Serial.print("\t");
  Serial.print(estado_s_at_izq);
  Serial.print("\t");
  Serial.print(estado_s_at_cnt);
  Serial.print("\t");
  Serial.print(estado_s_at_drch);
  Serial.println("\t");
  
}
//lee los sensores de linea
void leer_sensores_line(){
  estado_s_drch = digitalRead(s_drch);
  estado_s_iqz = digitalRead(s_izq);
  //codigo para comprobar el funcionamiento de los sensores de linea
  Serial.print("SENSORES DE LINEA");
  Serial.print("\t");
  Serial.print(estado_s_drch);
  Serial.print("\t");
  Serial.print(estado_s_iqz);
  Serial.print("\t");
}

//maniobras de movimiento

void girar_derecha() {
  servo_drch.write(50);
  servo_izq.write(50);
  delay(50);
}

void girar_izquierda() {
  servo_drch.write(80);
  servo_izq.write(80);
  delay(50);
}

void adelante() { 
  servo_drch.write(180);
  servo_izq.write(0);
  delay(100);
}

void atras() {
  servo_drch.write(0);
  servo_izq.write(180);
  delay(100);
}

void parado() {
  servo_drch.write(90);
  servo_izq.write(90);
  delay(50);
}

void evasion() {
  parado();
  delay(50);
  atras();
  delay(100);
} 

void selector_menus(){
  int valor;
  if (estado_boton)
  {
    valor++;
  }
  switch (valor)
  {
  case 1 :
    //menu 1
    Serial.println(" se pulso el boton 1 vez");
    menu_1();
    break;
 case 2 :
    //menu 2
    Serial.println(" se pulso el boton 2 vez");
    menu_2();
    break;
  case 3 :
    //menu 3
    Serial.println(" se pulso el boton 3 vez");
    menu_3();
    break;
  case 4 :
    //menu 4
    Serial.println(" se pulso el boton 4 vez");
    menu_4();
    break;
  default:
    Serial.println("no se pulso el boton");
    parado();
    break;
  }
}

void menu_1(){
  
}

void menu_2(){

}

void menu_3(){

}

void menu_4(){

}
