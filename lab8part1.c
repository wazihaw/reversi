#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void flipBoard(char board[][26], int n, int row, int col, char colour);
int countTiles(char board[][26], int n, int row, int col, char colour);

int main()
{
	char gameBoard[26][26];
    int gameDimension, row, col, i, j;
    char c0, c1, c2, c3, c4, c5;
    char turnComputer;
    char turn1, turn2;
    char turn = 'B';
    bool gameOver = false;
    int highScore, bestRow, bestCol;
    
    printf("Enter the board dimension: ");
    scanf("%d", &gameDimension);
    
    for (row=0; row<gameDimension; row++){
        for (col=0; col<gameDimension; col++){
            if(row == ((gameDimension/2) -1)){
                if(col == (gameDimension/2) -1){
                 gameBoard[row][col]='W';   
                } else if((col == (gameDimension/2))){
                    gameBoard[row][col]='B'; 
                } else {
                    gameBoard[row][col] = 'U';
                }
            } else if(row == ((gameDimension/2))){
                if(col == (gameDimension/2)-1){
                 gameBoard[row][col]='B';   
                } else if((col == (gameDimension/2))){
                    gameBoard[row][col]='W'; 
                } else {
                    gameBoard[row][col] = 'U';
                } 
            } else {
            gameBoard[row][col]='U';
            
            }
        }
    }
    
    // Ask user for computer colour
        printf("Computer plays (B/W): ");
        scanf("%c%c",&c0,&turnComputer);
        
        
        printBoard(gameBoard, gameDimension);
        
        
        //int firstMove = 0;
        
        
        while(!gameOver){
        
            int counterHuman = 0;
            
            if(turn == turnComputer){
                    highScore = 0;
                    int score = 0;
                    for(row = 0; row < gameDimension; row++){
                        for(col = 0; col < gameDimension; col++){
                            for(i=-1; i<=1; i++){
                                for(j=-1; j<=1; j++){
                                    if((checkLegalInDirection(gameBoard, gameDimension, row, col, turnComputer, i, j))){
                                        //printf("Legal here: %d %d\n", row, col);
                                        score = countTiles(gameBoard, gameDimension, row, col, turnComputer);
                                        //printf("This is %d score at position %d %d\n", score, row, col);
                                        if(score > highScore){
                                                  highScore = score;
                                                  bestRow = row;
                                                  bestCol = col;
                
                                    } 
                                }
                            }
                        }
                    }
            }
                printf("Computer places %c at %c%c.\n", turn, (bestRow+97), (bestCol+97));
                                flipBoard(gameBoard, gameDimension, bestRow, bestCol, turnComputer);
                                printBoard(gameBoard, gameDimension);
            
            
            
            }else {
            printf("Enter move for colour %c (RowCol): ", turn);
            scanf("%c%c%c", &c0, &c4, &c5);
                for(i=-1; i<=1; i++){
                    for(j=-1; j<=1; j++){
                        if((checkLegalInDirection(gameBoard, gameDimension, (c4-97), (c5-97), turn, i, j))){
                                flipBoard(gameBoard, gameDimension, (c4-97), (c5-97), turn);
                                printBoard(gameBoard, gameDimension);
                                counterHuman++;
            
                }
                }
            }
            
            if (counterHuman == 0){
                printf("Invalid move.\n", turnComputer);
                gameOver = true;
            }
        }
        


                        if(turn == 'B'){
                            turn1 = 'B';
                            turn2 = 'W';
                        } else {
                            turn1 = 'W';
                            turn2 = 'B';
                        }
                        
                        
                        int counterMovesAvailableTurn2 = 0;
                        int counterMovesAvailableTurn1 = 0;
                        
                        for(row = 0; row < gameDimension; row++){
                            for(col = 0; col < gameDimension; col++){
                                for(i=-1; i<=1; i++){
                                    for(j=-1; j<=1; j++){
                                        if((checkLegalInDirection(gameBoard, gameDimension, row, col, turn2, i, j))){
                                            counterMovesAvailableTurn2++;
                                        }
                                    }
                                }
                            }
                        }
                        
                        for(row = 0; row < gameDimension; row++){
                            for(col = 0; col < gameDimension; col++){
                                for(i=-1; i<=1; i++){
                                    for(j=-1; j<=1; j++){
                                        if((checkLegalInDirection(gameBoard, gameDimension, row, col, turn1, i, j))){
                                            counterMovesAvailableTurn1++;
                                        }
                                    }
                                }
                            }
                        }
                        
                        if(counterMovesAvailableTurn2 > 0){
                            turn = turn2;
                            //printf("%c has %d many moves available.\n", turn, counterMovesAvailableTurn2);
                        } else if(counterMovesAvailableTurn2 == 0 && counterMovesAvailableTurn1 > 0){
                            printf("%c player has no valid move.\n", turn2);
                            turn = turn1;
                        } else {
                           gameOver = true; 
                        }
                    
                    } 
                    
                    int counterB = 0;
                    int counterW = 0;
                    
                    for(row = 0; row < gameDimension; row++){
                        for(col = 0; col < gameDimension; col++){
                            for(i=-1; i<=1; i++){
                                for(j=-1; j<=1; j++){
                                    if(gameBoard[row][col]=='B'){
                                        counterB++;
                                    } else if(gameBoard[row][col]=='W'){
                                        counterW++;
                                    } else {
                                        ;
                                    }
                                }
                            }
                        }
                    }
                    
                    if(counterB>counterW){
                        printf("B player wins.\n"); 
                    }else if(counterW>counterB){
                        printf("W player wins.\n");
                    }else{
                        printf("Draw!\n");
                    }
                    
                    
    
return 0;
}

