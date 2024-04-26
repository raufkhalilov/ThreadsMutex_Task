#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int sharedData = 0; // это общая переменная для чтения и записи

void writerFunction() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        sharedData = i;
        std::cout << "Writer wrote: " << sharedData << std::endl;
        mtx.unlock();

        // Задержка для наглядности
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void readerFunction() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        std::cout << "Reader read: " << sharedData << std::endl;
        mtx.unlock();

        // Задержка для наглядности
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread writerThread(writerFunction);
    std::thread readerThread(readerFunction);

    writerThread.join();
    readerThread.join();

    return 0;
}
