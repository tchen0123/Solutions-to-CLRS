#include "LCS.h"

int LCSLength(std::string X, std::string Y, std::vector<std::vector<int>> &solution)
{
        solution.resize(X.size() + 1);
        for (std::size_t i = 0; i != solution.size(); ++i) {
                solution[i].resize(Y.size() + 1);
                solution[i].assign(Y.size() + 1, 0);
        }

        std::vector<std::vector<int>> result(X.size() + 1);
        for (std::size_t i = 0; i != result.size(); ++i) {
                result[i].resize(Y.size() + 1);
        }

        for (std::size_t i = 1; i <= X.size(); ++i) {
                for (std::size_t j = 1; j <= Y.size(); ++j) {
                        if (X[i - 1] == Y[j - 1]) {
                                result[i][j] = result[i - 1][j - 1] + 1;
                                solution[i][j] = 0;
                        }
                        else if (result[i - 1][j] >= result[i][j - 1]) {
                                result[i][j] = result[i - 1][j];
                                solution[i][j] = 1;
                        }
                        else {
                                result[i][j] = result[i][j - 1];
                                solution[i][j] = 2;
                        }
                }
        }
        return result[X.size()][Y.size()];
}

