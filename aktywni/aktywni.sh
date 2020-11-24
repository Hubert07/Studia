#!/bin/bash

./roblog.sh
# porownuje kazdy zapisany juz login z kazdym loginem z chwili biezacej
while read login
do
    if [ "$(cat log.txt | grep -c "$login")" = 1  ]
    then
	continue
    else
	echo "$login" >> log2.txt
    fi
done < log_temp.txt

rm log.txt
rm log_temp.txt
mv log2.txt log.txt

status=$(cat log.txt)
email=aaa@email.com

echo -e "Oto lista aktywnych uzytkownikow:\n$status" | mutt -s\
 "Aktywni" $email
echo "Wiadomosc zostala wyslana"
