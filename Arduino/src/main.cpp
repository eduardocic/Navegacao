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
void getRawData(MPU6050_t *mpu6050);
void printRawData(MPU6050_t *mpu6050);
void printEngData(MPU6050_t *mpu6050);


// ====================
//
//        SETUP
//
// ====================
MPU6050_t mpu6050; 

static float bias_z = 0.0;
int cont = 0;


void setup() {
  Serial.begin(9600);

  // Inicializa o MPU6050
  Wire.beginTransmission(MPU6050);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);

  /* Inicializa os parâmetros das constantes multiplicativas */
  mpu6050.ax.k_fs = kAccel[0] * g;
  mpu6050.ay.k_fs = kAccel[0] * g;
  mpu6050.az.k_fs = kAccel[0] * g;
  mpu6050.gx.k_fs = kGyro[0];
  mpu6050.gy.k_fs = kGyro[0];
  mpu6050.gz.k_fs = kGyro[0];
}



// ====================
//
//         LOOP
//
// ====================
void loop() {

  /* Coleta os dados pela I2C */ 
  getRawData(&mpu6050);

  /* Processa os dados e os transforma em dados de engenharia */
  engData(&mpu6050);


  cont++;
  bias_z = bias_z * (cont - 1) + mpu6050.az.pdata;
  bias_z /= cont;

  Serial.print(mpu6050.az.pdata);
  Serial.print(" ");
  Serial.println(bias_z);
  delay(100);
}













// Rotinas implementadas
// ======================
void display(matrix *A){
    for (int i = 0 ; i < A->lines ; i++){
        Serial.print("|  ");        
        for (int j = 0 ; j < A->columns ; j++){
            Serial.print(get(A, i, j));
        }
        Serial.println(" |");
    }
}

void getRawData(MPU6050_t *mpu6050){
  // Soliticação de dados do MPU6050, iniciando a partir do enderenço do
  // registrador do acelerômetro de medida x.
  Wire.beginTransmission(MPU6050);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU6050, 14, true);  
  
  mpu6050->ax.rdata    = Wire.read()<<8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  mpu6050->ay.rdata    = Wire.read()<<8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  mpu6050->az.rdata    = Wire.read()<<8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  mpu6050->temp.rdata  = Wire.read()<<8 | Wire.read();  // 0x41   (TEMP_OUT_H) & 0x42   (TEMP_OUT_L)
  mpu6050->gx.rdata    = Wire.read()<<8 | Wire.read();  // 0x43  (GYRO_XOUT_H) & 0x44  (GYRO_XOUT_L)
  mpu6050->gy.rdata    = Wire.read()<<8 | Wire.read();  // 0x45  (GYRO_YOUT_H) & 0x46  (GYRO_YOUT_L)
  mpu6050->gz.rdata    = Wire.read()<<8 | Wire.read();  // 0x47  (GYRO_ZOUT_H) & 0x48  (GYRO_ZOUT_L)
}


void printEngData(MPU6050_t *mpu6050){
  // Coloca os parâmetros no SI. 
  Serial.print("aX = ");    Serial.print(mpu6050->ax.pdata);
  Serial.print(" | aY = "); Serial.print(mpu6050->ay.pdata);
  Serial.print(" | aZ = "); Serial.print(mpu6050->az.pdata);
  Serial.print(" | gX = "); Serial.print(mpu6050->gx.pdata);
  Serial.print(" | gY = "); Serial.print(mpu6050->gy.pdata);
  Serial.print(" | gZ = "); Serial.print(mpu6050->gz.pdata);
  Serial.print(" | T = ");  Serial.println(mpu6050->temp.pdata);
}


void printRawData(MPU6050_t *mpu6050){
  // Coloca os parâmetros no SI. 
  Serial.print("aX = ");    Serial.print(mpu6050->ax.rdata);
  Serial.print(" | aY = "); Serial.print(mpu6050->ay.rdata);
  Serial.print(" | aZ = "); Serial.print(mpu6050->az.rdata);
  Serial.print(" | gX = "); Serial.print(mpu6050->gx.rdata);
  Serial.print(" | gY = "); Serial.print(mpu6050->gy.rdata);
  Serial.print(" | gZ = "); Serial.print(mpu6050->gz.rdata);
  Serial.print(" | T = ");  Serial.println(mpu6050->temp.rdata);
}