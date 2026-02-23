# cedit

`cedit` is a small terminal text editor written in C.
The goal of this project is learning — understanding how applications are built at a low level, how terminal input works, and how state is managed manually without external frameworks.

This is an educational project, not a production editor.

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/5ef99a2b-e6f3-473d-a847-4a0ecad1fa59" />

---

## Installation

### Linux (Binary Install – Recommended)

This will download and install the latest release for your architecture.

```bash
curl -fsSL https://raw.githubusercontent.com/Avinash-sord12k/cedit/main/scripts/install.sh | bash
```

After installation:

```bash
cedit filename.txt
```

---

### Other Platforms / Unsupported Architectures

If your OS or architecture is not supported by the binary installer, build from source.

#### Option 1: Use Source Install Script

```bash
git clone https://github.com/Avinash-sord12k/cedit
cd cedit
./scripts/source-install.sh
```

---

#### Option 2: Manual Build

```bash
git clone https://github.com/Avinash-sord12k/cedit
cd cedit

make
sudo cp dist/cedit /usr/local/bin/cedit
```

Then run:

```bash
cedit filename.txt
```

---


## Upgrade

Re-running the install command will automatically:

- Detect the installed version  
- Compare with the latest release  
- Upgrade if necessary  

```bash
curl -fsSL https://raw.githubusercontent.com/Avinash-sord12k/cedit/main/scripts/install.sh | bash
```

---

## Uninstall

To remove `cedit` from your system:

```bash
curl -fsSL https://raw.githubusercontent.com/Avinash-sord12k/cedit/main/scripts/install.sh | bash -s uninstall
```

Or manually:

```bash
sudo rm /usr/local/bin/cedit
```

---

## Purpose

This project exists to explore:

* raw terminal mode
* keyboard input parsing
* manual screen rendering
* dynamic memory management
* basic editor architecture in C

---

## Current Features

* Open a file from command line (filename is mandatory)
* Load file content into an editable buffer
* Edit ASCII text
* Insert characters and new lines
* Backspace delete
* Cursor movement (left / right)
* Copy current line
* Paste from clipboard
* Save file with `Ctrl + S`
* Quit with `Ctrl + Q`
* Dirty state tracking
* Status bar showing:

  * filename
  * modified state
  * character count
  * temporary status message

---

## Limitations / Missing Features

This is intentionally minimal. Many things are not implemented yet:

* No scrolling
* No syntax highlighting
* No mouse support
* No multi-line cursor navigation (up/down still basic)
* No undo / redo
* No search
* No selections
* Rendering is still simple and not optimized
* ASCII-only editing

---

## Notes

This editor is intentionally small.
The goal is to understand how editors work internally rather than to compete with existing tools.
