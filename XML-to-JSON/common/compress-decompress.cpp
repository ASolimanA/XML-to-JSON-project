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
void compress(const std::string& input) {
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
    //save compressed data into a text file
    char ch;
    ofstream CompressoutFile("compressed.txt");
    while(compressed.get(ch)) {
        CompressoutFile << ch ;
    }
    //save mapping into the text file
    CompressoutFile<<"\nMap contents:\n";
    for (const auto& pair : symbolToPattern) {
        CompressoutFile << pair.first << ">" << pair.second ;
    }
    
    
    
    //return compressed.str();
}

// Decompress function
std::string decompress(const std::string& CompressedfilePath/* ,const std::string& MapfilePath */) {
    std::stringstream decompressed;
    //std::ifstream CompressedFile(CompressedfilePath);
    string compressed="";
    string Map =""/* readFile(MapfilePath) */;
    unordered_map<char, std::string> recovered_map;
    unsigned char firstPart;
    string secondPart; 
    string input;
    input =readFile(CompressedfilePath);
    // Reconstructin the Map of rules
    string line;
    bool MapFlag=false;
    //string MapLine;
    for (char ch : input) {
        if(!MapFlag){
            if (ch == '\n') {
                if(line=="Map contents:"){
                    MapFlag=true;
                    continue;
                }
                compressed+=line;
                line.clear(); // Clear the line for the next one
            } else {
                line += ch; // Append the character to the current line
            }
        }
        else{
            for(char ch : input){
                Map+=ch;
            }
            break;
        }
    }
    
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



//// Main function
// int main() {
    
//         std::string filePath = "C:\\Users\\kareem\\Downloads\\7mb.xml";
//         // Read the XML file content
//         std::string input = readFile(filePath);

//         // Compress the input
//         compress(input);
//         //std::ofstream outputFile("compressed.txt", std::ios::binary);
//         //outputFile << compressed;
//         //outputFile.close();

//         // Decompress the data
//         std::string decompressed = decompress("C:\\C++\\DSA project\\repo2\\XML-to-JSON-project\\XML-to-JSON\\common\\compressed.txt");
//         std::ofstream outputFile2("decompressed.txt", std::ios::binary);
//         outputFile2 << decompressed;
//         outputFile2.close();


    
//     return 0;
// }
