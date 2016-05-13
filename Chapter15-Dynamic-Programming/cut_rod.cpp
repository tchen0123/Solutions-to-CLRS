/*
 * Solutions-to-CLRS/Chapter15-Dynamic-Programming/cut_rod.cpp
 *
 * Copyrigh(c) 2016  Jiawei Feng
 */

#include <iostream>
#include <cstdlib>
#include <ctime>


/*
 * Create a price table.
 */
static inline void CreatePriceTable(unsigned price[], const unsigned size)
{
        price[0] = 1;
        for (unsigned i = 1; i != size; ++i) {
                price[i] = price[i - 1] + rand() % 7;
        }
}

unsigned SimpleCutRod(const unsigned length, const unsigned price[]);
unsigned MemoizedCutRod(const unsigned length, const unsigned price[]);
unsigned MemoizedCutRodAux(const unsigned length, const unsigned price[], int memo[]);
unsigned BottomupCutRod(const unsigned length, const unsigned price[]);


int main()
{
        unsigned length;
        std::cout << "How long is the rod you will cut?" << std::endl;
        std::cin >> length;

        unsigned price[length];
        CreatePriceTable(price, length);

        std::cout << "Price Table\n";
        for (unsigned i : price) {
                std::cout << i << ' ';
        }
        std::cout << std::endl;

        unsigned revenue;
        decltype(std::clock()) start, stop;

        std::cout << "Simple cut rod:\n";
        start = std::clock();
        revenue = SimpleCutRod(length, price);
        stop = std::clock();
        std::cout << "Revenue: " << revenue << '\n';
        std::cout << "Time consuming: " << stop - start << "ms" << std::endl;

        std::cout << "Memoized cut rod:\n";
        start = std::clock();
        revenue = MemoizedCutRod(length, price);
        stop = std::clock();
        std::cout << "Revenue: " << revenue << '\n';
        std::cout << "Time consuming: " << stop - start << "ms" << std::endl;

        std::cout << "Buottom-up cut rod:\n";
        start = std::clock();
        revenue = BottomupCutRod(length, price);
        stop = std::clock();
        std::cout << "Revenue: " << revenue << '\n';
        std::cout << "Time consuming: " << stop - start << "ms" << std::endl;

        return 0;
}

/*
 * Simple cut-rod algorithm.
 */
unsigned SimpleCutRod(const unsigned length, const unsigned price[])
{
        if (length == 0) {
                return 0;
        }

        unsigned revenue = 0;
        for (unsigned i = 0; i != length; ++i) {
                unsigned temp = price[i] + SimpleCutRod(length - i - 1, price);
                revenue = revenue > temp ? revenue : temp;
        }

        return revenue;
}

/*
 * Memoized cut-rod algorithm.
 */
unsigned MemoizedCutRod(const unsigned length, const unsigned price[])
{
        int memo[length + 1];
        for (int &i : memo) {
                i = -1;
        }

        return MemoizedCutRodAux(length, price, memo);
}

unsigned MemoizedCutRodAux(const unsigned length, const unsigned price[], int memo[])
{
        if (memo[length] >= 0) {
                return memo[length];
        }

        unsigned revenue = 0;
        for (unsigned i = 0; i != length; ++i) {
                unsigned temp = price[i] + MemoizedCutRodAux(length - i - 1, price, memo);
                revenue = revenue > temp ? revenue : temp;
        }
        memo[length] = revenue;

        return revenue;
}

/*
 * Bottom-up cut-rod algorithm.
 */
unsigned BottomupCutRod(const unsigned length, const unsigned price[])
{
        unsigned memo[length + 1];
        memo[0] = 0;

        for (unsigned i = 1; i != length + 1; ++i) {
                unsigned revenue = 0;
                for (unsigned j = 0; j !=i; ++j) {
                        unsigned temp = price[j] + memo[i - j - 1];
                        revenue = revenue > temp ? revenue : temp;
                }
                memo[i] = revenue;
        }

        return memo[length];
}
