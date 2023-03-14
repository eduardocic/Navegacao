clear all; close all; clc; 

%%% Carrega a primeira parte. 
load('x_up_save.mat')

for i = 1:max(size(fx_hat))
    x1(i) = fx_hat{i}(1,1);
end

%%% Carrega a segunda parte. 
clear fx_hat fy_hat fz_hat


load('x_down_save.mat')
for i = 1:max(size(fx_hat))
    x2(i) = fx_hat{i}(1,1);
end

index = linspace(1, max(size(x1)), max(size(x2)));
plot(index, x1);
hold on;
plot(index, x2, 'r');