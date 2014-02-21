//
//  main.cpp
//  YemenData
//
//
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "../../snap-core/Snap.h"
//#include "csv_v3.h" - don't use this anymore
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

	//Hash Table
	THash<TUInt64, TPhoneCall> repeatCalls;

	Ss.Next();
	while(!Ss.Eof())
	{
		TVec<TPhoneCall> PhoneV(15000000, 0);
		//Find Day of call
		TInt day = (TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt());
		
		//Break monthly file into day-by-day
		while( !Ss.Eof() && ((TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt())) == day)
		{
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

			if(Ss.GetInt(8) == 1) //Sent call
			{
				//Source ID
				if(Ss.IsInt(0))
					src = (TStr(Ss.GetFld(0))).GetUInt64();
				else
					badcall = 1;

				//Destination ID
				if(Ss.IsInt(5))
				{
					TUInt64 temp = (TStr(Ss.GetFld(5))).GetUInt64();
					if(temp < 1000000 || temp == 7312345 || temp == 96773100004)
						badcall = 1;
					else
					{
						dest = (TStr(Ss.GetFld(5))).GetUInt64();
						if (dest < 1000000000 && dest > 10000000)
							dest = dest + 967000000000; //Add country code
				}	}
				else
				{ //About 1 error like this per 25,000 calls
					badcall = 1;
				}	

				//Source Location
				locsrc = Ss.GetFld(3); //Has numbers/letters

				//Destination Location doesn't exist
				locdest = "";
			}
			else if(Ss.GetInt(8) == 2) //Received call
			{
				//Source ID (note everything is swapped from above case)
				if(Ss.IsInt(5))
				{
					TUInt64 temp = (TStr(Ss.GetFld(5))).GetUInt64();
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
				{
					badcall = 1;
				}

				//Destination ID
				if(Ss.IsInt(0))
					dest = (TStr(Ss.GetFld(0))).GetUInt64();
				else
					badcall = 1;

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
			
			//Time of Call - YYYYMMDDHHMMSS
			TInt starttime;
			if(TStr(Ss.GetFld(9)).Len() >= 14)
				starttime = (TStr(Ss.GetFld(9)).GetSubStr(8)).GetInt();
			else
				badcall = 1;

			//Set TPhoneCall values
			call.setVals(src, dest, locsrc, locdest, duration, starttime);
			
			//If it's not a bad call, add it to the vector
			if(!badcall)
			{
				//Hash Table to see if src has made previous call
				if(repeatCalls.IsKey(src))	
				{
					//Check if the call in the hash table was the reciprocal call
					if(PhoneV.Len() > 0 && abs(repeatCalls.GetDat(src).getDuration() - duration) < 5 && abs(repeatCalls.GetDat(src).getTime() - starttime) < 5 && repeatCalls.GetDat(src).getDest() == dest)
					{
						//It is a repeat. Don't add to vector, simply update src/dest location
						badcall = 1; 
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
								//Increase this value to miss NO results - but slower
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
							}	
							//No need to update repeatCalls, since this call won't be repeated again...		
						}
						else
						{
							//Fill in LocDest
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
								//Increase this value to miss NO results - but a lot slower
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
							}
						}
					}
					else
						//Otherwise, simply add this call to the list of previous calls
						repeatCalls.AddDat(src,call);

				}	
				else
				{
					repeatCalls.AddDat(src, call);
				}
				
				
				//If a valid call, add to vector, and move on to next one
				if(!badcall)
					PhoneV.Add(call);
			}

			Ss.Next();

		}
		//Done with one day, save it to a file.
		cout << day << " " << (TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt()) << ", " << PhoneV.Len() << "\n";
		TFOut fout(argv[2] + day.GetStr());
		if(PhoneV.Len() > 100) //Denoising
			PhoneV.Save(fout);

	}

    cout << "Finished!\n";
    return 0;
        

}

