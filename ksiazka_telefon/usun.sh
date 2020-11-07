#!/bin/bash

clear
echo -e "Usuwanie kontaktu\n\tLista osob:"

cat dane.txt

echo -e "\nPodaj imie i nr telefonu osoby ktora chcesz usunac"
read imie_szuk nazwisko_szuk tel_szuk

touch dane_temp.txt

while read imie nazwisko tel
do
    if [ "$imie" == "$imie_szuk" ] && [ "$tel" == "$tel_szuk" ] && \
[ "$nazwisko" == "$nazwisko_szuk" ];
    then
	kanalia=1
    else
	echo "$imie $nazwisko $tel" >> dane_temp.txt
    fi
done < dane.txt

case "$kanalia" in
    1)
	rm dane.txt
	mv dane_temp.txt dane.txt
	echo "Podany kontakt zostal usuniety"
	;;
    *)
	rm dane.txt
	mv dane_temp.txt dane.txt
	echo "Nie znaleziono osoby"
	;;
esac
