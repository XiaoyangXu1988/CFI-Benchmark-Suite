# defining compiler if not. The default one is g++.
CXX ?= g++

# uncomment the next line or set CXXFLAGS if you want to set particular compilation flag
#CXXFLAGS ?= -m32

TARGETDIR ?= gpp

all: $(TARGETDIR) cppEH dynlinking fptr impExpData indirect-tailcall jit linux-callback linux-hw-except linux-multithreading linux-PLTcall ret switch vtablecall #calling_conventions

calling_conventions: calling_conventions.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -m32 -o $(TARGETDIR)/calling_conventions calling_conventions.cpp helper.cpp
	
cppEH: cppEH.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/cppEH cppEH.cpp helper.cpp
	
dynlinking: dynlinking.cpp helper.cpp helper.h libinc.so
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/dynlinking dynlinking.cpp helper.cpp -ldl
	
fptr: fptr.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/fptr fptr.cpp helper.cpp
	
impExpData: impExpData.cpp helper.cpp helper.h libinc.so
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/impExpData impExpData.cpp helper.cpp -linc -L$(PWD)/$(TARGETDIR)
	
indirect-tailcall: indirect-tailcall.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/indirect-tailcall indirect-tailcall.cpp helper.cpp
	
jit: jit.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/jit jit.cpp helper.cpp
	
linux-callback: linux-callback.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/linux-callback linux-callback.cpp helper.cpp -lpthread
	
linux-hw-except: linux-hw-except.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/linux-hw-except linux-hw-except.cpp helper.cpp
	
linux-multithreading: linux-multithreading.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/linux-multithreading linux-multithreading.cpp helper.cpp -lpthread
	
linux-PLTcall: linux-PLTcall.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/linux-PLTcall linux-PLTcall.cpp helper.cpp
	
ret: ret.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/ret ret.cpp helper.cpp
	
switch: switch.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/switch switch.cpp helper.cpp
	
vtablecall: vtablecall.cpp helper.cpp helper.h
	$(CXX) $(CXXFLAGS) -std=c++11 -o $(TARGETDIR)/vtablecall vtablecall.cpp helper.cpp

libinc.so: inc.o inc.h
	$(CXX) $(CXXFLAGS) -shared -o $(TARGETDIR)/libinc.so $(TARGETDIR)/inc.o
	
inc.o: inc.cpp inc.h
	$(CXX) $(CXXFLAGS) -o $(TARGETDIR)/inc.o -c -fpic inc.cpp

$(TARGETDIR):
	mkdir -p $@
