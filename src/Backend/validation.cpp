#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

bool valid (const string& filePath){ //filePath="I:\\#term\\Data Structure\\project\\sample.xml"
    ifstream file;
    string line;
    stack<string> st ; // to check from the content of the tags
    stack<int> st_pos ; // to save the position of the wrong tages
    file.open(filePath);
    if(!file){
        cerr << "Couldn't open the file";
        return false;
    }

    while(getline(file,line)){
        //int pos=0;
        int open_posopen = 0 , open_posclose = 0 ; //for opening
        //int close_posopen , close_posclose ; //for closing
        for(int pos=0;pos<line.length();pos++){
            if(line[pos]=='<'&& line[pos+1]!='/'){
                open_posopen = 0;
                open_posopen = pos;
            }
            else if(line[pos]=='>'){
                open_posclose = 0 ;
                open_posclose = pos;
            }
            if(line[open_posopen] == '<' && line[open_posclose] == '>' && line[open_posopen+1] != '/')
                st.push(line.substr(open_posopen+1, open_posclose - open_posopen -1 ));


            if(line[pos]=='<' && line[pos+1]=='/'){ //closing
                if(st.top() == line.substr(pos+1,st.top().size()-1)) st.pop();
            }
            
        }

        // return st.empty() ;   
    }
    file.close();
    return st.empty();
}


int main(){
    if (valid("I:\\#term\\Data Structure\\project\\sample.xml") == true ) cout << " valid ";
    else cout << "notvalid" ;
}

