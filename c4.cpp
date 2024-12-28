#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <string>

using namespace std;

string playerColor = "\033[33m";
string computerColor = "\033[31m";

void cs() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pb(const vector<vector<char>>& b) {
    cs();
    cout << "\033[90m";
    cout << " ";
    for (int j = 0; j < 7; j++) {
        cout << " " << (j + 1) << "  ";
    }
    cout << "\033[0m\n";
    
    cout << "\033[38;5;250m+---+---+---+---+---+---+---+\033[0m" << endl;
    
    for (int i = 0; i < 6; i++) {
        cout << "\033[38;5;250m|\033[0m";
        for (int j = 0; j < 7; j++) {
            char c = b[i][j];
            if (c == 'P') {
                cout << playerColor << " O \033[0m";
            } else if (c == 'C') {
                cout << computerColor << " O \033[0m";
            } else {
                cout << "\033[90m   \033[0m";
            }
            cout << "\033[38;5;250m|\033[0m";
        }
        cout << endl;
        cout << "\033[38;5;250m+---+---+---+---+---+---+---+\033[0m" << endl;
    }
    cout << endl;
}

int ev(const vector<vector<char>>& b) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            int countC = 0, countP = 0, empty = 0;
            for (int k = 0; k < 4; k++) {
                if (b[i][j+k] == 'C') countC++;
                else if (b[i][j+k] == 'P') countP++;
                else empty++;
            }
            if (countC == 4) return 1000000;
            if (countP == 4) return -1000000;
            if (countC == 3 && empty == 1) return 50000;
            if (countP == 3 && empty == 1) return -50000;
            if (countC == 2 && empty == 2) return 5000;
            if (countP == 2 && empty == 2) return -5000;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            int countC = 0, countP = 0, empty = 0;
            for (int k = 0; k < 4; k++) {
                if (b[i+k][j] == 'C') countC++;
                else if (b[i+k][j] == 'P') countP++;
                else empty++;
            }
            if (countC == 4) return 1000000;
            if (countP == 4) return -1000000;
            if (countC == 3 && empty == 1) return 50000;
            if (countP == 3 && empty == 1) return -50000;
            if (countC == 2 && empty == 2) return 5000;
            if (countP == 2 && empty == 2) return -5000;
        }
    }

    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            int countC = 0, countP = 0, empty = 0;
            for (int k = 0; k < 4; k++) {
                if (b[i-k][j+k] == 'C') countC++;
                else if (b[i-k][j+k] == 'P') countP++;
                else empty++;
            }
            if (countC == 4) return 1000000;
            if (countP == 4) return -1000000;
            if (countC == 3 && empty == 1) return 50000;
            if (countP == 3 && empty == 1) return -50000;
            if (countC == 2 && empty == 2) return 5000;
            if (countP == 2 && empty == 2) return -5000;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int countC = 0, countP = 0, empty = 0;
            for (int k = 0; k < 4; k++) {
                if (b[i+k][j+k] == 'C') countC++;
                else if (b[i+k][j+k] == 'P') countP++;
                else empty++;
            }
            if (countC == 4) return 1000000;
            if (countP == 4) return -1000000;
            if (countC == 3 && empty == 1) return 50000;
            if (countP == 3 && empty == 1) return -50000;
            if (countC == 2 && empty == 2) return 5000;
            if (countP == 2 && empty == 2) return -5000;
        }
    }

    int centerControl = 0;
    for (int i = 0; i < 6; i++) {
        if (b[i][3] == 'C') centerControl += 300;
        if (b[i][2] == 'C' || b[i][4] == 'C') centerControl += 100;
    }

    return centerControl;
}

bool cw(const vector<vector<char>>& b, char p) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (b[i][j] == p && b[i][j+1] == p && 
                b[i][j+2] == p && b[i][j+3] == p) return true;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (b[i][j] == p && b[i+1][j] == p &&
                b[i+2][j] == p && b[i+3][j] == p) return true;
        }
    }
    
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (b[i][j] == p && b[i-1][j+1] == p &&
                b[i-2][j+2] == p && b[i-3][j+3] == p) return true;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (b[i][j] == p && b[i+1][j+1] == p &&
                b[i+2][j+2] == p && b[i+3][j+3] == p) return true;
        }
    }
    
    return false;
}

bool ibf(const vector<vector<char>>& b) {
    for (int j = 0; j < 7; j++) {
        if (b[0][j] == ' ') return false;
    }
    return true;
}

bool mv(vector<vector<char>>& b, int col, char p) {
    if (col < 0 || col >= 7 || b[0][col] != ' ') return false;
    
    for (int i = 5; i >= 0; i--) {
        if (b[i][col] == ' ') {
            b[i][col] = p;
            return true;
        }
    }
    return false;
}

void um(vector<vector<char>>& b, int col) {
    for (int i = 0; i < 6; i++) {
        if (b[i][col] != ' ') {
            b[i][col] = ' ';
            break;
        }
    }
}

