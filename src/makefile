fullyExtended:    Parser.o HHSearchParser.o BlastParser.o HHSearchAlignment.o BlastAlignment.o Alignment.o Point.o Target.o Template.o Driver.o
	g++    Parser.o HHSearchParser.o BlastParser.o HHSearchAlignment.o BlastAlignment.o Alignment.o  Point.o Target.o Template.o Driver.o -o fullyExtended

Parser.o:Parser.cpp
	g++ -c Parser.cpp

HHSearchParser.o:HHSearchParser.cpp
	g++ -c HHSearchParser.cpp
		
BlastParser.o:BlastParser.cpp
	g++ -c BlastParser.cpp
	
Alignment.o: Alignment.cpp
	g++ -c Alignment.cpp


	
BlastAlignment.o: BlastAlignment.cpp
	g++ -c BlastAlignment.cpp	

HHSearchAlignment.o: HHSearchAlignment.cpp
	g++ -c HHSearchAlignment.cpp

Point.o:Point.cpp
	g++ -c Point.cpp
	
Target.o: Target.cpp
	g++ -c Target.cpp
	
Template.o: Template.cpp
	g++ -c Template.cpp
	
Driver.o: Driver.cpp
	g++ -c Driver.cpp
	

clean:
	rm *.o fullyExtended