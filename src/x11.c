#include "shared.c"

#include <X11/Xlib.h>
#include <X11/keysym.h>

// TODO:
// - look into using XStringToKeySym()

Display *display;
Window window;
Window rootWin;
Window focWin;
int revert;

char requires_shift_modifier(char c)
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

XKeyEvent create_key_event(int type, int keycode, unsigned int modifiers)
{
    XKeyEvent event;

    event.type        = type;
    event.display     = display;
    event.window      = focWin;
    event.root        = rootWin;
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

void sim_key_press_or_release(char ch, int modifiers, Bool press) {
    int type = press ? KeyPress : KeyRelease;

    XKeyEvent event = create_key_event(type, ch, modifiers);
    XSendEvent(event.display, event.window, True,
               KeyPressMask, (XEvent*)&event);
}

void sim_key_press_for_character(char ch) {
    static unsigned int modifiers = 0;

    if (requires_shift_modifier(ch)) {
        modifiers = ShiftMask;
    }

    // Simulate key press
    sim_key_press_or_release(ch, modifiers, True);
    msleep(KEY_PRESS_DELAY);

    // Simulate key release
    sim_key_press_or_release(ch, modifiers, False);
    msleep(KEY_PRESS_WAIT);

    // Clean up
    ch = '\0';
    modifiers = 0;
}

int sim_text_input(int argc, char **argv)
{
    char ch;
    char *string;

    display = XOpenDisplay(0);

    if (display == NULL) {
        return -1;
    }

    rootWin = XDefaultRootWindow(display);

    XGetInputFocus(display, &focWin, &revert);

    // Process stdin pipe (if given)
    if (!isatty(fileno(stdin))) {
        while (read(0, &ch, 1) > 0) {
            sim_key_press_for_character(ch);
        }
    }

    // Clean up
    ch = '\0';

    // Process arguments (if any)
    for (int c = 1; c < argc; c++) {
        string = argv[c];

        for (int i = 0, ilen = strlen(string); i < ilen; i++) {
            sim_key_press_for_character(string[i]);
            // Wipe the string as we go (for security reasons)
            string[i] = '\0';
        }
    }

    XCloseDisplay(display);

    return 0;
}
