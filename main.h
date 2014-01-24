
#include "../../snap-core/Snap.h"

//Define a class that holds a single call
class TPhoneCall
{
private:
	TStr source;
	TStr dest;
	TStr locsrc;
	TStr locdest;
	TStr duration;
	TStr starttime;

public:

	void Load(TSIn& SIn) 
	{  
		source.Load(SIn);  
		dest.Load(SIn);  
		locsrc.Load(SIn);  
		locdest.Load(SIn);
		duration.Load(SIn);
		starttime.Load(SIn);  
	}
	void Save(TSOut& SOut) const
	{
	 	source.Save(SOut);  
	 	dest.Save(SOut);  
	 	locsrc.Save(SOut);  
	 	locdest.Save(SOut);
	 	duration.Save(SOut);
	 	starttime.Save(SOut);  
	}

	 void setVals(TStr src, TStr dst, TStr lsrc, TStr ldest, TStr dur, TStr sttime)
	{
		source = src;
		dest = dst;
		locsrc = lsrc;
		locdest = ldest;
		duration = dur;
		starttime = sttime;
	}

	TStr getSrc()
	{
		return source;
	}

};



