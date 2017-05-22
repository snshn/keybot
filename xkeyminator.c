#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define KEYPRESS_DELAY 3
#define KEYPRESS_WAIT  10

void msleep(int milliseconds)
{
    struct timespec ts;

    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&ts, NULL);
}

XKeyEvent createKeyEvent(Display *display, Window *window, Window *rootWin,
                         int type, int keycode, unsigned int modifiers)
{
    XKeyEvent event;

    event.type        = type;
    event.display     = display;
    event.window      = *window;
    event.root        = *rootWin;
    event.subwindow   = None;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.state       = modifiers;
    event.keycode     = XKeysymToKeycode(display, keycode);
    event.same_screen = True;

    return event;
}

char requiresShiftModifier(char c)
{
    switch (c)
    {
        case '~':
        case '!':
        case '@':
        case '#':
        case '$':
        case '%':
        case '^':
        case '&':
        case '*':
        case '(':
        case ')':
        case '_':
        case '+':
        case 'Q':
        case 'W':
        case 'E':
        case 'R':
        case 'T':
        case 'Y':
        case 'U':
        case 'I':
        case 'O':
        case 'P':
        case '{':
        case '}':
        case '|':
        case 'A':
        case 'S':
        case 'D':
        case 'F':
        case 'G':
        case 'H':
        case 'J':
        case 'K':
        case 'L':
        case ':':
        case '"':
        case 'Z':
        case 'X':
        case 'C':
        case 'V':
        case 'B':
        case 'N':
        case 'M':
        case '<':
        case '>':
        case '?':
            return 1;
    }

    return 0;
}

void simKeyPress(Display *display, Window *focWin, Window *rootWin,
                  int keycode, unsigned int modifiers)
{
    XKeyEvent event = createKeyEvent(display, focWin, rootWin,
                                     KeyPress, keycode, modifiers);
    XSendEvent(event.display, event.window, True,
               KeyPressMask, (XEvent*)&event);

    msleep(KEYPRESS_DELAY);

    event = createKeyEvent(display, focWin, rootWin,
                           KeyRelease, keycode, modifiers);
    XSendEvent(event.display, event.window, True,
               KeyPressMask, (XEvent*)&event);

    msleep(KEYPRESS_WAIT);
}

int main(int argc, char **argv)
{
    Display *display = XOpenDisplay(0);

    if (display == NULL) {
        return -1;
    }

    Window rootWin = XDefaultRootWindow(display);

    Window focWin;
    int revert;
    XGetInputFocus(display, &focWin, &revert);

    char keycode;
    unsigned int modifiers = 0;
    char *string;

    if (isatty(fileno(stdin)) && argc < 2) { // NULL stdin, no arguments
        fprintf(stderr, "\n  Usage: %s \"string to type\"\n"
              "         cat ~/.ssh/id_rsa.pub | %s\n"
              "         %s \"string to type\" < ~/.ssh/id_rsa.pub\n\n"
              , argv[0], argv[0], argv[0]);
        return -1;
    }

    if (!isatty(fileno(stdin))) {
        while (read(0, &keycode, 1) > 0) {
            modifiers = 0;

            if (requiresShiftModifier(keycode)) {
                modifiers = ShiftMask;
            }

            simKeyPress(display, &focWin, &rootWin, keycode, modifiers);
        }
    }

    for (int c = 1; c < argc; c++) {
        string = argv[c];

        for (int i = 0, ilen = strlen(string); i < ilen; i++) {
            keycode = string[i];
            modifiers = 0;

            if (requiresShiftModifier(keycode)) {
                modifiers = ShiftMask;
            }

            simKeyPress(display, &focWin, &rootWin, keycode, modifiers);

            string[i] = '\0';
        }
    }

    XCloseDisplay(display);
    keycode = '\0';
    modifiers = 0;

    return 0;
}
