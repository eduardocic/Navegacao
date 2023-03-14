#ifndef _MPU_6050_H_
#define _MPU_6050_H_

/* Endereço para comunicação I2C */
const int MPU6050 = 0x68; 

/* Mapa de registradores */ 
#define ACCEL_XOUT_H         0x3B
#define ACCEL_XOUT_L         0x3C
#define ACCEL_YOUT_H         0x3D
#define ACCEL_YOUT_L         0x3E
#define ACCEL_ZOUT_H         0x3F
#define ACCEL_ZOUT_L         0x40
#define TEMP_OUT_H           0x41
#define TEMP_OUT_L           0x42
#define GYRO_XOUT_H          0x43
#define GYRO_XOUT_L          0x44
#define GYRO_YOUT_H          0x45
#define GYRO_YOUT_L          0x46
#define GYRO_ZOUT_H          0x47
#define GYRO_ZOUT_L          0x48

/* Parâmetros diversos */ 
#define g                    9.80665

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Macro de complemento 2 para decimal. 
 * Maiores detalhes podem ser consultados no link abaixo:
 * https://www.filipeflop.com/blog/complemento-de-dois/ 
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#define COMPLEMENTO_2(x)     (~x + 1)


/* Estrutura de dados individuais */
typedef struct{
  int      c2data;   /* c2 data   */
  double   rdata;    /* raw data  */
  double   bias;     /* bias      */
  double   pdata;    /* processed data                */
  double   k_fs;     /* constante do ACCEL FULL SCALE */
} ACCEL_t;

typedef struct{
  int      c2data;   /* c2 data   */
  double   rdata;    /* raw       */
  double   bias;     /* bias      */
  double   pdata;    /* processed data                */
  double   k_fs;     /* constante do GYRO FULL SCALE */
} GYRO_t;

typedef struct{
  int      c2data;   /* complemento 2                */
  double   pdata;    /* processed data               */
} TEMP_t;

/* Estrutura de dados condensadas */
typedef struct {
  ACCEL_t ax, ay, az;
  // GYRO_t  gx, gy, gz;
  // TEMP_t  temp;
} MPU6050_t;

/* (*) No MPU6050, as medidas de aceleração e de rotação são coletadas de 
 *     forma bruta (raw data), que nada mais é do que uma coleção de dados
 *     do tipo inteiro. Aqui estamos fazendo via comunicação I2C;
 * 
 * (*) Em seguida, as medidas precisam ser transformadas em unidades de 
 *     engenharia, ou seja, m/s2 e º/s (unidades tais que possam ser traba-
 *     lhadas em integração para obtenção dos dados de interesse);
 * 
 * (*) Cada sensor (giro e acelerômetros) no MPU6050 são de 16 bits. Com isso, 
 *     as medidas possíveis estão no range que vai de 0 até (2^16 - 1), tota-
 *     lizando 65.536 valores;
 * 
 * (*) Deve-se, então, após realizar a função de 'COMPLEMENTO_2' nas amostras 
 *     brutas (raw) adquiridas via comunicação I2C, multiplicar tal medida por
 *     um valor que transforme as medidas processadas em unidades de engenharia;
 * 
 * (*) Pelo datasheet o valor a ser multiplicado depende exclusivamente do sensor
 *     (se giro ou acelerômetro), e do 'Full Scale' individual setados nos regis-
 *     tradores GYRO_CONFIG e ACCEL_CONFIG;
 * 
 * (*) Os possíveis modos para os girômetros variam para escalas que vão de
 *     +-250º/s até +-2000º/s. Enquanto que para os acelerômetros, as escalas
 *     vão de +-2g até +-16g. 
 *
 * (*) Para se ter as medidas em unidades de engenharia, deve-se executar o se-
 *     guinte procedimento:
 *    
 *     1) Verificar a situação dos registradores GYRO_CONFIG e ACCEL_CONFIG, para
 *        saber em que 'Full Scale' cada um está setado. Por exemplo, para o giro
 *        está setado o valor +-250º/s e para o acelerômetro +- 2g;
 * 
 *     2) No caso de o giro estar apto a medir no intervalo [-250º/s, +250º/s], 
 *        perceba, então, que tal intervalor tem de ser englobado pelos 16bits, 
 *        em seus 65536 possíveis valores. Pela escala, o intervalor acima tem
 *        de ser equivalente ao intervalor [0, 65535]. Com isto, deve-se pegar
 *        o valor lido de rotação e realizar uma regra de três simples, que si-
 *        gnifica multiplicar por 500 (dado o range que eu quero medir) e divi-
 *        dir por 65536;
 * 
 *     3) No caso do acelerômetros estar apto a medir no intervalo [-2g, 2g], 
 *        perceba, então, que tal intervalor tem de ser englobado pelos 16bits, 
 *        em seus 65536 possíveis valores. Pela escala, o intervalor acima tem
 *        de ser equivalente ao intervalor [0, 65535]. Com isto, deve-se pegar
 *        o valor lido de aceleração e realizar uma regra de três simples, que
 *        significa multiplicar por 4g (dado o range que eu quero medir) e divi-
 *        dir por 65536;
 * 
 * (*) A depender de como está setado o GYRO_CONFIG, os possíveis valores para
 *     a constante multiplicativa dos girômetros são:
 *     
 *    1.  [ -250º/s,  +250º/s] ----> k =  500/65536 =~ 0.00762951;
 *    2.  [ -500º/s,  +500º/s] ----> k = 1000/65536 =~ 0.01525879;
 *    3.  [-1000º/s, +1000º/s] ----> k = 2000/65536 =~ 0.03051758;
 *    4.  [-2000º/s, +2000º/s] ----> k = 4000/65536 =~ 0.06103515;
 *
 * (*) A depender de como está setado o ACCEL_CONFIG, os possíveis valores para
 *     a constante multiplicativa dos acelerômetros são:
 *     
 *    1.  [ -2g,  +2g] ------------> k =   4g/65536 = g * 0.00006104;
 *    2.  [ -4g,  +4g] ------------> k =   8g/65536 = g * 0.00012207;
 *    3.  [ -8g,  +8g] ------------> k =  16g/65536 = g * 0.00024414;
 *    4.  [-16g, +16g] ------------> k =  32g/65536 = g * 0.00048828;
 */

const double kAccel[]  = {0.00006104,     0.00012207,     0.00024414, 0.00048828};
// enum FS_ACC { mm2g  = 0, 
//               mm4g  = 1, 
//               mm8g  = 2, 
//               mm16g = 3}; /* O 'mm' é para simbolizar o 'mais ou menos' */

const double dx[] = {1.0017053605,   0.0045963109,   0.0031082230,   0.0001341552};
const double dy[] = {1.0043009256,  -0.0075904210,  -0.0034263600,   0.0002361725};
const double dz[] = {0.9813303299,   0.0057193400,  -0.0021711114,  -0.0005080795};



// ============================================================================
// Deve ser iniciado depois
// 
// const double kGyro[4]  = {0.00762951, 0.01525879, 0.03051758, 0.06103515};
// ============================================================================


/* Protótipos de funções */
void getRawData(MPU6050_t *mpu6050);
void getProcessedData(MPU6050_t *mpu6050);

#endif

