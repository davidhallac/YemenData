//
//  analyze.cpp
//  YemenData
//
//  Created by David Hallac on 1/28/14.
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
	if (argc < 3)
	{
		cout << "Not enough arguments!" << "\n";
		return 0;
	}

	TVec<TPhoneCall> PhoneLoad;
	TFIn fin(argv[1]);
	PhoneLoad.Load(fin);


	//STATISTICS FOR SPECIFIC TOWER - 3 things to select:
	//tower IDs, call type to look at, and what you want to print to csv
	int counter = 0;
	int thresholds [] = {0, 1500, 3000, 4500, 10000, 11500, 13000, 14500, 20000, 21500, 23000, 24500, 30000, 31500, 33000, 34500, 40000, 41500, 43000, 44500, 50000, 51500, 53000, 54500, 60000, 61500, 63000, 64500, 70000, 71500, 73000, 74500, 80000, 81500, 83000, 84500, 90000, 91500, 93000, 94500, 100000, 101500, 103000, 104500, 110000, 111500, 113000, 114500, 120000, 121500, 123000, 124500, 130000, 131500, 133000, 134500, 140000, 141500, 143000, 144500, 150000, 151500, 153000, 154500, 160000, 161500, 163000, 164500, 170000, 171500, 173000, 174500, 180000, 181500, 183000, 184500, 190000, 191500, 193000, 194500, 200000, 201500, 203000, 204500, 210000, 211500, 213000, 214500, 220000, 221500, 223000, 224500, 230000, 231500, 233000, 234500, 240000};
	TVec<TPhoneCall> totals [96];

	//FILL IN TOWER IDS WITH TOWERS TO ANALYZE
	TVec<TStr> towerIDs;
	for (int j = 2; j < argc; j++)
	{
		towerIDs.Add(argv[j]);
	}

	for (int i=0; i < PhoneLoad.Len(); i++) 
	{
		//Look at calls only
		if(PhoneLoad[i].getDuration() > 1)
		{

			int meetsCondition = 0;
			for (int j=0; j < towerIDs.Len(); j++)
			{
				//UNCOMMENT THE OPTION YOU WANT
				//1) Outgoing calls
				//if(strncmp(PhoneLoad[i].getLocSrc().CStr(), towerIDs[j].CStr(), 13) == 0)
				//2) Incoming
				//if(strncmp(PhoneLoad[i].getLocDest().CStr(), towerIDs[j].CStr(), 13) == 0)
				//3) Either
				if(strncmp(PhoneLoad[i].getLocSrc().CStr(), towerIDs[j].CStr(), 13) == 0 || strncmp(PhoneLoad[i].getLocDest().CStr(), towerIDs[j].CStr(), 13) == 0)
				//4) Both (call stays within tower)
				//if(strncmp(PhoneLoad[i].getLocSrc().CStr(), towerIDs[j].CStr(), 13) == 0 && strncmp(PhoneLoad[i].getLocDest().CStr(), towerIDs[j].CStr(), 13) == 0)
				{
					meetsCondition = 1;
					break;
				}
			}
			if(meetsCondition)
			{
				counter++;
				for(int j = 0; j < 96; j++)
				{
					if (PhoneLoad[i].getTime() >= thresholds[j] && PhoneLoad[i].getTime() < thresholds[j+1])
					{
						totals[j].Add(PhoneLoad[i]);
						break;
					}
				}
			}

		}
	}
	//Now, analyze TVecs, broken down by start time
	char subbuff[9];
	memcpy( subbuff, &(argv[1])[13], 8 );
	subbuff[8] = '\0';
	cout << subbuff << "\n";
	ofstream fileout;
	fileout.open("startTimes.csv", ios::app);
	fileout << subbuff;
	fileout << ",";
	fileout << counter;
	for (int i=0; i < 96; i++)
	{
		//WriteVal is what you write to file
		int writeVal = 0;

		//UNCOMMENT THE SELECTION YOU WANT
		//Average duration
		/*int totalSum = 0;
		int counterSum = 0;
		if (totals[i].Len() > 0)
		{
			for(int j = 0; j < totals[i].Len(); j++)
			{
				if(totals[i][j].getDuration() < 1799 || totals[i][j].getDuration() > 1801)
				{
					totalSum += totals[i][j].getDuration();
					counterSum++;	
				}

			}
		}
		if(counterSum != 0)
			writeVal = totalSum / counterSum;*/
		

		//Average distance


		//Number of calls
		writeVal = totals[i].Len();

		fileout << ",";
		fileout << writeVal;
	}
	fileout << "\n";

	//Distance Distribution
	/*for(int i = 92; i < 96; i++)
	{
		for(int j = 0; j < totals[i].Len(); j++)
		{
			if(totals[i][j].getDuration() < 1799 || totals[i][j].getDuration() > 1801)
			{
				int writeVal = totals[i][j].getDuration();
				fileout << ",";
				fileout << writeVal;
			}
		}
	}
	fileout << "\n";*/

}