void printBoard(char board[][26], int n){
    int row, col;
    int letter;
    letter = 97;
    
    printf("  ");
    for (row=0; row<n; row++){
        printf("%c", letter);
        letter++;
    }
    printf("\n");
    
    letter = 97;
    for (row=0; row<n; row++){
        printf("%c ", letter);
        letter++;
        for (col=0; col<n; col++){
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
    
    return ;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
    
    // East
    if(deltaRow == 0 && deltaCol == 0)
        return 0;
    if(deltaRow == 0 && deltaCol == 1){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U'){
                    //printf("%c%c\n",(row+97), (col+97));
                    while(board[row+deltaRow][col+deltaCol+1] != colour){
                        deltaRow = deltaRow + deltaRow;
                        deltaCol = deltaCol + 1; 
                }
                   if((col+deltaCol+98)>(n+96)){
                      return 0;
                  }
                    
                    //printf("%c%c\n",(row+97), (col+97));
                    return 1;
                
            } else {
                return 0;
            }
        }
            }
    }
    
    // West
    
    if(deltaRow == 0 && deltaCol == -1){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U'){
                    //printf("%c%c\n",(row+97), (col+97));
                    while(board[row+deltaRow][col+deltaCol-1] != colour){
                        deltaRow = deltaRow + deltaRow;
                        deltaCol = deltaCol - 1; 
                }
                   if((col+deltaCol+97)<(97)){
                      return 0;
                  }
                    //printf("%c%c\n", colour, board[row+97][col+97]);
                    //printf("%c%c\n",(row+97), (col+97));
                    return 1;
                
            } else {
                return 0;
            }
        }
            }
    }
    
    // North
    
    if(deltaRow == -1 && deltaCol == 0){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U' && row != 0){
                    while(board[row+deltaRow-1][col+deltaCol] != colour){
                        deltaRow = deltaRow - 1;
                        deltaCol = deltaCol;
                        if((row+deltaRow+97)<(97)){
                            return 0;
                    }
                }
                //printf("%c%c\n", (row+97), (col+97));
                return 1;
            } else {
               return 0; 
            }
        }
    }
    }
    
    // South
    
    if(deltaRow == 1 && deltaCol == 0){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U' && row != (n-1)){
                    while(board[row+deltaRow+1][col+deltaCol] != colour){
                        deltaRow = deltaRow + 1;
                        deltaCol = deltaCol;
                        if((row+deltaRow+97)>(n+98)){
                            return 0;
                    }
                }
                //printf("%c%c\n", (row+97), (col+97));
                return 1;
            } else {
               return 0; 
            }
        }
    }
    }
    
    // North East
    
    if(deltaRow == -1 && deltaCol == 1){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U' && (row >= 0) && (col <n)){
                    while(board[row+deltaRow-1][col+deltaCol+1] != colour){
                        deltaRow = deltaRow - 1;
                        deltaCol = deltaCol + 1;
                        if((row+deltaRow+97)<(97) || (col+deltaCol+97)>(n+97) || board[row+deltaRow][col+deltaCol] == 'U'){
                            return 0;
                    }
                }
                //printf("%c%c\n",(row+97), (col+97));
                return 1;
            } else {
               return 0; 
            }
        }
    }
    }
    
    // North West
    
    if(deltaRow == -1 && deltaCol == -1){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U' && (row >= 0) && (col >=0)){
                    while(board[row+deltaRow-1][col+deltaCol-1] != colour){
                        deltaRow = deltaRow - 1;
                        deltaCol = deltaCol - 1;
                        if((row+deltaRow+97)<(97) || (col+deltaCol+97)<(97) || board[row+deltaRow][col+deltaCol] == 'U'){
                            return 0;
                    }
                }
                //printf("%c%c\n",(row+97), (col+97));
                return 1;
            } else {
               return 0; 
            }
        }
    }
    }
    
    // South East
    if(deltaRow == 1 && deltaCol == 1){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U' && (row !=(n-1)) && (col < n)){
                    while(board[row+deltaRow+1][col+deltaCol+1] != colour){
                        deltaRow = deltaRow + 1;
                        deltaCol = deltaCol + 1;
                        if((row+deltaRow+97)>(n+97) || (col+deltaCol+97)>(n+97) || board[row+deltaRow][col+deltaCol] == 'U'){
                            return 0;
                    }
                }
                //printf("%c%c\n",(row+97), (col+97));
                return 1;
            } else {
               return 0; 
            }
        }
    }
    }
    
    // South West 
    if(deltaRow == 1 && deltaCol == -1){
        for( ;row<n; row++){
            for( ;col<n; col++){
                if(board[row][col] == 'U'  && board[row+deltaRow][col+deltaCol] != colour && board[row+deltaRow][col+deltaCol] != 'U' && (row !=(n-1)) && (col >=0)){
                    while(board[row+deltaRow+1][col+deltaCol-1] != colour){
                        deltaRow = deltaRow + 1;
                        deltaCol = deltaCol - 1;
                        if((row+deltaRow+97)>(n+97) || (col+deltaCol+97)< 97 || board[row+deltaRow][col+deltaCol] == 'U'){
                            return 0;
                    }
                }
                //printf("%c%c\n",(row+97), (col+97));
                return 1;
            } else {
               return 0; 
            }
        }
    }
    
}

}

