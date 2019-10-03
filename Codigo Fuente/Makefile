DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/
DIRHEA := include/
CFLAGS := -I$(DIRHEA) -c 
LDLIBS := -pthread -std=c++11
CC := g++

all: dirs SSOOIIGLE

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

SSOOIIGLE: $(DIROBJ)SSOOIIGLE.o 
	$(CC) -o $(DIREXE)SSOOIIGLE $^ $(LDLIBS)

$(DIROBJ)SSOOIIGLE.o: $(DIRSRC)SSOOIIGLE.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

test:
	./$(DIREXE)SSOOIIGLE ./files/prueba.txt mario 4

book1:
	./$(DIREXE)SSOOIIGLE './files/17 LEYES DEL TRABAJO EN EQUIPO.txt' trabajo 5

book2:
	./$(DIREXE)SSOOIIGLE './files/21 LEYES DEL LIDERAZGO - JOHN C. MAXWELL.txt' leyes 2

book3:
	./$(DIREXE)SSOOIIGLE './files/25 MANERAS DE GANARSE A LA GENTE - .txt' gente 4

clean:
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~
