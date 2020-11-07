#!/bin/bash

clear
echo "Wyszukiwarka osoob"
echo "Wpisz imie lub/i nazwisko osoby ktora chcesz znalezc:"
read dana

spr=`grep "$dana" dane.txt`
if [ -z  "$spr" ]
then
    echo "Brak kontaktu spelniajacego kryteria"
else
    grep "$dana" dane.txt
fi
