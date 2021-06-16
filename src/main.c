#include "../headers/Morse.h"
#include "../headers/Graphic.h"

int main(int argc, char ** argv)
{
	Tree tree = initForMorse();
	switch(mainProg(tree, argc, argv))
	{
		case EXIT_FAILURE:
			destroyTree(tree), tree = NULL;
			return EXIT_FAILURE;
		break;
		case GRAPHIC:
			if(Graphic_Interface(tree) == EXIT_FAILURE)
			{
				destroyTree(tree), tree = NULL;
				return EXIT_FAILURE;
			}
		break;
	}
	destroyTree(tree), tree = NULL;
	return EXIT_SUCCESS;
}
