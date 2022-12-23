#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int rowNum= 8; // Values to avoid magic numbers
const int colNum = 8;
const int maxArraySize = 60;
const int maxSquare = 8;
const int minSquare = 0;

void PrintBoard(char *board[rowNum][colNum], int time){ // Printing the board
	int i;
	for(i = 0 ; i<20 ; i++) // 20 is arbitrary
		printf("--");
printf("\nChess Board: (t=%d) \n", time/2); // time/2 --> t = 0,1 printing 0 , t= 2,3 printing 1 ...Increments after every 2 plays
	for(i=maxSquare-1; i>=0 ; i-- ) {
		printf("\n%d   ", i+1);
		int j;
		for(j=0 ; j<maxSquare ; j++){
			printf("%s", board[i][j]);
			printf("  ");
		}
	}
	printf("\n ");
	char letter = 'A';
	for(i=0 ; i<maxSquare ; i++)
		printf("   %c", letter+i);

}

void Pawn(int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col); // Defining functions
void Rook(int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col);
void Queen(int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col);
void Bishop(int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col);
void King(int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col);
void Knight(int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col);

int* FeasibleSet(char *movement, char *board[rowNum][colNum]){ // Checks for available moves
	
	//int row = RowToInt( *(movement + 1)  );
	//int col = ColumnToInt(*movement);
	char temp = 'A';
	char temp2 = *(movement + 1);
	int row = temp2 - '0' - 1; // char to int  --> movement = something like A2 and converting '2' to 2 then decrease by 1
	int col = (int)(*movement - temp );      // A2 -> converting 'A' to 0 by equation  'A' - 'A' = 0       / 'B' - 'A' = 1
	int *freemoves = (int*)malloc(sizeof(int) * maxArraySize); // allocating memory
	
	int arrIndex = 0;
	char colorLetter;
	
	if( *(board[row][col]) == 'W') { // Assigning the "opponent" color letter. 
		colorLetter = 'B';
	}
	else{
		colorLetter = 'W';
	}
	
		if( *(board[row][col]+1) == 'P' ){   // Functions to check available moves for each piece
			Pawn(freemoves, colorLetter, board, row , col);
		}
		else if( *(board[row][col]+1) == 'R' ){
			Rook(freemoves, colorLetter, board, row , col);
		} 
		else if( *(board[row][col]+1) == 'K' ){ 
			Knight(freemoves, colorLetter, board, row , col);
		} 
		else if( *(board[row][col]+1) == 'B' ){ 
				Bishop(freemoves, colorLetter, board, row , col);
		}                                          
		else if( *(board[row][col]+1) == 'Q' ){
			Queen(freemoves, colorLetter, board, row , col);	
				                       
		}
		else if( *(board[row][col]+1) == 'G' ){ 
			King(freemoves, colorLetter, board, row , col);
		}
		
	return freemoves; // Returning the available sqaures stored in array
}

	



	bool CheckIfValid(char *piece, char* playerColor, char *board[rowNum][colNum] ) { // Checks if player chooses a square except his/her owns ( empty or opponent square )
	
		char temp = 'A';
		char temp2 = *(piece + 1);
		int row = temp2 - '0' - 1; // Same conversion above ( char to int ) 
		int col = (int)(*piece - temp ); // Same ( char substitution )
		
		if( board[row][col] == "0 "){ // If empty square 
			return false;
		}

		if( playerColor == "black" &&   *board[row][col] == 'W'   ){ // If opponent square
			return false;
		}

		if( playerColor == "white" &&   *board[row][col] == 'B'   ){  // If opponent square
			return false;
		}

		return true; // Otherwise its our square
	}
	
	
	
		
	void MovePiece( char *piece,  char *board[rowNum][colNum], int newRow, int newCol ){ // Moving the piece to chosen square(newrow newcol)

		char temp = 'A'; // Same conversions above
		char temp2 = *(piece + 1);
		int row = temp2 - '0' - 1;
		int col = (int)(*piece - temp );
		
		char letter = 'A';
		
		if ( board[newRow][newCol] != "0 "){ // Capturing part -> If the destination square is not empty, we eliminate the opponent's piece
			printf("Elimination: %d%c %s => %d%c %s \n", row , letter+col, board[row][col] , newRow, letter+newCol, board[newRow][newCol]  ); // letter+ col -> A + 1 = B column A+2 = C ...
			board[newRow][newCol] = board[row][col]; // Putting piece

			board[row][col] = "0 "; // Old square is empty now
			
		}
		else{ // If no pieces in the destination square, just switch
			board[newRow][newCol] = board[row][col];

			board[row][col] = "0 "; 
		}

	}


