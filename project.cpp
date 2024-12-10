#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
bool replaced=true;
bool ruled=true;
string rule_name;

class Symbol {
public:
    string value;       // Terminal (e.g., "a") or non-terminal (e.g., "R1")
    Symbol* prev;            // Previous symbol in the sequence
    Symbol* next;            // Next symbol in the sequence

    Symbol( string val) : value(val), prev(nullptr), next(nullptr) {}
};

class Rule {
public:
     string name;        // Name of the rule (e.g., "R1")
    Symbol* first;           // First symbol in the rule's expansion
    Symbol* last;            // Last symbol in the rule's expansion

    Rule( string ruleName) : name(ruleName), first(nullptr), last(nullptr) {}
};

class Sequitur {
private:
              // Map of rules
     unordered_map< string, Symbol*> digrams;//sequence (pair)      // Map for digram uniqueness
    int ruleCounter;                                       // Rule naming counter
    // Head of the sequence

    // Create a new rule
    Rule* createRule(const  string& expansion) {
        string ruleName = "R" +  to_string(ruleCounter++);
        Rule* rule = new Rule(ruleName);

        // Build the rule's sequence
        Symbol* prev = nullptr;
        for (char c : expansion) {
            Symbol* sym = new Symbol( string(1, c));
            if (!rule->first) rule->first = sym;
            if (prev) {
                prev->next = sym;
                sym->prev = prev;
            }
            prev = sym;
        }
        rule->last = prev;
        //rules[ruleName] = rule;
        return rule;
    }

    // Check if a digram exists
void processDigram(Symbol* s) {
        if (s==nullptr || s->next==nullptr) return;

         string digram = s->value + s->next->value;

        if (digrams.count(digram)) {
            
            // Digram exists: replace with a rule
            Symbol* existing = digrams[digram];
            Rule* rule;
            ruled=false;
            for (const auto pair : rules) {
            // pair is a reference to the key-value pair, but it's read-only due to `const`.
                if(pair.second->first->value==digrams[digram]->value &&pair.second->last->value==digrams[digram]->next->value){
                    ruled=true;
                    rule_name=pair.second->name;
                }
            }
            if (!ruled) {
                // Create a new rule for the digram
                rule = createRule(digram);
                rules[rule->name] = rule;
            } else {
                rule = rules[rule_name];
                existing->value=rule->name;
                existing->next=existing->next->next;
                
            }
            // Replace digram with non-terminal
            Symbol* temp=head;
            while(temp && temp->next){
                if(digram==string(temp->value)+string(temp->next->value)){
                    replaced=true;
                    temp->value = rule->name;
                    temp->next = temp->next->next;
                    if (temp->next) temp->next->prev = s;
                }
                temp=temp->next;
            }
              //////
        } else {
            // Digram is unique: add to map
            digrams[digram] = s;
        }
    }

public:
    Symbol* head;
    unordered_map< string, Rule*> rules; 
    Sequitur() : ruleCounter(1), head(nullptr) {}

    void compress(const  string& input) {
        // Initialize sequence from input string
        Symbol* prev = nullptr;
        for (char c : input) {
            Symbol* sym = new Symbol( string(1,c));
            if (!head) head = sym;
            if (prev) {
                prev->next = sym;
                sym->prev = prev;
            }
            prev = sym;
        }
        Symbol *temp=head; 
            while (temp)
            {
                replaced=false;
                processDigram(temp);
                temp=temp->next;
            }
            temp=head;
            while (temp)
            {
                replaced=false;
                processDigram(temp);
                temp=temp->next;
            }                
    }

    void printRules() {
         cout << "Rules:\n";
        for (const auto& pair : rules) {
             cout << pair.first << " -> ";
            Symbol* s = pair.second->first;
            while (s) {
                 cout << s->value;
                if (s->next)  cout << " ";
                s = s->next;
            }
             cout << "\n";
        }
    }

    void printSequence() {
        
        cout << "Compressed Sequence: ";
        Symbol* s = head;
        while (s) {
             cout << s->value;
            s = s->next;
            
        }
         
    }
    
};

int main() {
    string input="abcababcabcabcabc";
    string filePath = "C:\\Users\\kareem\\Desktop\\NIEM5.1_DNA_MP_Relatives_Case.xml";
    ostringstream fileStream;
    ifstream file(filePath);
    fileStream << file.rdbuf();
    string xmlContent = fileStream.str();
    std::ofstream outputFile("output.txt");
    std::ofstream outputFile2("output2.txt");
    
    // Write the XML content to the output file
    
    cout<<"uncompressed: "<<xmlContent.size()<<"\n";
    Sequitur sequitur;
    sequitur.compress(xmlContent);
    
    //sequitur.printSequence();
    //sequitur.printRules();
    outputFile << "XML Content:" << std::endl;
    Symbol *t=sequitur.head;
    while(t){
    outputFile << t->value << std::endl;
    t=t->next;
    }   
    while(t){
    outputFile << t->value << std::endl;
    t=t->next;
    } 
    
    for(int j=1;j<sequitur.rules.size();j++){
        string name= "R"+to_string(j);
        outputFile2<< sequitur.rules[name]->name;
        outputFile2<< "-->";
        outputFile2<< sequitur.rules[name]->first->value;
        outputFile2<< sequitur.rules[name]->last->value;
        outputFile<<"\n";
        
    }
    file.close();
    outputFile.close();
    cout<<"\n"<<sequitur.rules.size();
    return 0;
}
