CC = g++ -std=c++11
CFLAGS= -c 
TARGET= a.out
OBJECT= TDList.o Setdist.o TDNode.o main.o TDManager.o

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
TDManager.o: TDManager.cpp TDManager.h TDNode.h Setdist.h datastruct.h TDList.h
	$(CC) -c $^

main.o: main.c TDNode.h Setdist.h datastruct.h TDList.h TDManager.h
	$(CC) -c $^


clean:
	rm -f *.o
	rm -f $(TARGET)
hclean:
	rm -f *.gch
