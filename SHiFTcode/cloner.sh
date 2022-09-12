#!/bin/sh
# unocomment the following line to see the command passed to bash
#set -x  

if [ "$#" -ne 4 ]; then
    echo "Illegal number of parameters"
    echo "USAGE: ./cloner -s [source] -d [destination] "
    exit
fi


while getopts s:d: flag
do
    case "${flag}" in
        s) source=${OPTARG};;
        d) destination=${OPTARG};;    
    esac
done
#echo "Username: $username";
#echo "Age: $age";
#echo "Full Name: $fullname";

cp -R "$source" "$destination"
cd  "$destination"
rm -rf ./Debug
mv *.ioc $(basename $destination).ioc
#find . -name "*.launch" -exec rm -rf {} \;
#find . -name "*.bin" -exec rm -rf {} \;
#find . -name "*.elf" -exec rm -rf {} \;
#find . -name "*.o" -exec rm -rf {} \;


old=$(basename $source)
new=$(basename $destination)

find ./ -type f -exec sed -i "s/$old/$new/g" {} \;