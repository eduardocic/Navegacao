clear all; close all; clc; 

%%% CONSTANTES GERAIS
g = 9.78851;


%%% Carrega o arquivo 
load('x_up_in.mat');

%%% Separa as variáveis em estimativas locais
xm = D(:, 1);
ym = D(:, 2);
zm = D(:, 3);

%%% Médias e desvio padrão
media_x = mean(xm);
media_y = mean(ym);
media_z = mean(zm);
std_x   = std(xm);
std_y   = std(ym);
std_z   = std(zm);

%%% Indexes para os dados
n = max(size(D));
index = linspace(1, n, n);


%%% Definição das matrizes 2D e 3D
%%% ===============================
% b) Funções State Space em tempo discreto.
phi_k = eye(2);         
% phi_k = eye(3);

% c) Matrizes de saída.
C = [1  -g];
% C = [1  -g  g^2];

% d) Matrizes de erro
R_k_x = std_x^2;
R_k_y = std_y^2;
R_k_z = std_z^2;

% e) Erros de estados
Q_k = 10^-8 * eye(2);
% Q_k = 0 * eye(3);

% f) Identidade
I = eye(2);
% I = eye(3);

% g) Estimativas iniciais para P
P  = 99999999*eye(2);
% P = 99999999*eye(3);
p11(1) = P(1,1);
p22(1) = P(2,2);
% p33(1) = P(3,3);

% h) Estimativas iniciais para os estados a serem estimados
fx_hat{1} = [0; 0];
fy_hat{1} = [0; 0]; 
fz_hat{1} = [0; 0];

%%% =======================================================================
% 
%                             Variável X
%
%%% =======================================================================
% Recursão de Kalman (3D)
for k = 2:max(size(xm))    
    
    % Equação de Riccati.
    M = (phi_k) * P * (phi_k') + Q_k;
    K = M * (C') * inv(C * M * (C') + R_k_x);
    P = (I - K * C) * M;
    
    % Atualização dos estados.
    fx_hat{k} = phi_k * fx_hat{k-1} + K * (xm(k) - C * phi_k * fx_hat{k-1});
    
    p11(k) = P(1,1);
    p22(k) = P(2,2);
%     p33(k) = P(3,3);
end

% Separa os resultados para facilitar o plot.
for i = 1:max(size(xm))
   x1(i) = fx_hat{i}(1,1); 
   x2(i) = fx_hat{i}(2,1);
end

plot(xm);
hold on;
plot(x1 - x2*g, 'r');
grid;


% %%% =======================================================================
% % 
% %                             Variável Y
% %
% %%% =======================================================================
% % Recursão de Kalman (2D)
% for k = 2:size(index, 2)
%     % Equação de Riccati.
%     [P_2d{k}, K{k}] = kalman_calib(phi_k_2d, P_2d{k-1}, Q_k_2d, R_k_y, C_2d, I_2d);   
%     
%     % Atualização dos estados.
%     fy_hat{k} = fy_hat{k-1} + K{k} * (ym(k) - C_2d * phi_k_2d * fy_hat{k-1});
% end
% 
% % Separa os resultados para facilitar o plot.
% for i = 1:max(size(ym))
%    y1(i) = fy_hat{i}(1,1); 
%    y2(i) = fy_hat{i}(2,1);
% end
% 
% 
% 
% %%% =======================================================================
% % 
% %                             Variável Z
% %
% %%% =======================================================================
% clear P_2d K
% P_2d{1} = 99999999*eye(2);
% % Recursão de Kalman (2D)
% for k = 2:size(index, 2)
%     % Equação de Riccati.
%     [P_2d{k}, K{k}] = kalman_calib(phi_k_2d, P_2d{k-1}, Q_k_2d, R_k_z, C_2d, I_2d);   
%     
%     % Atualização dos estados.
%     fz_hat{k} = fz_hat{k-1} + K{k} * (zm(k) - C_2d * phi_k_2d * fz_hat{k-1});
% end
% 
% % plot(index, zm);
% % hold on;
% % plot(index, (-2*g*ones(1,1000) + bz -g*S_1_z + S_2_z * g * g), 'r');
% 
% 
save('x_up_save.mat', 'fx_hat', 'fy_hat', 'fz_hat');