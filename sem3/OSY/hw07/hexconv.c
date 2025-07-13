const char hex_digits[] = "0123456789abcdef";         //global char array with hexadecimal digits
const char end_line = '\n';                           //global char end line
const char ox[] = "0x";                               //global char array to simplify the writing of the hex. num.

//function for quick use write and exit
int syscall(int aa, int bb, int cc, int dd) {
    int ret;
    asm volatile (
        "int $0x80" :
        "=a" (ret) :
        "a" (aa), "b" (bb), "c" (cc), "d" (dd) :
        "memory");
    return ret;
}

//function to convert char array to int
long long conv_to_int(char buf[], int len) {
    long long num = 0;
    long long tens = 1;
    for (int i = len - 1; i >= 0; i--) {
        num += (buf[i] - '0') * tens;
        tens *= 10;
    }

    return num;
}

//function to convert int to char array with hex. representation
void conv_to_hex(char buf[], int len) {
    if (len == 0) return;

    syscall(4, 1, (int)(&ox), 2);

    long long num = conv_to_int(buf, len);
    if (num == 0) {
        syscall(4, 1, (int)(&hex_digits[0]), 1);
    }

    char hex_num[8];
    int hex_len = 0;

    while (num != 0) {
        hex_num[hex_len++] = hex_digits[num % 16];
        num /= 16;
    }

    for (int i = hex_len - 1; i >= 0; i--) {
        syscall(4, 1, (int)(&hex_num[i]), 1);
    }

    syscall(4, 1, (int)(&end_line), 1);
}

//start function
void _start(void) {
    int ret;
    char buf[20];
    int len = 0;
    while (1) {                                           //read input until EOF
        asm volatile (
            "int $0x80" :
            "=a" (ret) :
            "a" (3), "b" (0), "c" (&buf[len]), "d" (1) :
            "memory"
        );

        if (ret <= 0) {                                   //if EOF
            conv_to_hex(buf, len);
            break;
        }

        if (buf[len] == end_line || buf[len] == ' ' || buf[len] < '0' || buf[len] > '9') {
            conv_to_hex(buf, len);
            len = 0;
            continue;
        }

        len++;
    }

    syscall(1, 0, 0, 0);
}