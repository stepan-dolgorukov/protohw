CXX:=/usr/bin/clang++
CXXFLAGS:=-std=c++17

portscan: portscan.o scanner.o scan.o scanres.o
	$(CXX) portscan.o scanner.o scan.o scanres.o -o portscan -lboost_program_options

scan.o: scan.cxx
	$(CXX) $(CXXFLAGS) -c scan.cxx -o scan.o

portscan.o: portscan.cxx
	$(CXX) $(CXXFLAGS) -c portscan.cxx -o portscan.o

scanner.o: scanner.cxx
	$(CXX) $(CXXFLAGS) -c scanner.cxx -o scanner.o

scanres.o: scanres.cxx
	$(CXX) $(CXXFLAGS) -c scanres.cxx -o scanres.o