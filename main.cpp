#include <iostream>
#include <immintrin.h>
#include <chrono>
#include <cmath>
#include <string>

#define TABLE_LENGTH 154
#define COLUMN_LENGTH 30


uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}


int main() {
    {
        std::cout << "SIMPLE MULTIPLICATION" << std::endl;
        for (size_t i = 4; i < 9; ++i) {
            double val1 = 7.0;
            double val2 = 3.0;
            std::size_t operations = pow(10, i);
            auto start = std::chrono::system_clock::now();
            unsigned long long t1 = rdtsc();
            for (size_t j = 0; j < pow(10, i); ++j) {
                val1 = val1 + val2;
            }
            unsigned long long t2 = rdtsc();
            std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;
            double seconds = duration.count();
            double operations_per_second = operations / seconds;
            uint64_t processor_clocks = t2 - t1;
            double processor_clocks_per_second = processor_clocks / seconds;
            std::cout << operations << " - operations" << std::endl;
            std::cout << seconds << " - seconds" << std::endl;
            std::cout << operations_per_second << " - operations_per_second" << std::endl;
            std::cout << processor_clocks << " - processor_clocks" << std::endl;
            std::cout << processor_clocks_per_second << " - processor_clocks_per_second" << std::endl << std::endl;
            std::cout << "==================================================" << std::endl;
        }

    }
    {
        std::cout << "SSE2 MULTIPLICATION" << std::endl;
        for (size_t i = 4; i < 9; ++i) {
            const double array[2] = { 7.0, 7.0 };
            const double array2[2] = { 3.0, 3.0 };
            __m128d val1 = _mm_load_pd(&array[0]);
            __m128d val2 = _mm_load_pd(&array2[0]);
            std::size_t operations = pow(10, i);
            auto start = std::chrono::system_clock::now();
            unsigned long long t1 = rdtsc();
            for (size_t j = 0; j < pow(10, i) / 2; ++j) {
                val1 = _mm_add_pd(val1, val2);
            }
            unsigned long long t2 = rdtsc();
            std::chrono::duration<double> duration = std::chrono::system_clock::now() - start;
            double seconds = duration.count();
            double operations_per_second = operations / seconds;
            uint64_t processor_clocks = t2 - t1;
            double processor_clocks_per_second = processor_clocks / seconds;
            std::cout << operations << " - operations" << std::endl;
            std::cout << seconds << " - seconds" << std::endl;
            std::cout << operations_per_second << " - operations_per_second" << std::endl;
            std::cout << processor_clocks << " - processor_clocks" << std::endl;
            std::cout << processor_clocks_per_second << " - processor_clocks_per_second" << std::endl << std::endl;
            std::cout << "==================================================" << std::endl;
        }
    }
}