int main() {
	char* board[][8] = { // Defining the board 8x8
                    { "WR" , "WK" , "WB" , "WQ" , "WG" , "WB" , "WK" , "WR" },
                    { "WP" , "WP" , "WP" , "WP" , "WP" , "WP" , "WP" , "WP" },
                    { "0 " , "0 " , "0 " , "0 " ,"0 " , "0 " , "0 " , "0 "  },
                    { "0 " , "0 " , "0 " , "0 " ,"0 " , "0 " , "0 " , "0 "  },
                    { "0 " , "0 " , "0 " , "0 " ,"0 " , "0 " , "0 " , "0 "  },
                    { "0 " , "0 " , "0 " , "0 " ,"0 " , "0 " , "0 " , "0 "  },
                    { "BP" , "BP" , "BP" , "BP" , "BP" , "BP" , "BP" , "BP" },
                    { "BR" , "BK" , "BB" , "BQ" , "BG" , "BB" , "BK" , "BR" }
                    };

    int time = 0;
    int player =1;
    char piece[2];
    char* playerColor;
    char myLetter = 'A';
    
	while(1){ // There is no check-mate
		PrintBoard(board, time);
		
		if( time%2 == 0){ // time = 0 , 2 , 4 , 6 .. white plays
			printf("\n\nPlayer 1 (W):\n\n");
			playerColor = "white";
		}
		else{
			printf("\n\nPlayer 2 (B):\n\n"); // 1 , 3 , 5 ... black plays
			playerColor = "black";
		}
		
		while(1){ // loop continues until choosing a valid piece
			
			printf("Select a piece:\n\n");
			fflush(stdin); // To prevent skipping the next step
			scanf("%s", piece);
		
		
			if(CheckIfValid(piece, playerColor , board) ){
				
				break;
			}
			printf("Choose of your own pieces\n");
			
		}
		int* freeMoves = FeasibleSet(piece, board);
		if(freeMoves[0] == -1){ // If there is no place to move
			printf("The piece that you've chosen is not able to move\nChoose another one\n");
			continue;
		}
		int index = 0;
		int counter = 1;
		printf("\nPress: ");
			while( freeMoves[index] != -1 ){ // Continue until empty element
			
			printf("%d:%c%d  ", counter  ,myLetter + freeMoves[index+1] , freeMoves[index]+1 ); // Prints available squares
			counter++;
			index += 2; // Array holds row and column as seperate elements so arr[0] = row and arr[1] = column ...
			
		}
		
		
		int chooseMove;
		printf("\n\n");
		scanf("%d", &chooseMove); // Asks user to choose 

		MovePiece(piece, board, freeMoves[2*chooseMove -2], freeMoves[2* chooseMove-1]); // Calling Move func.
		
			time++; 
	}
	return 0;
}

