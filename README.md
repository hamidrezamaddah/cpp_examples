# cpp_examples
c++ examples code
```c
CircularBuffer<10> buffer;

uint8_t values[] = {1, 2, 3, 4};

buffer.push(values, 4);

uint8_t peeked_values[2];

bool peek_result = buffer.peek(peeked_values, 2, 1);

if (!peek_result) 
{
    std::cout << "peek failed, range is out of bounds" << std::endl;
} 
else 
{
    for (size_t i = 0; i < 2; ++i) 
    {
        std::cout << static_cast<int>(peeked_values[i]) << " ";
    }
    // prints "2 3"
}
```
