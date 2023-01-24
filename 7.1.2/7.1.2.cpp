#include <iostream>

#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <execution>

void SumVector(std::vector<int>& v1, std::vector<int>& v2, std::vector<int>& v3, size_t& n, size_t& m) {
    for (size_t i = n; i < m; i++)
    {
        v3[i] = v1[i] + v2[i];
    }
}

void VectorSumThread(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C, int threadNumber) {

    std::vector<std::thread> ZXC;
    size_t n = 0;
    size_t m = A.size() / threadNumber;

    for (size_t i = 0; i < threadNumber; i++)
    {

        ZXC.push_back(std::thread(SumVector, std::ref(A), std::ref(B), std::ref(C), std::ref(n), std::ref(m)));
        n = m + 1;
        if (i < static_cast<unsigned long long>(threadNumber) - 2) {
            m = m + A.size() / threadNumber;
        }
        else m = A.size();
    }
    for (auto& v : ZXC) {
        v.join();
    }
}

int main()
{
    std::cout << "Number of hardware cores - " << std::thread::hardware_concurrency() << "\n\n";
    std::cout << "\t\t1000\t\t10000\t\t100000\t\t1000000\n";



    for (size_t z = 0; z < 1; z++)
    {
        int NumThread = pow(2, 0);
        std::cout << NumThread << " threads ";
        for (size_t i = 1000; i < 1000000; i *= 10)
        {

            std::vector<int>A(i, rand() % 1000);
            std::vector<int>B(i, rand() % 1000);
            std::vector<int>C(i);

            auto start = std::chrono::high_resolution_clock::now();
            std::cout << 3;
            VectorSumThread(A, B, C, NumThread);
            std::cout << 4;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> time = end - start;
            std::cout << "\t" << time.count() << "\t";
        }std::cout << '\n';
    }
    return 0;
}