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
#include "csv_v3.h"
#include "main.h"

using namespace std;

int main(int argc, const char * argv[])
{

	//TZipIn zipfile("./TestData.csv.bz2");
	TStr testfile = "./TestData2.csv";
	TSsParser Ss(testfile, ssfCommaSep);
	while(Ss.Next())
	{
		cout << Ss.GetFld(0) << "\n";
		TPhoneCall call;
		TInt src = Ss.GetInt(0);
		TInt dest = Ss.GetInt(5);
		TStr locsrc = Ss.GetFld(3);
		TStr locdest = "Hello";//Ss.GetFld(3);
		TStr duration = Ss.GetFld(11);
		TInt starttime = Ss.GetInt(9);

		call.setVals(src, dest, locsrc, locdest, duration, starttime);
	}


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

