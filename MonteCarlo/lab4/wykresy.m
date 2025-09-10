clear; clc; close all;
K1 = csvread("pkt_kolo1.csv");
K2 = csvread("pkt_kolo2.csv");

dane_a = csvread("dane_a.csv");
dane_b = csvread("dane_b.csv");
dane_c = csvread("dane_c.csv");
dane_d = csvread("dane_d.csv");

figure;
scatter(K1(:,1), K1(:,2),5, "filled","r")
hold on
scatter(K2(:,1), K2(:,2),5, "filled","b")
hold off
xlabel("x");
ylabel("y");
legend("Kolo \alpha", "Kolo \beta")


figure;
errorbar(dane_a(:,1),dane_a(:,2),dane_a(:,3),".")
set(gca, "XScale", "log")
hold on
errorbar(dane_c(:,1),dane_c(:,2),dane_c(:,3),".")
set(gca, "XScale", "log")
hold off
legend("\alpha = A", "\alpha = B")
xlabel("n")
ylabel("Powierzchnia wspólna")

figure;
errorbar(dane_b(:,1),dane_b(:,2),dane_d(:,3),".")
set(gca, "XScale", "log")
hold on
errorbar(dane_d(:,1),dane_d(:,2),dane_d(:,3),".")
set(gca, "XScale", "log")
hold off
legend("\alpha = A", "\alpha = B")
xlabel("n")
ylabel("Powierzchnia wspólna")