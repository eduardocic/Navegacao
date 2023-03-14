import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 1. Ler os dados do arquivo, que não possuem header
# 2. Insiro a nomenclatura para as colunas
data = pd.read_fwf("z_mais_01.txt", sep = " ", header = None)
data.columns = ["x", "y", "z"]

# Pegos os valores isoladamente
x = data.x
y = data.y
z = data.z

# Valores de média
xmean = np.mean(x)
ymean = np.mean(y)
zmean = np.mean(z)
print("MEAN ...: ", xmean, ymean, zmean)

# Valores de desvio padrão
xsigma = np.std(x);
ysigma = np.std(y);
zsigma = np.std(z);
print("STD ....: ", xsigma, ysigma, zsigma)


count, bins = np.histogram(x)
plt.plot(count);
plt.show()



#plt.plot(x, 'b', y, 'r', z, 'k')
#plt.grid()
#plt.show()




