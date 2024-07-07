#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

// Escape sequences for moving the cursor
#define CURSOR_MOVE_UP "\033[A"
#define CURSOR_MOVE_DOWN "\033[B"
#define CURSOR_MOVE_RIGHT "\033[C"
#define CURSOR_MOVE_LEFT "\033[D"

// Function to enable raw mode
void enable_raw_mode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

// Function to disable raw mode
void disable_raw_mode() {
    struct termios orig;
    tcgetattr(STDIN_FILENO, &orig);
    orig.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &orig);
}

int main() {
    char ch;
    char seq[2];

    enable_raw_mode();
    printf("Use arrow keys to move the cursor. Press 'q' to quit.\n");

    {
        read(STDIN_FILENO, &ch, 1);

        if (ch == 'q') {
        }

        if (ch == 27) {  // ESC key
            read(STDIN_FILENO, seq, 2);

            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A':
                        printf(CURSOR_MOVE_UP);
                        break;
                    case 'B':
                        printf(CURSOR_MOVE_DOWN);
                        break;
                    case 'C':
                        printf(CURSOR_MOVE_RIGHT);
                        break;
                    case 'D':
                        printf(CURSOR_MOVE_LEFT);
                        break;
                }
            }
        }
    }
    while(1);

    disable_raw_mode();
    return 0;
}

