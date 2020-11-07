#!/bin/bash

echo "Dodawanie danych"
dalej="t"
while [ "$dalej" = "t" ]
do
    clear
    echo  "Podaj imie"
    read imie
    echo "Podaj naziwkso"
    read nazwisko
    echo "Podaj nr telefonu (+48-xxx-xxx-xxx)"
    read tel

    while read imie_baza nazwisko_baza tel_baza
    # program sprawdza tylko wzgledem nr telefonu
    # bo imie/nazwisko moze sie powtarzac
    do
	if [ "$tel" == "$tel_baza" ]
	then
	    dodaj_dane=0
        fi
    done < dane.txt

case "$dodaj_dane" in
    0)
	echo "W bazie danych istnieje osoba z podanym nr telefonu"
	;;
    *)
	echo "$imie $nazwisko $tel" >> dane.txt
	echo -e "Dodano $imie, $nazwisko, $tel"
	;;
esac

echo "Czu chcesz kontynuowac dodawanie osob? t/n"
read dalej
done
