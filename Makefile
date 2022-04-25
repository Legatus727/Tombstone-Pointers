main : main.o
	gcc -o main main.o

main.o : A4-tests-v3.cpp
	gcc -c A4-tests-v3.cpp -o main.o

clean:
	rm *.o main