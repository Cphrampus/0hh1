#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isletter(a) (('a'<=(a)&&(a)<='z')||('A'<=(a)&&(a)<='Z'))
#define RED		"\033[1;31m"
#define BLUE		"\033[1;36m"
#define NONE  		"\033[0m"

void attemptSolution(char **board, int dim){ //randomly assign values in board to attempt to have a unique solution
	static int version = 0, count = 0;
	printf("attemping to solve, %d\n", version++);
	//for(; count <= (dim*dim)/5;){
		int posx = random()%dim, posy = random()%dim;
		if(board[posx][posy] == ' '){
			if(posy < dim - 1 && board[posx][posy+1] == ' '){
				board[posx][posy+1] = random()%2?'B':'R';
				count++;
			}
			else if(posy < dim - 1 && board[posx][posy+1] == 'B'){
				board[posx][posy] = 'B';
				count++;
			}
			if(posy > 0 && board[posx][posy-1] == ' '){
				board[posx][posy-1] = random()%2?'B':'R';
				count++;
			}
			else if(posy > 0 && board[posx][posy-1] == 'B'){
				board[posx][posy] = 'B';
				count++;
			}
			if(posx < dim - 1 && board[posx+1][posy] == ' '){
				board[posx+1][posy] = random()%2?'B':'R';
				count++;
			}
			else if(posx < dim - 1 && board[posx+1][posy] == 'B'){
				board[posx][posy] = 'B';
				count++;
			}
			if(posx > 0 && board[posx-1][posy] == ' '){
				board[posx-1][posy] = random()%2?'B':'R';
				count++;
			}
			else if(posx > 0 && board[posx-1][posy] == 'B'){
				board[posx][posy] = 'B';
				count++;
			}
		}
		else if(posy < dim - 1 && board[posx][posy+1] == ' ' && board[posx][posy-1] == ' '){
				board[posx][posy+1] = board[posx][posy];
		}
	//}
	//printf("attempt\n");
}

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
	static int count = 0;
	//printf("                                              %d\n", count++);
	system("sleep 0.5");
	for (int i = 0; i < 2*dim+1; i++){
		fprintf(stdout, "\033[F");
	}
}

