CC = g++ -std=c++11
CFLAGS= -c 
TARGET= a.out
OBJECT= TDList.o Setdist.o TDNode.o main.o 

all: $(TARGET)

set: $(OBJECT)
$(TARGET): $(OBJECT)
	$(CC) -o $(TARGET) $(OBJECT)

TDList.o: TDList.h TDList.cpp TDNode.h
	$(CC) -c $^
Setdist.o: datastruct.h Setdist.cpp Setdist.h	
	$(CC) -c $^
TDNode.o: TDNode.h TDNode.cpp Setdist.h
	$(CC) -c $^
main.o: TDNode.h Setdist.h datastruct.h TDList.h main.c
	$(CC) -c $^

clean:
	rm -f *.o
	rm -f $(TARGET)
hclean:
	rm -f *.gch
