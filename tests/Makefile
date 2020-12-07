test : A_Star.o DFS.o PageRank.o Files.o test.o
		   clang++ A_Star.o DFS.o PageRank.o Files.o test.o -o test -std=c++11

A_Star.o : ../A_Star.cpp ../A_Star.h
		   clang++ -c ../A_Star.cpp -std=c++11

DFS.o : ../DFS.cpp ../DFS.h
		clang++ -c ../DFS.cpp -std=c++11

PageRank.o : ../PageRank.cpp ../PageRank.h
			 clang++ -c ../PageRank.cpp -std=c++11
			 
Files.o : ../Files.cpp ../Files.h
			 clang++ -c ../Files.cpp -std=c++11

test.o : test.cpp
		 clang++ -c test.cpp -std=c++11

clean : 
		 rm test *.o
