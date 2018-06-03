#include "Board.h"
#include <fstream>
#include <sys/stat.h>
#define _USE_MATH_DEFINES // for C++  
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

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
/*
string Board ::draw(const unsigned int n){
    cout << "draw" << endl;
    int dimx = n, dimy = n;
    const int image_size = n;
    const string filename = get_name();
    
    //initial background
    cout << "initial background" << endl;
    
    int** img; 
    
    img = new int*[image_size];
    for (int i = 0; i < image_size; ++i) img[i] = new int[image_size];
       
    for(int i=0; i < image_size; i++){ //fill background
        for(int j=0; j  <image_size; j++){
            img[i][j] = 255;
        }
    }
    
    
    
    
    cout << "write file" << endl;https://c9.io/yuda4
    ofstream imageFile(filename, ios::out | ios::binary);
    imageFile << "P6" << endl << image_size <<" " << image_size << endl << 255 << endl;
    
    RGB image[image_size*image_size];
    
        //draw X and O
    for(int row = 0; row < boardSize; ++row){
        for(int col = 0; col < boardSize; ++col){
            if(gameBoard[row][col] == 'X') print_X(row , col , image_size , img);
           // if(gameBoard[row][col] == 'O') print_O(row , col , image_size/boardSize , img);
        }
    }
    
    for(int i=0; i < image_size; i++){ //making columns
        for(int j=0; j  <image_size; j++){
            image[image_size*i+j].red = img[i][j];
            image[image_size*i+j].green = img[i][j];
            image[image_size*i+j].blue = img[i][j];
        }
    }
    
        
    for(int i=0;i<image_size;i++){
        for(int j=0;j<image_size;j++){
            
            image[i*image_size+j].red = img[i][j];
            image[i*image_size+j].green = img[i][j];
            image[i*image_size+j].blue = img[i][j];

        }
 
    }
    
    for(int i=0; i < image_size; i++){ 
        delete [] img[i];
    }
    
    delete [] img;
    
    
        
    /*for (int j = dimy/boardSize; j < dimy; j+=dimy/boardSize)  {  // row
        for (int i = 0; i < dimx; ++i) { // column
            image[dimx*j+i].red = 255;
            image[dimx*j+i].green = 255;
            image[dimx*j+i].blue = 255;
            
             image[dimx*i+j].red = 255;
            image[dimx*i+j].green = 255;
            image[dimx*i+j].blue = 255;
        }

    }*/

    //write the file

    

    
  /*  
    imageFile.write(reinterpret_cast<char*>(&image), 3*image_size*image_size);
    imageFile.close();
    cout << "image created: " << filename << endl;
    return filename;   
    }
*/


void drawX(int** pic, int Ioffset, int Joffset, int size){
    int x,y;
    int diff = Joffset-Ioffset;
    if (diff<0) {diff = diff*(-1);}
   
    for(x=Ioffset;x<(Ioffset+size);x++){
        for(y=Joffset;y<(Joffset+size);y++){
            if((x-y)==diff||(y-x)==diff||(x-Ioffset)+(y-Joffset)+1==size)
                pic[x][y] = 0;
        }
    }
}

void drawO(int** pic, int Ioffset, int Joffset, int size){
    int x,y;
    
    int r;
    if(size%2==0){
        r=size/2;
    }
    else{
        r=(size/2)+1;
    }
    int center_x=r+Ioffset, center_y=r+Joffset;
    double t;
    for(t = 0; t < 2*M_PI; t+=0.01){
            x = (int) (sin(t) * r);
            y = (int) (cos(t) * r);
            pic[x + center_x][y + center_y]=0;
    }
}

void drawBL(int** pic, int pic_s, int size){
    for(int i=0;i<pic_s;i+=size){
        for(int j=0;j<pic_s;j++){
            pic[i][j] = 0;
        }
    }
    for(int i=0;i<pic_s;i+=size){
        for(int j=0;j<pic_s;j++){
            pic[j][i] = 0;
        }
    }
}

string Board :: draw(const unsigned int pic_size){
   
    string name =get_name();
    
    int board_size = this->size();
    int sign_size = pic_size/board_size;
    int** pic;
    
    pic = new int*[pic_size];
    for (int i = 0; i < pic_size; ++i)
        pic[i] = new int[pic_size];
       
    for(int i=0;i<pic_size;i++){
        for(int j=0;j<pic_size;j++){
            pic[i][j] = 255;
        }
    }
    ofstream imageFile(name, ios::out | ios::binary);
    imageFile << "P6" << endl << to_string(pic_size) <<" " << to_string(pic_size) << endl << 255 << endl;
   
    
    
    
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            drawBL(pic,pic_size,sign_size);
            if(this->gameBoard[i][j]=='X'){
                drawX(pic,i*sign_size,j*sign_size,sign_size);
            }
            else if(this->gameBoard[i][j]=='O'){
                drawO(pic,i*sign_size,j*sign_size,sign_size);
            }
            
        }
        cout << endl;
    }
    
    RGB image[pic_size*pic_size];
    
    for(int i=0;i<pic_size;i++){
        for(int j=0;j<pic_size;j++){
            
            image[i*pic_size+j].red = pic[i][j];
            image[i*pic_size+j].green = pic[i][j];
            image[i*pic_size+j].blue = pic[i][j];
          
        }
    }
    for(int i=0; i < pic_size; i++){ 
        delete [] pic[i];
    }
    
    delete [] pic;
    
    imageFile.write(reinterpret_cast<char*>(&image), 3*pic_size*pic_size);
    imageFile.close();
    return name;
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
/*
void Board :: print_X(const int row_cor, const int col_cor , const int image_size , int** image){
    cout << "create X" << endl;
    int bound = image_size / boardSize;
    
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            //cout <<i<<','<<j<<';'<<i*sign_size<<','<< j*sign_size<<';'<<endl;
            if((this-> gameBoard[i][j])=='X'){
                int ib = i*bound;
                int jb = j*bound;
                int diff = jb - ib;
                if (diff < 0) {diff = diff*(-1);}
                for(int x=ib; x<(ib+bound);x++){
                    for(int y=jb; y<(jb+bound);y++){
                        if(/*(x-y)==diff||(y-x)==diff||*///(x-ib)+(y-jb)==bound)
                           // image[(bound*row_cor)+x][(bound*row_cor)+x] = 150;
                        }
                        /*image[(bound*row_cor)+row][(bound*row_cor)+row] = 255;
            
                        image[(bound*(row_cor+1))-row][(bound*row_cor)+row] = 255;   */ 
                    
                }
            }
        }
    }
    */
    
    /*
    for(int row = 1; row < bound-1; ++row){
        image[(bound*row_cor)+row][(bound*row_cor)+row] = 255;
        
        image[(bound*(row_cor+1))-row][(bound*row_cor)+row] = 255;
    }*/
    
    
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
/*void Board :: print_O(const int row_cor, const int col_cor , const int boarder_size , int** image){
    cout << "create O" << endl;
    int x_mid = row_cor*boarder_size + boarder_size/2;
    int y_mid = col_cor*boarder_size + boarder_size/2;
    int r = (boarder_size/2)-2;
    for (int j = 1; j < boarder_size; ++j)  {  // row
        for (int i = 1; i < boarder_size; ++i) { // column
            int dx = x_mid -((board_size*row_cor)+j); // horizontal offset
            int dy = y_mid -((bound*col_cor)+i); // vertical offset
            if ( (dx*dx + dy*dy) <= (r*r) ) image[j][i] = 255;
        }
    }
}
    */
