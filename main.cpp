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
void display_menu
void execute_instructions(int opcode);


int ACC, PC, opcode, operand;
vector<int> RAM;

int main()
{
    string filename, entry;

    filename = filename_prompt();
    ifstream(filename.c_str());


    if(.is_open()){
        while (filename >> entry && !filename.eof()){
            cout << entry << endl;
        }
    }
    else{
        cout << "Error in opening your file, try again." << endl;
        filename_prompt();
    }
    filename.close();

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
            operand = RAM[++pc];
            pc = operand;
            break;
        case 8:
            operand = RAM[++pc];
            if ( acc != 0 )
                pc = operand;
            else
                pc++;
            break;
        case 8:
            cout << "Program halted" << endl;
            break;
    }
}
