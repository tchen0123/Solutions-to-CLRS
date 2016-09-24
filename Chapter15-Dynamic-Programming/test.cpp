#include <iostream>
#include <vector>
#include <fstream>
#include "cut_rod.h"

void createPriceTable(std::vector<int> &price)
{
        std::ifstream ifstrm("price.txt");
        price.push_back(0);

        int temp;
        while (ifstrm >> temp) {
                price.push_back(temp);
        }
}

void printSolution(std::vector<int> &solution, int len)
{
        while (len){
                std::cout << solution[len] << " ";
                len -= solution[len];
        }
}

int main()
{
        std::vector<int> price;
        createPriceTable(price);

        std::vector<int> solution;
        std::size_t len;
        std::cin >> len;
        std::cout << bottomUpCutRod(price, len, solution) << std::endl;
        printSolution(solution, len);
        std::cout << std::endl;
}
