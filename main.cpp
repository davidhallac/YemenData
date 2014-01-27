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
#include "../../snap-core/Snap.h"
//#include "csv_v3.h"
#include "main.h"

using namespace std;

int main(int argc, const char * argv[])
{

	if (argc < 2)
	{
		cout << "Not enough arguments!" << "\n";
		return 0;
	}

	//cout << TZipIn::IsZipFNm("TestData2.csv.bz2") << "\n";
	//TZipIn ZipIn("TestData3.csv.bz2");
	
	//TStr testfile = "./TestData3.csv";
    TStr testfile = "../../../TRACK_REJ_CALLS_MAY_2010.csv";
    //TStr testfile = argv[1];

	//TSsParser Ss(argv[1], ssfCommaSep);
	//TSsParser Ss("TestData3.zip", ssfCommaSep);
	TSsParser Ss(testfile, ssfCommaSep);
	TInt counter = 0;

	Ss.Next();
	while(!Ss.Eof())
	{
		TVec<TPhoneCall> PhoneV(15000000, 0);
		//Find Day of call
		TInt day = (TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt());
		
		while( !Ss.Eof() && ((TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt())) == day)
		{
			//To see how fast the code is running
			counter = counter + 1;
			if (counter % 10000/*1000000*/ == 1)
				cout << counter << ", " << Ss.GetFld(9) << "\n";		
			
			TPhoneCall call;
			TInt badcall = 0; 	//Flag for "bad" call

			//Source ID
			TInt src = Ss.GetInt(0);

			//Destination ID
			TInt dest;
			if(Ss.IsInt(5))
			{
				dest = Ss.GetInt(5);
			}
			else{ //About 1 error like this per 25,000 calls. Just ignore these
				badcall = 1;
				//dest = 0;
			}	

			//Source Location
			TStr locsrc = Ss.GetFld(3); //Has numbers/letters

			//Destination Location???
			TInt locdest = 0;//Where is it?

			//Duration of Call (1 if SMS)
			TStr durfield = Ss.GetFld(11);
			durfield.DelChAll('.');
			TInt duration = (durfield).GetInt(); //Sometimes has a "." at the end
			//cout << Ss.GetFld(11) << ", " << duration << "\n";

			if (counter == 379283)
				cout << counter << ", " << Ss.GetFld(9) << "\n";

			//Time of Call
			TInt starttime;
			if(TStr(Ss.GetFld(9)).Len() >= 14)
				starttime = (TStr(Ss.GetFld(9)).GetSubStr(8)).GetInt();
			else
				badcall = 1;

			if (counter == 379283)
				cout << counter << ", " << Ss.GetFld(9) << "\n";

			call.setVals(src, dest, locsrc, locdest, duration, starttime);
			if(!badcall)
				PhoneV.Add(call);

			Ss.Next();

		}
		cout << day << " " << (TStr(Ss.GetFld(9)).GetSubStr(0,7).GetInt()) << "\n";
		TFOut fout(day.GetStr());
		PhoneV.Save(fout);

	}


	//load/save code. Seems to be working
	TVec<TPhoneCall> PhoneLoad;
	TFIn fin("20100430"); 
 	PhoneLoad.Load(fin);

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

