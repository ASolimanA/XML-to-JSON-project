Kareem^Mostafa
kareemmostafa2
Online

Soliman — 14-May-24 4:08 PM
Image
Hisham — 14-May-24 4:09 PM
Image
Soliman — 14-May-24 4:09 PM
https://developer.arm.com/Tools%20and%20Software/Arm%20Compiler%20for%20Embedded
Arm Compiler for Embedded
Generate code for running fast, compact, and energy-efficient applications on Arm.
Hisham — 14-May-24 4:16 PM
Image
Hisham — 14-May-24 4:25 PM
Build started: Project: tests
 Target 'Target 1' uses ARM-Compiler 'Default Compiler Version 5' which is not available.
 Please review the installed ARM Compiler Versions:
   'Manage Project Items - Folders/Extensions' to manage ARM Compiler Versions.
   'Options for Target - Target' to select an ARM Compiler Version for the target.
*** Build aborted.
Build Time Elapsed:  00:00:00
Soliman — 14-May-24 4:28 PM

/*
 * Auto generated Run-Time-Environment Configuration File
 *      *** Do not modify ! ***
 *
 * Project: 'EmbeddedProj' 
Expand
RTE_Components.h
1 KB
Hisham — 14-May-24 4:34 PM
Image
Image
Image
Soliman — 14-May-24 4:38 PM
https://arm-pro-pkg-repository.s3.eu-west-2.amazonaws.com/parts/ACOMPE-BN-00025-r6p22-00rel0/ARMCompiler6.22_standalone_win-x86_32.zip?X-Amz-Security-Token=FwoGZXIvYXdzEDcaDMC7mxHRWlMJD0CGayKvAXgmoeHKcM9zRBiH0bnRn8ZwWjgmMidQTu6rp2n6ebyyes6UiR8d7DJifIO%2FyiRk6Is9h8VvxAiK%2B53xdImUudjvobwZBdrKJqAng9ABPDVoFevjYPqn9BhmNb%2FD7q%2BwHKEOkt2IACKp8f0pC2t5mzoRsPRrC94Qt7FI1bwH52X1H8XUkXwlM2q6jb0h7exhc1TJrQyJT95mK7tnOWveqUuoqJI%2Fn0CMlBryzINwslIok9KNsgYyLcXhNx7JCpOz8DuDobUy74COqi48Ls6ww2VX1dMUnZrcbXER58EI29UOtiVZ%2FA%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20240514T133800Z&X-Amz-SignedHeaders=host&X-Amz-Expires=600&X-Amz-Credential=ASIAUCCFPAXAQIFGSS2S%2F20240514%2Feu-west-2%2Fs3%2Faws4_request&X-Amz-Signature=314688c0ca80de07608565e0bd67256dd81b5b495da068c0e06c94e45afac74a
Attachment file type: code
gps.o
12.75 KB
./objects/eeprom.o: EEPROM.c C:\Keil_v5\ARM\ARMCLANG\include\stdint.h \
  C:\Keil_v5\ARM\ARMCLANG\include\stdbool.h tm4c123gh6pm.h bit_utilies.h \
  EEPROM.h
eeprom.d
1 KB
Attachment file type: code
eeprom.o
7.89 KB
./objects/gpio_switches.o: GPIO_SWITCHES.c tm4c123gh6pm.h GPIO_SWITCHES.h \
  C:\Keil_v5\ARM\ARMCLANG\include\stdint.h
gpio_switches.d
1 KB
Attachment file type: code
gpio_switches.o
5.88 KB
./objects/gps.o: GPS.c GPS.h bit_utilies.h UART.h UART.c tm4c123gh6pm.h \
  C:\Keil_v5\ARM\ARMCLANG\include\math.h \
  C:\Keil_v5\ARM\ARMCLANG\include\string.h \
  C:\Keil_v5\ARM\ARMCLANG\include\stdlib.h
gps.d
1 KB
Soliman — 14-May-24 4:45 PM
./objects/system_tm4c123.o: RTE\Device\TM4C123GH6PM\system_TM4C123.c \
  C:\Keil_v5\ARM\ARMCLANG\include\stdint.h \
  C:\Users\bodi7\AppData\Local\Arm\Packs\Keil\TM4C_DFP\1.1.0\Device\Include\TM4C123\TM4C123.h \
  C:\Users\bodi7\AppData\Local\Arm\Packs\Keil\TM4C_DFP\1.1.0\Device\Include\TM4C123\TM4C123GH6PM.h \
  C:\Users\bodi7\AppData\Local\Arm\Packs\ARM\CMSIS\6.0.0\CMSIS\Core\Include\core_cm4.h \
  C:\Users\bodi7\AppData\Local\Arm\Packs\ARM\CMSIS\6.0.0\CMSIS\Core\Include\cmsis_version.h \
Expand
system_tm4c123.d
1 KB
./objects/lcd.o: LCD.c tm4c123gh6pm.h LCD.h SysTick_Timer.h \
  C:\Keil_v5\ARM\ARMCLANG\include\stdint.h \
  C:\Keil_v5\ARM\ARMCLANG\include\string.h
lcd.d
1 KB
Attachment file type: code
lcd.o
9.58 KB
./objects/main.o: main.c tm4c123gh6pm.h \
  C:\Keil_v5\ARM\ARMCLANG\include\stdbool.h \
  C:\Keil_v5\ARM\ARMCLANG\include\stdint.h \
  C:\Keil_v5\ARM\ARMCLANG\include\string.h bit_utilies.h UART.h \
  GPIO_SWITCHES.h EEPROM.h
main.d
1 KB
Attachment file type: code
main.o
2.84 KB
Attachment file type: code
startup_tm4c123.o
16.53 KB
Attachment file type: code
uart.o
4.44 KB
Attachment file type: code
system_tm4c123.o
11.71 KB
./objects/systick_timer.o: SysTick_Timer.c tm4c123gh6pm.h \
  C:\Keil_v5\ARM\ARMCLANG\include\stdint.h SysTick_Timer.h
systick_timer.d
1 KB
Attachment file type: code
systick_timer.o
3.54 KB
./objects/uart.o: UART.c UART.h tm4c123gh6pm.h bit_utilies.h
uart.d
1 KB
Soliman — 14-May-24 4:54 PM
Attachment file type: unknown
EmbeddedProj.axf
38.80 KB
Hisham — 14-May-24 4:59 PM
main.c(26): error:  #167: argument of type "char ()[18]" is incompatible with parameter of type "char"
      EEPROM_readall(&test2);
Image
Image
Hisham — 14-May-24 5:23 PM
Image
Soliman — 14-May-24 5:27 PM
https://arm-pro-pkg-repository.s3.eu-west-2.amazonaws.com/parts/DS500-PA-00002-r5p0-26rel0/30458d46-8f39-4fa5-a8e8-b455b7e1c132.zip?X-Amz-Security-Token=FwoGZXIvYXdzEDgaDG7vT03zJleNspLrfSKvAU%2FzD2955aVxfk3fWOuvcnxm7AGtNQ9Y061R%2FqT%2F16OfvPE1S4waxeKSqZIHmOPUpEJSXJ7XiQ%2FODPiXi0xqZ%2FKkL7C4KOX%2FrLCvzyl1sAzEwfR%2F%2BS0o75vD%2BE3GOLpfJ0Wlfli6vOyJoF22m%2BiSTpoe%2Ff%2B40U4%2BkqPOozSk%2Ba4BTNAN38R6Q9NMMTKaK%2FyrvO5qUzMaf442gkquaefhkKmMSK89aTkUu9PXq%2FFw7IkoreiNsgYyLZwgIFmzoViHdvCYVGj3FgR2wMZGk3DXpsnPhd1kOR0q8re%2FFqfZFl4Vwc8nGw%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20240514T142737Z&X-Amz-SignedHeaders=host&X-Amz-Expires=599&X-Amz-Credential=ASIAUCCFPAXA6FYSZ5EV%2F20240514%2Feu-west-2%2Fs3%2Faws4_request&X-Amz-Signature=460eab765485c10100ceacc04f483b7854e52090b827001b8b2adb52adab7ad6
zeyad9628 — 14-May-24 5:32 PM
Image
Hisham — 14-May-24 5:34 PM
Image
Soliman — 14-May-24 5:53 PM
EEPROM_write(1234567890);
    uint32_t test = EEPROM_read_word();
    if (test == 1234567890);
Soliman — 14-May-24 6:03 PM
serial.tools.list_ports
midohpro — 04-Dec-24 8:26 PM
str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
zeyad9628 — 04-Dec-24 8:39 PM
Image
#include <iostream>
#include "Tree.h"

using namespace std;

int main() {
    Tree newXML;
    newXML.Read_XML("test.txt");
    newXML.preorder_traversal(newXML.get_root());
    return 0;
}
Good to see you, Yousef elgendy. — 04-Dec-24 9:01 PM
zeyad9628 — 04-Dec-24 9:06 PM
Image
Image
midohpro — 04-Dec-24 10:31 PM
<([^>]+)>|[^<]+
omarAyman just landed. — 04-Dec-24 10:34 PM
zeyad9628 — 04-Dec-24 10:45 PM
std::string trim(const std::string& source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
}
midohpro — 04-Dec-24 10:55 PM
"\<([^>]+)\>|[^<]+"
#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>

using namespace std;

Node::Node(string data) {
    this->data = data;
}

std::string trim(const std::string& source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
}

Tree::Tree() {
    root = NULL;
}

Node* Tree::get_root() {
    return root;
}

void Tree::preorder_traversal(Node* node) {
    if (node == NULL)
        return;
    cout << node->data << endl;
    for (int i = 0; i < node->branches.size(); i++)
        preorder_traversal(node->branches[i]);
}

void Tree::Read_XML(string path) {
    string text, temp1, temp2;
    ifstream myFile(path);
    regex regexSet("\<([^>]+)\>|[^<]+");
    smatch matches;
    stack<Node> st;
    while (getline(myFile, text)) {
        string::const_iterator it(text.cbegin());
        while (regex_search(it, text.cend(), matches, regexSet)){

            cout<<matches[0]<<endl;
            temp1 = trim(matches[0]);
            temp2 = matches[1];
            if(!temp1.empty() && temp1[0] != '<'){
                cout<<"Tag value: "<<temp1<<endl;
            }

            else if (temp2[0] != '/') {
                Node attr = new Node(matches[1]);
                if (root == NULL) {
                    root = attr;
                }
                else if (!st.empty()) {
                    st.top()->branches.push_back(attr);
                }
                st.push(attr);
            }
            else if (!st.empty()) {
                if (st.top()->data == temp2.substr(1))
                    st.pop();
            }
            it = matches.suffix().first;

        }
    }
    myFile.close();
}
zeyad9628 — 04-Dec-24 11:07 PM
Node::Node(string data) {
    tagName = data;
    tagValue = "";
}
midohpro — 04-Dec-24 11:23 PM
#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>
Expand
Tree.cpp
2 KB
midohpro — 04-Dec-24 11:34 PM
#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>
Welcome Mahmoud Essam. Say hi! — 15-Dec-24 8:26 PM
midohpro — 15-Dec-24 8:27 PM
midohpro — 15-Dec-24 9:34 PM
if(argv[1] == "format"){
    }
    if(argv[1] == "json"){

    }
    if(argv[1] == "mini"){}
    if(argv[1] == "compress"){}
    if(argv[1] == "decompress"){}
    if(argv[1] == "xml_editor"){}
while(char opt = getopt(argc, argv, "i⭕")) {
        switch (opt) {
            case 'i':
                inputFile = optarg;
                cout << "Input file: " << optarg << endl;
                break;
            case 'o':
                outputFile = optarg;
                cout << "Output file: " << optarg << endl;
                break;
            default:
                cout << "Invalid command" << endl;
                return 0;
        }
    }
    if(argv[1] == "format"){
    }
    if(argv[1] == "json"){

    }
    if(argv[1] == "mini"){}
    if(argv[1] == "compress"){}
    if(argv[1] == "decompress"){}
    if(argv[1] == "xml_editor"){}
https://github.com/ASolimanA/XML-to-JSON-project
GitHub
GitHub - ASolimanA/XML-to-JSON-project
Contribute to ASolimanA/XML-to-JSON-project development by creating an account on GitHub.
GitHub - ASolimanA/XML-to-JSON-project
Kareem^Mostafa is here. — 18-Dec-24 10:29 PM
Soliman — 22-Dec-24 2:18 PM
@Yousef elgendy
CMAKE_PREFIX_PATH : path/to/Qt/6.8.1/mingw_64/
Soliman — 22-Dec-24 2:27 PM
-DCMAKE_PREFIX_PATH:STRING=path/to/Qt/6.8.1/mingw_64/
Soliman — 22-Dec-24 2:34 PM
path/to\Qt\Tools\mingw1310_64\bin\gcc.exe
zeyad9628 — Today at 6:44 PM
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
Expand
compress-decompress.cpp
6 KB
zeyad9628 — Today at 7:40 PM
Image
zeyad9628 — Today at 7:54 PM
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
Expand
compress-decompress.cpp
6 KB
Kareem^Mostafa — Today at 8:42 PM
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
Expand
compress-decompress_2.cpp
6 KB
Soliman — Today at 10:17 PM
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
Expand
compress-decompress.cpp
6 KB
﻿
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
using namespace std;
int flag=0;
int cnt=0;

// Maps for pattern-symbol conversion
std::unordered_map<std::string, char> patternToSymbol;
std::unordered_map<char, std::string> symbolToPattern;

// Set of used characters in the original sequence
std::unordered_map<int,char> usedCharacters;

// Function to initialize used characters
void initializeUsedCharacters(const std::string& input) {
    for (char c : input) {
        if(!usedCharacters.count((int)c))
            usedCharacters[(int)c]=(c);
    }
}

// Function to generate a new unique 1-byte character
string getUniqueCharacter(const std::string& pattern) {
    if (patternToSymbol.count(pattern)) {
        return string(1,patternToSymbol[pattern]);
    }
    if(!flag){
        // Iterate over possible 1-byte characters (0x00 to 0xFF)
        for (static unsigned candidate = 0x01; candidate <= 0xFF; candidate++) {
            if (candidate == 13) continue;
            if (!usedCharacters.count(abs((int)candidate))) {
                // Found a unique character
               
                usedCharacters[abs((int)candidate)]=candidate;
                patternToSymbol[pattern] = candidate;
                symbolToPattern[candidate] = pattern;
                return string(1,candidate);
            }
        }
    }
    flag=1;
    return pattern;
    
}
// Function to read the content of a file into a string
std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
// Compress function
void compress(const std::string& input, const std::string& filePath) {
    std::string compressed;
    size_t i = 0;

    // Initialize used characters set from the input
    initializeUsedCharacters(input);

    while (i < input.size() - 1) {
        std::string digram = input.substr(i, 2);
        string symbol = getUniqueCharacter(digram);

        compressed += symbol;
        i += 2; // Skip the digram   
    }
    // Add remaining character, if any
    while (i < input.size()) {
        compressed += input[i];
    }
    //save compressed data into a text file
    char ch;
    ofstream CompressoutFile(filePath);
    for (char ch : compressed) {
        CompressoutFile << ch;
    }
    //save mapping into the text file
    CompressoutFile << "#Map contents:#";
    for (const auto& pair : symbolToPattern) {
        CompressoutFile << pair.first << ">" << pair.second;
    }

}

// Decompress function
std::string decompress(const std::string& CompressedfilePath/*,const std::string& MapfilePath */) {
    std::string decompressed;
    //std::ifstream CompressedFile(CompressedfilePath);
    string compressed;
    string Map = ""/* readFile(MapfilePath) */;
    unordered_map<char, std::string> recovered_map;
    unsigned char symbol;
    string pattern;
    string input;
    int index = 0, mapIndex;
    input = readFile(CompressedfilePath);
    // Reconstructin the Map of rules
    string line;
    bool MapFlag = false;
    //string MapLine;
    for (char ch : input) {
        index++;
        if (!MapFlag) {
            if (ch == '#') {
                if (line == "Map contents:") {
                    MapFlag = true;
                    mapIndex = index;
                    continue;
                }
                compressed += line + "#";
                line.clear(); // Clear the line for the next one
            }
            else {
                line += ch; // Append the character to the current line
            }
        }
        else {
            for(int i=mapIndex;i<input.size();i++){
                if (input[i] == '\r') {
                    continue;
                }
                else {
                Map += input[i];
                }
            }
            break;
        }
    }

    for (int i = 0; i < Map.size(); i += 4) {
        symbol = Map[i];                 //get the compression char
        pattern = Map.substr(i + 2, 2); //get the replaced sequence
    
        recovered_map[symbol] = pattern;
    }

    for (char c : compressed) {
        if (recovered_map.count(c)) {
            decompressed += recovered_map[c];
        }
        else {
            decompressed += c; // Append single characters directly
        }
    }

    return decompressed;
}




//  int main() {
    
//         // std::string filePath = "C:\\Users\\kareem\\Downloads\\1mb.xml";
//          // Read the XML file content
//          //std::string input = readFile(filePath);

//          // Compress the input
//          //compress(input, "C:\\C++\\DSA project\\repo2\\XML-to-JSON-project\\XML-to-JSON\\common\\compressed.txt");
//          //std::ofstream outputFile("compressed.txt", std::ios::binary);
//          //outputFile << compressed;
//          //outputFile.close();

//          // Decompress the data
//          std::string decompressed = decompress("C:\\C++\\DSA project\\repo2\\XML-to-JSON-project\\XML-to-JSON\\common\\compressed.txt");
//          std::ofstream outputFile2("decompressed.txt", std::ios::binary);
//          outputFile2 << decompressed;
//          outputFile2.close();
//         return 0;
//  }
