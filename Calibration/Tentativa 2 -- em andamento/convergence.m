function [fx, fy, fz, i] = convergence(Dx, Dy, Dz, fm, ba)

% Chute inicial
fx = fm(1);
fy = fm(2);
fz = fm(3);
norma(1) = sqrt(fx^2 + fy^2 + fz^2);

for i = 2:10
    fx = Dx(1,1)*(fm(1) - ba(1)) + Dx(1,2)*fy + Dx(1,3)*fz + Dx(1,4)*fx*fx;
    fy = Dy(1,1)*(fm(2) - ba(2)) + Dy(1,2)*fx + Dy(1,3)*fz + Dy(1,4)*fy*fy;
    fz = Dx(1,1)*(fm(3) - ba(3)) + Dz(1,2)*fx + Dz(1,3)*fy + Dz(1,4)*fz*fz;
    
    norma(i) = sqrt(fx^2 + fy^2 + fz^2);
    
%     disp(['Iteração', num2str(i) ' -- Medidas: ' num2str(x), ', ', num2str(y), ', ', num2str(z)]);
    if( abs(norma(i) - norma(i-1)) < 10^-10)
%         disp(['Medidas: ' num2str(x), ', ', num2str(y), ', ', num2str(z)]);
        break
    end
end
i = i-1;

end