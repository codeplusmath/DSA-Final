#include "../headers/Graphic.h"

/* Graphical interface of the Software */
int Graphic_Interface(Tree tree){

	if(SDLnIMGnTTF_Initialize() == EXIT_FAILURE)
		return EXIT_FAILURE;

	SDL_Window * window = SDL_CreateWindow("Encode&Decode Morse Code", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
											SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(!window){
	
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window: %s\n", SDL_GetError());
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer){
		
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create renderer: %s\n", SDL_GetError());
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
		
	}

	SDL_Texture * background = Load_Texture("../images/back.jpg", renderer);
	if(!background){
	
		Clean_Up(window, renderer);
		return EXIT_FAILURE;
	}

	SDL_Texture * encode_btn = Load_Texture("../images/Encode_btnSprites.png", renderer);
	if(!encode_btn){
		
		SDL_DestroyTexture(background);
		Clean_Up(window, renderer);
		return EXIT_FAILURE;
		
	}

	int iWencode = 259, iHencode = 67, xEncode = 0, yEncode = 0;
	SDL_Rect encodeClips[3];
	for(int i = 0; i < 3; i++){
		encodeClips[i].x = i * iWencode; 
		encodeClips[i].y = 0;
		encodeClips[i].w = iWencode;
		encodeClips[i].h = iHencode;
	}

	SDL_Texture * decode_btn = Load_Texture("../images/Decode_btnSprites.png", renderer);
	if(!decode_btn){
	
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(encode_btn);
		Clean_Up(window, renderer);
		return EXIT_FAILURE;
	}

	int iWdecode = 259, iHdecode = 67, xDecode = 435, yDecode = 0;
	SDL_Rect decodeClips[3];
	for(int i = 0; i < 3; i++){
	
		decodeClips[i].x = i * iWdecode;
		decodeClips[i].y = 0;
		decodeClips[i].w = iWdecode;
		decodeClips[i].h = iHdecode;
	}

	SDL_Texture * submit_btn = Load_Texture("../images/Submit_btn.png", renderer);
	if(!submit_btn){
	
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(encode_btn);
		SDL_DestroyTexture(decode_btn);
		Clean_Up(window, renderer);
		return EXIT_FAILURE;
	
	}

	int iWsubmit = 259, iHsubmit = 67, xSubmit = 825, ySubmit = 508;

	SDL_Texture * inputText = Load_Texture("../images/InputText.png", renderer);
	if(!inputText){
	
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(encode_btn);
		SDL_DestroyTexture(decode_btn);
		SDL_DestroyTexture(submit_btn);
		Clean_Up(window, renderer);
		return EXIT_FAILURE;
	
	}

	int xInput = 660, xOutput = 660, yInput = 450, yOutput = 600, iWinputText = 610, iHinputText = 51;
	char * textInput = malloc(sizeof(char) * 61);
	strcpy(textInput, "Put your text here !");
	SDL_Color black = {0, 0, 0, 0xFF};
	SDL_Texture * texte = Render_Text(textInput, "../fonts/arial_narrow_7.ttf", black, 24, renderer);
	if(!texte){
	
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(encode_btn);
		SDL_DestroyTexture(decode_btn);
		SDL_DestroyTexture(submit_btn);
		SDL_DestroyTexture(inputText);
		Clean_Up(window, renderer);
		return EXIT_FAILURE;
	}
	
	int xTexte = xInput + 20, yTexte = yInput + 20;

	char * outputText = malloc(sizeof(char) * 80);
	memset(outputText, 0, strlen(outputText));
	SDL_Texture * output = Render_Text(" \0", "../fonts/arial_narrow_7.ttf", black, 24, renderer);
	if(!output){
	
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(encode_btn);
		SDL_DestroyTexture(decode_btn);
		SDL_DestroyTexture(submit_btn);
		SDL_DestroyTexture(inputText);
		SDL_DestroyTexture(texte);
		Clean_Up(window, renderer);
		return EXIT_FAILURE;
	}
	
	int xTexteOutput = xOutput + 20, yTexteOutput = yOutput + 20;
	int hoverEncode = 0, OnClickEncode = 0, encodeSelect = 1;
	int hoverDecode = 0, OnClickDecode = 0, decodeSelect = 0;
	int hoverSubmit = 0, OnClickSubmit = 0;
	int clickForText = 0;
	
	Uint32 frameStart, frameTime;
	SDL_StartTextInput();
	while(!SDL_QuitRequested()){
		
		frameStart = SDL_GetTicks();
		SDL_Event event;
		int reRenderText = 0;
		
		while(SDL_PollEvent(&event)){
		
			switch(event.type){
			
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT){
						if(isInRegion(event.button.x, event.button.y, xEncode, xEncode + iWencode, yEncode, yEncode + iHencode)){
						
							hoverEncode = 0;
							OnClickEncode = 1;
							encodeSelect = 1;
							decodeSelect = 0;
						}

						else if(isInRegion(event.button.x, event.button.y, xDecode, xDecode + iWdecode, yDecode, yDecode + iHdecode)){
			
							hoverDecode = 0;
							OnClickDecode = 1;
							encodeSelect = 0;
							decodeSelect = 1;
						}

						else if(isInRegion(event.button.x, event.button.y, xSubmit, xSubmit + iWsubmit, ySubmit, ySubmit + iHsubmit)){
			
							hoverSubmit = 0;
							OnClickSubmit = 1;
						}

						else if(isInRegion(event.button.x, event.button.y, xInput, xInput + iWinputText, yInput, yInput + iHinputText)) {
						
							clickForText = 1;
						
						}
						
						else if(clickForText){
						
							clickForText = 0;
						
						}
					}
				break;

				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT){
						
						if(isInRegion(event.button.x, event.button.y, xEncode, xEncode + iWencode, yEncode, yEncode + iHencode)){
						
							hoverEncode = 1;
							OnClickEncode = 0;
						
						}

						else if(isInRegion(event.button.x, event.button.y, xDecode, xDecode + iWdecode, yDecode, yDecode + iHdecode)){
			
							hoverDecode = 1;
							OnClickDecode = 0;
			
						}

						else{
							hoverEncode = 0;
							OnClickEncode = 0;
							hoverDecode = 0;
							OnClickDecode = 0;
							hoverSubmit = 0;
							OnClickSubmit = 0;
						}						
					}
				break;

				case SDL_MOUSEMOTION:
					if(isInRegion(event.motion.x, event.motion.y, xEncode, xEncode + iWencode, yEncode, yEncode + iHencode)){
					
						if(!OnClickEncode)
							hoverEncode = 1;
					
					}

					else if(isInRegion(event.motion.x, event.motion.y, xDecode, xDecode + iWdecode, yDecode, yDecode + iHdecode)){
					
						if(!OnClickDecode)
							hoverDecode = 1;
					
					}
					
					else{
						
						hoverEncode = 0;
						OnClickEncode = 0;
						hoverDecode = 0;
						OnClickDecode = 0;
					
					}
				break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							if(clickForText && strlen(textInput) > 0){
							
								textInput[strlen(textInput) - 1] = 0;
								reRenderText = 1;
							
							}
						break;

						case SDLK_c:
							if((SDL_GetModState() & KMOD_CTRL) && clickForText){
							
								SDL_SetClipboardText(textInput);
							}
						break;

						case SDLK_v:
							if((SDL_GetModState() & KMOD_CTRL) && clickForText){
							
								strcat(textInput, SDL_GetClipboardText());
								reRenderText = 1;
							
							}
						break;
					}
				break;

				case SDL_TEXTINPUT:
					if(!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL) && clickForText && strlen(textInput) < 60){
					
						strcat(textInput, event.text.text);
						reRenderText = 1;
					
					}
				break;
			}
		}

		if(reRenderText){
		
			SDL_DestroyTexture(texte);
			if(strcmp(textInput, "") != 0){
			
				texte = Render_Text(textInput, "../fonts/arial_narrow_7.ttf", black, 24, renderer);
				if(!texte){
					
					SDL_DestroyTexture(background);
					SDL_DestroyTexture(encode_btn);
					SDL_DestroyTexture(decode_btn);
					SDL_DestroyTexture(submit_btn);
					SDL_DestroyTexture(inputText);
					SDL_DestroyTexture(texte);
					SDL_DestroyTexture(output);
					Clean_Up(window, renderer);
					return EXIT_FAILURE;
				
				}
			}

			else{
				
				texte = Render_Text(" \0", "../fonts/arial_narrow_7.ttf", black, 24, renderer);
				if(!texte){
				
					SDL_DestroyTexture(background);
					SDL_DestroyTexture(encode_btn);
					SDL_DestroyTexture(decode_btn);
					SDL_DestroyTexture(submit_btn);
					SDL_DestroyTexture(inputText);
					SDL_DestroyTexture(texte);
					SDL_DestroyTexture(output);					
					Clean_Up(window, renderer);
					return EXIT_FAILURE;
				
				}				
			}
		}

		if(OnClickSubmit){
		
			OnClickSubmit = 0;
			SDL_DestroyTexture(output);
			if(decodeSelect){
				
				if(strcmp(textInput, "\0") != 0){
				
					memset(outputText, 0, strlen(outputText));
					char ** splitted = str_split(textInput, " \0");
					
					if(!splitted){
					
						fprintf(stderr, "Unable to split the string\n");
						return EXIT_FAILURE;
					
					}
					
					for(int i = 0; splitted[i] != NULL; i++){
					
						strcat(outputText, morseDecoder(tree, splitted[i]));
						if(splitted[i+1] != NULL){
							strcat(outputText, " \0");
						}
					}
					free(splitted); splitted = NULL;
					output = Render_Text(outputText, "../fonts/arial_narrow_7.ttf", black, 24, renderer);
					if(!output){
						
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(encode_btn);
						SDL_DestroyTexture(decode_btn);
						SDL_DestroyTexture(submit_btn);
						SDL_DestroyTexture(inputText);
						SDL_DestroyTexture(texte);					
						Clean_Up(window, renderer);
						return EXIT_FAILURE;
					
					}
				}
				else{
					
					SDL_Texture * output = Render_Text(" \0", "../fonts/arial_narrow_7.ttf", black, 24, renderer);
					if(!output){
					
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(encode_btn);
						SDL_DestroyTexture(decode_btn);
						SDL_DestroyTexture(submit_btn);
						SDL_DestroyTexture(inputText);
						SDL_DestroyTexture(texte);
						Clean_Up(window, renderer);
						return EXIT_FAILURE;
					}										
				}
			}
			else if(encodeSelect){
			
				if(strcmp(textInput, "\0") != 0){
				
					memset(outputText, 0, strlen(outputText));
					strcpy(outputText, morseEncrypter(tree, textInput));
					int pass = 0;
					int i = 0;
					while(outputText[i] != '.' && outputText[i] != '-'){
							pass++;
							i++;
					}
					
					char * outputTextPass = outputText + pass;
					output = Render_Text(outputTextPass, "../fonts/arial_narrow_7.ttf", black, 24, renderer);
					if(!output){
					
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(encode_btn);
						SDL_DestroyTexture(decode_btn);
						SDL_DestroyTexture(submit_btn);
						SDL_DestroyTexture(inputText);
						SDL_DestroyTexture(texte);					
						Clean_Up(window, renderer);
						return EXIT_FAILURE;
					
					}
				}
				else{
					
					SDL_Texture * output = Render_Text(" \0", "../fonts/arial_narrow_7.ttf", black, 24, renderer);
					if(!output){
						
						SDL_DestroyTexture(background);
						SDL_DestroyTexture(encode_btn);
						SDL_DestroyTexture(decode_btn);
						SDL_DestroyTexture(submit_btn);
						SDL_DestroyTexture(inputText);
						SDL_DestroyTexture(texte);
						Clean_Up(window, renderer);
						return EXIT_FAILURE;
						
					}					
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		Render_Texture(background, renderer, 0, 0, NULL);

		if(hoverEncode){
			Render_Texture(encode_btn, renderer, xEncode, yEncode, &encodeClips[1]);			
		}
		
		else if(OnClickEncode){
			Render_Texture(encode_btn, renderer, xEncode, yEncode, &encodeClips[2]);
		}
		
		else{
			Render_Texture(encode_btn, renderer, xEncode, yEncode, &encodeClips[0]);
		}

		if(hoverDecode){
			Render_Texture(decode_btn, renderer, xDecode, yDecode, &decodeClips[1]);
		}
		
		else if(OnClickDecode){
			Render_Texture(decode_btn, renderer, xDecode, yDecode, &decodeClips[2]);
		}
		
		else{
			Render_Texture(decode_btn, renderer, xDecode, yDecode, &decodeClips[0]);
		}

		Render_Texture(submit_btn, renderer, xSubmit, ySubmit, NULL);

		Render_Texture(inputText, renderer, xInput, yInput, NULL);
		Render_Texture(inputText, renderer, xOutput, yOutput, NULL);
		Render_Texture(texte, renderer, xTexte, yTexte, NULL);
		Render_Texture(output, renderer, xTexteOutput, yTexteOutput, NULL);
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;
		if(frameTime < DELAY_TIME){
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}


	SDL_StopTextInput();
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(encode_btn);
	SDL_DestroyTexture(decode_btn);
	SDL_DestroyTexture(submit_btn);
	SDL_DestroyTexture(inputText);
	SDL_DestroyTexture(texte);
	SDL_DestroyTexture(output);	
	Clean_Up(window, renderer);
	free(textInput);
	free(outputText);
	return EXIT_SUCCESS;
}


/* Initialization of SDL2, IMG and TTF */
int SDLnIMGnTTF_Initialize(){

	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
	
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	
	}

	if((initted & flags) != flags){
		
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize png images: %s\n", IMG_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
		
	}

	if(TTF_Init() == -1){

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize font feature: %s\n", TTF_GetError());
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;

	}

	return EXIT_SUCCESS;
}


/* Checking Region */
bool isInRegion(int x, int y, int xInf, int xSup, int yInf, int ySup){

	if((x >= xInf && x <= xSup) && (y >= yInf && y <= ySup))
		return true;
	return false;

}

/* Load texture */
SDL_Texture * Load_Texture(const char * filename, SDL_Renderer * renderer){

	SDL_Texture * texture = IMG_LoadTexture(renderer, filename);
	if(!texture){
	
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture: %s\n", SDL_GetError());
		return NULL;
	
	}

	return texture;
}

/* Copy the text to the rendering */
SDL_Texture * Render_Text(const char * text, const char * fontName, SDL_Color color, int fontSize, SDL_Renderer * renderer){

	TTF_Font * font = TTF_OpenFont(fontName, fontSize);
	if(!font){
	
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to open font: %s\n", TTF_GetError());
		return NULL;
	
	}

	SDL_Surface * surface = TTF_RenderText_Blended(font, text, color);
	
	if(!surface){
		TTF_CloseFont(font);
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to apply text on surface: %s\n", TTF_GetError());
		return NULL;
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	if(!texture){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture: %s\n", SDL_GetError());
	}
	
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}

/* Copy the texture clipped to the rendering */
void Render_Texture_Clip(SDL_Texture * texture, SDL_Renderer * renderer, SDL_Rect dest, SDL_Rect * clip){

	SDL_RenderCopy(renderer, texture, clip, &dest);

}

/* Copy the texture to the rendering */
void Render_Texture(SDL_Texture * texture, SDL_Renderer * renderer, int x, int y, SDL_Rect * clip){

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	if(!clip){
		
		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	}
	
	else{
	
		dest.w = clip->w;
		dest.h = clip->h;
	
	}
	Render_Texture_Clip(texture, renderer, dest, clip);
}

/* Clean all */
void Clean_Up(SDL_Window * window, SDL_Renderer * renderer){

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
