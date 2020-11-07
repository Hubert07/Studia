 #!/bin/sh

if [ "$1" = "-h" ]

then

cat instrukcja.txt | less

else

echo -e "Cze $USER"

dalej="t"

while [ "$dalej" = "t" ] || [ "$dalej" = "tak" ]
do

echo -e "\nJezeli potrzebujesz pomocy wpisz '"help"' w dowolnym momencie.\nPodaj pierwsza liczbe"
read l1

echo "Podaj znak dzialania: (+, - , *, /)"
read znak

echo "Podaj druga liczba"
read l2

if [ "$l1" = "help" ] || [ "$l2" = "help" ] || [ "$znak" = "help" ]
then
    echo -e "\nZa chwile otworzy sie instrukcja, dane ktore wspiales to:\n $l1 $znak  $l2"
    sleep 5
    cat instrukcja.txt | less

else

case "$znak" in

    "+") echo "wynik z dodawania wynosi ="
    echo "scale=3; $l1+$l2" | bc;;

    "-") echo "wynik z odejmownaia wynosi ="
    echo "scale=3; $l1-$l2" | bc;;

    "*") echo "wynik z mnozenia wynosi ="
    echo "scale=3; $l1*$l2" | bc;;

    "/") echo "wynik z dzienie wynosi ="
    echo "scale=3; $l1/$l2" | bc;;

    *) echo " zly znak dzialania"

esac

fi

echo "Czy chcesz kontynuowac? t/n (tak/nie)"
read dalej

clear

done
fi
