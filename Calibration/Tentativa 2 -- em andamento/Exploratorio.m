clear all; close all; clc; 

%  Arquivos calibração em X
% ==========================
D = importdata('x_up.txt');
xm = D(:,1);

for i = 1:max(size(xm))
    index(i)         = i; 
    
    % Média.
    x_medio(i)       = sum(xm(1:i))/i;
    
    % Desvio Padrão -- código matlab
    std_matlab(i)    = std(xm(1:i));    
end

plot(index, x_medio); grid;

figure;
plot(index, std_matlab, 'r');
grid;