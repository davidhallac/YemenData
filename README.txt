To Run: 1) Put YemenData folder in snap/examples
   	2) Make SNAP, then enter YemenData and make it
	3) Run "./process <filename> <filepath>/" to convert into daily vectors
		a) Process runs on a Zip file containing one month of data
		b) It breaks it up into daily files, each containing a TVec<TPhoneCall> containing every valid/unique call+text during that day
		c) In theory, you only have to run this once - just have a shell script process each of the 37 months to a distinct folder, one for each month
	4) Run "./analyze <filename>" to analyze a particular day
		a) As of now, analyze contains a lot of disjoint "analyze" methods, that I have used to look at a day of data
		b) It takes a daily TVec file as an input, and (usually) writes the desired output to a CSV files called startTimes.csv.
		c) Often, it is best to write a shell script to loop through each day, and run ./analyze on it. This can be used to populate startTimes.csv with all the data needed for your analysis
