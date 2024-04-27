#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>

std::mutex print_mutex;

int find_d_last_digit(int a, int b, int c) {
    return 10 - (a + b + c) % 10;
}

int sum_numbers_to_the_fifth(const std::vector<int>& v) {
    int total = 0;
    for (auto& num : v) {
        total += std::pow(num, 5);
    }
    return total;
}

int* solve_for_e(int a, int b, int c, int d) {
    std::vector<int> v = {a, b, c, d};
    long long sum_of_fifth = sum_numbers_to_the_fifth(v);
    long long e_to_fifth = std::stoll(std::to_string(a) + std::to_string(b) + std::to_string(c) + std::to_string(d) + "00000") - sum_of_fifth;
    if (e_to_fifth > 0) {
        int e = std::round(std::pow(e_to_fifth, 0.2));
        int* result = new int(e);
        return result;
    }
    return nullptr;
}

bool test_trueness_abcde(int a, int b, int c, int d, int e) {
    std::vector<int> v = {a, b, c, d, e};
    long long summed_numbers_to_fifth = sum_numbers_to_the_fifth(v);
    long long concatenated_numbers = std::stoll(std::to_string(a) + std::to_string(b) + std::to_string(c) + std::to_string(d) + std::to_string(e));
    return summed_numbers_to_fifth == concatenated_numbers;
}

void thread_function(int a_start, int a_end) {
    for (int a = a_start; a < a_end; ++a) {
        for (int b = 10000; b < 1000000; ++b) {
            for (int c = 10000; c < 1000000; ++c) {
                int d_last = find_d_last_digit(a, b, c);
                for (int d = 10000 + d_last; d < 1000000; d += 10) {
                    int* e_ptr = solve_for_e(a, b, c, d);
                    if (e_ptr != nullptr) {
                        int e = *e_ptr;
                        if (test_trueness_abcde(a, b, c, d, e)) {
                            std::lock_guard<std::mutex> lock(print_mutex);
                            std::cout << "Found one " << a << " " << b << " " << c << " " << d << " " << e << std::endl;
                        }
                        delete e_ptr;
                    }
                }
            }
        }
    }
}

int main() {
    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int range_per_thread = 1000000 / num_threads;
    
    for (int i = 0; i < num_threads; ++i) {
        int start = 10000 + i * range_per_thread;
        int end = i == num_threads - 1 ? 1000000 : start + range_per_thread;
        threads.emplace_back(thread_function, start, end);
    }

    for (auto& th : threads) {
        th.join();
    }

    return 0;
}
