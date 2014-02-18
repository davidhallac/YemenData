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
	cout << counter << "\n";*/




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
	cout << counter << "\n";*/



	//DESTINATION LOCATION INFO
	/*int counter1 = 0;
	int counter2 = 0;
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if (strncmp (PhoneLoad[i].getLocDest().CStr(), "", 1) != 0 && strncmp (PhoneLoad[i].getLocSrc().CStr(), "", 1) != 0 && PhoneLoad[i].getDuration() == 1)
		{
			counter1++;
		}
		else if (strncmp (PhoneLoad[i].getLocDest().CStr(), "", 1) != 0 && strncmp (PhoneLoad[i].getLocSrc().CStr(), "", 1) != 0 && PhoneLoad[i].getDuration() > 1)
		{
			counter2++;
		}
	}	
	char subbuff[9];
	memcpy( subbuff, &(argv[1])[13], 8 );
	subbuff[8] = '\0';
	cout << subbuff << "\n";
	//Write to file (append)
	ofstream fileout;
	fileout.open("startTimes.csv", ios::app);
	fileout << subbuff;
	fileout << ",";
	fileout << counter1;
	fileout << ",";
	fileout << counter2;
	fileout << ",";
	fileout << PhoneLoad.Len();
	fileout << "\n";*/


















	//GENERAL TABLE STATISTICS
	/*int total = PhoneLoad.Len();
	int counterPhone = 0;
	int counterText = 0;
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if (PhoneLoad[i].getDuration() > 1)
		{
			counterPhone++;
		}
		else if(PhoneLoad[i].getDuration() == 1)
		{
			counterText++;
		}
	}
	char subbuff[9];
	memcpy( subbuff, &(argv[1])[13], 8 );
	subbuff[8] = '\0';
	cout << subbuff << "\n";
	//Write to file (append)
	ofstream fileout;
	fileout.open("startTimes.csv", ios::app);
	fileout << subbuff;
	fileout << ",";
	fileout << total;
	fileout << ",";
	fileout << counterPhone;
	fileout << ",";
	fileout << counterText;
	

	//Tower Set 1 (closer)
	counterPhone = 0;
	counterText = 0;
	total = 0;
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if(strncmp (PhoneLoad[i].getLocSrc().CStr(), "", 1) != 0)
		{
			if (strncmp (PhoneLoad[i].getLocSrc().CStr(), "4210275302948", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "4210275302949", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "421027530294A", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A0282948", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A0282949", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A028294A", 13) == 0)
			{
				total++;
				if (PhoneLoad[i].getDuration() > 1)
				{
					counterPhone++;
				}
				else if(PhoneLoad[i].getDuration() == 1)
				{
					counterText++;
				}
			}
		}
	}
	fileout << ",";
	fileout << total;
	fileout << ",";
	fileout << counterPhone;
	fileout << ",";
	fileout << counterText;
	//Same thing but with LocDest
	counterPhone = 0;
	counterText = 0;
	total = 0;
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if(strncmp (PhoneLoad[i].getLocDest().CStr(), "", 1) != 0)
		{
			if (strncmp (PhoneLoad[i].getLocDest().CStr(), "4210275302948", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "4210275302949", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "421027530294A", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A0282948", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A0282949", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A028294A", 13) == 0)
			{
				total++;
				if (PhoneLoad[i].getDuration() > 1)
				{
					counterPhone++;
				}
				else if(PhoneLoad[i].getDuration() == 1)
				{
					counterText++;
				}
			}
		}
	}
	fileout << ",";
	fileout << total;
	fileout << ",";
	fileout << counterPhone;
	fileout << ",";
	fileout << counterText;


	//Tower Set 2 (farther)
	counterPhone = 0;
	counterText = 0;
	total = 0;
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if(strncmp (PhoneLoad[i].getLocSrc().CStr(), "", 1) != 0)
		{
			if (strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028CF", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028D0", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028D1", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028D2", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828CF", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828D0", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828D1", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828D2", 13) == 0)
			{
				total++;
				if (PhoneLoad[i].getDuration() > 1)
				{
					counterPhone++;
				}
				else if(PhoneLoad[i].getDuration() == 1)
				{
					counterText++;
				}
			}
		}
	}
	fileout << ",";
	fileout << total;
	fileout << ",";
	fileout << counterPhone;
	fileout << ",";
	fileout << counterText;
	//Same but with LocDest
	counterPhone = 0;
	counterText = 0;
	total = 0;
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if(strncmp (PhoneLoad[i].getLocDest().CStr(), "", 1) != 0)
		{
			if (strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028CF", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028D0", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028D1", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028D2", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828CF", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828D0", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828D1", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828D2", 13) == 0)
			{
				total++;
				if (PhoneLoad[i].getDuration() > 1)
				{
					counterPhone++;
				}
				else if(PhoneLoad[i].getDuration() == 1)
				{
					counterText++;
				}
			}
		}
	}
	fileout << ",";
	fileout << total;
	fileout << ",";
	fileout << counterPhone;
	fileout << ",";
	fileout << counterText;
	fileout << "\n";*/








	//START TIMES MAY 24th 2010
	/*int counter = 0;
	int thresholds [] = {0, 1500, 3000, 4500, 10000, 11500, 13000, 14500, 20000, 21500, 23000, 24500, 30000, 31500, 33000, 34500, 40000, 41500, 43000, 44500, 50000, 51500, 53000, 54500, 60000, 61500, 63000, 64500, 70000, 71500, 73000, 74500, 80000, 81500, 83000, 84500, 90000, 91500, 93000, 94500, 100000, 101500, 103000, 104500, 110000, 111500, 113000, 114500, 120000, 121500, 123000, 124500, 130000, 131500, 133000, 134500, 140000, 141500, 143000, 144500, 150000, 151500, 153000, 154500, 160000, 161500, 163000, 164500, 170000, 171500, 173000, 174500, 180000, 181500, 183000, 184500, 190000, 191500, 193000, 194500, 200000, 201500, 203000, 204500, 210000, 211500, 213000, 214500, 220000, 221500, 223000, 224500, 230000, 231500, 233000, 234500, 240000};
	uint totals [96] = {0};
	
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if(PhoneLoad[i].getDuration() == 1)
		{
			//Tower 1, both directions
			if (strncmp (PhoneLoad[i].getLocDest().CStr(), "4210275302948", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "4210275302949", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "421027530294A", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A0282948", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A0282949", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A028294A", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "4210275302948", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "4210275302949", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "421027530294A", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A0282948", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A0282949", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A028294A", 13) == 0)
			//Tower 2, both directions
			//if (strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028CF", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028D0", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028D1", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102753028D2", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828CF", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828D0", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828D1", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A02828D2", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028CF", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028D0", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028D1", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102753028D2", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828CF", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828D0", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828D1", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A02828D2", 13) == 0)
			{
				counter++;
				for(int j=0; j < (sizeof(thresholds)/sizeof(int)); j++)
				{
					if (PhoneLoad[i].getTime() >= thresholds[j] && PhoneLoad[i].getTime() < thresholds[j+1])
					{
						totals[j] = totals[j] + 1;
						break;
					}
				}
			}
		}
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
	fileout << counter;
	for (int j = 0; j < 96; j++)
	{
		fileout << ",";
		fileout << totals[j];
	}
	fileout << "\n";*/







	//UNIQUE USERS AT ONE TOWER
	/*int total = PhoneLoad.Len();	
	TVec<TUInt64> sourcesList(2*total, 0);
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		if (strncmp (PhoneLoad[i].getLocDest().CStr(), "4210275302948", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "4210275302949", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "421027530294A", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A0282948", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A0282949", 13) == 0 || strncmp (PhoneLoad[i].getLocDest().CStr(), "42102A028294A", 13) == 0)
		{
			sourcesList.Add(PhoneLoad[i].getDest());
		}
		if (strncmp (PhoneLoad[i].getLocSrc().CStr(), "4210275302948", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "4210275302949", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "421027530294A", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A0282948", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A0282949", 13) == 0 || strncmp (PhoneLoad[i].getLocSrc().CStr(), "42102A028294A", 13) == 0)
		{
			sourcesList.Add(PhoneLoad[i].getSource());
		}
	}	
	sourcesList.Sort(true);
	cout << sourcesList.Len() << "\n";

	//Count number of unique elements
	int counter = 0; //First element is always unique
	for (int i = 1; i<= sourcesList.Len(); i++)
	{
		if(sourcesList[i] != sourcesList[i-1])
			counter++;

	}
	cout << counter << " unique\n";*/










	//ENTIRE 3-YEAR DATASET - Calls/Texts, plus unique users
	int total = PhoneLoad.Len();
	int counterPhone = 0;
	int counterText = 0;	
	TVec<TUInt64> sourcesList(2*total, 0);
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		sourcesList.Add(PhoneLoad[i].getDest());
		sourcesList.Add(PhoneLoad[i].getSource());

		if (PhoneLoad[i].getDuration() > 1)
		{
			counterPhone++;
		}
		else if(PhoneLoad[i].getDuration() == 1)
		{
			counterText++;
		}
	}	
	sourcesList.Sort(true);

	int counter = 1; //First element is always unique
	for (int i = 1; i<= sourcesList.Len(); i++)
	{
		if(sourcesList[i] != sourcesList[i-1])
			counter++;
	}

	char subbuff[9];
	memcpy( subbuff, &(argv[1])[13], 8 );
	subbuff[8] = '\0';
	cout << subbuff << "\n";
	//Write to file (append)
	ofstream fileout;
	fileout.open("startTimes.csv", ios::app);
	fileout << subbuff;
	fileout << ",";
	fileout << PhoneLoad.Len();
	fileout << ",";
	fileout << counterPhone;
	fileout << ",";
	fileout << counterText;
	fileout << ",";
	fileout << counter;
	fileout << "\n";




	//TGNUPlot Practice:
	/*TVec<TInt> intTest;
	TGnuPlot GP("Plots/plottest", "", true);
	GP.SetXYLabel("Fraction of observed data (P)", "Number of connected components");
	GP.AddPlot(intTest, intTest, "Influence cascade", "lw 2",true, false, false, false, false, false);
	GP.SavePng();*/

}




