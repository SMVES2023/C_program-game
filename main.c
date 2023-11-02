#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRIES 10
#define WORD_COUNT 7

char *words[WORD_COUNT] = {"computer", "programming", "hangman", "language", "development", "cyber security"};


void drawHangman(int tries) {
    printf("\n");
    if (tries >= 1) {
        printf("  O\n");
    }
    if (tries >= 2) {
        printf(" /");
        if (tries >= 3) {
            printf("|");
        }
        if (tries >= 4) {
            printf("\\");
        }
        printf("\n");
    }
    if (tries >= 5) {
        printf(" /");
    }
    if (tries >= 6) {
        printf(" \\\n");
    }
}

int chooseRandomWord(char *word) {
    int index = rand() % WORD_COUNT;
    strcpy(word, words[index]);
    return strlen(word);
}

void displayWord(char *word, char *guessed) {
    for (int i = 0; i < strlen(word); i++) {
        if (strchr(guessed, word[i]) != NULL) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    char word[50];
    char guessedLetters[26];
    int tries = 0;
    int wordLength = chooseRandomWord(word);
    char guess;

    for (int i = 0; i < 26; i++) {
        guessedLetters[i] = ' ';
    }
    printf("Welcome to Hangman!\n");
    printf("the words are computer,programming, hangman, language, development\n");

    while (1) {
        drawHangman(tries);
        displayWord(word, guessedLetters);

        printf("Enter a letter: ");
        scanf(" %c", &guess);

        if (strchr(guessedLetters, guess) != NULL) {
            printf("You already guessed that letter.\n");
        } else if (strchr(word, guess) != NULL) {
            guessedLetters[strlen(guessedLetters)] = guess;
            printf("Good guess!\n");
        } else {
            guessedLetters[strlen(guessedLetters)] = guess;
            tries++;
            printf("Incorrect guess. You have %d tries left.\n", MAX_TRIES - tries);
        }

        int allGuessed = 1;
        for (int i = 0; i < strlen(word); i++) {
            if (strchr(guessedLetters, word[i]) == NULL) {
                allGuessed = 0;
                break;
            }
        }

        if (allGuessed) {
            printf("Congratulations! You guessed the word: %s\n", word);
            break;
        }

        if (tries >= MAX_TRIES) {
            drawHangman(tries);
            printf("You ran out of tries. The word was: %s\n", word);
            break;
        }
    }

    return 0;
}
