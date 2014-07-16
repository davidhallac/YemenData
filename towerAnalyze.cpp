//
//  towerAnalyze.cpp
//  YemenData
//
//  Created by David Hallac on 7/12/14.
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
	TFIn fin(argv[1]);
	PhoneLoad.Load(fin);

	THash<TStr, TFlt> towerLoc; //Map ID --> Lat + 33*Long (unique hash)
	THash<TFlt, TInt> towerNumber; //Helper that maps towers to an in-order ID (0 to ~1100)
	TSsParser Ss("LocationTowers.csv", ssfCommaSep);
	while(Ss.Next())
	{
		//cout << Ss.GetFld(0) << Ss.GetFld(1) << Ss.GetFld(2) << "\n";
		towerLoc.AddDat(Ss.GetFld(0), 100000*(-7*(Ss.GetFlt(1)-13) + 29*(Ss.GetFlt(2)-40)));
	}

	TPt <TNodeNet<TInt> > Net = TNodeNet<TInt>::New();

	PUNGraph G = TUNGraph::New();
	THash<TStr, TFlt>::TIter NI = towerLoc.BegI();
	towerLoc.SortByDat(); //Sorts towers
	TInt towerCount = 0;
	while(!NI.IsEnd())
	{
		TFlt tow = NI.GetDat();
		if(!G->IsNode(tow))
		{
			G->AddNode(tow);
			towerNumber.AddDat(tow, towerCount);
			towerCount++;
		}
		
		NI.Next();
	}

	int countt = 0;
	for (TUNGraph::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) 
	{
		countt++;
    	//printf("node id %d with degree %d\n",
    	//NI.GetId(), NI.GetDeg());
  	} 
	cout << towerCount << "\n";

	for (int e = 0; e < 10000; e++) {
    const int NId1 = G->GetRndNId();
    const int NId2 = G->GetRndNId();
    G->AddEdge(NId1, NId2);
	}
	IAssert(G->IsOk());

	//STATISTICS FOR SPECIFIC TOWER - 3 things to select:
	//tower IDs, call type to look at, and what you want to print to csv
	int counter = 0;
	//int thresholds [] = {0, 1500, 3000, 4500, 10000, 11500, 13000, 14500, 20000, 21500, 23000, 24500, 30000, 31500, 33000, 34500, 40000, 41500, 43000, 44500, 50000, 51500, 53000, 54500, 60000, 61500, 63000, 64500, 70000, 71500, 73000, 74500, 80000, 81500, 83000, 84500, 90000, 91500, 93000, 94500, 100000, 101500, 103000, 104500, 110000, 111500, 113000, 114500, 120000, 121500, 123000, 124500, 130000, 131500, 133000, 134500, 140000, 141500, 143000, 144500, 150000, 151500, 153000, 154500, 160000, 161500, 163000, 164500, 170000, 171500, 173000, 174500, 180000, 181500, 183000, 184500, 190000, 191500, 193000, 194500, 200000, 201500, 203000, 204500, 210000, 211500, 213000, 214500, 220000, 221500, 223000, 224500, 230000, 231500, 233000, 234500, 240000};
	TVec<TPhoneCall> totals [96];

	int numtowers = 1126;
	int a [96][numtowers];
	memset( a, 0, 96*numtowers*sizeof(int) );
	for (int i=0; i < PhoneLoad.Len(); i++) 
	{

		//Look at calls only
		if(PhoneLoad[i].getDuration() > 1)
		{
			
			TFlt sourceTow = towerLoc.GetDat(PhoneLoad[i].getLocSrc().CStr()); 
			TFlt destTow = towerLoc.GetDat(PhoneLoad[i].getLocDest().CStr());
			
			if (sourceTow > 1 || sourceTow < -1)
			{
				a[PhoneLoad[i].getTime()/10000*4 + (PhoneLoad[i].getTime()%10000)/1500][towerNumber.GetDat(sourceTow)]++;

			}
			if (destTow > 1 || destTow < -1)
			{
				a[PhoneLoad[i].getTime()/10000*4 + (PhoneLoad[i].getTime()%10000)/1500][towerNumber.GetDat(destTow)]++;
			}

		}
	}

	int height = 96;
	int width = numtowers;
	for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            std::cout << a[i][j] << ' ';
        }
        std::cout << std::endl;
    }




	//Now, analyze TVecs, broken down by start time
	// char subbuff[9];
	// memcpy( subbuff, &(argv[1])[13], 8 );
	// subbuff[8] = '\0';
	// cout << subbuff << "\n";
	// ofstream fileout;
	// fileout.open("startTimes.csv", ios::app);
	// fileout << subbuff;
	// fileout << ",";
	// fileout << counter;
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

		// fileout << ",";
		// fileout << writeVal;
	}
	// fileout << "\n";

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




