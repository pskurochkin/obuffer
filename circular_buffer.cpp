#include "circular_buffer.h"

template <class T>
CircularBuffer<T>::CircularBuffer(size_t size) {
    buffer.resize(size);
    wIt = rIt = buffer.begin();
    actualSize = 0;
}

template <class T>
void CircularBuffer<T>::push(const T *data, size_t n) {
    std::unique_lock<std::mutex> lock(mtx);

    while (buffer.size() - actualSize < n) {
        cv.wait(lock);
    }

    for (size_t i = 0; i < n; ++i) {
        *(wIt++) = data[i];

        if (wIt == buffer.end()) wIt = buffer.begin();
    }
    actualSize = actualSize + n;
    cv.notify_all();
}

template <class T>
void CircularBuffer<T>::pop(T *buf, size_t n) {
    std::unique_lock<std::mutex> lock(mtx);

    while (actualSize < n) {
        cv.wait(lock);
    }

    for (size_t i = 0; i < n; ++i) {
        buf[i] = *(rIt++);

        if (rIt == buffer.end()) rIt = buffer.begin();
    }
    actualSize = actualSize - n;
    cv.notify_all();
}

template class CircularBuffer<char>;
template class CircularBuffer<int>;
