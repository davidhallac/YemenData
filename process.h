
#include "../../snap-core/Snap.h"

//Define a class that holds a single call
class TPhoneCall
{
private:
	TUInt64 source;
	TUInt64 dest;
	TStr locsrc;
	TStr locdest;
	TInt duration;
	TInt starttime;

public:
	TPhoneCall() {
		source = 0;
		dest = 0;
		locsrc = "";
		locdest = "";
		duration = 0;
		starttime = 0;
	}

	explicit TPhoneCall(TSIn& SIn){Load(SIn);}

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

	 void setVals(TUInt64 src, TUInt64 dst, TStr lsrc, TStr ldest, TInt dur, TInt sttime)
	{
		source = src;
		dest = dst;
		locsrc = lsrc;
		locdest = ldest;
		duration = dur;
		starttime = sttime;
	}

	void setLocSrc(TStr lsrc)
	{
		locsrc = lsrc;
	}

	void setLocDest(TStr ldest)
	{
		locdest = ldest;
	}

	TUInt64 getSource()
	{
		return source;
	}

	TUInt64 getDest()
	{
		return dest;
	}

	TStr getLocSrc()
	{
		return locsrc;
	}

	TStr getLocDest()
	{
		return locdest;
	}

	TInt getTime()
	{
		return starttime;
	}

	TInt getDuration()
	{
		return duration;
	}

};

typedef TVec<TPhoneCall> TPhoneCallV;
//Add using TVec defined functions


