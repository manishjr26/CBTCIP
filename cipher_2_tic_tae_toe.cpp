#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class TicTacToe {
public:
    TicTacToe() : board(9, ' '), current_winner(' ') {}

    void print_board() {
        std::cout << "\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << "| " << board[i * 3] << " | " << board[i * 3 + 1] << " | " << board[i * 3 + 2] << " |\n";
        }
        std::cout << "\n";
    }

    bool make_move(int square, char letter) {
        if (board[square] == ' ') {
            board[square] = letter;
            if (check_winner(square, letter)) {
                current_winner = letter;
            }
            return true;
        }
        return false;
    }

    bool is_full() const {
        return std::find(board.begin(), board.end(), ' ') == board.end();
    }

    char get_winner() const {
        return current_winner;
    }

    void reset() {
        board.assign(9, ' ');
        current_winner = ' ';
    }

private:
    std::vector<char> board;
    char current_winner;

    bool check_winner(int square, char letter) {
        int row_ind = square / 3;
        if (board[row_ind * 3] == letter && board[row_ind * 3 + 1] == letter && board[row_ind * 3 + 2] == letter) {
            return true;
        }

        int col_ind = square % 3;
        if (board[col_ind] == letter && board[col_ind + 3] == letter && board[col_ind + 6] == letter) {
            return true;
        }

        if (square % 2 == 0) {
            if (board[0] == letter && board[4] == letter && board[8] == letter) {
                return true;
            }
            if (board[2] == letter && board[4] == letter && board[6] == letter) {
                return true;
            }
        }

        return false;
    }
};

int get_computer_move(TicTacToe& game) {
    std::vector<int> available_moves;
    for (int i = 0; i < 9; ++i) {
        if (game.make_move(i, ' ')) {
            available_moves.push_back(i);
        }
    }
    if (!available_moves.empty()) {
        return available_moves[rand() % available_moves.size()];
    }
    return -1;
}

int main() {
    std::srand(std::time(nullptr));
    TicTacToe game;
    std::string input;
    int move;

    std::cout << "Welcome to Tic-Tac-Toe!\n";

    while (true) {
        game.print_board();
        std::cout << "Enter your move (0-8), 'reset' to start over, or 'giveup' to quit: ";
        std::cin >> input;

        if (input == "reset") {
            game.reset();
            std::cout << "Game reset!\n";
            continue;
        } else if (input == "giveup") {
            std::cout << "You gave up! Game over.\n";
            break;
        }

        try {
            move = std::stoi(input);
            if (move < 0 || move > 8) {
                std::cout << "Invalid move! Please enter a number between 0 and 8.\n";
                continue;
            }
        } catch (...) {
            std::cout << "Invalid input! Please enter a number between 0 and 8, 'reset', or 'giveup'.\n";
            continue;
        }

        if (!game.make_move(move, 'X')) {
            std::cout << "Invalid move! The square is already occupied.\n";
            continue;
        }

        if (game.get_winner() == 'X') {
            game.print_board();
            std::cout << "You win! Congratulations!\n";
            break;
        }

        if (game.is_full()) {
            game.print_board();
            std::cout << "The game is a tie!\n";
            break;
        }

        int computer_move = get_computer_move(game);
        if (computer_move != -1) {
            game.make_move(computer_move, 'O');
        }

        if (game.get_winner() == 'O') {
            game.print_board();
            std::cout << "Computer wins! Better luck next time.\n";
            break;
        }

        if (game.is_full()) {
            game.print_board();
            std::cout << "The game is a tie!\n";
            break;
        }
    }

    return 0;
}
