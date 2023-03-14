clear all; close all; clc; 

%%% CONSTANTES GERAIS
g = 9.78851;

%%% Carrega o arquivo 
load('y_up_in.mat');

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
index  = linspace(1, max(size(xm)), max(size(xm)));


%%% Definição das matrizes 2D e 3D
%%% ===============================
% a) Funções State Space em tempo contínuo.
F_2d     = [ 0, 0; 
             0, 0];
F_3d     = [ 0, 0, 0;
             0, 0, 0;
             0, 0, 0];
% b) Funções State Space em tempo discreto.
phi_k_2d = eye(2);         
phi_k_3d = eye(3);

% c) Matrizes de saída.
C_2d = [1  -g];
C_3d = [1  -g  g^2];

% d) Matrizes de erro
R_k_x = std_x^2;
R_k_y = std_y^2;
R_k_z = std_z^2;

% e) Erros de estados
Q_k_2d = 0 * eye(2);
Q_k_3d = 0 * eye(3);

% f) Identidade
I_2d = eye(2);
I_3d = eye(3);

% g) Estimativas iniciais para P
P_2d{1}    = 99999999*eye(2);
P_3d{1}    = 99999999*eye(3);

% h) Estimativas iniciais para os estados a serem estimados
fx_hat{1} = [0; 0];
fy_hat{1} = [0; 0; 0]; 
fz_hat{1} = [0; 0];

%%% =======================================================================
% 
%                             Variável X
%
%%% =======================================================================
% Recursão de Kalman (2D)
for k = 2:size(index, 2)
    % Equação de Riccati.
    [P_2d{k}, K{k}] = kalman_calib(phi_k_2d, P_2d{k-1}, Q_k_2d, R_k_x, C_2d, I_2d);   
    
    % Atualização dos estados.
    fx_hat{k} = phi_k_2d * fx_hat{k-1} + K{k} * (xm(k) - C_2d * phi_k_2d * fx_hat{k-1});
end

% % Separa os resultados para facilitar o plot.
% for i = 1:max(size(xm))
%    bx(i)         = fx_hat{i}(1,1); 
%    theta_a_xz(i) = fx_hat{i}(2,1);
% end


%%% =======================================================================
% 
%                             Variável Y
%
%%% =======================================================================
clear K
% Recursão de Kalman (3D)
for k = 2:size(index, 2)
    % Equação de Riccati.
    [P_3d{k}, K{k}] = kalman_calib(phi_k_3d, P_3d{k-1}, Q_k_3d, R_k_y, C_3d, I_3d);   
    
    % Atualização dos estados.
    fy_hat{k} = phi_k_3d * fy_hat{k-1} + K{k} * ((ym(k)+2*g) - C_3d * phi_k_3d * fy_hat{k-1});
end

% % Separa os resultados para facilitar o plot.
% for i = 1:max(size(ym))
%    by(i)         = fy_hat{i}(1,1); 
%    theta_a_yz(i) = fy_hat{i}(2,1);
% end



%%% =======================================================================
% 
%                             Variável Z
%
%%% =======================================================================
clear P_2d K
P_2d{1}    = 99999999*eye(2);
% Recursão de Kalman (2D)
for k = 2:size(index, 2)
    % Equação de Riccati.
    [P_2d{k}, K{k}] = kalman_calib(phi_k_2d, P_2d{k-1}, Q_k_2d, R_k_z, C_2d, I_2d);   
    
    % Atualização dos estados.
    fz_hat{k} = phi_k_2d * fz_hat{k-1} + K{k} * (zm(k) - C_2d * phi_k_2d * fz_hat{k-1});
end
% 
% % Separa os resultados para facilitar o plot.
% for i = 1:max(size(zm))
%    bz(i)    = fz_hat{i}(1,1); 
%    S_1_z(i) = fz_hat{i}(2,1);
%    S_2_z(i) = fz_hat{i}(3,1);
% end

% plot(index, zm);
% hold on;
% plot(index, (-2*g*ones(1,1000) + bz -g*S_1_z + S_2_z * g * g), 'r');


save('y_up_save.mat', 'fx_hat', 'fy_hat', 'fz_hat');