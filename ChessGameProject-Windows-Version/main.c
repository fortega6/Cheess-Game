#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "GraphicalMode.h"
//#include "ConsoleMode.h"
int main(int argc, char** argv) {
	graphicalModeMain();
	/*if (argv[1] == NULL || strcmp(argv[1], "-c") == 0) { // Console mode
		//consoleModeMain();
	}
	else if (strcmp(argv[1], "-g") == 0) { // GUI mode
		//graphicalModeMain();
	}*/
	return 0;
}