#include "screen.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void init_terminal(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll() {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            size_t prev_index = (y - 1) * VGA_WIDTH + x;
            size_t curr_index = y * VGA_WIDTH + x;
            terminal_buffer[prev_index] = terminal_buffer[curr_index];
        }
    }
    size_t last_row_index = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (size_t x = 0; x < VGA_WIDTH; x++)
        terminal_buffer[last_row_index + x] = vga_entry(' ', terminal_color);
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
				terminal_scroll();
				terminal_row = 0;
			}
        }
    }
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int);
                    char buffer[32];
                    terminal_writestring(itoa(value, buffer, 10));
                    break;
                }
                case 'f': {
                    double value = va_arg(args, double);
                    char buffer[32];
                    terminal_writestring(ftoa(value, buffer));\
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    terminal_writestring(str);
                    break;
                }
                case 'c': {
                    char c = va_arg(args, int);
                    terminal_putchar(c);
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int);
                    char buffer[32];
                    terminal_writestring(itoa(value, buffer, 16));
                    break;
                }
                case 'u': {
                    unsigned int value = va_arg(args, unsigned int);
                    char buffer[32];
                    terminal_writestring(utoa(value, buffer, 10));
                    break;
                }
                default:
                    terminal_putchar('%');
                    terminal_putchar(*format);
                    break;
            }
        } else {
            terminal_putchar(*format);
        }
        format++;
    }
    va_end(args);
}

void kerror(const char* format, ...) {
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED);
    va_list args;
    va_start(args, format);
    terminal_writestring("ERROR: ");
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    int value = va_arg(args, int);
                    char buffer[32];
                    terminal_writestring(itoa(value, buffer, 10));
                    break;
                }
                case 'f': {
                    double value = va_arg(args, double);
                    char buffer[32];
                    terminal_writestring(ftoa(value, buffer));\
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    terminal_writestring(str);
                    break;
                }
                case 'c': {
                    char c = va_arg(args, int);
                    terminal_putchar(c);
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int);
                    char buffer[32];
                    terminal_writestring(itoa(value, buffer, 16));
                    break;
                }
                case 'u': {
                    unsigned int value = va_arg(args, unsigned int);
                    char buffer[32];
                    terminal_writestring(utoa(value, buffer, 10));
                    break;
                }
                default:
                    terminal_putchar('%');
                    terminal_putchar(*format);
                    break;
            }
        } else {
            terminal_putchar(*format);
        }
        format++;
    }
    va_end(args);
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}