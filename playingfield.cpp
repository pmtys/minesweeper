#include "playingfield.h"

#include <iostream>
#include <windows.h>

#include <stdlib.h>
#include <time.h>

PlayingField::PlayingField(int p){
    piece = p;
    mines = piece*piece/10;
    field_vec.resize(piece);
    for(int i = 0; i < piece; ++i) field_vec[i].resize(piece);
    mineMaker();
}

void PlayingField::newMove(int row, int column, bool& fail_move){
    int act_content = field_vec[row][column].getContent();

    if(act_content == 9){
        showFields(true, row, column);
        fail_move = true;
    }
    else act_content == 0 ? zeroSpaces(row, column) : field_vec[row][column].makeVisible();
}

void PlayingField::newMark(int row, int column){
    if(!field_vec[row][column].isVisible()) field_vec[row][column].switchMarked();
}

int PlayingField::countValidMoves(){
    int valid_moves = 0;
    for(int i = 0; i < piece; ++i){
        for(int j = 0; j < piece; ++j){
            if(!field_vec[i][j].isVisible()) ++valid_moves;
        }
    }

    return valid_moves;
}

int PlayingField::countMarkedFields(){
    int marked_fields = 0;
    for(int i = 0; i < piece; ++i){
        for(int j = 0; j < piece; ++j){
            if(field_vec[i][j].isMarked()) ++marked_fields;
        }
    }

    return marked_fields;
}

void PlayingField::mineMaker(){
    srand (time(NULL));
    int counter = 0;
    while(counter != mines){
        int row = 0;
        int column = 0;
        do{
            row = rand()%piece;
            column = rand()%piece;
        }while(field_vec[row][column].isMine());
        field_vec[row][column].makeMine();
        field_vec[row][column].setContent(9);
        nextToMine(row, column);
        ++counter;
    }
}

void PlayingField::nextToMine(int row, int column){
    int row_start = --row;
    --column;
    for(int i = 0; i < 9; ++i){
        if((row >= 0 && row < piece) && (column >=0 && column < piece) && !field_vec[row][column].isMine()){
            int act_content = field_vec[row][column].getContent();
            field_vec[row][column].setContent(++act_content);
        }

        ++row;
        if(i%3 == 2){
            row = row_start;
            ++column;
        }
    }
}

void PlayingField::zeroSpaces(int row, int column){
    if(row < 0 || row >= piece || column < 0 || column >= piece || field_vec[row][column].isVisible()) return;
    else{
        if(field_vec[row][column].getContent() != 0){
            field_vec[row][column].makeVisible();
        }else{
            field_vec[row][column].makeVisible();
            zeroSpaces(row-1, column-1);
            zeroSpaces(row-1, column);
            zeroSpaces(row-1, column+1);
            zeroSpaces(row, column-1);
            zeroSpaces(row, column+1);
            zeroSpaces(row+1, column-1);
            zeroSpaces(row+1, column);
            zeroSpaces(row+1, column+1);
        }
    }
}

void PlayingField::showFields(bool fail_move, int row, int column){

    HANDLE h_console;
    h_console = GetStdHandle(STD_OUTPUT_HANDLE);

    system("CLS");
    if(!fail_move) statusBar();
    std::cout << "    ";
    SetConsoleTextAttribute(h_console, 11);
    for(int i = 0; i < piece; ++i) std::cout << static_cast<char>(i+65) << " ";
    std::cout << std::endl;
    SetConsoleTextAttribute(h_console, 7);
    if(fail_move){
        showDown(row, column);
    }else{
        for(int i = 0; i < piece; ++i){
            SetConsoleTextAttribute(h_console, 11);
            i+1 < 10 ? std::cout << " " << i+1 << "| " : std::cout << i+1 << "| ";
            SetConsoleTextAttribute(h_console, 7);
            for(int j = 0; j < piece; ++j){
                if( !field_vec[i][j].isVisible() && !field_vec[i][j].isMarked() ){
                    SetConsoleTextAttribute(h_console, 8);
                    std::cout << static_cast<char>(223) << " ";
                    SetConsoleTextAttribute(h_console, 7);
                }else if(field_vec[i][j].isMarked()){
                    SetConsoleTextAttribute(h_console, 10);
                    std::cout << "! ";
                    SetConsoleTextAttribute(h_console, 7);
                }else{
                    int act_con = field_vec[i][j].getContent();
                    act_con == 0 ? std::cout << "  " : std::cout << act_con << " ";
                }
            }
            SetConsoleTextAttribute(h_console, 11);
            std::cout << "|" << i+1;
            std::cout << std::endl;
            SetConsoleTextAttribute(h_console, 7);
        }
    }
    std::cout << "    ";
    SetConsoleTextAttribute(h_console, 11);
    for(int i = 0; i < piece; ++i) std::cout << static_cast<char>(i+65) << " ";
    std::cout << std::endl;
    SetConsoleTextAttribute(h_console, 7);
}

void PlayingField::showDown(int row, int column){
    HANDLE h_console;
    h_console = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; i < piece; ++i){
        SetConsoleTextAttribute(h_console, 11);
        i+1 < 10 ? std::cout << " " << i+1 << "| " : std::cout << i+1 << "| ";
        SetConsoleTextAttribute(h_console, 7);
        for(int j = 0; j < piece; ++j){
            if(field_vec[i][j].isMine()){
                if(i == row && j == column){
                    SetConsoleTextAttribute(h_console, 192);
                    std::cout << static_cast<char>(15);
                    SetConsoleTextAttribute(h_console, 7);
                    std::cout << " ";
                }else{
                    SetConsoleTextAttribute(h_console, 12);
                    std::cout << static_cast<char>(15) << " ";
                    SetConsoleTextAttribute(h_console, 7);
                }
            }else{
                std::cout << "  ";
            }
        }
        SetConsoleTextAttribute(h_console, 11);
        std::cout << "|" << i+1;
        std::cout << std::endl;
        SetConsoleTextAttribute(h_console, 7);
    }
}

void PlayingField::statusBar(){
    std::cout << "Mines left: " << mines - countMarkedFields() << "\n";
}
