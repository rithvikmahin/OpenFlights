main : A_Star.o PageRank.o Files.o main.o
		   clang++ A_Star.o PageRank.o Files.o main.o -o main

A_Star.o : A_Star.cpp A_Star.h
		   clang++ -c A_Star.cpp

PageRank.o : PageRank.cpp PageRank.h
			 clang++ -c PageRank.cpp 
			 
Files.o : Files.cpp Files.h
			 clang++ -c Files.cpp 

main.o : main.cpp
		 clang++ -c main.cpp 

clean : 
		 rm main *.o
