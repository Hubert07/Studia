clear; clc; close all;
histy = csvread("histogramy_data2.csv");

h1 = histy(:,1);
h2 = histy(:,2);
h3 = histy(:,3);
h4 = histy(:,4);

x = [0.05:0.1:1];

xfun = 0:0.001:1;
yfun = (4/5)*(1 + xfun - xfun.^3);

subplot(2,2,1)
bar(x,h1,'hist','w');
hold on
plot(xfun, yfun,'r');
hold off
title("Rozkład złożony");

subplot(2,2,2)
bar(x,h2,'hist');
hold on
plot(xfun, yfun,'r');
hold off
title("Łańcuch Markowa \Delta = 0.5");

subplot(2,2,3)
bar(x,h3,'hist');
hold on
plot(xfun, yfun,'r');
hold off
title("Łańcuch Markowa \Delta = 0.05");

subplot(2,2,4)
bar(x,h4,'hist','w');
hold on
plot(xfun, yfun,'r');
hold off
title("Metoda eliminacji");



