#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printboard(char **board, int dim){
	for (int j = 0; j <= 4*dim; ++j)
	{
		printf("-");
	}
	printf("\n");
	for (int i = 0; i < dim; ++i)
	{
		printf("| ");
		for (int j = 0; j < dim; ++j)
		{
			printf("%c | ", board[i][j]);
		}
		printf("\n");
		for (int j = 0; j <= 4*dim; ++j)
		{
			printf("-");
		}
		printf("\n");
	}
}

void checkthrees(char **board, int dim){
	// printf("checking for doubles\n");
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			// printf("board[%d][%d]=%c\n", i, j, board[i][j]);
			if(j < dim-1 && board[i][j] == board[i][j+1] && board[i][j] != ' '){ //two of the same color in a row, cap ends
				// printf("found double in a row %d %d\n", i, j);
				if (j > 0){
					board[i][j-1] = board[i][j] == 'R'?'B':'R';
				}
				if (j < dim-2)
				{
					// printf("capping double\n");
					board[i][j+2] = board[i][j] == 'R'?'B':'R';
				}
			}
			if(i < dim-1 && board[i][j] == board[i+1][j] && board[i][j] != ' '){ //two of the same color in a column, cap ends
				// printf("found double in column %d %d\n", i, j);
				if (i > 0){
					board[i-1][j] = board[i][j] == 'R'?'B':'R';
				}
				if (i < dim-2)
				{
					board[i+2][j] = board[i][j] == 'R'?'B':'R';
				}
			}
			if(j < dim-2 && (board[i][j] == 'R' || board[i][j] == 'B') && board[i][j] == board[i][j+2] && board[i][j+1] == ' '){ //two of the same color in a column, cap ends
				// printf("found double sepparated in row %d %d\n", i, j);
					board[i][j+1] = board[i][j] == 'R'?'B':'R';
			}
			if(i < dim-2 && (board[i][j] == 'R' || board[i][j] == 'B') && board[i][j] == board[i+2][j] && board[i+1][j] == ' '){ //two of the same color in a column, cap ends
				// printf("found double sepparated in column %d %d\n", i, j);
					board[i+1][j] = board[i][j] == 'R'?'B':'R';
			}
		}
	}
}

void balancerows(char **board, int dim){
	// printf("checking rows\n");
	int countred = 0, countblue = 0, flag = 0, hasspaces = 0, spaces[dim];
	for (int i = 0; i < dim; ++i)
	{
		flag = 0;
		countred = 0;
		countblue = 0;
		hasspaces = 0;
		for (int j = 0; j < dim; ++j)
		{
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
			// printf("countblue: %d countred: %d\n", countblue, countred);
			if(countblue == dim/2){
				for (int k = 0; k < flag; ++k)
				{
					board[i][spaces[k]] = 'R';
				}
			}
			else if(countred == dim/2){
				for (int k = 0; k < flag; ++k)
				{
					board[i][spaces[k]] = 'B';
				}
			}
		}
		if(hasspaces == 2){
			// printf("hasspaces 2\n");
			for (int k = 0; k < dim; ++k)
			{
				flag = 1;
				if(k == i)
					continue;
				for (int l = 0; l < dim; ++l)
				{
					if(board[i][l] != ' ' && board[i][l] != board[k][l]){ //matches all characters common to both lines
						// printf("board[%d][%d] = %c board[%d][%d] = %c\n", i, l, board[i][l], k, l, board[k][l]);
						// printf("went wrong %d %d\n", k, i);
						flag = 0;
					}
					// else{
					// 	flag = 0;
					// }
				}
				if(flag){
					// printf("filling in %d from %d\n", i, k);
					board[i][spaces[0]] = board[k][spaces[1]];
				}
			
			}
		}
	}
}

void balancecols(char **board, int dim){
	// printf("checking cols\n");
	int countred = 0, countblue = 0, flag = 0, hasspaces = 0, spaces[dim];
	for (int i = 0; i < dim; ++i)
	{
		flag = 0;
		countred = 0;
		countblue = 0;
		hasspaces = 0;
		for (int j = 0; j < dim; ++j)
		{
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
			// printf("countblue: %d countred: %d\n", countblue, countred);
			if(countblue == dim/2){
				for (int k = 0; k < flag; ++k)
				{
					board[spaces[k]][i] = 'R';
				}
			}
			else if(countred == dim/2){
				for (int k = 0; k < flag; ++k)
				{
					board[spaces[k]][i] = 'B';
				}
			}
		}
		if(hasspaces == 2){
		for (int k = 0; k < dim; ++k)
		{
			flag = 1;
			if(k == i)
				continue;
			for (int l = 0; l < dim; ++l)
			{
				// printf("hasspaces %d\n", hasspaces);
				if(board[l][i] != ' ' && board[l][i] != board[l][k]){ //matches all characters common to both lines
					flag = 0;
				}
				// else{
				// 	flag = 0;
				// }
			}
			if(flag){
				board[spaces[0]][i] = board[spaces[1]][k];
			}
			
		}
	}
	}

}

int checkwin(char **board, int dim){
	// return 1;
	int countred = 0, countblue = 0;
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			if(strcmp(board[i],board[j]) == 0 && i != j){
				return 0;
			}
			if(board[i][j] == 'R')
				countred++;
			else if(board[i][j] == 'B')
				countblue++;
			else //blank space
				return 0;
		}
		// printf("blue:%d red:%d\n", countblue, countred);
		if(countblue != countred && countred != dim/2)
			return 0;
	}
	return 1;
}

int main(int argc, char const *argv[]){
	int dim, count = 0;
	printf("Please enter the dimension of the board: ");
	scanf("%d%*c", &dim);
	char **board=(char **)malloc(sizeof(char*)*dim);
	printf("Please enter the board:\nex.\nB   \n R  \n    \n R R\n");
	 for (int i = 0; i < dim; ++i){
	 	board[i] = (char*)malloc(sizeof(char)*dim+1);
		for (int j = 0; j < dim; ++j){
		// fgets(board[i], dim, stdin);
			scanf("%c",&board[i][j]);
		}
		getchar();
		board[i][dim] = '\0';
	}
	printf("Board:\n");
	printboard(board, dim);
	while(!checkwin(board, dim)){
		checkthrees(board, dim);
		// printboard(board, dim);
		balancerows(board, dim);
		// printboard(board, dim);
		balancecols(board, dim);
		// printboard(board, dim);
		if(count++ >= dim*dim){
			printf("could not solve\n");
			break;
		}
	}
	printf("Final:\n");
	printboard(board, dim);
	for (int i = 0; i < dim; ++i)
	{
		free(board[i]);
	}
	free(board);
	return 0;
}
