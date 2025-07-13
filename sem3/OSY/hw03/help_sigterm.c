#include "help_sigterm.h"

void help_sigterm() {
    const char* message = "GEN TERMINATED\n";
    write(2, message, strlen(message));
    _exit(0);
}
