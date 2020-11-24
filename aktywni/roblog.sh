#!/bin/bash

touch log2.txt
who > log_temp.txt
cat log_temp.txt | awk '{print $1}' > log_temp2.txt
rm log_temp.txt
mv log_temp2.txt log_temp.txt
