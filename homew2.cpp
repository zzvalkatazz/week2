#include <iostream>
#include <vector>
#include <random>
#include <ctime> // For measuring time

using namespace std;

random_device rd;
mt19937 rng(rd());

void initQueens(vector<int>& queens, int N) {
    for (int i = 0; i < N; i++) {
        queens[i] = i; // Start with one queen per row
    }
    shuffle(queens.begin(), queens.end(), rng); // Shuffle for randomness
}

int calculateConflicts(const vector<int>& queens, int N, int col, int row, const vector<int>& rowConf, const vector<int>& mainDiagConf, const vector<int>& secDiagConf) {
    return rowConf[row] + mainDiagConf[row - col + N - 1] + secDiagConf[row + col] - 3;
}

int getColWithQueenWithMaxConf(const vector<int>& queens, int N, const vector<int>& rowConf, const vector<int>& mainDiagConf, const vector<int>& secDiagConf) {
    vector<int> maxConfCols;
    int maxConf = -1;

    for (int col = 0; col < N; col++) {
        int row = queens[col];
        int conflicts = calculateConflicts(queens, N, col, row, rowConf, mainDiagConf, secDiagConf);

        if (conflicts > maxConf) {
            maxConf = conflicts;
            maxConfCols = { col };
        }
        else if (conflicts == maxConf) {
            maxConfCols.push_back(col);
        }
    }

    return maxConfCols[rng() % maxConfCols.size()]; // Randomly select among columns with max conflicts
}

int getRowWithMinConflict(const vector<int>& queens, int N, int col, const vector<int>& rowConf, const vector<int>& mainDiagConf, const vector<int>& secDiagConf) {
    vector<int> minConfRows;
    int minConf = N + 1;

    for (int row = 0; row < N; row++) {
        if (row == queens[col]) continue;

        int conflicts = calculateConflicts(queens, N, col, row, rowConf, mainDiagConf, secDiagConf);

        if (conflicts < minConf) {
            minConf = conflicts;
            minConfRows = { row };
        }
        else if (conflicts == minConf) {
            minConfRows.push_back(row);
        }
    }

    return minConfRows[rng() % minConfRows.size()]; // Randomly select among rows with min conflicts
}

bool hasConflicts(int N, const vector<int>& rowConf, const vector<int>& mainDiagConf, const vector<int>& secDiagConf) {
    for (int i = 0; i < N; i++) {
        if (rowConf[i] > 1) return true;
    }
    for (int i = 0; i < 2 * N - 1; i++) {
        if (mainDiagConf[i] > 1) return true;
    }
    return false;
}

void solve(int N) {
    clock_t startTime = clock(); // Start the clock

    vector<int> queens(N);
    vector<int> rowConf(N, 0), mainDiagConf(2 * N - 1, 0), secDiagConf(2 * N - 1, 0);

    initQueens(queens, N);

    // Initialize conflict counts
    for (int col = 0; col < N; col++) {
        int row = queens[col];
        rowConf[row]++;
        mainDiagConf[row - col + N - 1]++;
        secDiagConf[row + col]++;
    }

    int maxIter = 3 * N; // Adjust the multiplier as needed
    for (int iter = 0; iter < maxIter; iter++) {
        if (!hasConflicts(N, rowConf, mainDiagConf, secDiagConf)) {
            // Solution found
            clock_t endTime = clock(); // End the clock
            double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;

            if (N < 100) {
                // Print the board for small N
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        cout << (queens[i] == j ? '*' : '_') << ' ';
                    }
                    cout << endl;
                }
            }
            else {
                // Print only the time taken for large N
                cout << timeTaken << endl;
            }
            return;
        }

        int col = getColWithQueenWithMaxConf(queens, N, rowConf, mainDiagConf, secDiagConf);
        int newRow = getRowWithMinConflict(queens, N, col, rowConf, mainDiagConf, secDiagConf);

        // Update conflict counters for the old row
        int oldRow = queens[col];
        rowConf[oldRow]--;
        mainDiagConf[oldRow - col + N - 1]--;
        secDiagConf[oldRow + col]--;

        // Move queen to the new row and update conflict counters
        queens[col] = newRow;
        rowConf[newRow]++;
        mainDiagConf[newRow - col + N - 1]++;
        secDiagConf[newRow + col]++;
    }

    // Restart if solution not found within the limit
    solve(N);
}

int main() {
    int N;
    cin >> N;

    if (N == 1) {
        cout << "* " << endl; // Single queen solution for N = 1
    }
    else if (N <= 3) {
        cout << "No solution for table with size " << N << "x" << N << "." << endl;
    }
    else {
        solve(N);
    }

    return 0;
}

