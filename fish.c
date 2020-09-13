//
// Two Things: Board must display axis and the score tallies must be displayed.
//

/**
 * Player 1 (Me, testing my game).
 * 1,5 (1 point)
 * 3,3 (3 point)
 * 4,3 (3 point)
 * 2,1 (1 point)
 * 3,2 (2 point)
 * 3,1 (1 point)
 * 4,1 (1 point)
 * 6,3 (1 point)
 * 4,5 (2 point)
 * 4,6 (1 point)
 * 5,6 (1 point)
 * 5,5 (2 point)
 * 5,4 (2 point)
 * 5,3 (2 point)
 * 5,2 (2 point)
 * 5,1 (1 point)
 * 4,2 (2 point)
 * Total: 28
 *
 * Player 2 (AI)
 * 6,6 (1 point)
 * 4,4 (3 point)
 * 3,4 (3 point)
 * 2,3 (2 point)
 * 2,2 (2 point)
 * 1,3 (1 point)
 * 2,4 (2 point)
 * 2,5 (2 point)
 * 3,5 (2 point)
 * 2,6 (1 point)
 * 1,6 (1 point)
 * Total: 20
 */

#include <stdio.h>

const int SIZE = 6;

/**
 * Sets up the initial state of the board as...
 *
 * 1 1 1 1 1 1
 * 1 2 2 2 2 1
 * 1 2 3 3 2 1
 * 1 2 3 3 2 1
 * 1 2 2 2 2 1
 * 1 1 1 1 1 1
 *
 * @param array
 * @return void
 */
void initialBoard(char array[SIZE][SIZE]) {
    // The initial board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <SIZE; j++) {
            if (i == 0 || i == 5 || j == 0 || j == 5) {
                array[i][j] = '1';
            }
            else if (i == 1 || i == 4 || j == 1 || j == 4) {
                array[i][j] = '2';
            }
            else {
                array[i][j] = '3';
            }
        }
    }
}

/**
 * Returns true if the user-chosen starting point is valid (is on a 1-point octagon) and false if it is invalid.
 *
 * @param point
 * @param board
 * @return bool
 */
_Bool isValidStartingPoint(int row, int col, char board[SIZE][SIZE]) {
    //printf("Row: %i \n", row);
    //printf("Column: %i \n", col);

    // I represented the board starting from index 0, but the player starts from index 1.
    if (board[row - 1][col - 1] == '1') {
        // printf("%i \n", board[row - 1][column - 1]);
        return 1;
    }
    return 0;
}

/**
 * Displays the current board state of the game.
 *
 * @param array
 * @return void
 */
void display(char array[SIZE][SIZE]) {
    printf("    1 2 3 4 5 6 \n");
    for (int i = 0; i < SIZE; i++) {
        printf("\n");
        printf("%i   ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", array[i][j]);
        }
    }
    printf("\n \n");
}

/**
 * Returns true if the player still has valid moves left, false otherwise.
 *
 * This function must take in consideration the position of the player. If the player is at an edge, then they
 * obviously have less than 8 basic moves. Basic moves are moves of one step only. We only need to check if the
 * player can move one step in at least one direction, since that is the requirement for any move.
 *
 * This function receives the row and columns as values 1 - 6. But since the board is represented internally with
 * row and columns as values 0 - 5, this function makes the adjustment.
 *
 * @return if the player can make a valid move.
 */
