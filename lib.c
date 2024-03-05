#include "lib.h"

double fabs(double x) {
    return x < 0 ? -x : x;
}

char* itoa(int value, char* str, int base) {
    int i = 0;
    int isNegative = 0;
    if (value < 0 && base == 10) {
        isNegative = 1;
        value = -value;
    }
    do {
        int rem = value % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        value /= base;
    } while (value);
    if (isNegative)
        str[i++] = '-';
    str[i] = '\0';
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}

char* ftoa(float value, char* str) {
    int ipart = (int)value;
    float fpart = value - (float)ipart;
    itoa(ipart, str, 10);
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    str[i++] = '.';
    float rounding = 0.5;
    for (int j = 0; j < 6; j++) {
        rounding /= 10;
    }
    fpart += rounding;
    for (int j = 0; j < 6; j++) {
        fpart *= 10;
        int digit = (int)fpart;
        str[i++] = digit + '0';
        fpart -= digit;
    }
    str[i] = '\0';
    return str;
}

char* utoa(unsigned int value, char* str, int base) {
    char* ptr = str, *ptr1 = str, tmp_char;
    unsigned int tmp_value;
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789abcdef"[tmp_value - value * base];
    } while (value);
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return str;
}

void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;
    for (size_t i = 0; i < n; i++)
        pdest[i] = psrc[i];
    return dest;
}
 
void *memset(void *s, int c, size_t n) {
    uint8_t *p = (uint8_t *)s;
    for (size_t i = 0; i < n; i++)
        p[i] = (uint8_t)c;
    return s;
}
 
void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;
    if (src > dest) {
        for (size_t i = 0; i < n; i++)
            pdest[i] = psrc[i];
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--)
            pdest[i-1] = psrc[i-1];
    }
    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return p1[i] < p2[i] ? -1 : 1;
    }
    return 0;
}