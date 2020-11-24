#!/bin/bash

dalej="t"
while [ $dalej = "t" ]
do
clear

echo -e "Wysylanie wiadomosci \n\nPodaj imie: "
read imie
echo "Podaj nazwisko: "
read nazwisko

if [ "$(cat dane.txt | grep -c "$imie $naziwsko")" > 0 ]
then

nr_tel=$(cat dane.txt | grep "$imie $nazwisko" | awk '{print $3}' )

echo "$nr_tel"

else
echo "Nie znaleziono osoby"

fi

echo "Chcesz kontynuowac? t/n"
read dalej
done
./ksiazka.sh
