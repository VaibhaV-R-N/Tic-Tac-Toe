#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

void displayBoard();
int updateCpuMoves();
void randomMove();
int moveExists();
int cpuTurn(void);
int setMove(int x, int y, char move);
int isSpaceLeft();
int GameOver();


typedef struct{
	
	char name[25];
	char move;
	int co[2];
	int first;

} entity;

entity player, cpu;
int count,ind,indP;
int cpuMoves[18];
int cpuPMoves[18];
char winner,*c;
char buff[10];
char board[3][3] = {
			{' ',' ',' '},
			{' ',' ',' '},
			{' ',' ',' '}
		   };

int main(){
	printf("%+50s","****TIC - TAC - TOE****\n\n");
	strcpy(cpu.name,"CPU");

	printf("\nEnter your name : ");
	fgets(player.name,25,stdin);

	int size = sizeof(player.name)/sizeof(player.name[0]);

	if((c = strchr(player.name,'\n')) != NULL){
		*c = '\0';
	}

	while(player.move != 'X' && player.move != 'O'){
		printf("\nChoose a move (X or O) : ");
		scanf("%c",&player.move);
		scanf("%c");
		player.move = toupper(player.move);
	}
	

	cpu.move = (player.move == 'X')? 'O':'X';
	player.first = (player.move == 'X')? 1:0;
	while( GameOver()  && isSpaceLeft()){
		
		
		count = 0;
		if(player.first){
			displayBoard();
			while(count != 2){
		
				printf("\n%s enter your turn : ",player.name);
				fgets(buff,10,stdin);
				if(isdigit(buff[0])){
					count++;
				}
				for(int i=1; i<10;i++){
					if(isdigit(buff[i]) && buff[i-1] != '-'){
						count++;
					}
				}
			}
		
			sscanf(buff,"%d %d",&player.co[0],&player.co[1]);

			while((setMove(player.co[0],player.co[1],player.move)) == 1){
				count = 0;
				while(count != 2){
		
					printf("\n%s enter your turn : ",player.name);
					fgets(buff,10,stdin);
					if(isdigit(buff[0])){
						count++;
					}
					for(int i=1; i<10;i++){
						if(isdigit(buff[i]) && buff[i-1] != '-'){
							count++;
						}
					}
				}
				sscanf(buff,"%d %d",&player.co[0],&player.co[1]);
				
			}
		}
		cpuTurn();
		player.first = 1;


	}
	displayBoard();

	if(winner == player.move){
		printf("\n%s you won the game of tic-tac-toe.\n",player.name);
	}
	else if(winner == cpu.move){
		printf("\nCPU won the game.\n");
	}
	else{
		printf("\nIts a draw!\n");
	}

	return 0;
}

void displayBoard(){
	printf("\nStatus of the board : \n");
	printf("\n --- --- ---\n");
	for(int i=0; i<3; i++){
		
		for(int j=0; j<3; j++){
			
			printf("| %c ",board[i][j]);
			if(j == 2){
				printf("|");
			}
		}
		printf("\n --- --- ---\n");
	}

}



int setMove(int x, int y, char move){

	if(board[x][y] == ' '){
	
		board[x][y] = move;
		return 0;
	}
	return 1;

}

int isSpaceLeft(){

	for(int i=0; i<3; i++){
	
		for(int j=0; j<3; j++){
			if(board[i][j] == ' ')
				return 1;
		
		}
	}
	return 0;

}

int GameOver(){
	if(board[0][0] != ' ' && board[1][1] != ' ' && board[2][2] != ' '){
		if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
			winner = board[0][0];
			printf("%c",winner);
			return 0;
		}
	}
	if(board[0][2] != ' ' && board[1][1] != ' ' && board[2][0] != ' '){
		if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
			winner = board[0][2];
			printf("%c",winner);
			return 0;
		}
	}

	for(int i=0; i<3; i++){
		if(board[i][0] != ' ' && board[i][1] != ' ' && board[i][2] != ' '){
			if(board[i][0] == board[i][1] && board[i][1] == board[i][2]){
				winner = board[i][0];
				printf("%c",winner);
				return 0;
			}
		}
	}

	for(int i=0; i<3; i++){
		if(board[0][i] != ' ' && board[1][i] != ' ' && board[2][i] != ' '){
			if(board[0][i] == board[1][i] && board[1][i] == board[2][i]){
				winner = board[0][i];
				printf("%c",winner);
				return 0;
			}
		}
	}
	return 1;

}


