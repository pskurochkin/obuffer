#include <thread>
#include <atomic>

#include "circular_buffer.h"

int main() {
    CircularBuffer<int> cb(64);
    std::atomic<bool> flag(true);

    std::thread t1([&] {
        while (flag) {
            std::vector<int> v;
            for (int i = 0; i < 16; ++i) {
                v.push_back(rand() % 16);
            }

            cb.push(v.data(), v.size());
        }
    });

    std::thread t2([&] {
        while (flag) {
            std::vector<int> v(8);
            cb.pop(v.data(), v.size());
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    flag = false;

    t1.join();
    t2.join();

    return 0;
}