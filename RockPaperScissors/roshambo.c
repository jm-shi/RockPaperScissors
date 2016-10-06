//
//  roshambo.c
//  RockPaperScissors
//
//  Created on 9/2/16.
//

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Surface *loadImage(const char *srcImg) {
    SDL_Surface *outImage = SDL_LoadBMP(srcImg);
    return outImage;
}

void winner(SDL_Renderer *renderer, char *userChoice, char *compChoice) {
    SDL_Texture *texture;
    if (userChoice == NULL || compChoice == NULL) {
        return;
    }
    
    if (strcmp(userChoice, "rock") == 0) {
        if (strcmp(compChoice, "rock") == 0) {
            printf("Computer played Rock\n");
            printf("Tie\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/RockTie.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
        else if (strcmp(compChoice, "paper") == 0) {
            printf("Computer played Paper\n");
            printf("Red paper ate blue rock\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/RedPaperWin.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
        else {
            printf("Computer played Scissors\n");
            printf("Blue rock smashed red scissors\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/BlueRockWin.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
    }
    
    else if (strcmp(userChoice, "paper") == 0) {
        if (strcmp(compChoice, "rock") == 0) {
            printf("Computer played Rock\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/BluePaperWin.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
        else if (strcmp(compChoice, "paper") == 0) {
            printf("Computer played Paper\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/PaperTie.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
        else {
            printf("Computer played Scissors\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/RedScissorsWin.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
    }
    
    else if (strcmp(userChoice, "scissors") == 0) {
        if (strcmp(compChoice, "rock") == 0) {
            printf("Computer played Rock\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/RedRockWin.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
        else if (strcmp(compChoice, "paper") == 0) {
            printf("Computer played Paper\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/BlueScissorsWin.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
        else {
            printf("Computer played Scissors\n");
            texture = IMG_LoadTexture(renderer, "bmp_Images/ScissorsTie.bmp");
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }
    }
    
    printf("\n");
    SDL_RenderPresent(renderer);
}

char *compChoice() {
    srand((int)time(NULL));
    
    char *options[3] = {"rock",
        "paper",
        "scissors"};
    
    int randomIndex = rand() % 3; // 0 1 2
    char * compChoice = options[randomIndex];
    printf("compChoice is %s\n", compChoice);
    return compChoice;
}

void playAgainButtons(SDL_Renderer *renderer) {
    SDL_Rect playAgainRect;
    playAgainRect.x = WIDTH/10;
    playAgainRect.y = 0;
    playAgainRect.w = WIDTH/4;
    playAgainRect.h = HEIGHT/4;
    
    SDL_Rect yesRect;
    yesRect.x = WIDTH/10 + WIDTH/2;
    yesRect.y = 0;
    yesRect.w = WIDTH/8;
    yesRect.h = HEIGHT/8;
    
    SDL_Rect noRect;
    noRect.x = WIDTH/10 + WIDTH/2;
    noRect.y = WIDTH/8;
    noRect.w = WIDTH/8;
    noRect.h = HEIGHT/8;
    
    TTF_Font *font = TTF_OpenFont("Franklin Gothic Book Regular", 25);
    SDL_Color blue = {0, 0, 255};
    
    SDL_Surface *sPlayAgain = TTF_RenderText_Solid(font, "Play again?", blue);
    
    SDL_Surface *sYes = TTF_RenderText_Solid(font, "Yes", blue);
    SDL_Surface *sNo = TTF_RenderText_Solid(font, "No", blue);
    
    SDL_Texture *playAgain = SDL_CreateTextureFromSurface(renderer, sPlayAgain);
    SDL_Texture *yes = SDL_CreateTextureFromSurface(renderer, sYes);
    SDL_Texture *no = SDL_CreateTextureFromSurface(renderer, sNo);
    
    SDL_RenderCopy(renderer, playAgain, NULL, &playAgainRect);
    SDL_RenderCopy(renderer, yes, NULL, &yesRect);
    SDL_RenderCopy(renderer, no, NULL, &noRect);
}

// Add the words the message to the top of the screen
void addPlayerText(SDL_Renderer *renderer, SDL_Texture *message) {
    // First add white screen
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH;
    rect.h = HEIGHT/10;
    SDL_Texture *whiteTexture = IMG_LoadTexture(renderer, "bmp_Images/blankScreen.bmp");
    SDL_RenderCopy(renderer, whiteTexture, NULL, &rect);
    
    // Then add the message
    SDL_Rect messageRect;
    messageRect.x = 110;
    messageRect.y = 0;
    messageRect.w = WIDTH-200;
    messageRect.h = HEIGHT/10;
    SDL_RenderCopy(renderer, message, NULL, &messageRect);
}

void moveImg(SDL_Renderer *renderer, SDL_Rect rect, char *move, bool isUser) {
    if (move == NULL) {
        return;
    }
    if (strcmp(move, "rock") == 0) {
        SDL_Texture *texture;
        if (isUser) {
            texture = IMG_LoadTexture(renderer, "bmp_Images/MyRock.bmp");
        }
        else {
            texture = IMG_LoadTexture(renderer, "bmp_Images/CompRock.bmp");
        }
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    else if (strcmp(move, "paper") == 0) {
        SDL_Texture *texture;
        if (isUser) {
            texture = IMG_LoadTexture(renderer, "bmp_Images/MyPaper.bmp");
        }
        else {
            texture = IMG_LoadTexture(renderer, "bmp_Images/CompPaper.bmp");
        }
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    else if (strcmp(move, "scissors") == 0) {
        SDL_Texture *texture;
        if (isUser) {
            texture = IMG_LoadTexture(renderer, "bmp_Images/MyScissors.bmp");
        }
        else {
            texture = IMG_LoadTexture(renderer, "bmp_Images/CompScissors.bmp");
        }
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void showChoices(SDL_Renderer *renderer, SDL_Rect leftRect, SDL_Rect rightRect, SDL_Texture *leftTexture, SDL_Texture *rightTexture, SDL_Texture *message, char *userChoice, char *computerChoice) {
    
    moveImg(renderer, leftRect, userChoice, true);
    SDL_RenderCopy(renderer, rightTexture, NULL, &rightRect);
    addPlayerText(renderer, message);
    SDL_RenderPresent(renderer);
    
    SDL_Delay(1000);
    
    moveImg(renderer, leftRect, userChoice, true);
    moveImg(renderer, rightRect, computerChoice, false);
    SDL_RenderPresent(renderer);
    
}

// Reset to home screen
void reset(SDL_Renderer *renderer, SDL_Rect leftRect, SDL_Rect rightRect, SDL_Texture *leftTexture, SDL_Texture *rightTexture, SDL_Texture *message) {
    
    SDL_RenderCopy(renderer, leftTexture, NULL, &leftRect);
    SDL_RenderCopy(renderer, rightTexture, NULL, &rightRect);
    addPlayerText(renderer, message);
    SDL_RenderPresent(renderer);
}

int main(int argc, const char * argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    window = SDL_CreateWindow("Rock Paper Scissors",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_OPENGL);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_Surface *sBackground = loadImage("bmp_Images/RockPaperScissors.bmp");
    
    if (sBackground == NULL) {
        printf("background.bmp not found\n");
        SDL_Quit();
        exit(1);
    }
    
    SDL_Texture *tBackground = SDL_CreateTextureFromSurface(renderer, sBackground);
    
    // Render texture to screen
    SDL_RenderCopy(renderer, tBackground, NULL, NULL);
    // Update screen
    SDL_RenderPresent(renderer);
    
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    quit = true;
                    SDL_DestroyWindow(window);
                    SDL_DestroyRenderer(renderer);
                    SDL_Quit();
                    exit(0);
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_SPACE:
                            quit = true;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            SDL_DestroyWindow(window);
                            SDL_DestroyRenderer(renderer);
                            SDL_Quit();
                            exit(0);
                    }
                }
            }
        }
    }
    
    SDL_Rect leftRect;
    leftRect.x = 0;
    leftRect.y = HEIGHT/10;
    leftRect.w = WIDTH/2;
    leftRect.h = HEIGHT*9/10;
    SDL_Texture *leftTexture = IMG_LoadTexture(renderer, "bmp_Images/instructions.bmp");
    SDL_RenderCopy(renderer, leftTexture, NULL, &leftRect);
    
    SDL_Rect rightRect;
    rightRect.x = WIDTH/2;
    rightRect.y = HEIGHT/10;
    rightRect.w = WIDTH/2;
    rightRect.h = HEIGHT*9/10;
    SDL_Texture *rightTexture = IMG_LoadTexture(renderer, "bmp_Images/makeYourMove.bmp");
    SDL_RenderCopy(renderer, rightTexture, NULL, &rightRect);
    
    SDL_Surface *sMessage;
    TTF_Font *font = TTF_OpenFont("Franklin Gothic Book Regular.ttf", 25);
    SDL_Color blue = {0, 0, 255};
    
    sMessage = TTF_RenderText_Solid(font, "  You                         Computer", blue);
    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, sMessage);
    
    addPlayerText(renderer, message);
    SDL_RenderPresent(renderer);
    
    bool running = true;
    char *userChoice = NULL;
    
    while (running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            
            switch(event.type) {
                case SDL_QUIT: {
                    running = false;
                    break;
                }
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                            SDL_Quit();
                            exit(0);
                        case SDLK_r:
                            printf("You played Rock\n");
                            userChoice = "rock";
                            break;
                        case SDLK_p:
                            printf("You played Paper\n");
                            userChoice = "paper";
                            break;
                        case SDLK_s:
                            printf("You played Scissors\n");
                            userChoice = "scissors";
                            break;
                        default:
                            printf("Not a valid key\n");
                            continue;
                    }
                    
                }
                    
                    if (userChoice == NULL) {
                        printf("User choice is null\n");
                    }
                    char *computerChoice = compChoice();
                    // Show images of the user's pick and computer's pick
                    showChoices(renderer, leftRect, rightRect, leftTexture, rightTexture, message, userChoice, computerChoice);
                    
                    SDL_Delay(2000);
                    winner(renderer, userChoice, computerChoice);
                    
                    SDL_Delay(2000);
                    
                    reset(renderer,leftRect, rightRect, leftTexture, rightTexture, message);
            }
        }
    }
    
    SDL_DestroyTexture(tBackground);
    SDL_FreeSurface(sBackground);
    
    TTF_CloseFont(font);
    SDL_FreeSurface(sMessage);
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
    return 0;
}
