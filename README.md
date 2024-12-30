# XML-to-JSON Project

## Overview
This project provides both a Command-Line Interface (CLI) application and a Graphical User Interface (GUI) application for converting and validating XML files, generating JSON output, and offering various XML processing functionalities.

## Features
- Validate XML files and detect parsing or formatting errors.  
- Convert XML to JSON for easier data handling and storage.  
- Compress and decompress XML files (CLI future feature).  
- Simple GUI to load, format, and convert XML files. 
- CLI flags for quick batch processing of XML files.

## Requirements
- The [Mingw-w64](https://www.mingw-w64.org/) compiler (for Windows) or GCC (for Linux).
- [CMake](https://cmake.org/) (version ≥ 3.19).  
- [Qt6](https://www.qt.io/) if you want to build the GUI application.  
- A build system (e.g., Ninja, Make, Visual Studio).
## Quick Setup
1. Clone this repository locally.  
2. Ensure CMake and Qt6 are installed and available in your PATH.  
3. From the project root, configure and build:
   - Create a build folder:  
     ```
     mkdir build
     cd build
     ```
   - Generate build files:  
     ```
     cmake -G <your preffered building system> ..
     ```
   - Build all targets (using Ninja as an example):  
     ```
     ninja
     ```
4. Run the CLI app from the build directory:  
   - Windows:  
     ```shell
     build\CLI\cli_app.exe <command> -option <optionValue>
     ```
   - Other systems:  
     ```bash
     ./CLI/cli_app <command> -option <optionValue>
     ```
5. Run the GUI app (Qt required):  
   - Windows:  
     ```shell
     GUI\gui_app.exe
     ```
   - Other systems:  
     ```shell
     ./GUI/gui_app
     ```

## Usage
### CLI
Use the CLI for automated or script-based workflows:
```shell
    cli_app <command> -option <optionValue>
```
- `<command>`: The operation to perform (validate, convert, etc.).
- `-option <optionValue>`: The option to pass to the command (e.g., file path, output format).

### GUI
Use the GUI to explore XML files, format them, and convert to JSON interactively.

## Authors
| Name               | GitHub                                 |
| ------------------ | -------------------------------------- |
| AbdElRahman Soliman | [@ASolimanA](https://github.com/ASolimanA) |
| Zeyad Anwar        | [@Zeyad-Anwar](https://github.com/Zeyad-Anwar) |
| Kareem Mostafa     | [@KareemMostafa1](https://github.com/KareemMostafa1) |
| Ahmed Hussein      | [@Ahmed-Hussein-ElShahat](https://github.com/Ahmed-Hussein-ElShahat) |
| Hisham Hatem       | [@HishamHatem](https://github.com/HishamHatem) |
| Mahmoud Essam      | [@Mahmoud-Essam-Noureldin](https://github.com/Mahmoud-Essam-Noureldin) |
| Youssef Elgendy    | [@JoElgendy](https://github.com/JoElgendy) |
| Omar Ayman         | [@omarcs225](https://github.com/omarcs225) |