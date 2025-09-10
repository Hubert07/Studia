clear; close all; clc;

p1 = cell2mat(readcell("DaneP01.csv"));
p2 = cell2mat(readcell("DaneP05.csv"));
p3 = cell2mat(readcell("DaneP09.csv"));

x = p1(:,1);
blad_wzgl_sr = [p1(:,6)'; p2(:,6)'; p3(:,6)'];
blad_wzgl_var = [p1(:,7)'; p2(:,7)'; p3(:,7)'];

figure;
loglog(x,blad_wzgl_sr')
legend("p = 0.1", "p = 0.5", "p = 0.9");
xlabel("n");
ylabel("Błąd względny wartości średniej")

figure;
loglog(x,blad_wzgl_var')
legend("p = 0.1", "p = 0.5", "p = 0.9");
xlabel("n");
ylabel("Błąd względny wariancji")