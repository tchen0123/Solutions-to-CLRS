#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "cut_rod.h"
#include "LCS.h"

void createPriceTable(std::vector<int> &price)
{
        std::ifstream ifstrm("price.txt");
        price.push_back(0);

        int temp;
        while (ifstrm >> temp) {
                price.push_back(temp);
        }
}


int main()
{
        std::vector<int> price;
        createPriceTable(price);

        std::string A, B;
        std::cin >> A >> B;
        std::cout << A << '\n';
        std::cout << B << std::endl;
        std::vector<std::vector<int>> result;
        std::cout << LCS_Length(A, B, result) << std::endl;
        printLCS(A, A.size(), B.size(), result);
        std::cout << std::endl;
}
