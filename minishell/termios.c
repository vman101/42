#include "minishell.h"

void terminal_raw_mode_enable()
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void terminal_raw_mode_disable()
{
    struct termios orig;

    tcgetattr(STDIN_FILENO, &orig);
    orig.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &orig);
}
