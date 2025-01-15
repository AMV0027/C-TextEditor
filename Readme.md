## Custom C-lang Text Editor

A simple terminal-based text editor built with C and `ncurses` library. It provides basic features for text editing like moving through text, adding new lines, saving to files, and more. This editor can be run from the command line similar to `vim` or `nano`.

---

## Features

- **Text Navigation**:
  - Arrow keys for movement (`UP`, `DOWN`, `LEFT`, `RIGHT`).
  - The editor supports full navigation through lines and within lines.

- **Editing**:
  - Add new characters, delete characters, and backspace over text.
  - Add a new line using the `Enter` key.
  - `CTRL-S` to save the file.

- **File Handling**:
  - Open a file by passing the filename as an argument when starting the editor.
  - If no filename is specified, you can create a new file.

- **Command-Line Usage**:
  - Open a file for editing by passing it as a command argument: `miv myfile.txt`.
  - If the file doesn't exist, you can create and edit it in the same way.
  
- **Status Bar**:
  - Displays information like commands (`CTRL-Q: Quit`, `CTRL-S: Save`) at the bottom of the editor window.

---

## Getting Started

### Prerequisites

To run this project, you need:

- A C compiler like GCC
- The `ncurses` library (usually installed by default on Linux systems)

### Installation

1. **Clone this repository**:

   ```bash
   git clone https://github.com/AMV0027/C-TextEditor.git
   cd C-TextEditor
   ```

2. **Compile the program**:

   Compile the C code with `gcc` and the `ncurses` library. This command will output the editor as `miv`.

   ```bash
   gcc main -lncurses -o <your preferred editor name>
   ```

3. **Move the compiled editor to a directory in your PATH**:

   To be able to run the editor from any location on your system, move it to a directory that's included in your PATH, such as `/usr/local/bin`.

   ```bash
   sudo mv <your editor name> /usr/local/bin/
   ```

4. **Make the editor executable**:

   Ensure the editor file is executable.

   ```bash
   sudo chmod +x /usr/local/bin/ <your editor name>
   ```

---

## Usage

You can now run the text editor from the command line like `vim` or `nano`.

1. **To start editing a file:**

   ```bash
    <your editor name> myfile.txt
   ```

   - If `myfile.txt` exists, it will open for editing.
   - If `myfile.txt` doesn't exist, a new file with that name will be created.

2. **Navigation**:
   - Use the arrow keys to move the cursor around.
   - `ENTER` to create a new line.
   - `CTRL-Q` to quit the editor.
   - `CTRL-S` to save your file.

3. **Save your changes**:
   - After editing your file, press `CTRL-S` to save the current contents to the file.

4. **Quit the editor**:
   - Press `CTRL-Q` to quit the editor.

---

## Key Functions

### `init_screen()`
This function initializes the `ncurses` library, prepares the terminal screen for editing, and disables line buffering and echo to control the user input precisely.

**Usage**:
- Called at the beginning of the program.

### `draw_header(const char *header)`
This function displays a header on the top line of the editor window. It uses bold and reverse video attributes to highlight the header.

**Usage**:
- Displays the header (e.g., the editor's name or file being edited).

### `draw_status_bar(const char *status)`
Displays a status bar at the bottom of the editor. It contains helpful information such as keyboard shortcuts (`CTRL-Q: Quit | CTRL-S: Save`) for the user.

**Usage**:
- Called after displaying text content and before refreshing the screen.

### `save_to_file(char content[1024][256], int row_count)`
This function prompts the user for a filename and saves the edited content to the file. It creates or overwrites the file, depending on the filename provided.

**Usage**:
- Triggered when the user presses `CTRL-S`.

---

## How to Add It to PATH for All Users (Root Steps)

To make this program globally accessible on the system (i.e., callable by any user), you can place the compiled editor in a system-wide directory included in the `PATH`, such as `/usr/local/bin`.

Follow these steps:

1. **Compile the program** (as described above).
2. **Move the editor to `/usr/local/bin`**:

   ```bash
   sudo mv  <your editor name> /usr/local/bin/
   ```

3. **Ensure the file is executable**:

   ```bash
   sudo chmod +x /usr/local/bin/ <your editor name>
   ```

   This will make the editor accessible to all users on the system, and they can simply call `miv` from the command line to open it.
