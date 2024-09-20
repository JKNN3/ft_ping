#!/bin/bash

#IFS='\n'

#colors:
green="\e[32m"
red="\e[31m"
yellow="\e[93m"
endcolor="\e[0m"
filename=tests.txt

while read -r line; do
	ping $line > test_result_ping.txt
	../ft_ping $line > test_result_ft_ping.txt

	sed -e 's/[0-9]\{1,4\}\.[0-9]\{3\}/&/' test_result_ping.txt > test_result_ping_sed.txt
	
	sed -e 's/[0-9]\{1,4\}\.[0-9]\{3\}/&/' test_result_ft_ping.txt > test_result_ft_ping_sed.txt

	if ! diff -I 'round-trip*' test_result_ping_sed.txt test_result_ft_ping_sed.txt
	then
		echo -e "test :$yellow $line $red NOT PASSED $endcolor"
	else
		echo -e "test $yellow $line $green PASSED $endcolor"
	fi
done < $filename

