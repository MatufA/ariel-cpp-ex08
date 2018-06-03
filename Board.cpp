#include "Board.h"
#include <fstream>
#include <sys/stat.h>

Board :: Board (){
    this->boardSize = 3;
    alloc();
}

Board :: Board (int size){
    boardSize = size;
    alloc();
}

Board :: Board(Board& other){
    this-> boardSize = other.boardSize;
    
    alloc();
    for(int rows = 0; rows < (this-> boardSize); rows++)
    	 for(int columns = 0; columns < (this-> boardSize); columns++)
    	       (this-> gameBoard[rows][columns]) = other.gameBoard[rows][columns].get_sign();
}

Board :: ~Board(){
    dlloc();
}

int Board :: size() const{
    return boardSize;
}

void Board :: dlloc(){
    for(int i = 0; i < boardSize; i++)
		delete [] gameBoard[i];
	delete [] gameBoard; 
}

void Board :: alloc(){
	gameBoard = new place*[boardSize];
	for(int i = 0; i < boardSize; i++) gameBoard[i] = new place[boardSize];
}

void Board :: fill(char symbol){
        for(int rows = 0; rows < (this-> boardSize); rows++)
    	    for(int columns = 0; columns < (this-> boardSize); columns++)
    	       (this-> gameBoard[rows][columns]) = symbol;
}

place& Board :: operator[] (const pairs index){
    if(index.first >= boardSize || index.second >= boardSize){
      IllegalCoordinateException coordinate;
      coordinate.set_first(index.first);
      coordinate.set_second(index.second);
      throw coordinate;
    } 
    if(index.first < 0 || index.second < 0){
        IllegalCoordinateException coordinate;
        coordinate.set_first(index.first);
        coordinate.set_second(index.second);
        throw coordinate;
    }
    return gameBoard[index.first][index.second];
}

place Board :: operator [] (pairs index) const {//read only 
    return this -> gameBoard[index.first][index.second];
}

Board& Board ::operator= (Board& other){
    if(this == &other) return *this;
    dlloc();
    boardSize = other.boardSize;
    gameBoard = new place*[boardSize];
    for(int rows = 0; rows < (this-> boardSize); rows++){
	    gameBoard[rows] = new place[boardSize];
    	    for(int columns = 0; columns < (this-> boardSize); columns++)
    	       (this-> gameBoard[rows][columns]) = other.gameBoard[rows][columns];}
    return *this;
}

char Board :: operator= (char symbol){
    if(symbol == '.'){ fill(symbol); }
    else if (symbol != 'X' && symbol != 'O'){
        IllegalCharException ichar;
        ichar.set_illegal(symbol);
        throw ichar; }
    return symbol;
}

bool operator== (const Board& firstA, const Board& secondB){
    if(firstA.boardSize != secondB.boardSize) return false;
    for(int rows = 0; rows < (firstA.boardSize); rows++)
    	    for(int columns = 0; columns < (firstA.boardSize); columns++)
    	       if(firstA.gameBoard[rows][columns] != secondB.gameBoard[rows][columns]) return false;
    return true;
}

bool operator!= (const Board& firstA, const Board& secondB){ return !(firstA == secondB); } 

string Board ::draw(const unsigned int n){
    const int dimx = n, dimy = n;
    const string filename = get_name();
    RGB image[dimx*dimy];
    //initial background
    cout << "initial background" << endl;
    /**
    int rib = 0;
    int start = rib*boardSize; // 0
    int end = dimy/boardSize; // 200
    int haloka = dimy/boardSize; // 200
    
    for(int i = start; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(((i % haloka == 0 || j % haloka == 0) && (i != 0 || i != boardSize))){
                image[dimx*j+i].red = 255;
                image[dimx*j+i].green = 255;
                image[dimx*j+i].blue = 255;
            }
        }
    }*/

    for (int j = dimy/boardSize; j < dimy; j+=dimy/boardSize)  {  // row
        for (int i = 0; i < dimx; ++i) { // column
            image[dimx*j+i].red = 255;
            image[dimx*j+i].green = 255;
            image[dimx*j+i].blue = 255;
            
             image[dimx*i+j].red = 255;
            image[dimx*i+j].green = 255;
            image[dimx*i+j].blue = 255;
        }

    }
    //draw X and O
    for(int row = 0; row < boardSize; ++row){
        for(int col = 0; col < boardSize; ++col){
            if(gameBoard[row][col] == 'X') print_X(row , col , dimx , image);
            if(gameBoard[row][col] == 'O') print_O(row , col , dimx/boardSize , image);
        }
    }
    //write the file
    ofstream imageFile(filename, ios::out | ios::binary);
    imageFile << "P6" << endl << dimx <<" " << dimy << endl << 255 << endl;
    imageFile.write(reinterpret_cast<char*>(&image), 3*dimx*dimy);
    imageFile.close();
    return filename;   
    }

