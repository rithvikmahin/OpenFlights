main : PageRank.o Files.o main.o
		   clang++ PageRank.o Files.o main.o -o main

PageRank.o : PageRank.cpp PageRank.h
			 clang++ -c PageRank.cpp 
			 
Files.o : Files.cpp Files.h
			 clang++ -c Files.cpp 

main.o : main.cpp
		 clang++ -c main.cpp 

clean : 
		 rm main *.o
