CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h graphique.h sdl2-ttf-light.h one_use.h database.h events.h update.h
SRC = main.c sdl2-light.c graphique.c sdl2-ttf-light.c one_use.c database.c events.c update.c 
OBJ = $(SRC:%.c=%.o)
 
PROG = spacebattle

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html