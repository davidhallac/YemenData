//
//  main.cpp
//  YemenData
//
//  Created by David Hallac on 1/18/14.
//  Copyright (c) 2014 David Hallac. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "../../snap-core/Snap.h"
//#include "csv_v3.h"
#include "process.h"

using namespace std;

int main(int argc, const char * argv[])
{

	if (argc < 3)
	{
		cout << "Not enough arguments!" << "\n";
		return 0;
	}

	TSsParser Ss(argv[1], ssfCommaSep);
	TInt counter = 0;

	Ss.Next();
	while(!Ss.Eof())
	{
		TVec<TPhoneCall> PhoneV(15000000, 0);
		//Find Day of call
		TInt day = (TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt());
		
		while( !Ss.Eof() && ((TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt())) == day)
		{
			//Hash Table
			THash<TUInt64, TPhoneCall> repeatCalls;

			//To see how fast the code is running
			counter = counter + 1;
			if (counter % 1000000 == 1)
				cout << counter << ", " << Ss.GetFld(9) << "\n";		
			
			TPhoneCall call;
			TInt badcall = 0; 	//Flag for "bad" call

			TUInt64 src;
			TUInt64 dest;
			TStr locsrc;
			TStr locdest;

			if(Ss.GetInt(8) == 1)
			{
				//Source ID
				src = (TStr(Ss.GetFld(0))).GetUInt64();

				//Destination ID
				if(Ss.IsInt(5))
				{
					TUInt64 temp = (TStr(Ss.GetFld(5))).GetUInt64();
					//if(temp == 111 || temp == 8888 || temp == 7312345 || temp = 8889)
					if(temp < 1000000 || temp == 7312345 || temp == 96773100004)
						badcall = 1;
					else
					{
						dest = (TStr(Ss.GetFld(5))).GetUInt64();
						if (dest < 1000000000 && dest > 10000000)
							dest = dest + 967000000000;
				}	}
				else
				{ //About 1 error like this per 25,000 calls. Just ignore these
					badcall = 1;
				}	

				//Source Location
				locsrc = Ss.GetFld(3); //Has numbers/letters

				//Destination Location???
				locdest = "";//Doesn't exist
			}
			else if(Ss.GetInt(8) == 2)
			{
				if(Ss.IsInt(5))
				{
					TUInt64 temp = (TStr(Ss.GetFld(5))).GetUInt64();
					//if(temp == 111 || temp == 8888 || temp == 7312345 || temp = 8889)
					if(temp < 1000000 || temp == 7312345 || temp == 96773100004)
						badcall = 1;
					else
					{
						src = (TStr(Ss.GetFld(5))).GetUInt64();
						if (src < 1000000000 && src > 10000000)
							src = src + 967000000000;
					}
				}
				else
				{ //About 1 error like this per 25,000 calls. Just ignore these
					badcall = 1;
				}

				dest = (TStr(Ss.GetFld(0))).GetUInt64();

				locsrc = "";

				locdest = Ss.GetFld(3);
			}
			else
			{
				badcall = 1;
			}

			//Duration of Call (1 if SMS)
			TStr durfield = Ss.GetFld(11);
			durfield.DelChAll('.');
			TInt duration = (durfield).GetInt(); //Sometimes has a "." at the end
			
			//Time of Call
			TInt starttime;
			if(TStr(Ss.GetFld(9)).Len() >= 14)
				starttime = (TStr(Ss.GetFld(9)).GetSubStr(8)).GetInt();
			else
				badcall = 1;

			call.setVals(src, dest, locsrc, locdest, duration, starttime);
			
			if(!badcall)
			{
				//Hash Table:
				if(repeatCalls.IsKey(dest))	
				{
					//Check if most recent call was same one
					if(abs(repeatCalls.GetDat(dest).getDuration() - duration) < 5 && abs(repeatCalls.GetDat(dest).getTime() - starttime) < 5 && repeatCalls.GetDat(dest).getDest() == src)
					{
						badcall = 1;
						//cout << counter << "\n";
						if(Ss.GetInt(8) == 1)
						{
							if(PhoneV.Last().getSource() == src && PhoneV.Last().getDest() == dest)
							{
								//Vast majority of repeats are one behind
								PhoneV.Last().setLocSrc(locsrc);
							}
							else
							{
								//Unlucky (< 0.5% of repeats). No way but to start searching
								int sanitytest = 0;
								int elements = PhoneV.Len()-1;
								//Increase this value to miss NO results
								while(sanitytest < 100000 && elements >= 0)
								{
									if(PhoneV[elements].getSource() == src && PhoneV[elements].getDest() == dest)
									{
										PhoneV[elements].setLocSrc(locsrc);
										break;
									}
									sanitytest++;
									elements--;
								}
								//if(sanitytest == 1000000 || elements == -1)
								//	cout << "Missed element #" << counter << "\n";
							}			
						}
						else
						{
							//Need to fill in LocDest
							if(PhoneV.Last().getSource() == src && PhoneV.Last().getDest() == dest)
							{
								//Vast majority of repeats are one behind
								PhoneV.Last().setLocDest(locdest);
							}
							else
							{
								//Unlucky (< 0.5% of repeats). No way but to start searching
								int sanitytest = 0;
								int elements = PhoneV.Len()-1;
								//Increase this value to miss NO results
								while(sanitytest < 100000 && elements >= 0)
								{
									if(PhoneV[elements].getSource() == src && PhoneV[elements].getDest() == dest)
									{
										PhoneV[elements].setLocDest(locdest);
										break;
									}
									sanitytest++;
									elements--;
								}
								//if(sanitytest == 1000000 || elements == -1)
								//	cout << "Missed element #" << counter << "\n";
							}
						}
					}
					else
						repeatCalls.AddDat(src,call);

				}	
				else
				{
					repeatCalls.AddDat(src, call);
				}
				
				

				if(!badcall)
					PhoneV.Add(call);
			}

			Ss.Next();

		}
		cout << day << " " << (TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt()) << ", " << PhoneV.Len() << "\n";
		TFOut fout(argv[2] + day.GetStr());
		PhoneV.Save(fout);

	}


	//load/save code. Seems to be working
	//TVec<TPhoneCall> PhoneLoad;
	//TFIn fin("20100510"); 
	//PhoneLoad.Load(fin);
 	//cout << PhoneLoad[1].getTime() << "\n";



	//NON-SNAP METHOD
    /*ifstream in;
    in.open("TestData.csv");
	if (!in.is_open())
	{
		cout << "Could not open file\n";
		return 0;
	}*/
	//io::CSVReader<3, io::trim_chars<' '>, io::no_quote_escape<','>> in("TestData.csv");
  	//in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
  	//std::string vendor; int size; double speed;
  	//while(in.read_row(vendor, size, speed)){
    // do stuff with the data
  		//cout << vendor << "\n";
  	//}
	//Create new graph
	/*PNEGraph G = PNEGraph::TObj::New();
	string phonecall;
	while (getline(in,phonecall))
	{
		cout << phonecall << "\n";

		//For each edge, add it to the graph
		char delimiter = ',';
		string token = phonecall.substr(0, phonecall.find(delimiter));
		cout << token << "\n";
	}
	in.close();*/

    cout << "Hello, World!\n";
    return 0;
        

}

