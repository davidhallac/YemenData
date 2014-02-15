//
//  analyze.cpp
//  YemenData
//
//  Created by David Hallac on 1/28/14.
//  Copyright (c) 2014 David Hallac. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include "../../snap-core/Snap.h"
#include "process.h"
using namespace std;

int main(int argc, const char * argv[])
{
	if (argc < 2)
	{
		cout << "Not enough arguments!" << "\n";
		return 0;
	}

	TVec<TPhoneCall> PhoneLoad;
	//TFIn fin("20100501"); 
	TFIn fin(argv[1]);
	PhoneLoad.Load(fin);


	//DURATION

	/*int total = 6610258; //Total number of non-texts on 
	//int total = PhoneLoad.Len();
	int counter = 0;
	int thresholds [] = {1780, 1799, 1800, 1801,3500,3599,3601};

	for(int j=0; j < sizeof(thresholds)/sizeof(int); j++)
	{
		counter = 0;
		for (int i=0; i <= PhoneLoad.Len(); i++) 
		{
			if (PhoneLoad[i].getDuration() >= thresholds[j])
			{
				counter++;
			}
		}
		float percentage = counter*100;
		percentage = percentage/total;
		cout << percentage << ", " << counter << ", " << thresholds[j] << "\n";
		//cout << counter << "\n";
	}*/
	

	//START TIME
	/*int total = PhoneLoad.Len();
	int counter = 0;
	int thresholds [] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000, 210000, 220000, 230000,240000};
	float percentages [24];
	for(int j=0; j < sizeof(thresholds)/sizeof(int); j++)
	{
		counter = 0;
		for (int i=0; i <= PhoneLoad.Len(); i++) 
		{
			if (PhoneLoad[i].getTime() >= thresholds[j])
			{
				counter++;
			}
		}
		float percentage = counter*100;
		percentage = percentage/total;
		
		//cout << percentage << "\n";
		percentages[j] = percentage;
	}
	float marginals [24];
	marginals[0] = 100 - percentages[0];
	for(int j = 1; j < 24; j++)
	{
		marginals[j] = percentages[j-1] - percentages[j];
	}

	char subbuff[9];
	memcpy( subbuff, &(argv[1])[13], 8 );
	subbuff[8] = '\0';
	cout << subbuff << "\n";
	//Write marginals to file (append)
	ofstream fileout;
	fileout.open("startTimes.csv", ios::app);
	fileout << subbuff;
	fileout << ",";
	fileout << total;
	fileout << ",";
	fileout << marginals[0];
	for(int j = 1; j < 24; j++)
	{
		fileout << ",";
		fileout << marginals[j];
	}
	fileout << "\n";*/



	//SOURCE ID
	/*
	int total = PhoneLoad.Len();
	TVec<TUInt64> sources(total, 0);
	for (int i=0; i <= PhoneLoad.Len(); i++) 
	{
		sources.Add(PhoneLoad[i].getSource());
	}	
	sources.Sort(true);
	cout << sources.Len() << "\n";

	//Count number of elements matching a certain condition
	int counter = 0;
	for (int i = 0; i<= sources.Len(); i++)
	{
		if(sources[i] >= 967730000000 && sources[i] <= 967740000000)
			counter++;


	}
	cout << counter << "\n";
	cout << sources[1] << "\n";
	cout << sources[500000] << "\n";
	cout << sources[1000000] << "\n";
	cout << sources[2000000] << "\n";
	cout << sources[3000000] << "\n";
	cout << sources[4000000] << "\n";
	cout << sources[5000000] << "\n";*/




	//DESTINATION ID
	/*int total = PhoneLoad.Len();
	TVec<TUInt64> sourcesDest(total, 0);
	for (int i=0; i <= PhoneLoad.Len(); i++) 
	{
		sourcesDest.Add(PhoneLoad[i].getDest());
	}	
	sourcesDest.Sort(true);
	cout << sourcesDest.Len() << "\n";

	//Count number of unique elements
	int counter = 0; //First element is always unique
	for (int i = 1; i<= sourcesDest.Len(); i++)
	{
		if(sourcesDest[i] != sourcesDest[i-1])
			counter++;

	}
	cout << counter << "unique";

	counter = 0;
	for (int i = 0; i< sourcesDest.Len(); i++)
	{
		if(sourcesDest[i] > 967730000000 && sourcesDest[i] < 967740000000 )
			counter++;

	}
	cout << counter << "\n";
	cout << sourcesDest[1] << "\n";
	cout << sourcesDest[500000] << "\n";
	cout << sourcesDest[1000000] << "\n";
	cout << sourcesDest[2000000] << "\n";
	cout << sourcesDest[3000000] << "\n";*/



	//DESTINATION LOCATION INFO
	/*int counter = 0;
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if (strncmp (PhoneLoad[i].getLocSrc().CStr(), "", 1) != 0 && PhoneLoad[i].getDuration() > 1)
		{
			counter++;
		}
	}	
	cout << counter << "\n";
	cout << PhoneLoad.Len() << "\n";*/

}