void printBoard(char **board, int dim, int simple){
	for (int j = 0; j < dim; ++j){
		printf("+-");
	}
	printf("+");
	printf("\n");
	for (int i = 0; i < dim; ++i){
		printf("|");
		for (int j = 0; j < dim; ++j){
			if(board[i][j]=='R'){
				if (!simple)
					printf("%s█", RED);
				else
					printf("R");
			}
			else if (board[i][j]=='B'){
				if (!simple)
					printf("%s█", BLUE);
				else
					printf("B");
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

char** readBoard(int dim, int simple){ //read in board char by char, uses raw mode to allow writing intermediate chars
	system("stty raw");
	char **board=(char **)malloc(sizeof(char*) * dim);
	for (int i = 0; i < dim; i++){
		board[i] = (char *)malloc(sizeof(char)*dim+1);
		for (int j = 0; j < dim; j++){
			board[i][j] = ' ';
		}
		board[i][dim] = '\0';
	}
	if(!simple){
		for (int j = 0; j < dim; ++j){
			printf("+-");
		}
		printf("+");
		printf("\r\n");
	}
	for (int i = 0; i < dim; ++i){
		board[i] = (char*)malloc(sizeof(char)*dim+1);
		if(!simple)
			printf("|");
		char c;
		for (int j = 0; j < dim; ++j){
			do {	
				c = getchar();
				if(isletter(c)){
					c -=  ('a'<=c&&c<='z')?('a'-'A'):0;
				}
				if(c == 3 || c == 4){ //ctrl c or d
					system("stty cooked");
					exit(1);
				}
				if(c == '\n')
					printf("\n");
			} while(c != ' ' && c != 'R' && c != 'B');
			board[i][j] = c; 
			if(board[i][j]=='R'){
				if (!simple)
					printf("%s█", RED);
				else
					printf("R");

			}
			else if (board[i][j]=='B'){
				if (!simple)
					printf("%s█", BLUE);
				else
					printf("B");
			}
			else{
				printf(" ");

			}
			//putchar(board[i][j]);
			if (!simple)
				printf("%s|", NONE);
		}
		if(!simple){
			printf("\r\n");
			for (int j = 0; j < dim; ++j){
				printf("+-");
			}
			printf("+\r\n");
		}
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
			int flag = 0;
			if(strcmp(board[i],board[j]) == 0 && i != j && strchr(board[i], ' ') == NULL){ //check for impossible boards
				//printBoard(board, dim, 0);
				//printf("i %d\nj %d\nboard[i] %s\nboard[j] %s\n", i, j, board[i], board[j]);
				flag++;
			}
			else{
				if(j == 0 && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] != ' '){
					//printf("1\n");
					flag++;
				}
				else if(j == dim-1 && board[i][j] == board[i][j-1] && board[i][j] == board[i][j-2] && board[i][j] != ' '){
					//printf("2\n");
					flag++;
				}
				else if(board[i][j] == board[i][j-1] && board[i][j] == board[i][j+1] && board[i][j] != ' '){
					//printf("3\n");
					flag++;
				}
			}
			if(flag){
				printf("flag: %d impossible board\n", flag);
				return -1;

			}
			if(board[i][j] == 'R'){
				countred++;
			}
			else if(board[i][j] == 'B'){
				countblue++;
			}
			else //blank space
				return 0;
		}
		if(countblue > dim/2 || countred > dim/2){
			printf("impossible board\n");
			return -1;
		}
		if(countblue != countred && countred != dim/2)
			return 0;
	}
	return 1;
}

int solve(char **board, int dim, int simple){
	int count = 0; //number of times functions have been run to keep from infinite loop
	int flag; // Variable to chack that something was changed
	int thing = 1, win;
	while((win = checkWin(board, dim)) == 0){
		flag = checkThrees(board, dim);
		if(!simple){
			clearBoard(dim);
			printBoard(board, dim, simple);
		}

		flag += balanceRows(board, dim);
		if(!simple){
			clearBoard(dim);
			printBoard(board, dim, simple);
		}

		flag += balanceCols(board, dim);
		if(!simple){
			clearBoard(dim);
			printBoard(board, dim, simple);
		}
		if(flag == 0 || count++ >= dim*dim*dim){
			//if(thing){
			//	attemptSolution(board, dim);
			//	solve(board, dim, simple);
			//	thing = 0;
			//}
			if(checkWin(board, dim))
				return 1;
			if(!simple){
				clearBoard(dim);
				fprintf(stdout, "\033[F");
				fprintf(stdout, "\033[F");
			}
			printf("could not solve\n");
			if(!simple)
				for (int i = 0; i <= 2*dim+1; i++){
					printf("\n");
				}
			return 0;
		}
	}
	if(win == -1){
		return -1;
	}
	return 1;
}

int main(int argc, char const *argv[]){
	int dim;
	int simple = 0, verbose = 0;;
	if(argc > 1 && strcmp(argv[1], "-s") == 0){
		simple = 1;
		printf("simple mode on\n");
	}
	
	if(argc > 2 && strcmp(argv[2], "-v") == 0){
		verbose = 1;
		printf("verbose mode on\n");
	}

	printf("Please enter the dimension of the board(4,6,8,10): ");
	const char *ex;
	do {
		scanf("%d%*c", &dim);
		switch(dim){
			case 4:
				ex = "+-+-+-+-+\n"
					"|B| | | |\n"
					"+-+-+-+-+\n"
					"| |R| | |\n"
					"+-+-+-+-+\n"
					"| | | | |\n"
					"+-+-+-+-+\n"
					"| |R| |R|\n"
					"+-+-+-+-+\n\n\n";
				break;
			case 6:
				ex = "+-+-+-+-+-+-+\n"
					"|R| | | | |R|\n"
					"+-+-+-+-+-+-+\n"
					"| | |B|B| | |\n"
					"+-+-+-+-+-+-+\n"
					"| | |B| | | |\n"
					"+-+-+-+-+-+-+\n"
					"| | | | | | |\n"
					"+-+-+-+-+-+-+\n"
					"| |R| | | |R|\n"
					"+-+-+-+-+-+-+\n"
					"|R| |B| | | |\n"
					"+-+-+-+-+-+-+\n\n\n";
				break;
			case 8:
				ex =  "+-+-+-+-+-+-+-+-+\n"
					"|R| | |R|R|B| |B|\n"
					"+-+-+-+-+-+-+-+-+\n"
					"| | | | | | | |B|\n"
					"+-+-+-+-+-+-+-+-+\n"
					"| | |R|R| | |B| |\n"
					"+-+-+-+-+-+-+-+-+\n"
					"|B|B| | | | | | |\n"
					"+-+-+-+-+-+-+-+-+\n"
					"| | | | | |R| | |\n"
					"+-+-+-+-+-+-+-+-+\n"
					"| | | | |B| |B| |\n"
					"+-+-+-+-+-+-+-+-+\n"
					"| |B| |B| | | | |\n"
					"+-+-+-+-+-+-+-+-+\n"
					"| | | |R| | | | |\n"
					"+-+-+-+-+-+-+-+-+\n\n\n";
				break;
			case 10:
				ex =  "+-+-+-+-+-+-+-+-+-+-+\n"
					"| | |B| |B| | | | | |\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"|R| | | |B| | | |R|R|\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"| | | | | | | | | |B|\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"|R| | |R| | | | | | |\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"| | | | |R| | | |B| |\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"| | | |R| |B|B| | | |\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"| | | | | |B| | | |B|\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"| |R| | | | | | | |B|\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"| | | | |B| | | |R| |\n"
					"+-+-+-+-+-+-+-+-+-+-+\n"
					"|B| |R| | | |B| | | |\n"
					"+-+-+-+-+-+-+-+-+-+-+\n\n\n";

				break;
			default:
				printf("please enter 4, 6, 8. or 10\n");
				break;
		}
	}while (dim != 4 && dim != 6 && dim != 8 && dim != 10);

	printf("Please enter the board:(r's, b's and spaces only, ctrl-c to exit)\nex.\n%s", ex);

	char **board = readBoard(dim, simple);

	//if(solve(board, dim, simple) != 1 || !possible(board, dim)){
		printf("\nBoard does not have unique solution\nattempting solution\n");//\033[F\033[F");
		srandom(dim);
		char **saveboard = (char**)malloc(sizeof(char*)*dim); //save original board
		for(int i = 0; i < dim; i++)
			saveboard[i] = strdup(board[i]);
		printf("saved board\n");
		printBoard(saveboard, dim, 0);
		printBoard(board, dim, 0);
		solve(board, dim, simple);
		for(int i = 0; i < dim*dim; i++){
			attemptSolution(board, dim);
			printBoard(board, dim, simple);
			if(solve(board, dim, simple)){
				break;
			}
			printf("saved board\n");
			printBoard(saveboard, dim, 0);
			printBoard(board, dim, 0);
			for(int j = 0; j < dim; j++){ //restore board
				board[i] = strcpy(board[j], saveboard[j]);
			}
			//memcpy(board, saveboard, dim*sizeof(char*)+dim*sizeof(char)); //restore original board
			printf("saved board\n");
			printBoard(saveboard, dim, 0);
			printBoard(board, dim, 0);
		}
		for (int i = 0; i < dim; ++i){
			//free(saveboard[i]);
		}
		//free(saveboard);
	//}
	//else{
		//solve(board, dim, simple);
		//attemptSolution(board, dim);
	//}
	if(!simple){
		clearBoard(dim);
		fprintf(stdout, "\033[F");
	}
	else
		printf("\n");
		
	printf("Final:\n");
	printBoard(board, dim, simple);
	for (int i = 0; i < dim; ++i){
		//free(board[i]);
	}
	//free(board);
	return 0;
}
