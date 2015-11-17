#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stdlib.h>

using namespace std;

string filename_prompt();
map <string, int> translation;
map <string, int> ::iterator valid_entry;
void create_translation();
void display_menu();
void execute_instructions(int opcode);
char additional_instructions ();


int ACC, PC=0, opcode, operand, result;
vector<int> RAM;

int main()
{
    string filename, entry, user_added_opcode;

    char more_instruct_response;
    int new_operand;

    filename = filename_prompt();

    create_translation();

    while (true)
    {
    ifstream myfile(filename.c_str());
    if (myfile.is_open()){
        cout << "File is open";
        do {
            (myfile >> entry && !myfile.eof());//{
            valid_entry = translation.find(entry);
            if (valid_entry == translation.end()){
                istringstream(entry) >> result;
                RAM.push_back(result);
                }
            else
                RAM.push_back(valid_entry->second);
        } while (entry != "HALT");
        cout << RAM.size() <<endl;
        //cout <<endl;

        //for (int i=0; i<RAM.size(); i++){
        //cout << RAM[i] <<endl;
        //}

        for(int i=0; i<RAM.size(); i++){
            // Fetch cycle
            opcode = RAM[PC];
            execute_instructions(opcode);
        }


        more_instruct_response = additional_instructions();
        //if (more_instruct_response =='Y' || more_instruct_response =='y'){
        while (more_instruct_response =='Y' || more_instruct_response =='y'){
                if (RAM[(RAM.size())-1]==9)
                    RAM.erase (RAM.begin()+(RAM.size())-1);
                display_menu();
                //do {
                cin >> user_added_opcode;   //MAKE USER INPUT UPPER CASE!
                valid_entry = translation.find(user_added_opcode);
                if (valid_entry->first == "CLR" || valid_entry->first == "OUT" || valid_entry->first == "HALT"){
                    cout << "OK then..." <<endl;
                    RAM.push_back(valid_entry->second);
                    }

                else{
                    //cout << "Nevermind  then..." << endl;
                    cout << "Enter the operand: " <<endl;
                    cin >> new_operand;
                    RAM.push_back(new_operand);
                    }
                //}while (user_added_opcode != "HALT");
                //}

        //for (int i=0; i<RAM.size(); i++){
        //cout << RAM[i] <<endl;
        //}
        for(int i=0; i<RAM.size(); i++){
            // FETCH CYCLE
            opcode = RAM[PC];
            execute_instructions(opcode);
        }
        more_instruct_response = additional_instructions();
        }
        //else{
        if (more_instruct_response !='Y' || more_instruct_response !='y'){
            cout << "Exiting current program..." << endl;
            cout << "Returning to main menu..." <<endl;     //GO BACK TO MAIN MENU!
            exit (EXIT_SUCCESS);
        }
        }

        //break;
        //}



    else
        cout << "Error in opening your file, try again." << endl;
        cin >> filename;
    }

    return 0;
    /*


    if (myfile.is_open()){
        //while (myfile >> entry && !myfile.eof()){
        do {
            (myfile >> entry && !myfile.eof());//{
            valid_entry = translation.find(entry);
            if (valid_entry == translation.end()){
                istringstream(entry) >> result;
                RAM.push_back(result);
                }
            else
                RAM.push_back(valid_entry->second);
        } while (entry != "HALT");
        cout << RAM.size() <<endl;
        //cout <<endl;

        //for (int i=0; i<RAM.size(); i++){
        //cout << RAM[i] <<endl;
        //}

        for(int i=0; i<RAM.size(); i++){
            // Fetch cycle
            opcode = RAM[PC];
            execute_instructions(opcode);
        }

        more_instruct_response = additional_instructions();
        if (more_instruct_response =='Y' || more_instruct_response =='y'){
                display_menu();
                do {
                cin >> user_added_opcode;
                valid_entry = translation.find(user_added_opcode);
                {if (valid_entry->first == "CLR" || valid_entry->first == "OUT"} /|| valid_entry->first == "HALT"){
                    cout << "OK then..." <<endl;
                    RAM.push_back(valid_entry->second);
                    }
                else{
                    //cout << "Nevermind  then..." << endl;
                    cout << "Enter the operand: " <<endl;
                    cin >> new_operand;
                    RAM.push_back(new_operand);
                    }
                }
                }while (user_added_opcode != "HALT");

        //for (int i=0; i<RAM.size(); i++){
        //cout << RAM[i] <<endl;
        //}
        for(int i=0; i<RAM.size(); i++){
            // FETCH CYCLE
            opcode = RAM[PC];
            execute_instructions(opcode);
        }
        }
        else{
            cout << "Exiting current program..." << endl;
            cout << "Returning to main menu..." <<endl;     //GO BACK TO MAIN MENU!
            exit (EXIT_SUCCESS);
        }
        }
    }

    myfile.close();
    return 0;
    */
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
    cout << "Step 1: Select an operation to perform: " <<endl;
    cout << "Enter CLR to clear last calculated value, OR" << endl;
    cout << "Enter LOAD to load an operand to the accumulator, OR" << endl;
    cout << "Enter ADD to add operand to last calculated value, OR" << endl;
    cout << "Enter SUB to subtract operand from last calculated value, OR" << endl;
    cout << "Enter MUL to multiply last calculated value by an operand, OR" << endl;
    cout << "Enter DIV to divide last calculated value by an operand, OR" << endl;
    cout << "Enter OUT to display last calculated value, OR" << endl;
    cout << "Enter HALT to halt program." << endl;
    //cout << endl;
    //cout << "Then enter the operand: " <<endl;
}

char additional_instructions (){
    char response;
    cout << "Do you have additional instructions? If so, enter 'Y'. " << endl;
    cin >> response;
    return response;
}
