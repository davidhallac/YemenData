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
#include "/Users/Hallac/Desktop/Snap-2.1/snap-core/Snap.h"

using namespace std;

int main(int argc, const char * argv[])
{

	//Confirm that file exists
    ifstream in;
    in.open("TestData.csv");
	if (!in.is_open())
	{
		cout << "Could not open file\n";
		return 0;
	}

	string value;
	while (getline(in,value))
	{
		cout << value << "\n";

		//Do SNAP stuff here
		

	}
	in.close();

    cout << "Hello, World!\n";
    return 0;
        

}

