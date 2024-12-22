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
        for (static unsigned candidate = 0x00; candidate <= 0xFF; candidate++) {
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
std::string compress(const std::string& input) {
    std::stringstream compressed;
    size_t i = 0;

    // Initialize used characters set from the input
    initializeUsedCharacters(input);

    while (i < input.size() - 1) {
        std::string digram = input.substr(i, 2);
        string symbol = getUniqueCharacter(digram);
        
        compressed << symbol;
        i += 2; // Skip the digram   
    }
    // Add remaining character, if any
    while (i < input.size()) {
        compressed << input[i];
    }
    //save mapping into a text file
    // Open output file
    ofstream outFile("map_contents.txt");
    for (const auto& pair : symbolToPattern) {
        outFile << pair.first << ">" << pair.second ;
    }
    return compressed.str();
}

// Decompress function
std::string decompress(const std::string& CompressedfilePath,const std::string& MapfilePath) {
    std::stringstream decompressed;
    string compressed=readFile(CompressedfilePath);
    string Map = readFile(MapfilePath);
    unordered_map<char, std::string> recovered_map;
    unsigned char firstPart;
    string secondPart; 
    
    // Reconstructin the Map of rules
        for(int i=0;i<Map.size();i+=4){
            firstPart = Map[i];                 //get the compression char
            secondPart = Map.substr(i+2,2);     //get the replaced sequence
            recovered_map[firstPart]=secondPart;
        }
    
    for (char c : compressed) {
        if (symbolToPattern.count(c)) {
            decompressed << symbolToPattern[c];
        } else {
            decompressed << c; // Append single characters directly
        }
    }

    return decompressed.str();
}



// Main function
int main() {
    try {
        std::string filePath = "C:\\Users\\kareem\\Downloads\\10mb.xml";

        // Read the XML file content
        std::string input = readFile(filePath);

        // Compress the input
        std::string compressed = compress(input);
        std::ofstream outputFile("compressed.txt", std::ios::binary);
        outputFile << compressed;
        outputFile.close();

        // Decompress the data
        std::string decompressed = decompress("C:\\C++\\DSA project\\source code\\pt3\\compressed.txt","C:\\C++\\DSA project\\source code\\pt3\\map_contents.txt");
        std::ofstream outputFile2("decompressed.txt", std::ios::binary);
        outputFile2 << decompressed;
        outputFile2.close();

        // Optional: Check if decompressed matches original input
        if (input == decompressed) {
            std::cout << "Decompression verified successfully!" << std::endl;
        } else {
            std::cout << "Decompression failed!" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
