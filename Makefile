main : Files.o main.o
		   clang++ Files.o main.o -o main 

Files.o : Files.cpp Files.h
			 clang++ -c Files.cpp 

main.o : main.cpp
		 clang++ -c main.cpp 

clean : 
		 rm main *.o
