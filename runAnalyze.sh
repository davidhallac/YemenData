#!/bin/bash

make analyze

#Nested for loops, for each month, analyze each day

#months=(Jan2010 Feb2010 Mar2010 Apr2010 May2010 Jun2010 Jul2010 Aug2010 Sep2010 Oct2010 Nov2010 Dec2010 Jan2011 Feb2011 Mar2011 Apr2011 May2011 Jun2011 Jul2011 Aug2011 Sep2011 Oct2011 Nov2011 Dec2011 Jan2012 Feb2012 Mar2012 Apr2012 May2012 Jun2012 Jul2012 Aug2012 Sep2012 Oct2012 Nov2012 Dec2012 Jan2013)
months=()
for month in ${months[@]}
do

for file in data/$month/*
do

    ./analyze $file startTimes.csv

done
done

#TODO: Better way to do this
#Analyze May 24th, 2010 Drone Strike
#./analyze data/May2010/20100503
#./analyze data/May2010/20100510
#./analyze data/May2010/20100517
#./analyze data/May2010/20100524
#./analyze data/May2010/20100531
#./analyze data/Jun2010/20100607
#./analyze data/Jun2010/20100614
#./analyze data/May2010/20100504
#./analyze data/May2010/20100511
#./analyze data/May2010/20100518
#./analyze data/May2010/20100525
#./analyze data/Jun2010/20100601
#./analyze data/Jun2010/20100608
#./analyze data/Jun2010/20100615

#Analyze Al-Alwaki Strike (9/30/2011)
./analyze data/Sep2011/20110909
./analyze data/Sep2011/20110916
./analyze data/Sep2011/20110923
./analyze data/Sep2011/20110930
./analyze data/Oct2011/20111007
./analyze data/Oct2011/20111014
./analyze data/Oct2011/20111021
./analyze data/Sep2011/20110910
./analyze data/Sep2011/20110917
./analyze data/Sep2011/20110924
./analyze data/Oct2011/20111001
./analyze data/Oct2011/20111008
./analyze data/Oct2011/20111015
./analyze data/Oct2011/20111022

#Analyze Zinjibar Strike (6/3/2011)




