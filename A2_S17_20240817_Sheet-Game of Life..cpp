
/*     test cases

 1 - load file: file input(000010111) width input(3),height input(3)  ,output all the generation

 2 - output all the generation

 3 - input the alive cells (4) , index row col //4 4 5 3 5 4 5 5 ,output all the generation

 note: if you want to see the last generation only remove the comment (//) on system("cls") in display () line 146

  */
#include <iostream>
#include <fstream>
#include <cstdlib> // for random function (rand())
#include <string>
#include <vector>
using namespace std;
class Universe {
private:
    int row,column,generation;
   vector<vector<char>>grid;
    vector<vector<char>>next_grid;
    // function to check the on the cell if its alive
    bool is_alive(int r, int c) {
        if (grid[r][c] == '1')
            return true ;
        else
            return false ;
    }
public:
    Universe(){};
    // Initialize the attributes
    Universe(int r, int c,int g) {
        row = r;
        column = c;
        generation=g;
        grid.resize(row, vector<char>(column, ' '));
        next_grid.resize(row, vector<char>(column, ' '));
    }

    void initialize(int &play) {
        if(play==2) {//play with random cells
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                grid[i][j] = (rand() % 3 == 0) ? '1' : '0'; // Initialize 30 % for live cells
            }
        }
            run(generation);
        }
        else if (play==3){ //play with chosen cells
            int r,c,num_of_cells;
            reset();
            display();
            cout<<"How many cells do you want to access number\n";
            cin>>num_of_cells;
            while (num_of_cells--){
                cout<<"enter the index of cell that you want { 0 <= (row and column) <= 29 }\n";
                cin>>r>>c;
                grid[r][c]='1';
                    display();
                }
            run(generation);
            }
    }
   // Reset all cells to dead
    void reset() {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                grid[i][j] = '0';

            }
        }
    }
    void load_file(const string &file){
        int width,height;
        cout<<"Please enter the size of the file (Width,Height)\n";
        cin>>width>>height;
        row = width;
        column = height;
        grid.resize(row, vector<char>(column, '0'));
        next_grid.resize(row, vector<char>(column, '0'));
        ifstream f(file);
        if (!f.is_open()) {
            cout << "Error cannot open this file \n";
            return;
        }
        char index;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (f >> index) {
                    grid[i][j] = index;
                }
            }
        }
        f.close();
        display();
        run(generation);
    }
    //Returns the number of alive neighbors.
    int count_neighbors(int r, int c) {
        int count = 0;

        // check on the cell in all directions ( horizontal & vertical & diagonals)
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue; // Skip the cell itself
                int num_row,num_col;
                num_row = r + i;
                num_col = c + j;
                if (num_row >= 0 && num_row < row && num_col >= 0 && num_col < column && is_alive(num_row, num_col)) {
                    count++;
                }
            }
        }
        return count;
    }

   // produces a new state of the game based on the transition rules.
   void next_generation() {
       for (int i = 0; i < row; ++i) {
           for (int j = 0; j < column; ++j) {
               int alive_neighbors = count_neighbors(i, j);
               if (is_alive(i, j)) {
                   // conditions for alive cells
                   if (alive_neighbors < 2 || alive_neighbors > 3) {
                       next_grid[i][j] = ' '; // Cell dies
                   } else {
                       next_grid[i][j] = '1'; // Cell survives
                   }
               } else {
                   // conditions for dead cells
                   if (alive_neighbors == 3) {
                       next_grid[i][j] = '1'; // Cell becomes alive
                   } else {
                       next_grid[i][j] = ' '; // Cell remains dead
                   }
               }
           }
       }
       // Update the grid
       grid = next_grid;
   }
    // shows the game status on the console
    void display(){
      // system("cls"); // to clear the screen
        for(int i=0;i<row;++i) {
            for (int j = 0; j < column; ++j) {
               cout<< grid[i][j] << " " ;
            }
            cout<<"\n";
        }
    }
    //To start the game for a certain number of runs.
    void run(int gen) {
        for (int i = 0; i < gen; ++i) {
            cout<<"\n";
            cout<<"generation ( "<<i+1<<" ) = \n";
            cout<<"\n";
            display();
            next_generation();
        }
    }
};
void displayMenu()
{
    cout << "1. Load Program from File\n";
    cout << "2. play with the random cells\n";
    cout << "3. chose your cells\n";
    cout << "4. Exit\n";
}
void Choice(int ch){
    Universe u(30,30,10); //Default size
    if(ch==1) {
        string filename;
        cout<<"Please enter your file name.\n";
        cin>>filename;
        u.load_file(filename);
    }
     else if (ch == 2){
         int play_with=2;
        u.initialize(play_with);
        u.display();
    }
     else if(ch==3) {
        int play_with=3;
        u.reset();
        u.initialize(play_with);
    }
     else if (ch == 4)
        return;
     else
         cout<<"Wrong choice.\n";
}
int main() {
    int choice;
    displayMenu();
    cin>>choice;
    Choice(choice);
    return 0;
}
