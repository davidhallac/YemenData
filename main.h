
#include "../../snap-core/Snap.h"

//Define a class that holds a single call
class TPhoneCall
{
private:
	TInt source;
	TInt dest;
	TStr locsrc;
	TInt locdest;
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

	 void setVals(TInt src, TInt dst, TStr lsrc, TInt ldest, TStr dur, TInt sttime)
	{
		source = src;
		dest = dst;
		locsrc = lsrc;
		locdest = ldest;
		duration = dur;
		starttime = sttime;
	}

	TInt getTime()
	{
		return starttime;
	}

};

typedef TVec<TPhoneCall> TPhoneCallV;
//Add using TVec defined stuff


