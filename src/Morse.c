#include "../headers/Morse.h"



/** Creation of a new node **/
Tree new_node(){
	Node * node = malloc(sizeof(*node));
	
	// If unable to allocate memory
	if(!node){
		fprintf(stderr, "Node creation failure\n");
		return NULL;
	}

	 // Else
	node->dot = NULL;
	node->dash = NULL;
	node->character = '\0';

	return node;
}


/** Adding a character to the tree **/
Tree add_char(Tree * tree, char * morse, char c){
	// if morse code is not given or tree is not given
	if(!morse || !tree){
		fprintf(stderr, "Unable to add a character.\n");
		return NULL;
	}

	// if tree is not initialise
	if(!*tree) {
		
		*tree = new_node(*tree);
		//create and assign newnode to tree
		if(!*tree){
			fprintf(stderr, "Unable to create node\n");
			return NULL;
		}
	}

	// assigning character node to treenode
	if(!*morse){
		
		(*tree)->character = c; 
		return *tree;
	}

	// adding dot and dash to respective nodes
	if(*morse == DOT){
		return add_char(&(*tree)->dot, ++morse, c);
	}
	
	if(*morse == DASH) {
		return add_char(&(*tree)->dash, ++morse, c);
	}
	return NULL;
}



/** Construction of the tree **/
Tree initForMorse(){
	Tree tree = NULL;

    	// Add all 54 the characters from the morse table
    	add_char(&tree, ".-\0", 'A');
	add_char(&tree, "-...\0", 'B');
	add_char(&tree, "-.-.\0", 'C');
	add_char(&tree, "-..\0", 'D');
	add_char(&tree, ".\0", 'E');
	add_char(&tree, "..-.\0", 'F');
	add_char(&tree, "--.\0", 'G');
	add_char(&tree, "....\0", 'H');
	add_char(&tree, "..\0", 'I');
	add_char(&tree, ".---\0", 'J');
	add_char(&tree, "-.-\0", 'K');
	add_char(&tree, ".-..\0", 'L');
	add_char(&tree, "--\0", 'M');
	add_char(&tree, "-.\0", 'N');
	add_char(&tree, "---\0", 'O');
	add_char(&tree, ".--.\0", 'P');
	add_char(&tree, "--.-\0", 'Q');
	add_char(&tree, ".-.\0", 'R');
	add_char(&tree, "...\0", 'S');
	add_char(&tree, "-\0", 'T');
	add_char(&tree, "..-\0", 'U');
	add_char(&tree, "...-\0", 'V');
	add_char(&tree, ".--\0", 'W');
	add_char(&tree, "-..-\0", 'X');
	add_char(&tree, "-.--\0", 'Y');
	add_char(&tree, "--..\0", 'Z');
	add_char(&tree, ".----\0", '1');
	add_char(&tree, "..---\0", '2');
	add_char(&tree, "...--\0", '3');
	add_char(&tree, "....-\0", '4');
	add_char(&tree, ".....\0", '5');
	add_char(&tree, "-....\0", '6');
	add_char(&tree, "--...\0", '7');
	add_char(&tree, "---..\0", '8');
	add_char(&tree, "----.\0", '9');
	add_char(&tree, "-----\0", '0');
	add_char(&tree, ".-.-.-\0", '.');
	add_char(&tree, "--..--\0", ',');
	add_char(&tree, "..--..\0", '?');
	add_char(&tree, "-..-.\0", '/');
	add_char(&tree, ".----.\0", '\'');
	add_char(&tree, "-.-.--\0", '!');
	add_char(&tree, "-.-.-.\0", ';');
	add_char(&tree, "---...\0", ':');
	add_char(&tree, ".-.-.\0", '+');
	add_char(&tree, "-....-\0", '-');
	add_char(&tree, "-...-\0", '=');
	add_char(&tree, "-.--.\0", '(');
	add_char(&tree, "-.--.-\0", ')');
	add_char(&tree, "..--.-\0", '_');
	add_char(&tree, "...-..-\0", '$');
	add_char(&tree, ".-..-.\0", '"');
	add_char(&tree, ".--.-.\0", '@');

	return tree;
}



/** Search for the character in the tree **/
char seekChar(Tree tree, char * morse){
     	//If the tree is empty
	if(!tree){
		return '?';
	}
    	
    	// If we get at the end of the character string
	if(!*morse){
		return tree->character;
	}
    	
    	// If the character is a point
	if(*morse == DOT){
		return seekChar(tree->dot, ++morse);
	}
    	
    	// If the character is a hyphen
	if(*morse == DASH){
		return seekChar(tree->dash, ++morse);
	}
	return '?';
}



