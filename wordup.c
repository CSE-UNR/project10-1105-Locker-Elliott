//Elliott Locker
//05/02/25
//Project 10

#include <stdio.h>
#define LENGTH 5
#define MAXGUESSES 6

int readMysteryWord(char word[]);
int stringLength(char str[]);
void makeUppercase(char str[]);
void toLowerCase(char str[]);
int validGuess(char guess[], char word[]);
void getUserInput(char guess[], int guessNum);
int correctGuess(char guess[], char word[]);
void printGuessList(char guesses[][LENGTH + 1], int count, char word[]);


int main(){
	char mysteryWord[LENGTH +1];
	char guesses[MAXGUESSES][LENGTH +1];
	int guessCount = 0;
	
	if (!readMysteryWord(mysteryWord)){
	return 1;
	}
	while (guessCount < MAXGUESSES){
		char guess[LENGTH + 2];
		
		while (1){
    		getUserInput(guess, guessCount);

   			if (validGuess(guess, mysteryWord)) {
       			break; 
    			}

   			printf("Your guess must be 5 letters long. Your guess must only contain letters.\n");
		}
		toLowerCase(guess);
		
			for(int i = 0; i <LENGTH; i++){
			guesses[guessCount][i] = guess[i];
			}	
			guesses[guessCount][LENGTH] = '\0';
	
	
			printGuessList(guesses, guessCount + 1, mysteryWord);
	
				if(correctGuess(guess, mysteryWord)){
				printf("		%s		\n", mysteryWord);
				printf("  	 You won in %d guesses!		\n		Nice!		\n", guessCount + 1);
				return 0; 
				}
				guessCount++;
	}
	printf("Sorry, you ran out of guesses, correct word was %s\n", mysteryWord);
	
	return 0;
}

int readMysteryWord(char word[]) {
	FILE *file = fopen("word.txt", "r");
	if (file == NULL) {
		printf("Failed to open word.txt\n");
		return 0;
	}
	fscanf(file, "%s", word);
	fclose(file);
	return 1;
}

int stringLength(char str[]) {
	int strLength = 0;
	while(str[strLength] != '\0'){
	strLength ++;
	}
	return strLength;
}

void makeUppercase(char str[]) {
	for (int i = 0; i < LENGTH; i++){
		if (str[i] >= 'a' && str[i] <= 'z') {
            	str[i] = str[i] - 'a' + 'A';
		}
	}
}
void toLowerCase(char str[]) {
	for (int i = 0; i < LENGTH; i++) {
       		if (str[i] >= 'A' && str[i] <= 'Z') {
            	str[i] = str[i] - 'A' + 'a';
      		}
   	}
}
int validGuess(char guess[], char word[]) {
 	if (stringLength(guess) != LENGTH) return 0;

   		for (int i = 0; i < LENGTH; i++) {
      		char c = guess[i];
      			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            return 0;
        		}
    		}
    return 1;
}
void getUserInput(char guess[], int guessNum){
		if (guessNum == MAXGUESSES - 1) {
   		printf("FINAL GUESS: ");
		}else{
  		printf("GUESS %d! Enter your guess: ", guessNum + 1);
		}
		scanf("%s", guess);
		int p;
		while(( p = getchar()) != '\n' && p != EOF){
	
		}
}

int correctGuess(char guess[], char word[]){
	for (int i=0; i<LENGTH; i++) {
		if(guess[i] != word[i])
		return 0;
	}
	return 1;
}

 

void printGuessList(char guesses[][LENGTH + 1], int count, char word[]) {
	printf("================================\n");

	for (int i = 0; i < count; i++) {
        char *guess = guesses[i];

        	for (int j = 0; j < LENGTH; j++) {
            		if (guess[j] == word[j]) {
               		if (guess[j] >= 'a' && guess[j] <= 'z') {
                    printf("%c", guess[j] - 'a' + 'A');
                	}else {
                    printf("%c", guess[j]);
                	}
            		}else {
                	printf("%c", guess[j]);
            		}		
        	}		
        printf("\n");
	for (int j = 0; j < LENGTH; j++) {
		if (guess[j] == word[j]) {
                printf(" ");
            	}else {
                int found = 0;
                	for (int k = 0; k < LENGTH; k++) {
                   		 if (guess[j] == word[k] && guess[k] != word[k]) {
                       		 found = 1;
                       		 break;
                    }
               		 }
               		 printf(found ? "^" : " ");
            	}
        }
        printf("\n");
    }
}

