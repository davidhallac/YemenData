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

		//Why can't I TZipIn this zipfile?
	//cout << TZipIn::IsZipFNm("./TestData2.csv.bz2") << "\n";
	//TZipIn ZipIn("./TestData2.csv.bz2");
	
	//TStr testfile = "./TestData2.csv";
    TStr testfile = "../../../TRACK_REJ_CALLS_MAY_2010.csv";
    TSsParser Ss(testfile, ssfCommaSep);
	TInt counter = 0;
	TVec<TPhoneCall> PhoneV(15000000, 0);
	Ss.Next();
	while(!Ss.Eof())
	{
		//Find Day of call
		TInt day = Ss.GetInt(9)/1000000;
		cout << day << " " << Ss.GetInt(9)/1000000 << "\n";
		while( !Ss.Eof() && (Ss.GetInt(9)/1000000) == day)
		{
			//To see how fast the code is running
			counter = counter + 1;
			if (counter % 1000000 == 1)
				cout << counter << ", " << Ss.GetFld(0) << "\n";		
			
			TPhoneCall call;
			TInt badcall = 0; 	//Flag for "bad" call

			TInt src = Ss.GetInt(0);
			TInt dest;
			if(Ss.IsInt(5))
			{
				dest = Ss.GetInt(5);
			}
			else{ //About 1 error like this per 25,000 calls. Just ignore these
				badcall = 1;
				dest = 0;
			}
			TStr locsrc = Ss.GetFld(3); //Has numbers/letters
			TInt locdest = 0;//Where is it?
			TStr duration = Ss.GetFld(11); //Sometimes has a "." at the end
			TInt starttime = Ss.GetInt(9);

			call.setVals(src, dest, locsrc, locdest, duration, starttime);
			
			if(!badcall)
				PhoneV.Add(call);
			
			Ss.Next();

		}

		TFOut fout("a.bin");
		PhoneV.Save(fout);

	}


	//load/save code. Seems to be working
	/*TFOut fout("a.bin"); 
	call.Save(fout);
	TPhoneCall a;
	TFIn fin("a.bin"); 
 	a.Load(fin);
 	cout << a.getSrc() << "\n";*/



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

