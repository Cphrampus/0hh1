#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isletter(a) (('a'<=(a)&&(a)<='z')||('A'<=(a)&&(a)<='Z'))
#define RED		"\033[1;31m"
#define BLUE	"\033[1;36m"
#define NONE  	"\033[0m"

int possible(char **board, int dim){
	int count = 0;
	for (int i = 0; i < dim; i++){
		for (int j = 0; j < dim; j++){
			count += board[i][j] != ' '?1:0;
		}
	}
	if(count >= (dim*dim)/5)
		return 1;
	return 0;
}


void clearBoard(int dim){
	system("sleep 0.5");
	for (int i = 0; i < 2*dim+1; i++){
		fprintf(stdout, "\033[F");
	}
}

void printBoard(char **board, int dim){
	for (int j = 0; j < dim; ++j){
		printf("+-");
	}
	printf("+");
	printf("\n");
	for (int i = 0; i < dim; ++i){
		printf("|");
		for (int j = 0; j < dim; ++j){
			if(board[i][j]=='R'){
				printf("%s█", RED);
			}
			else if (board[i][j]=='B'){
				printf("%s█", BLUE);
			}
			else{
				printf(" ");
			}
			printf("%s|", NONE);
		}
		printf("\n");
		for (int j = 0; j < dim; ++j){
			printf("+-");
		}
		printf("+");
		printf("\n");
	}
}

char** readBoard(int dim){ //read in board char by char, uses raw mode to allow writing intermediate chars
	system("stty raw");
	char **board=(char **)malloc(sizeof(char*) * dim);
	for (int i = 0; i < dim; i++){
		board[i] = (char *)malloc(sizeof(char)*dim+1);
		for (int j = 0; j < dim; j++){
			board[i][j] = ' ';
		}
		board[i][dim] = '\0';
	}
	for (int j = 0; j < dim; ++j){
		printf("+-");
	}
	printf("+");
	printf("\r\n");
	for (int i = 0; i < dim; ++i){
		board[i] = (char*)malloc(sizeof(char)*dim+1);
		printf("|");
		char c;
		for (int j = 0; j < dim; ++j){
			do {	
				c = getchar();
				if(isletter(c)){
					c -=  ('a'<=c&&c<='z')?('a'-'A'):0;
				}
			} while(c != ' ' && c != 'R' && c != 'B');
			board[i][j] = c; 
			if(board[i][j]=='R'){
				printf("%s█", RED);
			}
			else if (board[i][j]=='B'){
				printf("%s█", BLUE);
			}
			else{
				printf(" ");
				
			}
			//putchar(board[i][j]);
			printf("%s|", NONE);
		}
		printf("\r\n");
		for (int j = 0; j < dim; ++j){
			printf("+-");
		}
		printf("+\r\n");
		board[i][dim] = '\0';
	}
	system("stty cooked");
	return board;
}

int checkThrees(char **board, int dim){
	int flag = 0;
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			if(j < dim-1 && board[i][j] == board[i][j+1] && board[i][j] != ' '){ //two of the same color in a row, cap ends
				if (j > 0 && board[i][j-1] == ' '){
					board[i][j-1] = board[i][j] == 'R'?'B':'R';
					flag++;
				}
				if (j < dim-2 && board[i][j+2] == ' '){
					board[i][j+2] = board[i][j] == 'R'?'B':'R';
					flag++;
				}
			}
			if(i < dim-1 && board[i][j] == board[i+1][j] && board[i][j] != ' '){ //two of the same color in a column, cap ends
				if (i > 0 && board[i-1][j] == ' '){
					board[i-1][j] = board[i][j] == 'R'?'B':'R';
					flag++;
				}
				if (i < dim-2 && board[i+2][j] == ' '){
					board[i+2][j] = board[i][j] == 'R'?'B':'R';
					flag++;
				}
			}
			if(j < dim-2 && (board[i][j] == 'R' || board[i][j] == 'B') && board[i][j] == board[i][j+2] && board[i][j+1] == ' '){ //two of the same color in a column, cap ends
				board[i][j+1] = board[i][j] == 'R'?'B':'R';
				flag++;
			}
			//if(i < dim-2)
			//	printf("board[%d][%d]=%c board[%d][%d]=%c board[%d][%d]=%c\n", i, j, board[i][j], i+1, j, board[i+1][j], i+2, j, board[i+2][j]);
			if(i < dim-2 && (board[i][j] == 'R' || board[i][j] == 'B') && board[i][j] == board[i+2][j] && board[i+1][j] == ' '){ //two of the same color in a column, cap ends
				board[i+1][j] = board[i][j] == 'R'?'B':'R';
				flag++;
			}
		}
	}
	return flag;
}