/** Morse code decoding **/
char * morseDecoder(Tree tree, char * morse){
	
	// Pointer to the morse code
	char * current = morse;
	
	// Allocate memory for the result
	char * parsed = malloc(sizeof(char) * (strlen(morse)+1)); 
	
	// If the allocation has not been made
	if(!parsed) {
		fprintf(stderr, "Unable to alloc memory\n");
		return NULL;
	}

	// Pointer on the result
	char * current_parsed = parsed; 
	int done = 0;
	
	// As long as decoding is not over
	while(!done){
	
		// We browse the morse code to the separator
		while(*current && *current != SEP) {
			++current;
		}
		
		// If we get to the end of the Morse code we are done
		if(!*current){
			done = 1;
		}
		
		// Otherwise we reduce the chain to where we arrived
		else {
			*current = '\0';
		}
		
		// If it's not a space
		if(strcmp(morse, " ") != 0){
			*current_parsed = seekChar(tree, morse);
		}
		
		// If it is a space
		else {
			*current_parsed = ' ';
		}
		++current_parsed;
		++current;
		// We go to next pointer
		morse = current; 
	}
	
	// We have to close at end
	*current_parsed = '\0'; 
	return parsed;
}



/** Morse code encoding **/
char * morseEncrypter(Tree tree, char * text){
	int i = 0, find = 0;
	
	// Allocate memory for the result
	char *parsed = malloc(sizeof(char) * 4 * (strlen(text)+1)); 
	
	// If the allocation has not been made
	if(!parsed){
	
		fprintf(stderr, "Unable to alloc memory\n");
		return NULL;
	}
	
	// Define the number of morse code in the array
	size_t size = 54; 
	char *morseCode[] = {".-\0", "-...\0", "-.-.\0", "-..\0", ".\0", "..-.\0", "--.\0",
						   "....\0", "..\0", ".---\0", "-.-\0", ".-..\0", "--\0", "-.\0",
						   "---\0", ".--.\0", "--.-\0", ".-.\0", "...\0", "-\0", "..-\0",
						   "...-\0", ".--\0", "-..-\0", "-.--\0", "--..\0", "-...-\0",
						   ".----\0", "..---\0", "...--\0", "....-\0", ".....\0", 
						   "-....\0", "--...\0", "---..\0", "----.\0", "-----\0",
						   ".-.-.-\0", "--..--\0", "..--..\0", "-..-.\0", ".----.\0",
						   "-.-.--\0", "-.-.-.\0", "---...\0", ".-.-.\0", "-....-\0",
						   "-...-\0", "-.--.\0", "-.--.-\0", "..--.-\0", "...-..-\0",
						   ".-..-.\0", ".--.-.\0", ".-...\0"};
	
	// Pointer on the result
	char * current_parsed = parsed; 
	
	// As long as we haven't reached the end of the chain
	while(text[i]){
		
		// We assign the uppercase letter to the character
		char c = toupper(text[i]); 
		
		// If it's a space
		if(c == ' '){
			// We concatenate the space with the current string
			strcat(current_parsed, " \0"); 
			i++;
			// We pass all the code that follows
			continue; 
		}
		
		// We browse the whole morse code table
		for(int k = 0; k < size; k++){
			
			// We check if we find the character corresponding to the morse code
			if(seekChar(tree, morseCode[k]) == c){
				find = 1;
				// We concatenate the found Morse code with the existing string
				strcat(current_parsed, morseCode[k]); 
				// We exit the loop
				break; 
			}
		}
		
		// If we have not found an equivalent
		if(!find) {
			strcat(current_parsed, "?\0"); //On concatène avec un point d'intérrogation
		}
		

		i++;
		// If we haven't reached the end of the string and it's not a space
		if(text[i] != '\0' && text[i] != ' ') {
			// We add the separator
			strcat(current_parsed, "_\0"); 
		}
		find = 0;
		if(text[i+1] == '\0')
			strcat(current_parsed, "\0");
	}
	return parsed;
}



/** Destroy tree **/
void destroyTree(Tree tree){
    // If the tree is not empty
	if(tree) {
		destroyTree(tree->dot);
		destroyTree(tree->dash);
		free(tree);
	}
}


