#include <iostream>
#include <string>
#include <windows.h>

#include "playingfield.h"

void theIOProcess(std::string& attempt, PlayingField& area);
void makesAMove(std::string& attempt, PlayingField& area, bool& is_end);
bool wantNewGame(bool fail_move);

int main()
{
    bool new_game = false;
    do{
        system("CLS");
        std::cout << "Find The Mine\n make a field visible: c6\n mark a field: m c6\n\n";
        std::cout << "Choose the level:\n 1 beginner(10x10)\n 2 advanced(20x20)\n";

        int choice = 0;
        do{
            std::cin >> choice;
        }while(choice != 1 && choice != 2);

        PlayingField area(choice*10);

        bool fail_move = false;
        while(area.countValidMoves() > area.getMines() && !fail_move){
            std::string attempt;

            theIOProcess(attempt, area);
            makesAMove(attempt, area, fail_move);
        }

        new_game = wantNewGame(fail_move);
    }while(new_game);

    return 0;
}

void theIOProcess(std::string& attempt, PlayingField& area){
    system("CLS");
    area.showFields();
    std::cout << "\nGet a field: ";
    do{
        getline(std::cin, attempt);
    }while(attempt.size() != 2 && attempt.size() != 3 && attempt.size() != 4 && attempt.size() != 5);
}

void makesAMove(std::string& attempt, PlayingField& area, bool& fail_move){
    int row = -1;
    int column = -1;
    if(attempt.size() < 4){
        column = toupper(attempt[0])-65;
        row = atoi(attempt.substr(1).c_str())-1;
        area.newMove(row, column, fail_move);
    }else{
        column = toupper(attempt[2])-65;
        row = atoi(attempt.substr(3).c_str())-1;
        area.newMark(row, column);
    }
}

bool wantNewGame(bool fail_move){
    fail_move ? std::cout << "\nYou lose!\n" : std::cout << "\nYou win!\n";
    int choice = 0;
    std::cout << "Do you want a new game? (1-yes / 2-no): ";
    do{
        std::cin >> choice;
    }while(choice != 1 && choice != 2);

    return choice == 1 ? true : false;
}
