#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

string filename_prompt();
map <string, int> translation;
map <string, int> ::iterator valid_entry;
void create_translation();
void display_menu();
void execute_instructions(int opcode);


int ACC, PC, opcode, operand, result;
vector<int> RAM;

int main()
{
    string filename, entry, convert;


    filename = filename_prompt();
    ifstream myfile(filename.c_str());

    create_translation();
    //execute_instructions();


    if(myfile.is_open()){
        while (myfile >> entry && !myfile.eof()){
            //cout << entry <<endl;
            valid_entry = translation.find(entry);
            if (valid_entry == translation.end()){
                istringstream(entry) >> result;
                RAM.push_back(result);
                }
            else
                RAM.push_back(valid_entry->second);
        }
        for (int i=0; i<RAM.size(); i++){
        cout << RAM[i] <<endl;
        }
    }


    else{
        cout << "Error in opening your file, try again." << endl;
        filename_prompt();
    }
    myfile.close();

    return 0;
}


string filename_prompt(){
    string textfile;

    cout << "Enter the filename: " << endl;
    cin >> textfile;
    return textfile;
}

void create_translation(){
    translation ["CLR"] = 0;
    translation ["LOAD"] = 1;
    translation ["ADD"] = 2;
    translation ["SUB"] = 3;
    translation ["MUL"] = 4;
    translation ["DIV"] = 5;
    translation ["OUT"] = 6;
    translation ["JMP"] = 7;
    translation ["BNZ"] = 8;
    translation ["HALT"] = 9;
}

void execute_instructions(int opcode){
    switch(opcode){
        case 0:
            ACC = 0;
            PC++;
            break;
        case 1:

            PC++;
            break;
        case 2:
            operand = RAM[++PC];
            ACC += operand;
            PC++;
            break;
        case 3:
            operand = RAM[++PC];
            ACC -= operand;
            PC++;
            break;
        case 4:
            operand = RAM[++PC];
            ACC *= operand;
            PC++;
            break;
        case 5:
            operand = RAM[++PC];
            if (operand == 0)
                cout << "Cannot divide by zero" <<endl;
            else{
                ACC /= operand;
                PC++;
            }
            break;
        case 6:
            cout << ACC << endl;
            PC++;
            break;
        case 7:
            operand = RAM[++PC];
            PC = operand;
            break;
        case 8:
            operand = RAM[++PC];
            if ( ACC != 0 )
                PC = operand;
            else
                PC++;
            break;
        case 9:
            cout << "Program halted" << endl;
            break;
    }
}

void display_menu(){
    cout << "Enter CLR to clear last calculated value" << endl;
    cout << "Enter LOAD to load an operand to the accumulator." << endl;
    cout << "Enter ADD to add operand to last calculated value." << endl;
    cout << "Enter SUB to subtract operand from last calculated value." << endl;
    cout << "Enter MUL to multiply last calculated value by an operand." << endl;
    cout << "Enter DIV to divide last calculated value by an operand." << endl;
    cout << "Enter OUT to display last calculated value." << endl;
    cout << "Enter HALT to halt program." << endl;
}
