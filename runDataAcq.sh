#! /bin/bash

echo $1
echo $2

# Parse command line filename
filebase="$1"
n="$2"

# Increment over the number we want
for (( i = 0; i < n; i++ )); do
	printf -v filename "%s-%03d.dat" "$filebase" $i
	echo $filename

	/home/selena/Documents/UWTopMetalDrone/topMetalDrone -o $filename 
done



# run 