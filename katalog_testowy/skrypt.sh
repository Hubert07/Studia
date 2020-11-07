#!/bin/bash

echo "witaj"
echo "que tal?"

echo "zawartosc katalogu przed touch"
slepp 3
ls -l

echo "tworze plik"

touch plik_ze_skryptu

echo "zawartosc po dodaniu pliku"
sleep 2
ls -l

finger Jan > plik_ze_skryptu

chmod 755 plik_ze_skryptu
