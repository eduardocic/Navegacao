#include "MPU6050.h"

/***********************************************
 * Aplica a conversão dos dados de acordo com 
 * o COMPLEMENTO_2 
/**********************************************/
void engData(MPU6050_t *mpu6050){
  mpu6050->ax.pdata   = (mpu6050->ax.k_fs) * ((float) COMPLEMENTO_2(mpu6050->ax.rdata));
  mpu6050->ay.pdata   = (mpu6050->ay.k_fs) * ((float) COMPLEMENTO_2(mpu6050->ay.rdata));
  mpu6050->az.pdata   = (mpu6050->az.k_fs) * ((float) COMPLEMENTO_2(mpu6050->az.rdata));
  mpu6050->gx.pdata   = (mpu6050->gx.k_fs) * ((float) COMPLEMENTO_2(mpu6050->gx.rdata));
  mpu6050->gy.pdata   = (mpu6050->gy.k_fs) * ((float) COMPLEMENTO_2(mpu6050->gy.rdata));
  mpu6050->gz.pdata   = (mpu6050->gz.k_fs) * ((float) COMPLEMENTO_2(mpu6050->gz.rdata));
  mpu6050->temp.pdata = (mpu6050->temp.rdata/340.00) + 36.53;
}


// /* Função de calibração do EIXO X */
// /* ============================== */
// void calib_x(MPU6050_t *mpu6050){
//   static float bias_x = 0.0;
//   static int     cont = 0;
//   bias_x = bias_x * (cont - 1) + mpu6050.ax.pdata;
//   bias_x /= cont;
//   mpu6050.ax.bias = bias_x;
// }





