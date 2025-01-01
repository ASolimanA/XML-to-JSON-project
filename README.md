# XML-to-JSON Project

## Overview
This project provides both a Command-Line Interface (CLI) application and a Graphical User Interface (GUI) application for converting and validating XML files, generating JSON output, and offering various XML processing functionalities.

## Features
- Validate XML files and detect parsing or formatting errors.  
- Convert XML to JSON for easier data handling and storage.  
- Compress and decompress XML files.
- Pretty-print XML files for better readability.
- Minify XML files to reduce storage space.
- Simple GUI to load, format, and convert XML files. 
- CLI flags for quick batch processing of XML files.
- Analyze social media XML files and visualize the relationships between users and posts using graph analysis.

## Requirements
- [Graphviz](https://graphviz.org/) must be installed for generating and drawing the graphs.
- **Download and use the prebuilt Qt application from the GitHub Releases** instead of building from source for a quicker setup.
- **Building from source** requires the following:
  - CMake 3.19 or later.
  - Qt6.
  - A C++17-compatible compiler.
  - Ninja (optional but recommended for faster builds).

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
5. Run the GUI app:
    - Prebuilt Qt application:  
      - Download the latest release
      - Run the executable file (bin/gui_app.exe).
    - Building from source:
      - Run the GUI app from the build directory:  
        ```shell
        ./GUI/gui_app
        ```
6. Enjoy the XML Manipulation software!

## Usage
### CLI
Use the CLI for automated or script-based workflows:
```shell
    cli_app <command> --option <optionValue>
```
- `<command>`: The operation to perform (validate, convert, etc.).
- `-option <optionValue>`: The option to pass to the command (e.g., file path, output format).

### GUI
Use the GUI to explore XML files, format them, and convert to JSON interactively as well as analyze the social media XML files using the graph analysis and visualization feature.

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