void King( int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col){ // All functions below, letter = opponents color
	int arrIndex =0;
		if( row+1 < maxSquare ) {
			if( board[row+1][col] == "0 " || *(board[row+1][col]) == letter ){ // If it's opponent or empty square 
			
				freemoves[arrIndex] = (row+1) ;  // Filling the array, first row then column // All the same in the lines below
				arrIndex++;
				freemoves[arrIndex] = col ;
				arrIndex++;
			}
		}
		if( row+1 < maxSquare && col+1 <maxSquare){
			if( board[row+1][col+1] == "0 " || *(board[row+1][col+1]) == letter ){  
			
				freemoves[arrIndex] = (row+1) ;
				arrIndex++;
				freemoves[arrIndex] = col+1 ;
				arrIndex++;
			}
		}
		if( row+1 < maxSquare && col-1 >= 0){
			if( board[row+1][col-1] == "0 " || *(board[row+1][col-1]) == letter ){
				freemoves[arrIndex] = (row+1) ;
				arrIndex++;
				freemoves[arrIndex] = col-1 ;
				arrIndex++;
			}
		}
		if( row -1 >= 0 ){
			if( board[row-1][col] == "0 " || *(board[row-1][col]) == letter ){
			
				freemoves[arrIndex] = (row-1) ;
				arrIndex++;
				freemoves[arrIndex] = col ;
				arrIndex++;
				}
		}
		if( row -1 >= 0 && col-1 >= 0 ) {
			if( board[row-1][col-1] == "0 " || *(board[row-1][col-1]) == letter ){
			
				freemoves[arrIndex] = (row-1) ;
				arrIndex++;
				freemoves[arrIndex] = col-1 ;
				arrIndex++;
			}
		}
		
		if( row -1 >= 0 && col+1  < maxSquare ){
			if( board[row-1][col+1] == "0 " || *(board[row-1][col+1]) == letter ){
			
				freemoves[arrIndex] = (row-1) ;
				arrIndex++;
				freemoves[arrIndex] = col+1 ;
				arrIndex++;
			}
		}
		if( col+1  < maxSquare ){
			if( board[row][col+1] == "0 " || *(board[row][col+1]) == letter ){
			
				freemoves[arrIndex] = (row) ;
				arrIndex++;
				freemoves[arrIndex] = col+1 ;
				arrIndex++;
			}
		}
		if( col-1 >= 0 ){
			if( board[row][col-1] == "0 " || *(board[row][col-1]) == letter ){
			
				freemoves[arrIndex] = (row) ;
				arrIndex++;
				freemoves[arrIndex] = col-1 ;
				arrIndex++;
			}
		}
			int k;
			for( k =arrIndex ; k<maxArraySize ; k++) // Fill with -1 after filling the array
				freemoves[k] = -1;
}

