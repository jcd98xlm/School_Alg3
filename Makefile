# Arquivo makefile para o trabalho de algoritmos 3

# Variaveis importantes
CC = gcc
CFLAGS = -Wall

# Arquivos fonte
SCRavl = avl.c
SCRmyavl = myavl.c
SCRinput_reader = input_reader.c

# Dependencias particulares
DEPSavl = avl.h
DEPSmyavl = avl.h input_reader.h
DEPSinput_reader = input_reader.h avl.h

# Regra default
all: myavl clean

# Regras de ligacao
myavl: avl.o input_reader.o myavl.o 
	$(CC) $(CFLAGS) -o $@ $^

# Regras de compilacao dos itens
avl.o: $(SCRavl) $(DEPSavl)
	$(CC) $(CFLAGS) -c -o $@ $<
input_reader: $(SCRinput_reader) $(DEPSinput_reader)
	$(CC) $(CFLAGS) -c -o $@ $<
myavl.o: $(SCRmyavl) $(DEPSmyavl)
	$(CC) $(CFLAGS) -c -o $@ $<

# Remove arquivos temporarios
clean:
	-rm avl.o input_reader.o myavl.o
