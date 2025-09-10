clear; close all; clc;

x = rand([100000 1]);
rozklad = zeros(100000,1);

for i = 1:length(rozklad)
    rozklad(i) = sqrt(-2*log(x(i)))*sin(2*pi*rand());
end

histogram(rozklad,100)