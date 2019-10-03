#ifndef OBUFFER_CIRCULAR_BUFFER_H
#define OBUFFER_CIRCULAR_BUFFER_H

#include <vector>
#include <mutex>
#include <condition_variable>

template <class T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t size);

    void push(const T *data, size_t n);

    void pop(T *buf, size_t n);

private:
    std::vector<T> buffer;
    std::mutex mtx;
    std::condition_variable cv;

    typename std::vector<T>::iterator wIt;
    typename std::vector<T>::iterator rIt;
    size_t actualSize;
};


#endif //OBUFFER_CIRCULAR_BUFFER_H
