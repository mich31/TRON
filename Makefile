#JEU	= texte
JEU = graphique

ifeq ($(JEU),texte)
	SRCS = Joueur.c Terrain.c Jeu.c ncursJeu.c main.c
	FINAL_TARGET = tron_txt
	DEFINE = -DJEU_NCURSES
	LIBS = -lncurses
else
	SRCS = Joueur.c Terrain.c Jeu.c sdlJeu.c main.c
	FINAL_TARGET = tron_gfx
	DEFINE = -DJEU_SDL
	LIBS = -lSDL -lSDLmain -lSDL_image -lSDL_ttf
endif

CC 			  = gcc
LD 			  = gcc
CFLAGS 		  = $(DEFINE) -Wall -pedantic -ansi -ggdb -std=c99
INCLUDE_DIR   = -I/usr/include -Isrc -I/usr/include/SDL
OBJ_DIR 	  = obj
SRC_DIR 	  = src
BIN_DIR 	  = bin

default: $(BIN_DIR)/$(FINAL_TARGET)

$(BIN_DIR)/$(FINAL_TARGET): $(SRCS:%.c=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LIB_DIR) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIR) $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(FINAL_TARGET)
