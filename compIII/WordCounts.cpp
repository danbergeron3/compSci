//ctrl z
#include <iostream>
#include<string>
#include<map>
//extra record modify way to exclude
using namespace std;

int main(int argc, char* argv[]){
    string aword;
    //create a map
    map<string, int> word;
    map<string, int>::iterator p;
    while(cin >> aword){
        //extra credit
        
        //cout << "Read: " << aword << endl;
        p = word.find(aword);
        if(p == word.end()){
            word.insert({aword, 1});
        } else {
            int temp = (*p).second;
            temp++;
            (*p).second = temp;
        }
    }
    
    for (p = word.begin(); p != word.end(); ++p) {
        cout << p->first; 
        cout << ": " << p->second << endl;
    }
    return 0;
}