% =========================================================================
% (*) O que este programa faz é simplesmente ler os arquivos do tipo 
%     '*.txt', separando-os no seguinte formato:
%     
%     1. o 'm' é para simbolizar a medida (measurement);
%     2. o primeiro 'x', 'y' ou 'z', junto ao 'm', é para simbolizar que a
%        medida é obtida naquele determinado eixo;
%     3. o '*_up' ou '*_down' é para simbolizar se o eixo em questão está
%        apontado para cima ou para baixo. 
%
%     Exemplo:
%      
%     -- o 'mx_x_up' é a forma de simbolizar as medidas captadas pelo
%        acelerômetro 'x' quando o eixo 'x' apontava para cima.
%  
% Eduardo H Santos. 
% 13/03/2023
% =========================================================================



clear all; close all; clc; 



%  Arquivos calibração em X
% ==========================
D = importdata('x_up.txt');
mx_x_up = D(:,1);
my_x_up = D(:,2);
mz_x_up = D(:,3);

clear D;
D = importdata('x_down.txt');
mx_x_down = D(:,1);
my_x_down = D(:,2);
mz_x_down = D(:,3);

%  Arquivos calibração em Y
% ==========================
D = importdata('y_up.txt');
mx_y_up = D(:,1);
my_y_up = D(:,2);
mz_y_up = D(:,3);

clear D;
D = importdata('y_down.txt');
mx_y_down = D(:,1);
my_y_down = D(:,2);
mz_y_down = D(:,3);


%  Arquivos calibração em Z
% ==========================
D = importdata('z_up.txt');
mx_z_up = D(:,1);
my_z_up = D(:,2);
mz_z_up = D(:,3);

clear D;
D = importdata('z_down.txt');
mx_z_down = D(:,1);
my_z_down = D(:,2);
mz_z_down = D(:,3);

clear D;
% =========================================================================
% =========================================================================
% =========================================================================

%%% X UP
for i = 1:max(size(mx_x_up))
    mx(i) = sum(mx_x_up(1:i))/i;
    my(i) = sum(my_x_up(1:i))/i;
    mz(i) = sum(mz_x_up(1:i))/i;
end
fx_x_up = mean(mx(400:end));
fy_x_up = mean(my(400:end));
fz_x_up = mean(mz(400:end));

%%% X DOWN
clear mx my mz
for i = 1:max(size(mx_x_down))
    mx(i) = sum(mx_x_down(1:i))/i;
    my(i) = sum(my_x_down(1:i))/i;
    mz(i) = sum(mz_x_down(1:i))/i;
end
fx_x_down = mean(mx(400:end));
fy_x_down = mean(my(400:end));
fz_x_down = mean(mz(400:end));

%%% Y UP
for i = 1:max(size(mx_y_up))
    mx(i) = sum(mx_y_up(1:i))/i;
    my(i) = sum(my_y_up(1:i))/i;
    mz(i) = sum(mz_y_up(1:i))/i;
end
fx_y_up = mean(mx(400:end));
fy_y_up = mean(my(400:end));
fz_y_up = mean(mz(400:end));

%%% Y DOWN
clear mx my mz
for i = 1:max(size(mx_y_down))
    mx(i) = sum(mx_y_down(1:i))/i;
    my(i) = sum(my_y_down(1:i))/i;
    mz(i) = sum(mz_y_down(1:i))/i;
end
fx_y_down = mean(mx(400:end));
fy_y_down = mean(my(400:end));
fz_y_down = mean(mz(400:end));


%%% Z UP
for i = 1:max(size(mx_z_up))
    mx(i) = sum(mx_z_up(1:i))/i;
    my(i) = sum(my_z_up(1:i))/i;
    mz(i) = sum(mz_z_up(1:i))/i;
end
fx_z_up = mean(mx(400:end));
fy_z_up = mean(my(400:end));
fz_z_up = mean(mz(400:end));

%%% Z DOWN
clear mx my mz
for i = 1:max(size(mx_z_down))
    mx(i) = sum(mx_z_down(1:i))/i;
    my(i) = sum(my_z_down(1:i))/i;
    mz(i) = sum(mz_z_down(1:i))/i;
end
fx_z_down = mean(mx(400:end));
fy_z_down = mean(my(400:end));
fz_z_down = mean(mz(400:end));

% Salva os parâmetros médios obtidos pelo sustema.
save('calib_acc.mat', ...
     'fx_x_up',   'fy_x_up',   'fz_x_up'  ,...
     'fx_x_down', 'fy_x_down', 'fz_x_down',...
     'fx_y_up',   'fy_y_up',   'fz_y_up'  ,...
     'fx_y_down', 'fy_y_down', 'fz_y_down',...
     'fx_z_up',   'fy_z_up',   'fz_z_up'  ,...
     'fx_z_down', 'fy_z_down', 'fz_z_down');

 clear all; clc;





