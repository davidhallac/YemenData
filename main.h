
#include "../../snap-core/Snap.h"

//Define a class that holds a single call
class TPhoneCall
{
private:
	TInt source;
	TStr dest;
	TStr locsrc;
	TStr locdest;
	TStr duration;
	TInt starttime;

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

	 void setVals(TInt src, TStr dst, TStr lsrc, TStr ldest, TStr dur, TInt sttime)
	{
		source = src;
		dest = dst;
		locsrc = lsrc;
		locdest = ldest;
		duration = dur;
		starttime = sttime;
	}

	TInt getSrc()
	{
		return source;
	}

};



