CC = gcc
OBJS = main.o SPChess.o SPChessMainWin.o SPChessGUIManager.o \
SPChessSlotWin.o SPChessGameModeWin.o SPChessDiffWin.o SPChessColorWin.o SPChessGameWin.o ConsoleMode.o GraphicalMode.o
 
EXEC = chessprog
CC_COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = `sdl2-config --cflags --libs` -D_REENTRANT
SDL_LIB = -L/usr/include/SDL2 -Wl,-rpath,/usr/include/SDL2 -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
ConsoleMode.o: ConsoleMode.c ConsoleMode.h SPChess.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GraphicalMode.o: GraphicalMode.c GraphicalMode.h SPChess.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
main.o: main.c ConsoleMode.h GraphicalMode.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChess.o: SPChess.c SPChess.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChessGameWin.o: SPChessGameWin.c SPChessGameWin.h SPChess.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChessSlotWin.o: SPChessSlotWin.c SPChessSlotWin.h  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChessGameModeWin.o: SPChessGameModeWin.c SPChessGameModeWin.h  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChessDiffWin.o: SPChessDiffWin.c SPChessDiffWin.h  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChessColorWin.o: SPChessColorWin.c SPChessColorWin.h SPChess.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChessMainWin.o: SPChessMainWin.c SPChessMainWin.h  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SPChessGUIManager.o: SPChessGUIManager.c SPChessGameWin.h SPChessMainWin.h SPChessSlotWin.h SPChessGameModeWin.h SPChessDiffWin.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
