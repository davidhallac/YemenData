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
#include "../../snap-core/Snap.h"
#include "process.h"
using namespace std;

int main(int argc, const char * argv[])
{

	TVec<TPhoneCall> PhoneLoad;
	//TFIn fin("OldFiles/20100430"); 
	TFIn fin("20100430"); 
	PhoneLoad.Load(fin);
 	cout << PhoneLoad[0].getDest() << "\n";
 	cout << PhoneLoad[997].getDest() << "\n";
 	cout << PhoneLoad[997].getTime() << "\n";
 	cout << PhoneLoad[PhoneLoad.Len()-1].getTime() << "\n";


}




