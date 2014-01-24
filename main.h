
#include "../../snap-core/Snap.h"

//Define a class that holds a single call
class phonecall
{
private:
	TInt source;
	TInt dest;
	TInt locsrc;
	TInt locdest;
	TInt duration;
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



};



