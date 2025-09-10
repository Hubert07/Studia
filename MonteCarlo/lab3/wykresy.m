clear; clc; close all;
P1 = csvread("dane1.csv");
P2 = csvread("dane2.csv");
P3 = csvread("dane3.csv");
P4 = csvread("dane4.csv");

figure;
plot(P1(1,:), P1(2,:), '.')
xlabel("x");
ylabel("y");

figure;
plot(P2(1,:), P2(2,:), '.')
xlim([-1.1 1.1]);
ylim([-1.1 1.1]);
xlabel("x");
ylabel("y");

figure;
plot(P3(1,:), P3(2,:), '.')
xlim([-1 1]);
ylim([-1 1]);
xlabel("x");
ylabel("y");

figure;
plot(P4(1,:), P4(2,:), '.')
%xlim([-1 1]);
%ylim([-1 1]);
xlabel("x");
ylabel("y");