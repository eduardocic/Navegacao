function [P_k, K_k] = kalman_calib(phi_k, P_k_1, Q_k, R_k, C, I)

    % Equação de Riccati.
    M   = phi_k * P_k_1 * phi_k' + Q_k;
    K_k = M * (C') * inv(C * M * (C') + R_k);
    P_k = (I - K_k * C) * M;       
end