#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Symbols used in the game.
const char PLAYER = 'X';
const char BOT = 'O';
const char EMPTY = ' ';

typedef struct {
    char board[9];
    bool isPlayer;
} Game;

// Creates a new game.
Game newGame();

// Executes a player's move.
bool play(Game *game, int place);

// Executes a bot's move.
void playBot(Game *game);

// Check if the game is over.
int isGameOver(Game *game);

int main() {
    Game game = newGame();

    printf("**************\n");

    if (game.isPlayer) {
        printf("You start!\n");
    } else {
        printf("Bot starts!\n");
    }

    printf("**************\n");

    while (true) {
        if (game.isPlayer) {
            int place;

            printf("Which place [1-9]?: ");
            scanf("%d", &place);

            if (!play(&game, place)) {
                printf("Impossible!\n");
                continue;
            }
        } else {
            printf("Bot plays!\n**************\n");
            playBot(&game);
        }

        for (int i = 0; i < 9; i++) {
            printf(i % 3 == 2 ? " %c\n" : " %c |", game.board[i]);
        }

        printf("**************\n");

        switch (isGameOver(&game)) {
            case 0:
                printf("You lost!\n");
                return 0;
            case 1:
                printf("You won!\n");
                return 0;
            default:
                break;
        }

        game.isPlayer = !game.isPlayer;
    }
}

Game newGame() {
    srand(time(0));

    bool isPlayer = rand() % 2;

    Game game = {{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, isPlayer};

    return game;
}

bool play(Game *game, int place) {
    if (place < 1 || place > 9 || game->board[place - 1] != EMPTY) {
        return false;
    }

    game->board[place - 1] = PLAYER;

    return true;
}

void playBot(Game *game) {
    int place = rand() % 9;

    while (true) {
        if (game->board[place] == EMPTY) {
            game->board[place] = BOT;
            break;
        }

        place++;

        if (place == 9) {
            place -= 9;
        }
    }
}

int isGameOver(Game *game) {
    if (game->board[0] != EMPTY && game->board[0] == game->board[1] && game->board[0] == game->board[2]) {
        return game->board[0] == PLAYER ? 1 : 0;
    } else if (game->board[3] != EMPTY && game->board[3] == game->board[4] && game->board[3] == game->board[5]) {
        return game->board[3] == PLAYER ? 1 : 0;
    } else if (game->board[6] != EMPTY && game->board[6] == game->board[7] && game->board[6] == game->board[8]) {
        return game->board[6] == PLAYER ? 1 : 0;
    } else if (game->board[0] != EMPTY && game->board[0] == game->board[3] && game->board[0] == game->board[6]) {
        return game->board[0] == PLAYER ? 1 : 0;
    } else if (game->board[1] != EMPTY && game->board[1] == game->board[4] && game->board[1] == game->board[7]) {
        return game->board[1] == PLAYER ? 1 : 0;
    } else if (game->board[2] != EMPTY && game->board[2] == game->board[5] && game->board[2] == game->board[8]) {
        return game->board[2] == PLAYER ? 1 : 0;
    } else if (game->board[0] != EMPTY && game->board[0] == game->board[4] && game->board[0] == game->board[8]) {
        return game->board[0] == PLAYER ? 1 : 0;
    } else if (game->board[2] != EMPTY && game->board[2] == game->board[4] && game->board[2] == game->board[6]) {
        return game->board[2] == PLAYER ? 1 : 0;
    }

    return -1;
}
