#pragma once
#include "place.hpp"

struct RGB {
  unsigned int red, green, blue;
public:
  RGB(): red(0), green(0), blue(0){}
  RGB(unsigned int red, unsigned int green, unsigned int blue): red(red), green(green), blue(blue) {}
};

struct pairs{
    int first; //row
    int second; //column
};

class Board{
public:
    place** gameBoard;
    int boardSize;
    
    Board();
    Board(Board&);
    Board(int); 
    ~Board();
    
    void alloc();
    void dlloc();
    int size() const;
    
    string draw(const unsigned int);
    string get_name()const;
    void print_X(const int , const int , const int , RGB*);
    void print_O(const int , const int , const int , RGB*);
	
    friend ostream& operator<<(ostream& os, const Board& b); //input
    friend istream &operator>>(istream& input, Board& b);
    
    Board& operator= (Board&);
    char operator= (char);
    friend bool operator== (const Board&, const Board&);
    friend bool operator!= (const Board&, const Board&);

    place& operator[] (const pairs);
    place operator [] (pairs index) const;
    

    void fill(char);
};

    inline ostream& operator<< (ostream& os, const Board& b){
		for(int rows = 0; rows < b.boardSize; rows++){
			for(int columns = 0; columns < b.boardSize; columns++ ){
				os << (b.gameBoard[rows][columns]).get_sign();
			}
			os << endl;
		}
		
        return os;
    }
 
    inline istream &operator>> (istream& input, Board& b) { 
     	 string line;
    	 input >> line;
	     //initial new board
	     b.dlloc();
         b.boardSize = line.size();
         b.gameBoard = new place*[b.boardSize];
         for(int rows = 0; rows < b.boardSize; rows++){
    	     b.gameBoard[rows] = new place[b.boardSize];
    	        //fill each line in the board
         	     for(int columns = 0; columns < b.boardSize; columns++)
        	        b.gameBoard[rows][columns] = line.at(columns);
             input >> line;
         }
         return input;            
      }