//Su Hyang Kim

#include <iostream>
#include "console.h"
#include <fstream>
#include "filelib.h"
#include "grid.h"
#include <string>
#include "simpio.h"
#include <locale>
#include <cctype>
#include "lifegui.h"

using namespace std;

//function declarations
Grid<char> fileOpener(Grid<char>& cellGrid);
char request();
bool quit();
int animate(Grid<char>& cellGrid);
Grid<char> tick(Grid<char>& cellGrid);
int copyGrid(Grid<char>& cellGrid, const Grid<char>& cellGridCopy);
int printGrid(const Grid<char>& cellGrid);

//main program run
int main() {
    //introduction
    cout << "Welcome to the CS 106B/X Game of Life!" << endl;
    cout << "This program simulates the lifecycle of a bacterial colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "* A cell with 1 or fewer neighbors dies." << endl;
    cout << "* Locations with 2 neighbors remain stable." << endl;
    cout << "* Locations with 3 neighbors will create life." << endl;
    cout << "* A cell with 4 or more neighbors dies." << endl;
    cout << endl;

    //initializes graphic user interface
    LifeGUI::initialize();

    //while this loop is running, the program will continue to run
    //this while loop will end only when the method quit() returns false
    bool running = true;
    while(running){
        //creates a cellGrid
        Grid<char> cellGrid;
        
        //opens file and puts the data into the cellGrid
        fileOpener(cellGrid);

        //while this remains true, the loop will continue to ask and perform
        //the necessary tasks
        bool questioning = true;
        while(questioning){
            //asks the user if they want to quit, tick, or animate and verifies
            //that only a q, a, or t is returned
            char inputChar = request();
            
            //if user inputs q then it will run the quit() method
            //if user inputs a then it will run the animate() method
            //if user inputs t then it will run the tick() method
            if(inputChar=='q'){
                if(quit()){
                    questioning = false;
                    running = false;
                } else{
                    questioning = false;
                }
            } else if (inputChar=='a'){
                animate(cellGrid);
            } else if(inputChar=='t'){
                tick(cellGrid);
            }
        }
    }
    return 0;
}

//this method opens the file, verifies its contents, and moves the data
//into the grid that is referenced as to save money and memory
Grid<char> fileOpener(Grid<char>& cellGrid){
    //opens file
    ifstream infile;
    promptUserForFile(infile, "Grid input file name?");
    string line;
    
    //finds number of rows and columns
    getline(infile, line);
    int rows = stringToInteger(line);
    getline(infile, line);
    int cols = stringToInteger(line);
    
    //creates new empty grid
    cellGrid.resize(rows, cols);
    
    //adjusts the GUI
    LifeGUI::resize(rows, cols);
    LifeGUI::clear();
    LifeGUI::repaint();
    
    //fills grid based on text
    char ch;
    for(int currRow=0; currRow<rows; currRow++){
        for(int currCol=0; currCol<cols; currCol++){
            //each character is extracted and placed in grid
            infile.get(ch);
            cellGrid.set(currRow, currCol, ch);
            cout<<ch;
        }
        //this is in place for the new line "character" at the end of each line
        infile.get(ch);
        cout << ch;
    }
    //closes the file
    infile.close();
    
    //returns the newly filled grid
    return cellGrid;
}

//this method asks for the user's intent on how to continue with the program
//and verifies that it is only a, q, or t and takes into consideration the enter
//before returning the user's choice
char request(){
    char inputChar;
    string input;
    char inputCharQ;
    
    //while the answer is incorrect/invalid, it will keep asking the user until a valid
    //character is provided and it will return that character
    bool incorrect = true;
    while(incorrect){
        input = getLine("a)nimate, t)ick, q)uit? ");
        //if the input is empty (the user presses enter) it'll change the character to t
        //for simplicity as the enter does the same task/method as entering t
        if(input.empty()){
            inputCharQ = 't';
        } else{
            inputCharQ = stringToChar(input);
            inputCharQ = tolower(inputCharQ);
        }
        if(inputCharQ == 'a' || inputCharQ == 'q' || inputCharQ == 't'){
            incorrect = false;
            inputChar = inputCharQ;
        }
    }
    return inputChar;
}

//this method is run when the user intends to quit and will ask if they would like to
//open another file or if they want to quit
bool quit(){
    //if the user doesn't want to open another file it will quit the GUI and end the program
    //with a "Have a nice Life!"
    if(!getYesOrNo("Load another file? (y/n)")){
        cout << "Have a nice Life!" << endl;
        LifeGUI::shutdown();
    }else{
        return false;
    }
    return true;
}

//this method is run when the user intends to animate the cells a fixed number of times and
//tick the cell for that number of times with a 100 millisecond pause in between each while
//clearing the console and GUI at the same time
int animate(Grid<char>& cellGrid){
    int numOfTimes = getInteger("How many frames? ");
    clearConsole();
    LifeGUI::clear();
    for(int i = 0; i < numOfTimes; i++){
        tick(cellGrid);
        pause(100);
        clearConsole();
        LifeGUI::clear();
    }
    return 0;
}

//this method is run when the user intends to tick or see the cell animation only once and
//step by step
Grid<char> tick(Grid<char>& cellGrid){
    LifeGUI::clear();
    int rows = cellGrid.height();
    int cols = cellGrid.width();
    Grid<char> cellGridCopy(rows, cols);
    for(int r = 0; r < rows; r++){
      for(int c = 0; c < cols; c++){
         int numOfNeighbors = 0;
         for(int rFiller = -1; rFiller < 2; rFiller++){
            for(int cFiller = -1; cFiller < 2; cFiller++){
               int modRow = ((r + rFiller) + rows) % rows;
               int modCol = ((c + cFiller) + cols) % cols;
               if(!(modRow == r && modCol == c)){
                  if(cellGrid[modRow][modCol] == 'X'){
                     numOfNeighbors++;
                  }
               }
            }
         }
         //follows the contrainsts of whether the cell will live or die
         if(numOfNeighbors <= 1){
            cellGridCopy[r][c] = '-';
         }else if(numOfNeighbors == 2){
            cellGridCopy[r][c] = cellGrid[r][c];
            if(cellGrid[r][c]=='X'){
                LifeGUI::fillCell(r,c);
            }
         }else if(numOfNeighbors == 3){
            cellGridCopy[r][c] = 'X';
            LifeGUI::fillCell(r,c);
         }else if(numOfNeighbors >= 4){
            cellGridCopy[r][c] = '-';
         }
      }
    }
    //copies all the contents of the newly filled copy of the cellGrid into the original cellGrid
    copyGrid(cellGrid, cellGridCopy);
    
    //prints the new original grid
    printGrid(cellGrid);
    
    //returns the original cellGrid
    return cellGrid;
}

//copies all the contents of the newly filled copy of the cellGrid into the original celLGrid
int copyGrid(Grid<char>& cellGrid, const Grid<char>& cellGridCopy){
    int rows = cellGrid.numRows();
    int cols = cellGrid.numCols();
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            cellGrid[r][c] = cellGridCopy[r][c];
        }
    }
    return 0;
}

//prints the grid that is referenced in the parameters
int printGrid(const Grid<char>& cellGrid){
    int rows = cellGrid.numRows();
    int cols = cellGrid.numCols();
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            cout << cellGrid[r][c];
        }
        cout << endl;
    }
    LifeGUI::repaint();
    return 0;
}
