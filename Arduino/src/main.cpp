/********************************************************
 * Para programar no Visual Studio Code a gente precisa
 * incluir esta library 'Arduino.h'.                               
 ********************************************************/
#include <Arduino.h>

/* Demais library a serem utilizadas */
#include <stdio.h>
#include <stdlib.h>
#include <Wire.h>

/* Adicionar as bibliotecas implementadas em C */
extern "C" {
  #include "matrix.h"
  #include "matematica.h"
  #include "control_system.h"
  #include "MPU6050.h"
}

/* Protótipo de funções
/ ====================== */
void display(matrix *A);
void getC2Data(MPU6050_t *mpu6050);


// ====================
//
//        SETUP
//
// ====================
MPU6050_t mpu6050; 

void setup() {
  Serial.begin(9600);

  /* Inicializa o MPU6050 */ 
  Wire.beginTransmission(MPU6050);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);


  /*======================================================== */
  /* Inicializa os parâmetros das constantes multiplicativas */
  mpu6050.ax.k_fs = kAccel[0] * g;
  mpu6050.ay.k_fs = kAccel[0] * g;
  mpu6050.az.k_fs = kAccel[0] * g;

  /* Inicializa o bias */
  mpu6050.ax.bias = -0.6449172520;
  mpu6050.ay.bias =  0.3271865289;
  mpu6050.az.bias =  0.6571711751;
  /*======================================================== */
}



// ====================
//
//         LOOP
//
// ====================
void loop() {

  /* Coleta os dados pela I2C */ 
  getC2Data(&mpu6050);
  getRawData(&mpu6050);
  getProcessedData(&mpu6050);

  Serial.print(mpu6050.ax.pdata, 8);
  Serial.print(" ");
  Serial.print(mpu6050.ay.pdata, 8);
  Serial.print(" ");
  Serial.println(mpu6050.az.pdata, 8);
  delay(50);
}




/* Rotinas implementadas */
void display(matrix *A){
    for (int i = 0 ; i < A->lines ; i++){
        Serial.print("|  ");
        for (int j = 0 ; j < A->columns ; j++){
            Serial.print(get(A, i, j));
        }
        Serial.println(" |");
    }
}

void getC2Data(MPU6050_t *mpu6050){

  /* Solicita o dispositivo e registrador a partir de onde virão os dados */
  Wire.beginTransmission(MPU6050);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);

  /* Solicita a leitura de 'X' bytes */
  Wire.requestFrom(MPU6050, 6, true); 

  /* Ler e concatena os dados no formato leitura, sem nenhum tipo de processamento (rdata) */
  mpu6050->ax.c2data    = Wire.read()<<8 | Wire.read();
  mpu6050->ay.c2data    = Wire.read()<<8 | Wire.read();
  mpu6050->az.c2data    = Wire.read()<<8 | Wire.read();
  // mpu6050->temp.c2data  = Wire.read()<<8 | Wire.read();
  // mpu6050->gx.c2data    = Wire.read()<<8 | Wire.read();
  // mpu6050->gy.c2data    = Wire.read()<<8 | Wire.read();
  // mpu6050->gz.c2data    = Wire.read()<<8 | Wire.read();
}