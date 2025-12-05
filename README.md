# MP3 Tag Reader & Editor

## Overview
This is a C-based command-line tool developed to read and edit **ID3v2 metadata** in MP3 files. It allows users to view current tags and modify specific details like Artist, Title, Album, and Year directly from the terminal.

## Features
* **View Mode:** Displays existing ID3v2 tags (Title, Artist, Album, Year, etc.).
* **Edit Mode:** Modifies specific tag information using command-line arguments.
* **Help Menu:** Provides a user-friendly guide on how to use the tool.

## Prerequisites
* GCC Compiler (Linux/Windows/macOS)
* Basic understanding of the Command Line Interface (CLI)

## How to Compile
Use the GCC compiler to build the executable:
```bash
gcc main.c functions.c -o mp3_editor

## Usage
1. Help Menu
	./mp3_editor --help
2. View MP3 Tags
	./mp3_editor -v <file_name.mp3>
3. Edit MP3 Tags
	./mp3_editor -e <modifier> "New Value" <file_name.mp3>
