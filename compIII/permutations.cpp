#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <set>
using namespace std;

string generate_permutations(list<string>& inputList);
void print_permutations(string perm);

int main(int argc, char *argv[])
{
    list<string> inputList;
    string aLine, aString;
    // read in strings from stdin
    cout << "Enter strings, separated by a space:";
    getline(cin, aLine); //read a line from keyboard
    istringstream iss(aLine); //convert aLine to an istringstream obj

    //parse each string
    while(iss >> aString)
    {
        inputList.push_back(aString);
    }

    auto permutations = generate_permutations(inputList);

    // print permutations to stdout
    print_permutations(permutations);

    return 0;
}

string generate_permutations(list<string>& inputList){
    string word;
    set<string> permSet;
    string* stringList = new string[inputList.size()];
    int size = 0;
    list<string>::iterator index = inputList.begin();
    for(; index != inputList.end(); index++){
        permSet.insert(*index);
    }
    set<string>::iterator setIndex = permSet.begin();
    for(; setIndex != permSet.end(); setIndex++){
        stringList[size] = *setIndex;
        size++;
    }
    //sort(stringList, stringList + size);
    int count = 1;
    do{
        //convert to string
        word += to_string(count);
        word += ". ";
        for(int i = 0; i < size; i++){
            
            word += stringList[i];
            word += ' ';
        }
        word += '\n';
        count++;
    }while(next_permutation(stringList,stringList + size));

    //put in permutation object
    delete [] stringList;
    return word;
}

void print_permutations(string perm){
    cout << "Permtations are: \n";
    cout << perm << endl;
    return;
}

