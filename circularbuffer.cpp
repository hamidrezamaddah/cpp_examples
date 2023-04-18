template <size_t N>
class CircularBuffer {
public:
    CircularBuffer() : head_(0), tail_(0), size_(0) {}

    bool push(uint8_t value) {
        if (size_ == N) {
            return false;
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % N;
        ++size_;
        return true;
    }

    bool push(const uint8_t* values, size_t count) {
        if (count > N - size_) {
            return false;
        }
        for (size_t i = 0; i < count; ++i) {
            buffer_[tail_] = values[i];
            tail_ = (tail_ + 1) % N;
            if (size_ < N) {
                ++size_;
            } else {
                head_ = (head_ + 1) % N;
            }
        }
        return true;
    }

    bool pop(uint8_t& value) {
        if (size_ == 0) {
            return false;
        }
        value = buffer_[head_];
        head_ = (head_ + 1) % N;
        --size_;
        return true;
    }

    bool pop(uint8_t* values, size_t count) {
        if (count > size_) {
            return false;
        }
        for (size_t i = 0; i < count; ++i) {
            values[i] = buffer_[head_];
            head_ = (head_ + 1) % N;
            --size_;
        }
        return true;
    }

    bool peek(uint8_t* values, size_t count, size_t position) const {
        if (position + count > size_) {
            return false;
        }
        for (size_t i = 0; i < count; ++i) {
            values[i] = buffer_[(head_ + position + i) % N];
        }
        return true;
    }

    bool remove(size_t count, size_t position) {
        if (position + count > size_) {
            return false;
        }
        for (size_t i = 0; i < count; ++i) {
            head_ = (head_ + 1) % N;
        }
        size_ -= count;
        return true;
    }

private:
    uint8_t buffer_[N];
    size_t head_;
    size_t tail_;
    size_t size_;
};
