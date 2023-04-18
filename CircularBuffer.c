#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 10

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t size;
} CircularBuffer;

void init_buffer(CircularBuffer* buffer) {
    buffer->head = 0;
    buffer->tail = 0;
    buffer->size = 0;
}

bool push(CircularBuffer* buffer, uint8_t value) {
    if (buffer->size == BUFFER_SIZE) {
        return false;
    }
    buffer->buffer[buffer->tail] = value;
    buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
    ++buffer->size;
    return true;
}

bool push_multiple(CircularBuffer* buffer, const uint8_t* values, size_t count) {
    if (count > BUFFER_SIZE - buffer->size) {
        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        buffer->buffer[buffer->tail] = values[i];
        buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
        if (buffer->size < BUFFER_SIZE) {
            ++buffer->size;
        } else {
            buffer->head = (buffer->head + 1) % BUFFER_SIZE;
        }
    }
    return true;
}

bool pop(CircularBuffer* buffer, uint8_t* value) {
    if (buffer->size == 0) {
        return false;
    }
    *value = buffer->buffer[buffer->head];
    buffer->head = (buffer->head + 1) % BUFFER_SIZE;
    --buffer->size;
    return true;
}

bool pop_multiple(CircularBuffer* buffer, uint8_t* values, size_t count) {
    if (count > buffer->size) {
        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        values[i] = buffer->buffer[buffer->head];
        buffer->head = (buffer->head + 1) % BUFFER_SIZE;
        --buffer->size;
    }
    return true;
}

bool peek(const CircularBuffer* buffer, uint8_t* values, size_t count, size_t position) {
    if (position + count > buffer->size) {
        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        values[i] = buffer->buffer[(buffer->head + position + i) % BUFFER_SIZE];
    }
    return true;
}

bool remove_items(CircularBuffer* buffer, size_t count, size_t position) {
    if (position + count > buffer->size) {
        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        buffer->head = (buffer->head + 1) % BUFFER_SIZE;
    }
    buffer->size -= count;
    return true;
}