void Queen( int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col){
	int arrIndex = 0; 
	// Queens move ability is equal to rook's + bishop's
	if(row+1 < maxSquare){ // The Rook Move Part Starts Here // Explaination is in Rook function
			int m;
				for(  m=row+1; m<maxSquare ; m++){
					if( 	board[m][col] == "0 " || 	*board[m][col] == letter ){
						freemoves[arrIndex] = m;
						arrIndex++;
						freemoves[arrIndex] = col;
						arrIndex++;

				
					}
					if( *board[m][col] == 'B' || *board[m][col] == 'W')	{
						break;	
					}
				}
			}
			
			if( row-1 >= 0){
			
			int m;
				for(  m=row-1; m>=0 ; m--){
				if( 	board[m][col] == "0 " || 	*board[m][col] == letter ){
					freemoves[arrIndex] = m ;
						arrIndex++;
						freemoves[arrIndex] = col ;
						arrIndex++;
					
				
				}
				if( *board[m][col] == 'B' || *board[m][col] == 'W')	{
					break;	
					}
				}	
			}
			
			if( col+1 < maxSquare){
				int n;
				for(  n=col+1; n<maxSquare ; n++){
				if( 	board[row][n] == "0 " || 	*board[row][n] == letter ){
					freemoves[arrIndex] = row ;
						arrIndex++;
						freemoves[arrIndex] = n ;
						arrIndex++;

				
				}
				if( *board[row][n] == 'B' || *board[row][n] == 'W' )	{
					break;	
					}
				}
			}
			
			if( col-1 >=0) {
				
				int n;
				for(  n=col-1; n>=0 ; n--){
					if( 	board[row][n] == "0 " || 	*board[row][n] == letter ){
						freemoves[arrIndex] = row ;
						arrIndex++;
						freemoves[arrIndex] = n ;
						arrIndex++;
					
				
					}
					if( *board[row][n] == 'B' || *board[row][n] == 'W' )	{
						break;	
					}
				}
			}  // The Rook Move Part Ends Here
				int i;
			for(i=1 ; i<=maxSquare-1 ; i++){ // The Bishop Move Part Starts Here // Explaination is in Bishop function

				if( row + i >= maxSquare || col+i >= maxSquare){
					break;
				}
				if( board[row+i][col+i] == "0 "  || *board[row+i][col+i] == letter ){

					freemoves[arrIndex] = (row+i) ;
						arrIndex++;
						freemoves[arrIndex] = (col+i) ;
						arrIndex++;
					
				}
				if( *board[row+i][col+i] == 'B' || *board[row+i][col+i] == 'W')
					{
						break;

					}
			}
			
			for(i=1 ; i<=maxSquare-1 ; i++){

				if( row + i >= maxSquare || col-i < 0){
					break;
				}
				if( board[row+i][col-i] == "0 "  || *board[row+i][col-i] == letter ){
					freemoves[arrIndex] = (row+i) ;
						arrIndex++;
						freemoves[arrIndex] = (col-i) ;
						arrIndex++;
				}
				if( *board[row+i][col-i] == 'B' || *board[row+i][col-i] == 'W')
					{
						break;
					}
			}
			for(i=1 ; i<=maxSquare-1 ; i++){

				if( row-i < 0 || col-i < 0){
					break;
				}
				if( board[row-i][col-i] == "0 "  || *board[row-i][col-i] == letter ){
					freemoves[arrIndex] = (row-i) ;
						arrIndex++;
						freemoves[arrIndex] = (col-i) ;
						arrIndex++;
					
				}
				if(  *board[row-i][col-i] == 'B' || *board[row-i][col-i] == 'W')
					{
						break;
					}
			}
			for(i=1 ; i<=maxSquare-1 ; i++){
				if( row - i < 0 || col+i >= maxSquare){
					break;
				}
				if( board[row-i][col+i] == "0 "  || *board[row-i][col+i] == letter ){
					freemoves[arrIndex] = (row-i) ;
						arrIndex++;
						freemoves[arrIndex] = (col+i) ;
						arrIndex++;
				
				}
					if(  *board[row-i][col+i] == 'B' || *board[row-i][col+i] == 'W')
					{
						break;
					}
		 // The Bishop Move Part Ends Here
		
	
	}
	int k;
	for( k =arrIndex ; k<maxArraySize ; k++) // Filling empty ones with -1 
				freemoves[k] = -1;
}

void Bishop( int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col) {
	int arrIndex =0;
	int i;
				for(i=1 ; i<=maxSquare-1 ; i++){ // Checking the upper right cross

				if( row + i >= maxSquare || col+i >= maxSquare){
					break;
				}
				if( board[row+i][col+i] == "0 "  || *board[row+i][col+i] == letter ){

					freemoves[arrIndex] = (row+i) ;
						arrIndex++;
						freemoves[arrIndex] = (col+i) ;
						arrIndex++;
					
				}
				if( *board[row+i][col+i] == 'B' || *board[row+i][col+i] == 'W') // If there is a piece, we cant jump behind it // Same below
					{
						break;

					}
			}
			for(i=1 ; i<=maxSquare-1 ; i++){ // Checking the upper left cross

				if( row + i >= maxSquare || col-i < 0){
					break;
				}
				if( board[row+i][col-i] == "0 "  || *board[row+i][col-i] == letter ){
					freemoves[arrIndex] = (row+i) ;
						arrIndex++;
						freemoves[arrIndex] = (col-i) ;
						arrIndex++;
				}
				if( *board[row+i][col-i] == 'B' || *board[row+i][col-i] == 'W')
					{
						break;
					}
			}
			for(i=1 ; i<=maxSquare-1 ; i++){ // Checking the lower left cross 

				if( row-i < 0 || col-i < 0){
					break;
				}
				if( board[row-i][col-i] == "0 "  || *board[row-i][col-i] == letter ){
					freemoves[arrIndex] = (row-i) ;
						arrIndex++;
						freemoves[arrIndex] = (col-i) ;
						arrIndex++;
					
				}
				if(  *board[row-i][col-i] == 'B' || *board[row-i][col-i] == 'W')
					{
						break;
					}
			}
			for(i=1 ; i<=maxSquare-1 ; i++){ // Checking the lower right cross 

				if( row - i < 0 || col+i >= maxSquare){
					break;
				}
				if( board[row-i][col+i] == "0 "  || *board[row-i][col+i] == letter ){
					freemoves[arrIndex] = (row-i) ;
						arrIndex++;
						freemoves[arrIndex] = (col+i) ;
						arrIndex++;
				
				}
					if(  *board[row-i][col+i] == 'B' || *board[row-i][col+i] == 'W')
					{
						break;
					}
			}
			int k;
		for(k =arrIndex ; k<maxArraySize ; k++)
				freemoves[k] = -1;
}

