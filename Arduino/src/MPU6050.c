#include "MPU6050.h"

/***************************************************************
 * 
 * Aplica a conversão dos dados pelo 'COMPLEMENTO_2' em dados 
 * brutos ainda não processados (bias e média). 
 * 
 ***************************************************************/
void getRawData(MPU6050_t *mpu6050){

      mpu6050->ax.rdata   = (mpu6050->ax.k_fs) * ((double) COMPLEMENTO_2(mpu6050->ax.c2data));
      mpu6050->ay.rdata   = (mpu6050->ay.k_fs) * ((double) COMPLEMENTO_2(mpu6050->ay.c2data));
      mpu6050->az.rdata   = (mpu6050->az.k_fs) * ((double) COMPLEMENTO_2(mpu6050->az.c2data));
      // mpu6050->gx.rdata   = (mpu6050->gx.k_fs) * ((double) COMPLEMENTO_2(mpu6050->gx.c2data));
      // mpu6050->gy.rdata   = (mpu6050->gy.k_fs) * ((double) COMPLEMENTO_2(mpu6050->gy.c2data));
      // mpu6050->gz.rdata   = (mpu6050->gz.k_fs) * ((double) COMPLEMENTO_2(mpu6050->gz.c2data));
      // mpu6050->temp.pdata = (mpu6050->temp.rdata/340.00) + 36.53;
}


/***************************************************************
 * 
 * Aplica a correção nos dados do tipo 'rdata' de modo a possi-
 * bilitar a utilização nas atividades de navegação. Ou seja, 
 * os dados já utilizam os parâmetros de correção de calibragem
 * 
 ***************************************************************/
void getProcessedData(MPU6050_t *mpu6050){

      /* Variáveis auxiliares */ 
      double fx = mpu6050->ax.rdata;
      double fy = mpu6050->ay.rdata;
      double fz = mpu6050->az.rdata;

      /* Solução via brute force, por convergência */
      for (int i = 0 ; i < 7 ; i++){
         fx =  dx[0]*(mpu6050->ax.rdata - mpu6050->ax.bias) + dx[1]*fy + dx[2]*fz + dx[3]*fx*fx;
         fy =  dy[0]*(mpu6050->ay.rdata - mpu6050->ay.bias) + dy[1]*fx + dy[2]*fz + dy[3]*fy*fy;
         fz =  dz[0]*(mpu6050->az.rdata - mpu6050->az.bias) + dz[1]*fx + dz[2]*fy + dz[3]*fz*fz;      
      }

      /* Atualiza as variáveis */
      mpu6050->ax.pdata = fx;
      mpu6050->ay.pdata = fy;
      mpu6050->az.pdata = fz;
}
