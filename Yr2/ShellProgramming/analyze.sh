#!/bin/sh

#loop through files and output desired information
list="`ls | grep -o '7Eleven_\d\d\d\d\d_\d\d\d\d-\d\d-\d\d.log'`"
for file in ${list}
do
	echo ${file}":"
	cat ${file} | cut -d"," -f2 ${file}| sort | uniq -c | sort -nr | head -n3
done