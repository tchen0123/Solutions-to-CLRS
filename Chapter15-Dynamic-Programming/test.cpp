#include <iostream>
#include <fstream>
#include <vector>
#include "cut_rod.h"


void inputPrice(std::vector<int> &price)
{
        std::fstream fstrm("price.txt");
        std::string temp;
        for (std::size_t i = 0; i != 10; ++i) {
                fstrm >> temp;
                price.push_back(std::stoi(temp));
        }
}

void printSolution(std::vector<int> &solution, std::size_t length)
{
        while (length) {
                std::cout << solution[length] << " ";
                length -= solution[length];
        }
}


int main()
{
        std::vector<int> price;
        inputPrice(price);

        std::size_t length;
        std::cin >> length;

        std::vector<int> solution(length + 1);
        std::cout << bottomUpcutRod(price, length, solution) << std::endl;
        printSolution(solution, length);
        //std::cout << memoizedCutRod(price, length) << std::endl;
        //std::cout << cutRod(price, length) << std::endl;
}
