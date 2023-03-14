clear all; close all; clc; 

% Parâmetros diversos. 
g = 9.78851;

% Carrega o arquivo com os parâmetros médios
load('calib_acc.mat');


%  Z+ e Z-
% =========
bx(1)      =  (fx_z_up + fx_z_down)/2;
theta_a_xz = -(fx_z_up - fx_z_down)/(2*g);

by(1)      =  (fy_z_up + fy_z_down)/2;
theta_a_yz = -(fy_z_up - fy_z_down)/(2*g);

S1_z       = -(4*g + (fz_z_up - fz_z_down))/(2*g);


%  Y+ e Y-
% =========
bx(2)      =  (fx_y_up + fx_y_down)/2;
theta_a_xy = -(fx_y_up - fx_y_down)/(2*g);

S1_y       = -(4*g + (fy_y_up - fy_y_down))/(2*g);

bz(1)      =  (fz_y_up + fz_y_down)/2;
theta_a_zy = -(fz_y_up - fz_y_down)/(2*g);


%  X+ e X-
% =========
S1_x       = -(4*g + (fx_x_up - fx_x_down))/(2*g);

by(2)      =  (fy_x_up + fy_x_down)/2;
theta_a_yx = -(fy_x_up - fy_x_down)/(2*g);

bz(2)      =  (fz_x_up + fz_x_down)/2;
theta_a_zx = -(fz_x_up - fz_x_down)/(2*g);


%% Resolução dos parâmetros médios do sistema. 

% Matriz de bias (tomado como uma média geral entre os parâmetros dispostos
bx = mean(bx);
by = mean(by);
bz = mean(bz);
ba = [bx; by; bz];

% Matriz S1
S1 = [ S1_x     0     0;
          0  S1_y     0;
          0     0  S1_z];
      
% Matriz S2
S2_x = (((fx_x_up + fx_x_down)/2) - bx)/(g^2);
S2_y = (((fy_y_up + fy_y_down)/2) - by)/(g^2);
S2_z = (((fz_z_up + fz_z_down)/2) - bz)/(g^2);
S2 = [ S2_x     0     0;
          0  S2_y     0;
          0     0  S2_z];

% Matriz Na
Na = [         1   theta_a_xy   theta_a_xz;
      theta_a_yx            1   theta_a_yz;
      theta_a_zx   theta_a_zy            1;];
  
  
%% Tentativa de criar matriz de correção
K    = eye(3) + S1 + Na;

% Determinação dos parâmetros 'Delta'. 
Dx = [1/K(1,1),  -K(1,2)/K(1,1),  -K(1,3)/K(1,1), -S2(1,1)/K(1,1)];
Dy = [1/K(2,2),  -K(2,1)/K(2,2),  -K(2,3)/K(2,2), -S2(2,2)/K(2,2)];
Dz = [1/K(3,3),  -K(3,1)/K(3,3),  -K(3,2)/K(3,3), -S2(3,3)/K(3,3)];

% Importando dados
D =  importdata('x_up.txt');

for i = 1:max(size(D))
    f_meas = D(i,:);
    tic;
    [x(i), y(i), z(i), interation(i)] = convergence(Dx, Dy, Dz, f_meas, ba);
    t(i) = toc;
end


% Imprime o resultado num arquivo '*.txt'.
FILE = fopen('output_calib_acc.txt', 'w');

% Matrix X.
fprintf(FILE, "+---------------------------------------+\n");
fprintf(FILE, "|                                       |\n");
fprintf(FILE, "|  Parâmetros da calibração do MPU6050  |\n");
fprintf(FILE, "|                                       |\n");
fprintf(FILE, "+---------------------------------------+\n\n");
fprintf(FILE, "bx ....: ");
fprintf(FILE, "%2.10f\n", bx);
fprintf(FILE, "fx ....: ");
for i = 1:4
    if (i ~=  4)
        fprintf(FILE,' %2.10f, ', Dx(i));        
    else
        fprintf(FILE,' %2.10f', Dx(i));        
    end
end

fprintf(FILE, "\n\nby ....: ");
fprintf(FILE, "%2.10f\n", by);
fprintf(FILE, "fy ....: ");
for i = 1:4
    if (i ~=  4)
        fprintf(FILE,' %2.10f, ', Dy(i));
    else
        fprintf(FILE,' %2.10f', Dy(i));
    end
end

fprintf(FILE, "\n\nbz ....: ");
fprintf(FILE, "%2.10f\n", bz);
fprintf(FILE, "fz ....: ");
for i = 1:4
    if (i ~= 4)
        fprintf(FILE,' %2.10f, ', Dz(i));
    else
        fprintf(FILE,' %2.10f', Dz(i));
    end
end



fclose(FILE);



% plot(x);
% hold on;
% plot(D(:,1), 'r'); 
% grid;
% legend('Estimado', 'Medido');
% 
% 
% 
% figure;
% plot(y);
% hold on;
% plot(D(:,2), 'r'); 
% grid;
% legend('Estimado', 'Medido');
% 
% figure;
% plot(z);
% hold on;
% plot(D(:,3), 'r'); 
% grid;
% legend('Estimado', 'Medido');