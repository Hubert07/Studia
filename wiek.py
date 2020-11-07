#!bin/python
# -*- coding: utf-8 -*-

from datetime import date

today = date.today()

teraz = int(today.strftime("%Y"))

check = False

while(check is False):
    try:
        urodz = int(input("Podaj rok urodzenia: "))
        if(urodz > 0):
            check = True
        else:
            print("Powinienes dawno umrzec, oszuscie")
    except:
        print("Podana wartosc jest nieprawidlowa")

wiek = teraz - urodz
if(wiek > 4 and wiek < 22):
    print("masz ", wiek, "lat")
else:
    if(wiek%10 > 1 and wiek%10 < 5):
        print("masz", wiek, "lata")
    else:
        print("masz", wiek, "lat")