int balanceRows(char **board, int dim){
	int countred = 0, countblue = 0, flag = 0, hasspaces = 0, spaces[dim], ret = 0;
	for (int i = 0; i < dim; ++i){
		flag = 0;
		countred = 0;
		countblue = 0;
		hasspaces = 0;
		for (int j = 0; j < dim; ++j){
			if(board[i][j] == 'R')
				countred++;
			else if(board[i][j] == 'B')
				countblue++;
			else{ //blank space
				spaces[flag++] = j;
				hasspaces++;
			}
		}
		if(flag){
			if(countblue == dim/2){
				for (int k = 0; k < flag; ++k){
					board[i][spaces[k]] = 'R';
					ret++;
				}
			}
			else if(countred == dim/2){
				for (int k = 0; k < flag; ++k){
					board[i][spaces[k]] = 'B';
					ret++;
				}
			}
		}
		if(hasspaces == 2){
			for (int k = 0; k < dim; ++k){
				flag = 1;
				if(k == i)
					continue;
				for (int l = 0; l < dim; ++l){
					if(board[i][l] != ' ' && board[i][l] != board[k][l]){ //matches all characters common to both lines
						flag = 0;
					}
				}
				if(flag){
					board[i][spaces[0]] = board[k][spaces[1]];
					ret++;
				}

			}
		}
	}
	return ret;
}

int balanceCols(char **board, int dim){
	int countred = 0, countblue = 0, flag = 0, hasspaces = 0, spaces[dim], ret = 0;
	for (int i = 0; i < dim; ++i){
		flag = 0;
		countred = 0;
		countblue = 0;
		hasspaces = 0;
		for (int j = 0; j < dim; ++j){
			if(board[j][i] == 'R')
				countred++;
			else if(board[j][i] == 'B')
				countblue++;
			else{ //blank space
				spaces[flag++] = j;
				hasspaces++;
			}
		}
		if(flag){
			if(countblue == dim/2){
				for (int k = 0; k < flag; ++k){
					board[spaces[k]][i] = 'R';
					ret++;
				}
			}
			else if(countred == dim/2){
				for (int k = 0; k < flag; ++k){
					board[spaces[k]][i] = 'B';
					ret++;
				}
			}
		}
		if(hasspaces == 2){
			for (int k = 0; k < dim; ++k){
				flag = 1;
				if(k == i)
					continue;
				for (int l = 0; l < dim; ++l){
					if(board[l][i] != ' ' && board[l][i] != board[l][k]){ //matches all characters common to both lines
						flag = 0;
					}
				}
				if(flag){
					board[spaces[0]][i] = board[spaces[1]][k];
					ret++;					
				}

			}
		}
	}
	return ret;
}

int checkWin(char **board, int dim){
	int countred = 0, countblue = 0;
	for (int i = 0; i < dim; ++i){
		countred = 0;
		countblue = 0;
		for (int j = 0; j < dim; ++j){
			if(strcmp(board[i],board[j]) == 0 && i != j){
				printf("impossible board\n");
				exit(1);
			}
			if(board[i][j] == 'R')
				countred++;
			else if(board[i][j] == 'B')
				countblue++;
			else //blank space
				return 0;
		}
		if(countblue > dim/2 || countred > dim/2){
			printf("impossible board\n");
			exit(1);
		}
		if(countblue != countred && countred != dim/2)
			return 0;
	}
	return 1;
}

int main(int argc, char const *argv[]){
	int dim, count = 0;
	printf("Please enter the dimension of the board: ");
	scanf("%d%*c", &dim);
	printf("Please enter the board:\nex.\n"
			"+-+-+-+-+\n"
			"|B| | | |\n"
			"+-+-+-+-+\n"
			"| |R| | |\n"
			"+-+-+-+-+\n"
			"| | | | |\n"
			"+-+-+-+-+\n"
			"| |R| |R|\n"
			"+-+-+-+-+\n\n\n");
	char **board = readBoard(dim);
	if(!possible(board, dim)){
		printf("Board not possible to solve\n");
		return 1;
	}
	int flag; // Variable to chack that something was changed
	while(checkWin(board, dim) != 1){
		flag = checkThrees(board, dim);
		clearBoard(dim);
		printBoard(board, dim);

		flag += balanceRows(board, dim);
		clearBoard(dim);
		printBoard(board, dim);

		flag += balanceCols(board, dim);
		clearBoard(dim);
		printBoard(board, dim);
		if(flag == 0 || count++ >= dim*dim){
			clearBoard(dim);
			fprintf(stdout, "\033[F");
			fprintf(stdout, "\033[F");
			printf("could not solve\n");
			for (int i = 0; i <= 2*dim+1; i++){
				printf("\n");
			}
			break;
		}
	}
	clearBoard(dim);
	fprintf(stdout, "\033[F");
	printf("Final:\n");
	printBoard(board, dim);
	for (int i = 0; i < dim; ++i){
		free(board[i]);
	}
	free(board);
	//printf("\033[1;31m█ \033[1;36m█\n");
	return 0;
}
