#include <iostream>

#include <vector>

#include <chrono>
#include <stdlib.h>
#include <time.h>

#include <algorithm>

int N = 0;
int* queens = nullptr;
int* r = nullptr;
int* d1 = nullptr;
int* d2 = nullptr;
int diag_size = 0;

int main_diag_index(int row_index, int col_index) {
    return (N - 1) + (col_index - row_index);
}

int secondary_diag_index(int row_index, int col_index) {
    return col_index + row_index;
}

int get_conflicts(int row_index, int col_index) {
    int conflicts = r[row_index] + d1[main_diag_index(row_index, col_index)] + d2[secondary_diag_index(row_index, col_index)];

    if (queens[col_index] == row_index) {
        conflicts -= 3;
    }

    return conflicts;
}

int get_col_max_conf() {
    int conflicts = -1;
    int column = -1;
    std::vector<int> container;

    // 'i' is a column
    for (int i = 0; i < N; ++i) {
        if (queens[i] < 0) {
            // No queen assigned yet
            continue;
        }

        int current_conflicts = get_conflicts(queens[i], i);

        if (current_conflicts > conflicts) {
            conflicts = current_conflicts;
            column = i;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (queens[i] < 0) {
            // No queen assigned yet
            continue;
        }
        int current_conflicts = get_conflicts(queens[i], i);

        if (current_conflicts == conflicts) {
            container.push_back(i);
        }
    }

    if (!container.empty()) {
        int container_size = container.size();

        column = container.at(rand() % container_size);
    }

    return column;
}

int get_row_min_conf(int column) {
    int conflicts = N;
    int row = -1;
    std::vector<int> container;

    // 'i' is a row
    for (int i = 0; i < N; ++i) {
        int current_conflicts = get_conflicts(i, column);

        if (current_conflicts < conflicts) {
            conflicts = current_conflicts;
            row = i;
        }
    }

    for (int i = 0; i < N; ++i) {
        int current_conflicts = get_conflicts(i, column);

        if (current_conflicts == conflicts) {
            container.push_back(i);
        }
    }

    if (!container.empty()) {
        int container_size = container.size();

        row = container.at(rand() % container_size);
    }

    return row;
}

bool has_conf() {
    int column = get_col_max_conf();
    bool has_conf = get_conflicts(queens[column], column);

    return has_conf;
}

bool has_conf_col(int column) {
    return get_conflicts(queens[column], column);
}

void print_board() {
    std::cout << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (queens[j] == i) {
                std::cout << "* ";
            }
            else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void move_queen(int curr_col, int new_row) {
    if (queens[curr_col] != -1) {
        r[queens[curr_col]]--;
        d1[main_diag_index(queens[curr_col], curr_col)]--;
        d2[secondary_diag_index(queens[curr_col], curr_col)]--;
    }

    queens[curr_col] = new_row;
    r[queens[curr_col]]++;
    d1[main_diag_index(queens[curr_col], curr_col)]++;
    d2[secondary_diag_index(queens[curr_col], curr_col)]++;
}

void init() {
    std::vector<int> rows;
    for (int i = 0; i < N; ++i) {
        rows.push_back(i);
    }
    std::random_shuffle(rows.begin(), rows.end());

    for (int i = 0; i < N; ++i) {
        move_queen(i, rows.at(i));
    }
}

void solve() {
    init();

    int iter = 0;
    while (iter++ <= 3 * N) {
        int column = get_col_max_conf();

        if (!has_conf_col(column)) {
            return;
        }

        int row = get_row_min_conf(column);

        move_queen(column, row);
    }

    if (has_conf()) {
        solve();
    }
}

int main() {
    srand(time(NULL));
    // Number of queens
    std::cin >> N;
    if (N == 2 || N == 3) {
        std::cout << "No solution for a " << N << 'x' << N << " board." << std::endl;
        return -1;
    }
    diag_size = 2 * N - 1;

    // Array of queens
    queens = new int[N];
    for (int i = 0; i < N; ++i) {
        // No queens are assigned yet
        queens[i] = -1;
    }

    // Store the count of the queens for each row
    r = new int[N]();

    // Store the count of the queens for each diagonal - main (d1) and secondary (d2)
    d1 = new int[diag_size]();
    d2 = new int[diag_size]();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    solve();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // Print the solution
    if (N <= 20) {
        print_board();
    }
    else {
        std::cout << "Time elapsed (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    }

    delete[] queens;
    delete[] r;
    delete[] d1;
    delete[] d2;

    return 0;
}
