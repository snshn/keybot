#include "shared.c"

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

void sim_key_press_or_release(UniChar ch, bool press) {
    // Create a new keyboard key press (or release) event
    CGEventRef event;

    if (ch == '\n') {
        event = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)kVK_Return, press);
    } else {
        event = CGEventCreateKeyboardEvent(NULL, 0, press);
        CGEventKeyboardSetUnicodeString(event, 1, &ch);
    }

    // Post keyboard event
    CGEventPost(kCGHIDEventTap, event);

    // Clean up
    CFRelease(event);
    ch = '\0';
    press = false;
}

void sim_key_press_for_character(char ch) {
    // Simulate key press
    sim_key_press_or_release((UniChar)ch, true);
    msleep(KEY_PRESS_DELAY);

    // Simulate key release
    sim_key_press_or_release((UniChar)ch, false);
    msleep(KEY_PRESS_WAIT);

    // Clean up
    ch = '\0';
}

int sim_text_input(int argc, char **argv)
{
    char ch;
    char *string;

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

    return 0;
}
