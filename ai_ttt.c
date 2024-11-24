#include <stdio.h>

void initialize_board(char board[3][3]);
void display_board(char board[3][3]);
int is_valid_move(int row, int col, char board[3][3]);
int check_winner(char board[3][3]);

int minimax(char board[3][3], int depth, int isAI);
void ai_move(char board[3][3]);
int evaluate(char board[3][3]);
int is_moves_left(char board[3][3]);

int main() {
    char board[3][3];
    int row, col;
    int player = 1;
    int winner = 0;
    int player_choice;
    printf("Player 1 uses 'X' Player 2 uses 'O'!");
    printf("Do you want to play first or second? (1 for first, 2 for second): ");
    scanf("%d", &player_choice);

    initialize_board(board);

    do {
        display_board(board);

        if ((player == 1 && player_choice == 1) || (player == 2 && player_choice == 2)) {
            // Player's turn
            do {
                printf("Player, enter your move (row [1-3] column [1-3]): ");
                scanf("%d %d", &row, &col);
                row--;
                col--;
            } while (!is_valid_move(row, col, board));

            board[row][col] = (player_choice == 1) ? 'X' : 'O';  // Player uses 'X' if they play first, otherwise 'O'
            player = 2;  // Switch to AI
        } else {
            // AI's turn
            printf("AI's move:\n");
            ai_move(board);
            player = 1;  // Switch back to player
        }

        winner = check_winner(board);

    } while (winner == 0);

    display_board(board);

    if (winner == 1) {
        printf("Player wins!\n");
    } else if (winner == 2) {
        printf("AI wins!\n");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}

void initialize_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void display_board(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int is_valid_move(int row, int col, char board[3][3]) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        return 1;
    } else {
        printf("Invalid move. Please try again.\n");
        return 0;
    }
}

// Check for winner or draw (-1: Draw, 0: No Winner, 1: Player 1, 2: AI)
int check_winner(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return (board[i][0] == 'X') ? 1 : 2;
        }
    }
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return (board[0][j] == 'X') ? 1 : 2;
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
        return (board[1][1] == 'X') ? 1 : 2;
    }

    if (!is_moves_left(board)) return -1;
    return 0;
}

// Check if any moves are left
int is_moves_left(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 1;
    return 0;
}

// Minimax function to find the best move for AI
int minimax(char board[3][3], int depth, int isAI) {
    int score = evaluate(board);
    if (score == 10 || score == -10)
        return score;
    if (!is_moves_left(board))
        return 0;

    if (isAI) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';  // AI is 'O'
                    best = (best > minimax(board, depth + 1, 0)) ? best : minimax(board, depth + 1, 0);
                    board[i][j] = ' ';  // Undo move
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';  // Player is 'X'
                    best = (best < minimax(board, depth + 1, 1)) ? best : minimax(board, depth + 1, 1);
                    board[i][j] = ' ';  // Undo move
                }
            }
        }
        return best;
    }
}

// Evaluate the board for minimax
int evaluate(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'O') return +10;
            else if (board[row][0] == 'X') return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'O') return +10;
            else if (board[0][col] == 'X') return -10;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return +10;
        else if (board[0][0] == 'X') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return +10;
        else if (board[0][2] == 'X') return -10;
    }
    return 0;
}

// AI move function
void ai_move(char board[3][3]) {
    int bestVal = -1000;
    int row = -1, col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[row][col] = 'O';  // AI places 'O'
}
