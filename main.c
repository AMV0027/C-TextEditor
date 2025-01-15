#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#define CTRL_KEY(k) ((k) & 0x1f)
#define MAX_ROWS 1024
#define MAX_COLS 256

void init_screen() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
}

void draw_header(const char *header) {
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "%*s", COLS, ""); // Clear the entire line
    mvprintw(0, (COLS - strlen(header)) / 2, "%s", header);
    attroff(COLOR_PAIR(1));
    refresh();
}

void draw_status_bar(const char *status, int cx, int cy) {
    attron(COLOR_PAIR(2));
    mvprintw(LINES - 1, 0, "%*s", COLS, ""); // Clear the entire line
    mvprintw(LINES - 1, 0, "%s | Pos: %d,%d", status, cy + 1, cx + 1);
    attroff(COLOR_PAIR(2));
    refresh();
}

void cleanup_screen() {
    endwin();
}

void save_to_file(char content[MAX_ROWS][MAX_COLS], int row_count) {
    char filename[MAX_COLS];
    memset(filename, 0, sizeof(filename));

    // Clear status bar and show prompt
    move(LINES - 1, 0);
    clrtoeol();
    attron(COLOR_PAIR(2));
    printw("Save as: ");
    echo();
    refresh();

    // Get filename
    getnstr(filename, MAX_COLS - 1);
    noecho();

    if (strlen(filename) > 0) {
        FILE *fp = fopen(filename, "w");
        if (fp) {
            for (int i = 0; i < row_count; i++) {
                fprintf(fp, "%s\n", content[i]);
            }
            fclose(fp);
            mvprintw(LINES - 1, 0, "File '%s' saved successfully! Press any key...", filename);
        } else {
            mvprintw(LINES - 1, 0, "Error: Could not save file! Press any key...");
        }
    } else {
        mvprintw(LINES - 1, 0, "Save cancelled! Press any key...");
    }

    clrtoeol();
    refresh();
    getch();
}

int main() {
    char content[MAX_ROWS][MAX_COLS] = {{0}};
    int cx = 0, cy = 0;
    int row_count = 0;

    init_screen();

    // Initialize first row
    content[0][0] = '\0';

    while (1) {
        // Clear and redraw the screen
        clear();
        draw_header("Amv Text Editor");

        // Display content
        for (int i = 0; i <= row_count; i++) {
            mvprintw(i + 1, 0, "%s", content[i]);
        }

        // Show status bar
        draw_status_bar("CTRL-Q: Quit | CTRL-S: Save", cx, cy);

        // Position cursor
        move(cy + 1, cx);
        refresh();

        int ch = getch();
        if (ch == CTRL_KEY('q')) {
            break;
        } else if (ch == CTRL_KEY('s')) {
            save_to_file(content, row_count + 1);
        } else if (ch == KEY_UP && cy > 0) {
            cy--;
            if (cx > strlen(content[cy]))
                cx = strlen(content[cy]);
        } else if (ch == KEY_DOWN && cy < row_count) {
            cy++;
            if (cx > strlen(content[cy]))
                cx = strlen(content[cy]);
        } else if (ch == KEY_LEFT) {
            if (cx > 0) {
                cx--;
            } else if (cy > 0) {
                cy--;
                cx = strlen(content[cy]);
            }
        } else if (ch == KEY_RIGHT) {
            if (cx < strlen(content[cy])) {
                cx++;
            } else if (cy < row_count) {
                cy++;
                cx = 0;
            }
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (cx > 0) {
                memmove(&content[cy][cx - 1], &content[cy][cx], strlen(content[cy]) - cx + 1);
                cx--;
            } else if (cy > 0) {
                int prev_len = strlen(content[cy - 1]);
                if (prev_len + strlen(content[cy]) < MAX_COLS - 1) {
                    strcat(content[cy - 1], content[cy]);
                    for (int i = cy; i < row_count; i++) {
                        strcpy(content[i], content[i + 1]);
                    }
                    row_count--;
                    cy--;
                    cx = prev_len;
                }
            }
        } else if (ch == '\n' || ch == KEY_ENTER) {
            if (row_count < MAX_ROWS - 1) {
                for (int i = row_count + 1; i > cy + 1; i--) {
                    strcpy(content[i], content[i - 1]);
                }
                content[cy + 1][0] = '\0';

                if (cx < strlen(content[cy])) {
                    strcpy(content[cy + 1], &content[cy][cx]);
                    content[cy][cx] = '\0';
                }

                row_count++;
                cy++;
                cx = 0;
            }
        } else if (ch >= 32 && ch <= 126) {
            if (strlen(content[cy]) < MAX_COLS - 1) {
                memmove(&content[cy][cx + 1], &content[cy][cx], strlen(content[cy]) - cx + 1);
                content[cy][cx] = ch;
                cx++;
            }
        }
    }

    cleanup_screen();
    return 0;
}
