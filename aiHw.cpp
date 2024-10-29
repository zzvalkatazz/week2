#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <stack>
#include <string>

using namespace std;

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
string directions[] = { "down", "up", "right", "left" };

string reverseDirection(const string& dir) {
    if (dir == "right") return "left";
    if (dir == "left") return "right";
    if (dir == "down") return "up";
    if (dir == "up") return "down";
    return dir;
}

int manhattan(const vector<vector<int>>& board, const vector<pair<int, int>>& targetPos) {
    int dist = 0;
    int N = board.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) continue; // Ignore the blank space
            pair<int, int> target = targetPos[board[i][j]]; // Get the target position
            dist += abs(i - target.first) + abs(j - target.second); // Manhattan distance
        }
    }
    return dist;
}

bool isSolvable(const vector<vector<int>>& board, int N,int zeroIndex) {
    vector<int> flattenedBoard;
    int zeroRow = 0; // Row of the blank tile (0-indexed)

    // Flatten the board and locate the blank tile
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                zeroRow = i; // Save the row index of the blank tile
            }
            else {
                flattenedBoard.push_back(board[i][j]);
            }
        }
    }

    // Count inversions
    int inversions = 0;
    for (int i = 0; i < flattenedBoard.size(); i++) {
        for (int j = i + 1; j < flattenedBoard.size(); j++) {
            if (flattenedBoard[i] > flattenedBoard[j]) {
                ++inversions;
            }
        }
    }

    // Solvability conditions
    if (N % 2 == 1 || (N%2 == 0 && zeroIndex !=-1))
    { // Odd grid size
        return inversions % 2 == 0;
    }

    else if(N%2 == 0)
    { // Even grid size
       
        return ((zeroRow % 2 == 0) == (inversions % 2 == 1));
    }
}

struct State {
    vector<vector<int>> board;
    int zero_x, zero_y;
    int g, h; // g - cost to reach state, h - estimated cost to goal
    vector<string> path;

    bool operator<(const State& other) const {
        return g + h > other.g + other.h;
    }
};

State dfsWithStack(State start, int limit, int& next_limit, bool& found, const vector<pair<int, int>>& targetPos) {
    stack<State> s;
    s.push(start);

    while (!s.empty()) {
        State current = s.top();
        s.pop();

        int f = current.g + current.h;
        if (f > limit) {
            next_limit = min(next_limit, f);
            continue;
        }

        if (current.h == 0) { // Solution found
            found = true;
            return current;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nx = current.zero_x + dx[dir];
            int ny = current.zero_y + dy[dir];

            if (nx >= 0 && nx < current.board.size() && ny >= 0 && ny < current.board.size()) {
                State next = current;
                swap(next.board[current.zero_x][current.zero_y], next.board[nx][ny]);
                next.zero_x = nx;
                next.zero_y = ny;
                next.g = current.g + 1;
                next.h = manhattan(next.board, targetPos);
                next.path.push_back(directions[dir]);
                s.push(next);
            }
        }
    }
    return start; // Return the current state if no solution found within the limit
}

bool idaStar(State start, const vector<pair<int, int>>& targetPos) {
    int limit = start.g + start.h;
    clock_t startTime = clock();

    while (true) {
        int next_limit = INT_MAX;
        bool found = false;

        State solution = dfsWithStack(start, limit, next_limit, found, targetPos);

        if (found) {
            clock_t endTime = clock();
            double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;

            cout << solution.g << endl;

            for (const string& move : solution.path) {
                cout << reverseDirection(move) << endl;
            }

            cout << "time: " << timeTaken << endl;
            return true;
        }

        if (next_limit == INT_MAX) {
            break;
        }

        limit = next_limit;
    }
    return false;
}

int main() {
    int totalTiles, indexZero;
    cin >> totalTiles >> indexZero;

    int N = sqrt(totalTiles + 1);

    vector<vector<int>> board(N, vector<int>(N));
    int zero_x, zero_y;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 0) {
                zero_x = i;
                zero_y = j;
            }
        }
    }

    vector<vector<int>> target(N, vector<int>(N));
    vector<pair<int, int>> targetPos(N * N);
    int counter = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (indexZero != -1 && i * N + j == indexZero) {
                target[i][j] = 0;
                targetPos[0] = { i, j };
            }
            else if (indexZero == -1 && i == N - 1 && j == N - 1) {
                target[i][j] = 0;
                targetPos[0] = { i, j };
            }
            else {
                target[i][j] = counter;
                targetPos[counter] = { i, j };
                counter++;
            }
        }
    }

    State start = { board, zero_x, zero_y, 0, manhattan(board, targetPos), {} };

    if (!isSolvable(board, N,indexZero)) {
        cout << -1 << endl;
        return 0;
    }

    if (!idaStar(start, targetPos)) {
        cout << -1 << endl;
    }

    return 0;
}
