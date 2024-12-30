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

std::string fileToString(const std::string& filePath) {
    std::ifstream file(filePath); // Open the file
    if (!file) {
        throw std::ios_base::failure("Error opening file");
    }
    std::ostringstream buffer;
    buffer << file.rdbuf(); // Read the file's content into a stream
    return buffer.str();    // Convert the stream to a string
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
                    // Remove the last character ('#') from the compressed string
                    compressed = compressed.substr(0, compressed.size() - 1);
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
//
////          // Compress the input
//// 
//           std::string filePath = "C:/Users/lap shop/source/repos/XML-to-JSON-project/XML-to-JSON/common/sample.xml";
//           std::string input = fileToString(filePath);
//          compress(input, "C:/Users/lap shop/source/repos/XML-to-JSON-project/XML-to-JSON/common/compressed.txt");
//
////          // Decompress the data
//          std::string decompressed = decompress("C:/Users/lap shop/source/repos/XML-to-JSON-project/XML-to-JSON/common/compressed.txt");
//          std::ofstream outputFile2("decompressed.txt", std::ios::binary);
//          outputFile2 << decompressed;
//          outputFile2.close();
//         return 0;
//}
