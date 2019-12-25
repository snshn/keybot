#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define KEY_PRESS_DELAY 3
#define KEY_PRESS_WAIT  10

#if __APPLE__
#include "quartz.c"
#else
#include "x11.c"
#endif

int main(int argc, char **argv)
{
    if (isatty(fileno(stdin)) && argc < 2) { // no stdin pipe, no arguments
        fprintf(stderr, "\n  Usage: %s \"string to type\"\n"
              "         cat ~/.ssh/id_rsa.pub | %s\n"
              "         %s \"string to type\" < ~/.ssh/id_rsa.pub\n\n"
              , argv[0], argv[0], argv[0]);
        return -1;
    }

    return sim_text_input(argc, argv);
}
