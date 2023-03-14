import serial


# Informações sobre a comunicação serial estabelecida
sensor      = "MPU6050"
serial_port = "/dev/ttyUSB0"
baud_rate   = 9600
ser         = serial.Serial(serial_port, baud_rate)

# Arquivo log a ser utilizado
f = open("y_up.txt", "wb")

# Tempo de coleta de dados.
t    = 0;
tMax = 3000;

###########################################################
print("Estou iniciando as medições")
while t < tMax:
	data = ser.readline()
	print(data)
	f.write(data)
	f.flush()
	t = t+1
f.close()
print("Estou terminando as medições")
###########################################################