/** breaks string (s) into a series of tokens using the delimiter (const char * ct) return as an array **/
char ** str_split(char * s, const char * ct){
	char ** tab = NULL;
	// checking if the strings are not empty
	if(s && ct){
		int i;
		char * cs = NULL;
		// Initial size from 1 to array
		size_t size = 1;
		// As long as strtok (...) does not return us NULL
		for(i = 0; (cs = strtok(s, ct)); i++) {
            // If the size of the array is less than the next iteration
			if(size <= i + 1){
			    // We create a temp variable to reallocate our array
				void * tmp = NULL;
                // We multiply the size by 2 (2 ^ 1)
				size <<= 1;
				// We reallocate via tmp
				tmp = realloc(tab, sizeof(*tab) * size);
				// If  tmp! = NULL
				if(tmp){
					tab = tmp;
				}
				else{
					fprintf(stderr, "Unable to allocate memory\n");
					free(tab); tab = NULL;
					return NULL;
				}
			}
            // We add the truncated string to index i
			tab[i] = cs;
			s = NULL;
		}
        // We pass the last index of the array to NULL
		tab[i] = NULL;
	}
	return tab;
}


/** Display Morse Table **/
void morseTable(Tree tree){

    // clear the previous display
    clrscr();
    // change the display to blue
    color(BLUE);
    puts("\t-----------------");
    puts("\t|  MORSE TABLE  |");
    printf("\t-----------------\n\n");
    // reset the color of the terminal
    resetColor;

    int j;
    char c;
    // change the display to magenta
    color(MAGENTA);

    // browse half of the characters of the tree in 2 times (2x26 characters)
    for(int i = 0; i < 26; i++){
		char str1[2], str2[2];
		
		// store the result in a chain (A-Z)
		sprintf(str1, "%c", (char)(65+i));
		
		// For displaying the characters
		if(i < 10){
			j = i;
			c = (char)(48 + j);
		}
		
		else if(i < 12 && i > 9){
			j = i % 10;
			c = (char)(33 + j);
		}
		
		else if(i < 15 && i > 11){
			j = i - 12;
			c = (char)(39 + j);
		}
		
		else if(i < 19 && i > 14){
			j = i - 15;
			c = (char)(43 + j);
		}
		
		else if(i < 21 && i > 18){
			j = i - 19;
			c = (char)(58 + j);
		}
		
		else if(i < 23 && i > 20){
			j = i - 21;
			c = (char)(63 + j);
		}
		
		if(i >= 23){
			switch(i){
				case 23:
					c = '=';
				break;
				case 24:
					c = '$';
				break;
				case 25:
					c = '_';
				break;
			}
		}
		
		// store the character in a string
		sprintf(str2, "%c", c);	
		
		// display table	
		printf("%s\t%c\t\t%s\t%c\n", morseEncrypter(tree, str1) , (char)(65+i),morseEncrypter(tree, str2), c); 
	}
	
	// reset the color of the terminal
	resetColor; 

}