int cpuTurn(void){

	if(moveExists() == 0){
		randomMove();
		return 0;
	}

	updateCpuMoves();
	printf("indP : %d\n",indP);
	// for(int i = 0;i<18;i++){
	// 	printf("%d\n",cpuPMoves[i]);
	// }

	// printf("\nvalue of ind : %d\n",ind);
	if(ind < 2) {
		randomMove();
		return 0;
	}

	srand(time(0));
	// if(indP == 0){
		int r = rand() % (ind-1);

		
		if(r % 2 == 0){
			setMove(cpuMoves[r],cpuMoves[r+1],cpu.move);
		}
		else{
			setMove(cpuMoves[r-1],cpuMoves[r],cpu.move);
		}
	// }
	// else{
	// 	int r = rand() % (indP-1);

		
	// 	if(r % 2 == 0){
	// 		setMove(cpuPMoves[r],cpuPMoves[r+1],cpu.move);
	// 	}
	// 	else{
	// 		setMove(cpuPMoves[r-1],cpuPMoves[r],cpu.move);
	// 	}
	// }

	return 0;	
}

int updateCpuMoves(){
	ind = 0;
	// indP = 0;
	// int x,y;

	// for(int i=0; i<3; i++){
	
	// 	for(int j=0; j<3;j++){
	// 		if(board[i][j] == cpu.move){
	// 			int c=0;
	// 			for(int k=0; k<3; k++){
	// 				if(board[k][j] == cpu.move){
	// 					c++;
	// 				}
	// 				if(board[k][j] == ' '){
	// 					 x = k;
	// 					 y = j;
	// 				}
	// 				if(c == 2){
	// 					cpuPMoves[indP] = x;
	// 					cpuPMoves[++indP] = y;
	// 					indP++;
	// 				}
	// 			}
	// 			c = 0;
	// 			for(int k=0; k<3; k++){
	// 				if(board[i][k] == cpu.move){
	// 					c++;
	// 				}
	// 				if(board[i][k] == ' '){
	// 					 x = k;
	// 					 y = j;
	// 				}
	// 				if(c == 2){
	// 					cpuPMoves[indP] = x;
	// 					cpuPMoves[++indP] = y;
	// 					indP++;
	// 				}
	// 			}
	// 			c = 0;
	// 			if(i==0 && j==0 || i==1 && j==1 || i==2 && j==2 ){
	// 				for(int k = 0,l = 0; k<3 && l<3; k++,l++){
	// 						if(board[k][l] == cpu.move){
	// 							c++;
	// 						}
	// 						if(board[k][l] == ' '){
	// 							x = k;
	// 							y = l;
	// 						}
	// 						if(c == 2){
	// 						cpuPMoves[indP] = x;
	// 						cpuPMoves[++indP] = y;
	// 						indP++;
	// 						}	
	// 				}
	// 			}

				
	// 		}
	// 	}
	// }



	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == cpu.move){
				if(i==0 && j==0 || i==1 && j==1 || i==2 && j==2 ){
					for(int k = 0,l = 0; k<3 && l<3; k++,l++){
						if(board[k][l] == ' '){
							cpuMoves[ind] = k;
							cpuMoves[++ind] = l;
							ind++;
							
						}
					}
				}
				for(int k = 0; k < 3; k++){
					if(board[k][j] == ' '){
						cpuMoves[ind] = k;
						cpuMoves[++ind] = j;
						ind++;
						
					}
				}

				for(int k = 0; k < 3; k++){
					if(board[i][k] == ' '){
						cpuMoves[ind] = i;
						cpuMoves[++ind] = k;
						ind++;
						
					}
				}
			

			}
		}
	}
}

int moveExists(){

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == cpu.move) return 1;
		}
	}
	return 0;

}

void randomMove(){
	int index[18], k=0;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(board[i][j] == ' '){
				index[k] = i;
				index[++k] = j;
				k++;
			}
		}
	}
	srand(time(0));
	int r = rand() % (k-1);
	
	if(r % 2 == 0){
		setMove(index[r],index[r+1],cpu.move);
	}
	else{
		setMove(index[r-1],index[r],cpu.move);
	}	
}