void Knight( int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col ) {
	int arrIndex = 0;
		if(  col-1 >= 0 && row+2 < maxSquare ) { 
				if(  board[row+2][col-1] == "0 " || 	*board[row+2][col-1]  == letter ){  // Checking for all 8 possibilities / row+-2/1 col+- 2/1 ( 8 pos.)

						freemoves[arrIndex] = (row+2) ;
						arrIndex++;
						freemoves[arrIndex] = (col-1) ;
						arrIndex++;
				}
			}
			
			if( row+1 <maxSquare && col-2 >= 0) {
				if(  board[row+1][col-2] == "0 " || 	*board[row+1][col-2] == letter ){

						freemoves[arrIndex] = (row+1) ;
						arrIndex++;
						freemoves[arrIndex] = (col-2) ;
						arrIndex++;
				}
			}
			if( row-1 >= 0 && col-2 >= 0) {
				if(  board[row-1][col-2] == "0 " || 	*board[row-1][col-2] == letter ){

						freemoves[arrIndex] = (row-1) ;
						arrIndex++;
						freemoves[arrIndex] = (col-2) ;
						arrIndex++;
				}
			}
			if( row-2 >= 0 && col-1 >= 0) {
				if(  board[row-2][col-1] == "0 " || 	*board[row-2][col-1] == letter ){

						freemoves[arrIndex] = (row-2) ;
						arrIndex++;
						freemoves[arrIndex] = (col-1) ;
						arrIndex++;
				}
			}
			if( row-2 >= 0 && col+1 < maxSquare ) {
				if(  board[row-2][col+1] == "0 " || 	*board[row-2][col+1] == letter ){

						freemoves[arrIndex] = (row-2) ;
						arrIndex++;
						freemoves[arrIndex] = (col+1) ;
						arrIndex++;
				}
			}
			if( row-1 >= 0 && col+2 < maxSquare) {
				if(  board[row-1][col+2] == "0 " || 	*board[row-1][col+2]  == letter ){

						freemoves[arrIndex] = (row-1) ;
						arrIndex++;
						freemoves[arrIndex] = (col+2) ;
						arrIndex++;
				}
			}
			if( row+1 < maxSquare && col+2 < maxSquare) {
				if(  board[row+1][col+2] == "0 " || 	*board[row+1][col+2] == letter ){

						freemoves[arrIndex] = (row+1) ;
						arrIndex++;
						freemoves[arrIndex] = (col+2) ;
						arrIndex++;
				}
			}
			if( row+2 < maxSquare && col+1 < maxSquare) {
				if(  board[row+2][col+1] == "0 " || 	*board[row+2][col+1] == letter ){

						freemoves[arrIndex] = (row+2) ;
						arrIndex++;
						freemoves[arrIndex] = (col+1) ;
						arrIndex++;
				}
			}
			int k;
			for(k =arrIndex ; k<maxArraySize ; k++)
				freemoves[k] = -1;
}

