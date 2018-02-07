#!/bin/sh

# Create the output file
touch ${1}.log

# Loop through all store logs and append them to a temporary log
list="`ls | grep -o '7Eleven_\d\d\d\d\d_\d\d\d\d-\d\d-\d\d.log'`"
for file in ${list}
do	
	cat ${file} | grep ${1} >> temp.log
done

# Sort the log file in ascending order and save it into the output log
sort temp.log -n > ${1}.log

# Delete the temporary log
rm temp.log

# Checks if the log file is empty, and deletes if it is
if ! [ -s ${1}.log ]
then
	echo "No records found for $1"
	rm ${1}.log
fi 