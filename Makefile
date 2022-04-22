CC=gcc

FLAGGLUT=-lglut -lGL -lGLU -lm

FLAG=-Wall -std=c99
SRCS=*.c 
OBJET = $(SRCS:.c=.o)
EXEC= program

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) -c $(SRCS) $(FLAG) $(FLAGGLUT)
	$(CC) -o $(EXEC) $(OBJET) $(FLAG) $(FLAGGLUT)
	
clean:
	rm -rf $(EXEC)
	rm -rf *.o