_Bool canPlayerMove(int row, int col, char state[SIZE][SIZE]) {
    // Upper left corner of the board.
    row = row - 1;
    col = col - 1;
    if (row == 0 && col == 0) {
        // Hard code coordinates.
        if ((state[row + 1][col] == '.' || state[row + 1][col] == 'A' || state[row + 1][col] == 'P') &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P') &&
            (state[row + 1][col + 1] == '.' || state[row + 1][col + 1] == 'A' || state[row + 1][col + 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Left vertical perimeter of the board. (Not including corners).
    else if (row != 0 && row != 5 && col == 0) {
        if ((state[row + 1][col] == '.' || state[row + 1][col] == 'A' || state[row + 1][col] == 'P')             &&
            (state[row - 1][col + 1] == '.' || state[row - 1][col + 1] == 'A' || state[row - 1][col + 1] == 'P') &&
            (state[row - 1][col] == '.' || state[row - 1][col] == 'A' || state[row - 1][col] == 'P')             &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P')             &&
            (state[row + 1][col + 1] == '.' || state[row + 1][col + 1] == 'A' || state[row + 1][col + 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Bottom left corner of the board.
    else if (row == 5 && col == 0) {
        if ((state[row - 1][col] == '.' || state[row - 1][col] == 'A' || state[row - 1][col] == 'P') &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P') &&
            (state[row - 1][col + 1] == '.' || state[row - 1][col + 1] == 'A' || state[row - 1][col + 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Bottom horizontal perimeter of the board. (Not including corners).
    else if (row == 5 && col != 0 && col != 5) {
        // If all the available options are blocked then the player can't move anymore.
        if ((state[row][col - 1] == '.' || state[row][col - 1] == 'A' || state[row][col - 1] == 'P')             &&
            (state[row - 1][col + 1] == '.' || state[row - 1][col + 1] == 'A' || state[row - 1][col + 1] == 'P') &&
            (state[row - 1][col] == '.' || state[row - 1][col] == 'A' || state[row - 1][col] == 'P')             &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P')             &&
            (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Bottom right corner of the board.
    else if (row == 5 && col == 5) {
        if ((state[row - 1][col] == '.' || state[row - 1][col] == 'A' || state[row - 1][col] == 'P') &&
            (state[row][col - 1] == '.' || state[row][col - 1] == 'A' || state[row][col - 1] == 'P') &&
            (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Right vertical perimeter of the board. (Not including corners).
    else if (row != 0 && row != 5 && col == 5) {
        if ((state[row][col - 1] == '.' || state[row][col - 1] == 'A' || state[row][col - 1] == 'P')             &&
            (state[row + 1][col - 1] == '.' || state[row + 1][col - 1] == 'A' || state[row + 1][col - 1] == 'P') &&
            (state[row - 1][col] == '.' || state[row - 1][col] == 'A' || state[row - 1][col] == 'P')             &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P')             &&
            (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Top right corner of the board.
    else if (row == 0 && col == 5) {
        if ((state[row + 1][col] == '.' || state[row + 1][col] == 'A' || state[row + 1][col] == 'P') &&
            (state[row][col - 1] == '.' || state[row][col - 1] == 'A' || state[row][col - 1] == 'P') &&
            (state[row + 1][col - 1] == '.' || state[row + 1][col - 1] == 'A' || state[row + 1][col - 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Top horizontal perimeter of the board. (Not including corners).
    else if (row == 0 && col != 0 && col != 5) {
        // Left
        if ((state[row][col - 1] == '.' || state[row][col - 1] == 'A' || state[row][col - 1] == 'P')             &&
            (state[row + 1][col - 1] == '.' || state[row + 1][col - 1] == 'A' || state[row + 1][col - 1] == 'P') &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P')             &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P')             &&
            (state[row + 1][col + 1] == '.' || state[row + 1][col + 1] == 'A' || state[row + 1][col + 1] == 'P')) {
            return 0;
        }
        return 1;
    }
    // Interior of the board, where there are 8 basic moves.
    else {
        // Left
        if ((state[row][col - 1] == '.' || state[row][col - 1] == 'A' || state[row][col - 1] == 'P')             &&
            (state[row + 1][col - 1] == '.' || state[row + 1][col - 1] == 'A' || state[row + 1][col - 1] == 'P') &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P')             &&
            (state[row - 1][col] == '.' || state[row - 1][col] == 'A' || state[row - 1][col] == 'P')             &&
            (state[row][col + 1] == '.' || state[row][col + 1] == 'A' || state[row][col + 1] == 'P')             &&
            (state[row + 1][col + 1] == '.' || state[row + 1][col + 1] == 'A' || state[row + 1][col + 1] == 'P') &&
            (state[row - 1][col + 1] == '.' || state[row - 1][col + 1] == 'A' || state[row - 1][col + 1] == 'P')) {
            return 0;
        }
        return 1;
    }
}

/**
 * Returns true if the move to the new coordinate is valid, and false otherwise.
 *
 * Returns false if the player enters coordinates less than 1 or greater than 6.
 * Returns false if the player enters coordinates for the space that has been visited already, or is not new, or is occupied by the AI.
 *
 * This function receives the row and columns as values 1 - 6. But since the board is represented internally with
 * row and columns as values 0 - 5, this function makes the adjustment.
 *
 * @param row
 * @param col
 * @param newRow
 * @param newCol
 * @param state
 * @return true if the move is valid, false otherwise.
 */
_Bool isValidMove(int row, int col, int newRow, int newCol, char state[SIZE][SIZE]) {


    // Index out of bounds. The user had entered an invalid coordinate.
    if (newRow < 1 || newRow > 6 || newCol < 1 || newCol > 6) {
        return 0;
    }
    // If the new position has already been visited, or is not new, or is being occupied by the AI...return false.
    if (state[newRow - 1][newCol - 1] == '.' || state[newRow - 1][newCol - 1] == 'P' || state[newRow - 1][newCol - 1] == 'A') {
        return 0;
    }


    // Horizontal moves.
    // Moved right.
    if (newCol > col && row == newRow) {
        col = col + 1;
        // Keep moving right until we reach our target destination.
        while (col <= newCol) {
            // If along the way we encountered a block to our path, then the target coordinate is not reachable.
            if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                return 0;
            }
            col = col + 1;
        }
        // The target coordinate is valid.
        return 1;
    }
    // Moved left.
    else if (newCol < col && row == newRow) {
        col = col - 1;
        // Keep moving left until we reach our target destination.
        while (col >= newCol) {
            // If along the way we encountered a block to our path, then the target coordinate is not reachable.
            if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                return 0;
            }
            col = col - 1;
        }
        // The target coordinate is valid.
        return 1;
    }



    // Vertical moves.
    // Moved down.
    else if (newRow > row && col == newCol) {
        row = row + 1;
        // Keep moving down until we reach our target destination.
        while (row <= newRow) {
            // If along the way we encountered a block to our path, then the target coordinate is not reachable.
            if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                return 0;
            }
            row = row + 1;
        }
        // The target coordinate is valid.
        return 1;
    }

    // Moved up.
    else if (newRow < row && col == newCol) {
        row = row - 1;
        // Keep moving up until we reach our target destination.
        while (row >= newRow) {
            // If along the way we encountered a block to our path, then the target coordinate is not reachable.
            if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                return 0;
            }
            row = row - 1;
        }
        // The target coordinate is valid.
        return 1;
    }

    // Diagonal moves. Wasn't vertical or horizontal, so it must be diagonal or invalid.
    else {
        // Most likely up-left. Row decrease, column decrease. (-1, -1)
        if (newRow < row && newCol < col) {
            int tmpRow = row - 1;
            int tmpCol = col - 1;
            _Bool isValid = 0;
            // Check if the path is linear.
            while (tmpRow > 0 && tmpCol > 0 && !isValid) {
                if (tmpRow == newRow && tmpCol == newCol) {
                    isValid = 1;
                }
                tmpRow = tmpRow - 1;
                tmpCol = tmpCol - 1;
            }
            // If the path wasn't linear, then it isn't valid.
            if (isValid == 0) {
                return 0;
            }
            // Since the coordinate is linear to our position, check if the path is blocked.
            row = row - 1;
            col = col - 1;
            while (row != newRow && col != newCol) {
                if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                    return 0;
                }
                row = row - 1;
                col = col - 1;
            }

            return 1;
        }
        // Most likely up-right. Row decrease, column increase. (-1, +1)
        else if (newRow < row && newCol > col) {
            int tmpRow = row - 1;
            int tmpCol = col + 1;
            _Bool isValid = 0;
            // Check if the path is linear.
            while (tmpRow > 0 && tmpCol <= 6 && !isValid) {
                if (tmpRow == newRow && tmpCol == newCol) {
                    isValid = 1;
                }
                tmpRow = tmpRow - 1;
                tmpCol = tmpCol + 1;
            }
            // If the path wasn't linear, then it isn't valid.
            if (isValid == 0) {
                return 0;
            }
            // Since the coordinate is linear to our position, check if the path is blocked.
            row = row - 1;
            col = col + 1;
            while (row != newRow && col != newCol) {
                if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                    return 0;
                }
                row = row - 1;
                col = col + 1;
            }

            return 1;
        }
        // Most likely down-left. Row increase, column decrease. (+1, -1)
        else if (newRow > row && newCol < col) {
            int tmpRow = row + 1;
            int tmpCol = col - 1;
            _Bool isValid = 0;
            // Check if the path is linear.
            while (tmpRow <= 6 && tmpCol > 0 && !isValid) {
                if (tmpRow == newRow && tmpCol == newCol) {
                    isValid = 1;
                }
                tmpRow = tmpRow + 1;
                tmpCol = tmpCol - 1;
            }
            // If the path wasn't linear, then it isn't valid.
            if (isValid == 0) {
                return 0;
            }
            // Since the coordinate is linear to our position, check if the path is blocked.
            row = row + 1;
            col = col - 1;
            while (row != newRow && col != newCol) {
                if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                    return 0;
                }
                row = row + 1;
                col = col - 1;
            }

            return 1;
        }
        // Most likely down-right. Row increase, column increase. (+1, +1)
        else if (newRow > row && newCol > col) {
            int tmpRow = row + 1;
            int tmpCol = col + 1;
            _Bool isValid = 0;
            // Check if the path is linear.
            while (tmpRow <= 6 && tmpCol <= 6 && !isValid) {
                if (tmpRow == newRow && tmpCol == newCol) {
                    isValid = 1;
                }
                tmpRow = tmpRow + 1;
                tmpCol = tmpCol + 1;
            }
            // If the path wasn't linear, then it isn't valid.
            if (isValid == 0) {
                return 0;
            }
            // Since the coordinate is linear to our position, check if the path is blocked.
            row = row + 1;
            col = col + 1;
            while (row != newRow && col != newCol) {
                if (state[row - 1][col - 1] == '.' || state[row - 1][col - 1] == 'A' || state[row - 1][col - 1] == 'P') {
                    return 0;
                }
                row = row + 1;
                col = col + 1;
            }

            return 1;
        }
    }
    return 1;
}

/**
 * Updates the state of the board by moving the AI position to the octagon of maximum points.
 *
 * @param row
 * @param col
 * @param state
 * @return void
 */
//_Bool smartAI(int row, int col, char state[SIZE][SIZE]) {
//    // Handles the AI's first move.
//    if (row == 6 && col == 6) {
//        // The AI always starts at the bottom right corner, so its best first move would be to take the center 3 points, if possible.
//        if (isValidMove(row, col, 4, 4, state)) {
//            state[row - 1][col - 1] = '.';
//            state[3][3] = 'A';
//        }
//        // If the player makes a smart move and blocks the optimal path for the AI, then it's best bet is traverse up or left.
//        // I'll make the AI go up.
//        else {
//            _Bool moved = 0;
//            int startRow = row;
//            row = row - 1;
//            // Traverse up and find the first suitable spot.
//            while (row > 0 && !moved) {
//                if (isValidMove(startRow, col, row, col, state)) {
//                    state[startRow - 1][col - 1] = '.';
//                    state[row - 1][col - 1] = 'A';
//                    moved = 1;
//                }
//                row = row - 1;
//            }
//        }
//    }
//    // Handles the rest of the AI's moves, after the first.
//    else {
//        // I guess the idea is that the AI looks around and sees which 1-distance neighbor has the best value.
//        // Then it moves there and searches at least two blocks ahead in the same direction to see if there is anything better.
//        // If not it stays, if so, then it moves.
//
//    }
//}

int main() {
    char state[SIZE][SIZE];
    initialBoard(state);

    int tallyPlayer1[50];
    int tallyCounterPlayer1 = 0;
    int tallyAI[50];
    int tallyCounterAI = 0;

    // Sets all of the values in the array to 0, so I can identify which values are mine and which are not.
    for (int i = 0; i < 50; i++) {
        tallyPlayer1[i] = 0;
        tallyAI[i] = 0;
    }

    // Initial point is 1 for both players.
    tallyPlayer1[tallyCounterPlayer1] = 1;
    tallyAI[tallyCounterAI] = 1;
    tallyCounterPlayer1 = tallyCounterPlayer1 + 1;
    tallyCounterAI = tallyCounterAI + 1;

    // Each player is guaranteed 1 point, because they both started at 1 point tiles.
    int playerScore = 1;
    int AIScore = 1;

    display(state);

    // Your implementation will prompt the user before game play to determine where (which octagon) player’s penguin is.
    // Both players can only select an octagon with 1 point as a starting point.
    int row;
    int col;

    // Have the user enter the starting position.
    do {
        printf("Please enter a row and column as a starting position for your penguin. The starting position must have only 1-point. "
               "Ex: 1 ( presss enter) 2 ( press enter) means row 1 and column 2.");
        scanf("%i %i", &row, &col);
    } while (isValidStartingPoint(row, col, state) == 0);

    state[row - 1][col - 1] = 'P';

    // Must have the AI choose a starting point. The starting point of the AI is the bottom right of the board.
    int AIrow = 6;
    int AIcol = 6;
    // If the player chooses the AI's default starting point, then the new AI starting point is at the top right of the board.
    if (AIrow == row && AIcol == col) {
        AIrow = AIrow - 5;
    }

    state[AIrow - 1][AIcol - 1] = 'A';
    printf("Your turn: \n \n");
    display(state);

    // While there is still moves for at least one of the players, continue the game.
    while (canPlayerMove(row, col, state) == 1 || canPlayerMove(AIrow, AIcol, state) == 1) {
        int newRow;
        int newCol;
        _Bool message = 0;

        // Moving the player.
        if (canPlayerMove(row, col, state) == 1) {
            printf("Please enter a row and column to move to a different position. "
                   "Ex: 1 ( press enter) 2 ( press enter) means move to row 1 and column 2. \n \n");
            do {
                if (message == 1) {
                    printf("Invalid move. Please choose a new row and column that is linearly reachable given the board state: \n \n");
                    display(state);
                }
                scanf("%i %i", &newRow, &newCol);
                message = 1;
            } while (isValidMove(row, col, newRow, newCol, state) == 0);

            // Update score of player 1.
            if (state[newRow - 1][newCol - 1] == '1') {
                playerScore = playerScore + 1;
                tallyPlayer1[tallyCounterPlayer1] = 1;
                tallyCounterPlayer1 = tallyCounterPlayer1 + 1;
            }
            else if (state[newRow - 1][newCol - 1] == '2') {
                playerScore = playerScore + 2;
                tallyPlayer1[tallyCounterPlayer1] = 2;
                tallyCounterPlayer1 = tallyCounterPlayer1 + 1;
            }
            else {
                playerScore = playerScore + 3;
                tallyPlayer1[tallyCounterPlayer1] = 3;
                tallyCounterPlayer1 = tallyCounterPlayer1 + 1;
            }

            // Update board.
            state[row - 1][col - 1] = '.';
            row = newRow;
            col = newCol;
            state[row - 1][col - 1] = 'P';
            printf("Your turn: \n \n");
            display(state);
        }
        else {
            printf("Player 1 does have any valid moves. Skipping Player 1's turn. \n");
        }
        // Moving the AI.
        if (canPlayerMove(AIrow, AIcol, state) == 1) {
            // From all positions, the best place to be is in the center four blocks.
            int newRow;
            int newCol;
            if (isValidMove(AIrow, AIcol, 3, 3, state)) {
                newRow = 3;
                newCol = 3;
            }
            else if (isValidMove(AIrow, AIcol, 3, 4, state)) {
                newRow = 3;
                newCol = 4;
            }
            else if (isValidMove(AIrow, AIcol, 4, 4, state)) {
                newRow = 4;
                newCol = 4;
            }
            else if (isValidMove(AIrow, AIcol, 4, 3, state)) {
                newRow = 4;
                newCol = 3;
            }
            // Look for a two-pointer instead.
            else {
                if (isValidMove(AIrow, AIcol, 2, 2, state)) {
                    newRow = 2;
                    newCol = 2;
                }
                else if (isValidMove(AIrow, AIcol, 2, 3, state)) {
                    newRow = 2;
                    newCol = 3;
                }
                else if (isValidMove(AIrow, AIcol, 2, 4, state)) {
                    newRow = 2;
                    newCol = 4;
                }
                else if (isValidMove(AIrow, AIcol, 2, 5, state)) {
                    newRow = 2;
                    newCol = 5;
                }
                else if (isValidMove(AIrow, AIcol, 3, 5, state)) {
                    newRow = 3;
                    newCol = 5;
                }
                else if (isValidMove(AIrow, AIcol, 4, 5, state)) {
                    newRow = 4;
                    newCol = 5;
                }
                else if (isValidMove(AIrow, AIcol, 5, 5, state)) {
                    newRow = 5;
                    newCol = 5;
                }
                else if (isValidMove(AIrow, AIcol, 5, 4, state)) {
                    newRow = 5;
                    newCol = 4;
                }
                else if (isValidMove(AIrow, AIcol, 5, 3, state)) {
                    newRow = 5;
                    newCol = 3;
                }
                else if (isValidMove(AIrow, AIcol, 5, 2, state)) {
                    newRow = 5;
                    newCol = 2;
                }
                else if (isValidMove(AIrow, AIcol, 4, 2, state)) {
                    newRow = 4;
                    newCol = 2;
                }
                else if (isValidMove(AIrow, AIcol, 3, 2, state)) {
                    newRow = 3;
                    newCol = 2;
                }
                // Settle for a one-pointer.
                else {
                    // Down-right.
                    if (isValidMove(AIrow, AIcol, AIrow + 1, AIcol + 1, state)) {
                        newRow = AIrow + 1;
                        newCol = AIcol + 1;
                    }
                    // Down-left
                    else if (isValidMove(AIrow, AIcol, AIrow + 1, AIcol - 1, state)) {
                        newRow = AIrow + 1;
                        newCol = AIcol - 1;
                    }
                    // Up-right.
                    else if (isValidMove(AIrow, AIcol, AIrow - 1, AIcol + 1, state)) {
                        newRow = AIrow - 1;
                        newCol = AIcol + 1;
                    }
                    // Up-left.
                    else if (isValidMove(AIrow, AIcol, AIrow - 1, AIcol - 1, state)) {
                        newRow = AIrow - 1;
                        newCol = AIcol - 1;
                    }
                    // Right
                    else if (isValidMove(AIrow, AIcol, AIrow, AIcol + 1, state)) {
                        newRow = AIrow;
                        newCol = AIcol + 1;
                    }
                    // Left
                    else if (isValidMove(AIrow, AIcol, AIrow, AIcol - 1, state)) {
                        newRow = AIrow;
                        newCol = AIcol - 1;
                    }
                    // Up
                    else if (isValidMove(AIrow, AIcol, AIrow - 1, AIcol, state)) {
                        newRow = AIrow - 1;
                        newCol = AIcol;
                    }
                    // Down
                    else {
                        newRow = AIrow - 1;
                        newCol = AIcol;
                    }
                }
            }

            // Update AI score.
            if (state[newRow - 1][newCol - 1] == '1') {
                AIScore = AIScore + 1;
                tallyAI[tallyCounterAI] = 1;
                tallyCounterAI = tallyCounterAI + 1;
            }
            else if (state[newRow - 1][newCol - 1] == '2') {
                AIScore = AIScore + 2;
                tallyAI[tallyCounterAI] = 2;
                tallyCounterAI = tallyCounterAI + 1;
            }
            else {
                AIScore = AIScore + 3;
                tallyAI[tallyCounterAI] = 3;
                tallyCounterAI = tallyCounterAI + 1;
            }

            state[AIrow - 1][AIcol - 1] = '.';
            state[newRow - 1][newCol - 1] = 'A';
            AIrow = newRow;
            AIcol = newCol;
        }
        else {
            printf("AI does have any valid moves. Skipping AI's turn. \n \n");
        }
        printf("AI's turn: \n \n");
        display(state);
    }

    printf("Game over, there are no more moves available. \n");

    int stop = 0;

    printf("%-25s", "Player 1's score is: ");
    for(int i = 0; i < 10; i++) {
        if (tallyPlayer1[i] != 0) {
            stop++;
        }
    }

    for (int i = 0; i < stop; i++) {
        if (i == stop - 1) {
            printf("%i = ", tallyPlayer1[i]);
        }
        else {
            printf("%i + ", tallyPlayer1[i]);
        }
    }

    printf("%i \n", playerScore);


    int stop2 = 0;

    printf("%-25s", "AI's score is: ");
    for(int i = 0; i < 10; i++) {
        if (tallyAI[i] != 0) {
            stop2++;
        }
    }

    for (int i = 0; i < stop2; i++) {
        if (i == stop2 - 1) {
            printf("%i = ", tallyAI[i]);
        }
        else {
            printf("%i + ", tallyAI[i]);
        }
    }

    printf("%i \n", AIScore);


    if (playerScore > AIScore) {
        printf("Player 1 wins!");
    }
    else if (playerScore < AIScore) {
        printf("AI wins!");
    }
    else {
        printf("Draw!");
    }

    return 0;
}