int minimax(vector<vector<char>>& b, int depth, int alpha, int beta, bool isMaximizing, int lastCol) {
    if (cw(b, 'C')) return 1000000 + depth;
    if (cw(b, 'P')) return -1000000 - depth;
    if (ibf(b)) return 0;
    if (depth == 0) return ev(b);

    vector<int> moves = {3, 2, 4, 1, 5, 0, 6};
    
    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (int j : moves) {
            if (mv(b, j, 'C')) {
                int eval = minimax(b, depth - 1, alpha, beta, false, j);
                um(b, j);
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int j : moves) {
            if (mv(b, j, 'P')) {
                int eval = minimax(b, depth - 1, alpha, beta, true, j);
                um(b, j);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) break;
            }
        }
        return minEval;
    }
}

pair<int, int> cm(vector<vector<char>>& b) {
    int bestScore = INT_MIN;
    int bestCol = 3;
    vector<int> moves = {3, 2, 4, 1, 5, 0, 6};
    
    int emptySpaces = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (b[i][j] == ' ') emptySpaces++;
        }
    }
    
    int depth = emptySpaces > 30 ? 10 : 
                emptySpaces > 20 ? 12 : 
                emptySpaces > 10 ? 14 : 16;

    for (int j : moves) {
        if (mv(b, j, 'C')) {
            int score = minimax(b, depth, INT_MIN, INT_MAX, false, j);
            um(b, j);
            
            if (score > bestScore) {
                bestScore = score;
                bestCol = j;
            }
        }
    }
    
    for (int i = 5; i >= 0; i--) {
        if (b[i][bestCol] == ' ') {
            return {i, bestCol};
        }
    }
    
    return {-1, -1};
}

void botVsBotGame(vector<vector<char>>& b) {
    while (true) {
        auto [row, ccol1] = cm(b);
        mv(b, ccol1, 'P');
        pb(b);
        
        if (cw(b, 'P')) {
            cout << playerColor << "Yellow bot wins!\033[0m" << endl;
            break;
        }
        
        if (ibf(b)) {
            cout << "\033[90mIt's a tie!\033[0m" << endl;
            break;
        }
        
        auto [row2, ccol2] = cm(b);
        mv(b, ccol2, 'C');
        pb(b);
        
        if (cw(b, 'C')) {
            cout << computerColor << "Red bot wins!\033[0m" << endl;
            break;
        }
        
        if (ibf(b)) {
            cout << "\033[90mIt's a tie!\033[0m" << endl;
            break;
        }
    }
}

int pm(vector<vector<char>>& b, bool& botVsBot) {
    string input;
    while (true) {
        cout << "\033[90mEnter column (1-7) or code: \033[0m";
        cin >> input;
        
        if (input == "bb") {
            botVsBot = true;
            return -2;
        }
        
        if (input == "bot") {
            auto [row, ccol] = cm(b);
            return ccol;
        }
        
        if (input.substr(0, 1) == "#") {
            playerColor = "\033[38;2;" + 
                         to_string(stoi(input.substr(1,2), nullptr, 16)) + ";" +
                         to_string(stoi(input.substr(3,2), nullptr, 16)) + ";" +
                         to_string(stoi(input.substr(5,2), nullptr, 16)) + "m";
            continue;
        }
        
        if (input.substr(0, 2) == "c#") {
            computerColor = "\033[38;2;" + 
                          to_string(stoi(input.substr(2,2), nullptr, 16)) + ";" +
                          to_string(stoi(input.substr(4,2), nullptr, 16)) + ";" +
                          to_string(stoi(input.substr(6,2), nullptr, 16)) + "m";
            continue;
        }

        try {
            int col = stoi(input) - 1;
            if (col >= 0 && col < 7 && b[0][col] == ' ') {
                return col;
            }
        } catch (...) {}
        cout << "\033[31mInvalid move! Try again.\033[0m" << endl;
    }
}

void pg() {
    vector<vector<char>> b(6, vector<char>(7, ' '));
    cout << "\033[36mConnect Four starting!\033[0m" << endl;
    cout << "\033[33mWarning: The AI plays perfectly!\033[0m" << endl;
    pb(b);
    
    bool botVsBot = false;
    
    while (true) {
        int col = pm(b, botVsBot);
        
        if (botVsBot) {
            botVsBotGame(b);
            break;
        }
        
        mv(b, col, 'P');
        pb(b);
        
        if (cw(b, 'P')) {
            cout << playerColor << "Congratulations! You win!\033[0m" << endl;
            break;
        }
        if (ibf(b)) {
            cout << "\033[90mIt's a tie!\033[0m" << endl;
            break;
        }
        
        cout << "\033[90mThinking...\033[0m" << endl;
        auto [row, ccol] = cm(b);
        mv(b, ccol, 'C');
        pb(b);
        
        if (cw(b, 'C')) {
            cout << computerColor << "Computer wins!\033[0m" << endl;
            break;
        }
        if (ibf(b)) {
            cout << "\033[90mIt's a tie!\033[0m" << endl;
            break;
        }
    }
    
    char pa;
    cout << "\033[36mPlay again? (Y/N): \033[0m";
    cin >> pa;
    if (pa == 'Y' || pa == 'y') {
        pg();
    } else {
        cout << "\033[36mThanks for playing!\033[0m" << endl;
    }
}

int main() {
    pg();
    return 0;
}
