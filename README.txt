To Run: 1) Put YemenData folder in snap/examples
   	2) Edit snap/Makefile.config file to include: 
	     LIBS += -lpthread
	     CXXFLAGS += -std=c++11 -Wall
	     	      if on Linux: use -std=C++0x instead
	3) Go back to YemenData directory and "make"
	4) Run "./main"
