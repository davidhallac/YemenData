#!/bin/bash

#Make appropriate directories
#monthsdir=(Jan2010 Feb2010 Mar2010 Apr2010 May2010 Jun2010 Jul2010 Aug2010 Sep2010 Oct2010 Nov2010 Dec2010)
#for month in ${monthsdir[@]}
#do
#mkdir data/$month
#done

make

#Process each month
#years=(2010 2011 2012)
years=()
for year in ${years[@]}
do
./process ../../../ZipFiles/JANUARY_$year.zip data/Jan$year/
./process ../../../ZipFiles/FEBRUARY_$year.zip data/Feb$year/
./process ../../../ZipFiles/MARCH_$year.zip data/Mar$year/
./process ../../../ZipFiles/APRIL_$year.zip data/Apr$year/
./process ../../../ZipFiles/MAY_$year.zip data/May$year/
./process ../../../ZipFiles/JUNE_$year.zip data/Jun$year/
./process ../../../ZipFiles/JULY_$year.zip data/Jul$year/
./process ../../../ZipFiles/AUGUST_$year.zip data/Aug$year/
./process ../../../ZipFiles/SEPTEMBER_$year.zip data/Sep$year/
./process ../../../ZipFiles/OCTOBER_$year.zip data/Oct$year/
./process ../../../ZipFiles/NOVEMBER_$year.zip data/Nov$year/
./process ../../../ZipFiles/DECEMBER_$year.zip data/Dec$year/
done
#Don't forget Jan 2013
#./process ../../../ZipFiles/JANUARY_2013.zip data/Jan2013

#Nested for loops, for each month, analyze each day
#months=(Jan2010 Feb2010 Mar2010 Apr2010 May2010 Jun2010 Jul2010 Aug2010 Sep2010 Oct2010 Nov2010 Dec2010)
months=()
for month in ${months[@]}
do

for file in data/$month/*
do

    ./analyze $file startTimes.csv

done
done


#Analyze each drone strike
while read line           
do           
    ./analyze $line
    echo "./analyze $line"           
done < StrikeData.csv