/** Function which runs this software **/
int mainProg(Tree tree, int argc, char ** argv){
	
	// If there are no arguments
	if(argc <= 1){
		
		// We change the color of the terminal to red
		color(RED); 
		printf("Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		// We reset the color of the terminal
		resetColor; 
		return EXIT_FAILURE;
	}
	
	// If we want to display the help
	if(strcmp(argv[1], "--help") == 0){
	
		// We change the color of the terminal to yellow
		color(YELLOW);
		puts("Welcome to the help of Morse Decode & Encode, here are the usable options: ");
		printf("Utilization: %s [Options]\n", argv[0]);
		printf("You can use spaces to separate words and use '_' to paste Morse letters\n");
		printf("Exemple: %s -d ._. ..\n", argv[0]);

		// We change the color of the terminal to cyan
		color(CYAN);
		puts("-d [morse]\t\tDecode the Morse code passed in parameter");
		puts("-e [text]\t\tEncode text in Morse code");
		puts("-g\t\t\tSwitching to graphic display");
		puts("-a\t\t\tDisplaying the Morse Table");
		puts("-f [filename] -d/-e\tDecode or encode a file");
		puts("--help\t\t\tShow help");

		// We reset the color of the terminal
		resetColor;
	}
	
	// If we want to display the morse code table
	else if(strcmp(argv[1], "-a") == 0){

	    	morseTable(tree);
	}

	// If we want to start the program in graphics
	else if(strcmp(argv[1], "-g") == 0){

	   	return GRAPHIC;
	}

	// If we put an argument other than -d or -e or -d or -e but no text / morse
	else if(argc <= 2 || (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-f") != 0)) {
		color(RED);
		printf("Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		resetColor;
		return EXIT_FAILURE;
	}
	
	// If we want to decode Morse code
	else if(strcmp(argv[1], "-d") == 0){
		printf("%s",morseDecoder(tree, argv[2]));
		
		// If we have a string with spaces
		if(argc > 2) {
			// We do the same operation for all the following arguments
			for(int i = 3; i < argc; i++){
				printf("%s",morseDecoder(tree, " \0"));
				printf("%s",morseDecoder(tree, argv[i]));
			}
		}
		printf("\n");
	}
	
	// If we want to encode text to Morse code
	else if(strcmp(argv[1], "-e") == 0){
	
		printf("%s", (morseEncrypter(tree, argv[2])));
		// If we have a string with spaces
		if(argc > 2) {
			// We do the same operation for all the following arguments
			for(int i = 3; i < argc; i++) {
				printf("%s",morseEncrypter(tree, " \0"));
				printf("%s", morseEncrypter(tree, argv[i]));
			}
		}
		printf("\n");
	}
	else if(strcmp(argv[1], "-f") == 0){
		if(argc < 4){
			
			color(RED);
			printf("Usage %s [Option]\n", argv[0]);
			fprintf(stderr, "Use --help as an option to open the help list\n");
			resetColor;
			return EXIT_FAILURE;
		}

		FILE * file = fopen(argv[2], "r");
		if(!file){
			
			color(RED);
			printf("File opening failure..\n");
			fprintf(stderr, "Unable to open : %s\n", argv[2]);
			fprintf(stderr, "Use --help as an option to open the help list\n");
			resetColor;
			return EXIT_FAILURE;			
		}

		if(strcmp(argv[3], "-e") == 0){
			
			char * filenameOutput = malloc(sizeof(char) * 60);
			if(!filenameOutput){
			
				color(RED);
				printf("Unable to allocate memory\n");
				fprintf(stderr, "Insuffisant memory\n");
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;			

			}
			strcpy(filenameOutput, argv[2]);
			strcat(filenameOutput, "_encoded\0");
			FILE * outputFile = fopen(filenameOutput, "w");
			if(!outputFile){
				color(RED);
				printf("File creation failure..\n");
				fprintf(stderr, "Unable to create the file : %s\n", filenameOutput);
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;				
			}
			free(filenameOutput);
			char buff[255];
			while(fgets(buff, 255, file) != NULL)
				fprintf(outputFile, "%s\n", morseEncrypter(tree, buff));
			fclose(outputFile);
		}

		else if(strcmp(argv[3], "-d") == 0){
			char * filenameOutput = malloc(sizeof(char) * 60);
			if(!filenameOutput){
				color(RED);
				printf("Unable to allocate memory\n");
				fprintf(stderr, "Insuffisant memory\n");
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;			

			}
			strcpy(filenameOutput, argv[2]);
			strcat(filenameOutput, "_decoded\0");
			FILE * outputFile = fopen(filenameOutput, "w");
			if(!outputFile){
				color(RED);
				printf("File creation failure..\n");
				fprintf(stderr, "Unable to create the file : %s\n", filenameOutput);
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;				
			}
			free(filenameOutput);
			char buff[255];
			while(fgets(buff, 255, file) != NULL){
				char * outputDecypher = malloc(sizeof(char) * 255);
				char ** splitted = str_split(buff, " \0");
				if(!splitted){
					color(RED);
					printf("str_split error\n");
					fprintf(stderr, "Unable to split the string\n");
					fprintf(stderr, "Use --help as an option to open the help list\n");
					resetColor;
					return EXIT_FAILURE;				

				}

				for(int i = 0; splitted[i] != NULL; i++){
					strcat(outputDecypher, morseDecoder(tree, splitted[i]));
					if(splitted[i+1] != NULL)
						strcat(outputDecypher, " \0");
				}
				free(splitted); splitted = NULL;

				fprintf(outputFile, "%s\n", outputDecypher);
			}
			fclose(outputFile);
		}

		else{
			color(RED);
			printf("Unable to do your options\n");
			fprintf(stderr, "%s is not an argument for the %s option\n", argv[3], argv[1]);
			fprintf(stderr, "Use --help as an option to open the help list\n");
			resetColor;
			return EXIT_FAILURE;						
		}

		fclose(file);	
	}
	return EXIT_SUCCESS;
}