void flipBoard(char board[][26], int n, int row, int col, char colour){
    int i, j;
    for(i=-1; i<=1; i++){
        for(j=-1; j<=1; j++){
            if (i ==0 && j ==0){
                ;
            }else{
                //printf("Direction under study: %d(i) and %d(j)\n at %d(row) and %d(col)", i,j, row, col);
                if((checkLegalInDirection(board, n, row, col, colour, i, j))){
                    //printf("This direction is validated: %d (i) %d (j)\n", i, j);
//                    board[row][col] = colour;
                    board[row+i][col+j] = colour;
                    int k =2;
                    while(board[row+k*i][col+k*j] != colour){
                        board[row+k*i][col+k*j] = colour;
                        k = k++;
                    }
                }
            }
        }
    }
    board[row][col] = colour;
}


    
int countTiles(char board[][26], int n, int row, int col, char colour){
    
    int score = 0;
    int i, j;
    for(i=-1; i<=1; i++){
        for(j=-1; j<=1; j++){
            if (i ==0 && j ==0){
                ;
            }else{
                //printf("Direction under study: %d(i) and %d(j)\n", i,j);
                if((checkLegalInDirection(board, n, row, col, colour, i, j))){
                    //printf("This direction is validated: %d (i) %d (j)\n", i, j);
                    score++;
                    //printf("%d", score);
                    int k =2;
                    while(board[row+k*i][col+k*j] != colour){
                        score++;
                        k = k+1;
                    }
                }
            }
        }
    }
    
    return score;
}
    
     
