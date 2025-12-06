#ifndef PRINT_H
#define PRINT_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

class Print {
public:
    virtual size_t write(uint8_t ch) = 0;

    virtual size_t write(const uint8_t *buffer, size_t size) {
        size_t n = 0;
        for (size_t i = 0; i < size; ++i) n += write(buffer[i]);
        return n;
    }

    size_t write(const char *str) {
        if (!str) return 0;
        return write((const uint8_t*)str, strlen(str));
    }

    size_t print(const char *str) {
        return write(str);
    }

    // convenience
    size_t println(const char *str) {
        size_t n = write(str);
        n += write('\r');
        n += write('\n');
        return n;
    }
};

#endif // PRINT_H
