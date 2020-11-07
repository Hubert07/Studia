#!/bin/bash

clear

if [ "$1" = "-h" ] || [ "$1" = "-?" ]

then
    cat instrukcja.txt | less
else

dalej="t"

while [ "$dalej" = "t" ] || [ "$dalej" = "tak" ]
do
echo "To jest ksiazka telefoniczna"

echo "Co chcesz zrobic?"

echo -e "\tl. Dodac nowy kontakt;"
echo -e "\t2. Wyswietl dane;"
echo -e "\t3. Sortuj dane"
echo -e "\t4. Wyszukaj osobe"
echo -e "\t5. Usun osobe"
echo -e "\t9. Pomoc"
echo -e "\t0. Wyjsce z porgoramu"
echo "Podaj nr (0-9)"

read menu

case "$menu" in
    1)
    	./dodawanie_danych.sh
    ;;
    2)
    	cat dane.txt | less
    ;;
    3)
	sort -d dane.txt
    ;;
    4)
	./szukaj.sh
    ;;
    5)
	./usun.sh
    ;;
    9)

	cat instrukcja.txt | less
    ;;
    0)
	clear
        echo "Dziekuje za skorzystanie z programu"
	exit
    ;;
    *)
        echo "Zly wybor";;
esac

echo "Czy chcesz kontynuowac? t/n (tak/nie)"
read dalej
clear

done

fi