void Rook( int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col ) {
	int arrIndex = 0;
		if(row+1 < maxSquare){
			int m;
				for(  m=row+1; m<maxSquare ; m++){ // Checking the squares upper side
					if( 	board[m][col] == "0 " || 	*board[m][col] == letter ){
						freemoves[arrIndex] = m;
						arrIndex++;
						freemoves[arrIndex] = col;
						arrIndex++;

				
					}
					if( *board[m][col] == 'B' || *board[m][col] == 'W')	{
						break;	
					}
				}
			}
			
			if( row-1 >= 0){
				int m;
				for(  m=row-1; m>=0 ; m--){ // Checking the squares lower side
				if( 	board[m][col] == "0 " || 	*board[m][col] == letter ){
					freemoves[arrIndex] = m ;
						arrIndex++;
						freemoves[arrIndex] = col ;
						arrIndex++;
					
				
				}
				if( *board[m][col] == 'B' || *board[m][col] == 'W')	{
					break;	
					}
				}	
			}
			
			if( col+1 < maxSquare){
				int n;
				for( n=col+1; n<maxSquare ; n++){ // Checking the squares right side
				if( 	board[row][n] == "0 " || 	*board[row][n] == letter ){
					freemoves[arrIndex] = row ;
						arrIndex++;
						freemoves[arrIndex] = n ;
						arrIndex++;

				
				}
				if( *board[row][n] == 'B' || *board[row][n] == 'W' )	{
					break;	
					}
				}
			}
			
			if( col-1 >=0) { // Checking the squares left side
			int n;
				for( n=col-1; n>=0 ; n--){
					if( 	board[row][n] == "0 " || 	*board[row][n] == letter ){
						freemoves[arrIndex] = row ;
						arrIndex++;
						freemoves[arrIndex] = n ;
						arrIndex++;
					
				
					}
					if( *board[row][n] == 'B' || *board[row][n] == 'W' )	{
						break;	
					}
				}
			}
			int k;
			for( k =arrIndex ; k<maxArraySize ; k++)
				freemoves[k] = -1;
}


void Pawn( int* freemoves , char letter, char *board[rowNum][colNum] , int row , int col) {
	int arrIndex = 0;

	if ( letter == 'B') { // If the Opponent is black - Our piece is White -
		
		if( board[row+1][col] == "0 "  ){ // If 1 square up to it is empty,
				if(board[row+1][col] == "0 " ){ //  we'll check 1 more square if we are in the second row( if pawn has not moved)

					if ( board[row+2][col] == "0 " && row == 1){
	
						freemoves[arrIndex] = row+2 ;
						arrIndex++;
						freemoves[arrIndex] = col ;
						arrIndex++;

					}
				}
				freemoves[arrIndex] = (row+1) ;
						arrIndex++;
						freemoves[arrIndex] = col ;
						arrIndex++;
			}	
			
			if( row + 1<8 && col+1 <maxSquare ){ // If we are not in the margins, check the right and left crosses for an opponent
				if( *(board[row+1][col+1] ) == 'B' ){
					freemoves[arrIndex] = row+1 ;
						arrIndex++;
						freemoves[arrIndex] = col+1 ;
						arrIndex++;
				}
			}
			if( row+1 < maxSquare && col-1 >= 0){
				if( *(board[row+1][col-1] ) == 'B' ){
					freemoves[arrIndex] = row+1 ;
						arrIndex++;
						freemoves[arrIndex] = col-1 ;
						arrIndex++;
				}
			}
int k;
				for(k =arrIndex ; k<60 ; k++)
				freemoves[k] = -1;
		} 
	else{ // If piece is black
		if( board[row-1][col] == "0 "  ){ // Same things
				if(board[row-1][col] == "0 " ){
					if ( board[row-2][col] == "0 " && row == 6){
						freemoves[arrIndex] = row-2 ;
						arrIndex++;
						freemoves[arrIndex] = col ;
						arrIndex++;
						
					}
				}
				freemoves[arrIndex] = (row-1) ;
						arrIndex++;
						freemoves[arrIndex] = col ;
						arrIndex++;
			}	
			
			if( row - 1 >= 0 && col+1 <maxSquare ){
				if( *(board[row-1][col+1] ) == 'W' ){
					freemoves[arrIndex] = row-1 ;
						arrIndex++;
						freemoves[arrIndex] = col+1 ;
						arrIndex++;
				}
			}
			if( row-1 >= 0 && col-1 >= 0){
				if( *(board[row-1][col-1] ) == 'W' ){
					freemoves[arrIndex] = row-1 ;
						arrIndex++;
						freemoves[arrIndex] = col-1 ;
						arrIndex++;
				}
			}
			int k;
				for( k =arrIndex ; k<maxArraySize ; k++)
				freemoves[k] = -1;
	}
}