string Board ::get_name()const{
    int num=0;
    string filename = "board_" + std::to_string(num) +".ppm";
    struct stat buffer;   
    while(stat (filename.c_str(), &buffer) == 0){
        num++;
        filename = "board_" + std::to_string(num) +".ppm";
    }
    return filename;
}

void Board :: print_X(const int row_cor, const int col_cor , const int image_size , RGB* image){
    int bound = image_size / boardSize;
    for(int row = 1; row < bound-1; ++row){
        image[(image_size*row_cor*bound)+(image_size*row)+row].red = 255;
        image[(image_size*row_cor*bound)+(image_size*row)+row].green = 0;
        image[(image_size*row_cor*bound)+(image_size*row)+row].blue = 0;
        
        image[(image_size*(row_cor+1)*bound)-(image_size*row)+row].red = 255;
        image[(image_size*(row_cor+1)*bound)-(image_size*row)+row].green = 0;
        image[(image_size*(row_cor+1)*bound)-(image_size*row)+row].blue = 0;
    }
    
    
    /**
    int boarder_size = image_size / boardSize;
    int x_mid = row_cor*boarder_size + boarder_size/2;
    int y_mid = col_cor*boarder_size + boarder_size/2;
    int bound = (boarder_size/2) -2;
    for(int row = 0; row < bound; ++row){
        //draw X from middle to top left: [x_mid-row][y_mid-row]
        cout << "(x_mid-row) " << image_size*(x_mid-row) << " (y_mid-row): " << (y_mid-row) << endl; 
        image[image_size*(x_mid-row)+(y_mid-row)].red = 255;
        image[image_size*(x_mid-row)+(y_mid-row)].green = 0;
        image[image_size*(x_mid-row)+(y_mid-row)].blue = 0;
        //draw X from middle to top right: [x_mid-row][y_mid+row]
        image[image_size*(x_mid-row)+(y_mid+row)].red = 255;
        image[image_size*(x_mid-row)+(y_mid+row)].green = 0;
        image[image_size*(x_mid-row)+(y_mid+row)].blue = 0;
        //draw X from middle to down left: [x_mid+row][y_mid-row]
        image[image_size*(x_mid+row)+(y_mid-row)].red = 255;
        image[image_size*(x_mid+row)+(y_mid-row)].green = 0;
        image[image_size*(x_mid+row)+(y_mid-row)].blue = 0;
        //draw X from middle to down right:[x_mid+row][y_mid+row]
        image[image_size*(x_mid+row)+(y_mid+row)].red = 255;
        image[image_size*(x_mid+row)+(y_mid+row)].green = 0;
        image[image_size*(x_mid+row)+(y_mid+row)].blue = 0;
    }*/
    
}
//https://stackoverflow.com/questions/13920576/how-to-draw-a-filled-circle
void Board :: print_O(const int row_cor, const int col_cor , const int boarder_size , RGB* image){
   int x_mid = row_cor*boarder_size + boarder_size/2;
    int y_mid = col_cor*boarder_size + boarder_size/2;
    int r = (boarder_size/2)-2;
    for (int j = (row_cor*boarder_size)+1; j < (row_cor+1)*boarder_size; ++j)  {  // row
        for (int i = (col_cor*boarder_size)+1; i < (col_cor+1)*boarder_size; ++i) { // column
            int dx = x_mid -j; // horizontal offset
            int dy = y_mid -i; // vertical offset
            if ( (dx*dx + dy*dy) <= (r*r) ){
             image[(col_cor+1)*boarder_size*j+i].red = 0;
             image[(col_cor+1)*boarder_size*j+i].green = 0;
             image[(col_cor+1)*boarder_size*j+i].blue = 255;
            }
        }
    }
}
    
