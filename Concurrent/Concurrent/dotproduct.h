#pragma once

#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <atomic>

using Vector = std::vector<int>;
struct DotProduct
{
    std::mutex result_mutex;
    bool atomic;
    DotProduct(const Vector& a, const Vector& b, bool atomic) : a(a), b(b), atomic(atomic)
    {
        if (a.size() != b.size())
            throw "The vectors are of unequal length";
    }

    double operator()()
    {
        size_t nr_threads = 4;
        size_t length = a.size();

        int delta = length / nr_threads;
        int remainder = length % nr_threads;
        int L = 0, R = 0;
        if (atomic)
        {
            resulta = 0;
        }
        else
        {
            result = 0;
        }
        // Create threads
        for (int i = 0; i < nr_threads; ++i) {
            R = L + delta;
            if (i == nr_threads - 1)
                R += remainder;
            workers.push_back(std::thread(&DotProduct::partial_dot_product, this, L, R));
            L = R;
        }
        // Join threads
        for (auto& thread : workers) {
            thread.join();
        }
        if (atomic)
        {
            return resulta;
        }
        else
        {
            return result;
        }
    }

private:
    const Vector& a;
    const Vector& b;

    std::vector<std::thread> workers;
    int result = 0;
    std::atomic_int resulta;

    void partial_dot_product(int L, int R)
    {
        for (int i = L; i < R; ++i) {
            if (atomic)
            {
                resulta += a[i] * b[i];
            }
            else
            {
                std::lock_guard<std::mutex> lock(result_mutex);
                result += a[i] * b[i];
            }
        }
    }

};

void dotproduct(bool atomic);