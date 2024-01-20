#include<iostream>
#include<vector>
#include <deque>

using namespace std;

enum PieceType {
    X,
    O,
    Empty
};

class PlayingPiece {
    public:
    PieceType pieceType;

    PlayingPiece(PieceType pt) : pieceType(pt) {
    }
};

class PlayingPeiceX : public PlayingPiece {
    public:

    PlayingPeiceX() : PlayingPiece(PieceType::X) {}
};

class PlayingPeiceO : public PlayingPiece {
    public:

    PlayingPeiceO() : PlayingPiece(PieceType::O) {}
};

class PlayingPeiceEmpty : public PlayingPiece {
    public:
    PlayingPeiceEmpty() : PlayingPiece(PieceType::Empty) {};
};

class Board {
    public:
    int size;
    vector<vector<PlayingPiece>>board;

    Board(int size) : size(size) {
        PlayingPeiceEmpty p;
        vector<vector<PlayingPiece>>v (size, vector<PlayingPiece>(size, p));
        this->board = v;
    }

    void printBoard() {
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                cout<<board[i][j].pieceType<<" | ";
            }
            cout<<endl;
        }
    }

    vector<vector<int>> getFreeCells() {
        vector<vector<int>>res;
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (board[i][j].pieceType == PieceType::Empty) {
                    vector<int>x {i,j};
                    res.push_back(x);
                }
            }
        }
        return res;
    }

    bool addPiece(int x, int y, PlayingPiece p) {
        if (x < 0 || x >= size || y < 0 || y >= size)
            return false;
        if (board[x][y].pieceType != PieceType::Empty) {
            return false;
        }

        board[x][y] = p;
        return true;
    }
};

class Player {
    public:
    string name;
    PlayingPiece playingPiece;

    Player(string name, PlayingPiece playingPiece) : name(name), playingPiece(playingPiece) {

    }
};

class TicTacToeGame {
    public:
    deque<Player> players;
    Board gameBoard;

    TicTacToeGame () : gameBoard(3) {
        // create 2 players

        PlayingPeiceX px;
        PlayingPeiceO po;
        Player p1("xPlayer", px);
        Player p2("oPlayer", po);

        players.push_back(p1);
        players.push_back(p2);
    }

    string startGame() {
        bool noWinner = true;
        while (noWinner) {
            // Get the player at the front and then push him in the end
            Player curr = players.front();
            players.pop_front();

            gameBoard.printBoard();

            vector<vector<int>> emptySpaces = gameBoard.getFreeCells();

            // no winner
            if (emptySpaces.empty()) {
                noWinner = false;
                continue;
            }

            // read user input
            cout<<"Player:"<<curr.name<<" "<<"Enter row and col";
            int x,y;
            cin>>x>>y;

            bool isPlaceSuccessfully = gameBoard.addPiece(x,y,curr.playingPiece);

            if (!isPlaceSuccessfully) {
                cout<<"Incorrect position chosen, try again";
                players.push_front(curr);
                continue;
            }

            players.push_back(curr);

            bool isWinner = isThereWinner(x, y, curr.playingPiece.pieceType);

            if (isWinner)
                return curr.name;

        }
        return "tie";
    }

    bool isThereWinner(int x, int y, PieceType p) {
        bool rowMatch = true;
        bool colMatch = true;
        bool diagonalMatch = true;
        bool antiDiagonalMatch = true;

        for (int i=0;i<gameBoard.size;i++) {
            if (gameBoard.board[x][i].pieceType == PieceType::Empty || gameBoard.board[x][i].pieceType != p) {
                rowMatch = false;
                break;
            } 
        }

        for (int i=0;i<gameBoard.size;i++) {
            if (gameBoard.board[i][y].pieceType == PieceType::Empty || gameBoard.board[i][y].pieceType != p) {
                colMatch = false;
                break;
            }
        }

        for (int i=0;i<gameBoard.size;i++) {
            if (gameBoard.board[i][i].pieceType == PieceType::Empty || gameBoard.board[i][i].pieceType != p) {
                diagonalMatch = false;
                break;
            }
        }

        int i = 0;
        int j = gameBoard.size-1;
        while (i < gameBoard.size) {
            if (gameBoard.board[i][j].pieceType == PieceType::Empty || gameBoard.board[i][j].pieceType != p) {
                antiDiagonalMatch = false;
                break;
            }
            i++;
            j--;
        }

        return rowMatch || colMatch || diagonalMatch || antiDiagonalMatch;
    }
};


int main() {
    TicTacToeGame game;
    string res = game.startGame();
    cout<<res;
}