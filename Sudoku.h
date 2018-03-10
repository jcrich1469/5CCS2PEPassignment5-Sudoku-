#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include<vector>
#include<set>
#include<iostream>
#include<cmath>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::iterator;
using std::sqrt;

// TODO: Your Sudoku class goes here:


class Sudoku : public Searchable{

	protected:
	long boardSize;
	long boardRoot;
	vector<vector<set<int>>> board;// row column partition of the input value
	vector<vector<int>> placedValues;
	
	public:


	Sudoku(const long& sizeIn){
		
		double rootIn = sqrt(sizeIn);
		
		if((rootIn - rootIn) == 0){// is the root an integer?
			
			boardSize = sizeIn;
			boardRoot = rootIn;			

		}
		
		for(int i = 0; i< sizeIn;++i){// now for the rows.
		
			vector<set<int>>row;

			for(int j = 0;j<sizeIn;++j){// now for each set attach n values;

				set<int> numbers;

				for(int k = 1; k<=sizeIn; ++k){
					
					numbers.insert(k);					
					
				}
				
		
				row.push_back(numbers);			
				
			}	
		
			board.push_back(row);	
				
		}

		
		for(int i = 0; i< sizeIn;++i){
				
			vector<int>rowInts;

			for(int j = 0;j<sizeIn;++j){

				rowInts.push_back(0);		
				
			}
			
			placedValues.push_back(rowInts);		
		}

	}
	
	/**
	~Sudoku(){
		
		for(int i = 0; i<boardSize;++i){
			
			for(int j = 0; j<boardSize;++j){
				
				
				// delete all the sets???				
								
			
			}			
			
		}
		
	}*/
	
	/**
	*Now going setting the square
	*/
	
	bool setSquare(const int row, const int col, const int value){// return false???Must return false
		
		
		// assume he values 0-8 for now.
		int currentNum;
		//i.e size 9 = range 0->8
		if((row<0 || row>boardSize-1)||(col<0 || col>boardSize-1)){
			
			cout<<"invalid row and column entry for square"<<endl;
			return false;			
			
		}
		//1->9
		if(value<1 || value>boardSize){
			
			cout<<"invalid input value"<<endl;
			return false;
		}

		// place the value first and then remove around that value.
		
		putInSet(row,col,value);// place in that set.... so it is a singleton.
		//testing
		removeFromSquare(row,col,value);
		removeFromRow(row,col,value);
		removeFromColumn(row,col,value);
		//the LOOP lets do it their; way.
		//int currentNum = 0;

		// while sets become smaller.
		//bool isRemoved = true;
//		
			
		// it can get in.
		/**
		while(isRemoved){// keep looping until we do not remove anymore.
		
			
			isRemoved = false;
			// watch out for managing these booleans.
		*/
		// looking for unplaced singletons.
		bool boardIsChanged = true;

		while(boardIsChanged){

			boardIsChanged = false;

			for(int i = 0; i<boardSize;++i){
				
				for(int j = 0; j<boardSize;++j){
					
					//cout<<"row: "<<j<<" column: "<<i<<endl;

					set<int>& currentSet = board[i][j];
				
					if(currentSet.size() == 1){
						
						set<int>::iterator rowSetIter = currentSet.begin();		
						currentNum = *rowSetIter;
						
						//cout<<"num"<currentNum<<<endl;
						
						if(removeFromSquare(j,i,currentNum) || removeFromRow(j,i,currentNum) || removeFromColumn(j,i,currentNum)){

							//cout<<"was true"<<endl;	

							boardIsChanged = true;

						}
					}
					
					if(currentSet.size()==0){
							
						return false;
					
					}
				}
			}
		}

		//cout<<"left loop"<<endl;

		placedValues[col][row] = value;
		

		return true;
	}

	private:void putInSet(const int& row, const int& column, const int& value){

		set<int>& rowSet = board[column][row];


		rowSet.clear();
		rowSet.insert(value);

	}
	
	private:bool removeFromSquare(const int& row, const int& column, const int& value){
		
		int subRow = row%boardRoot;// get the modulus of row and column
		int subColumn = column%boardRoot;// get the modulus of row and column		
		int startColumn = column - subColumn;// i.e. column = 4, so 4mod3 = 1, = 3... 8-2 = 6 etc.
		int startRow = row - subRow;
		
		//vector<set<int>>& currentColumn;
		//set<int>& currentSet;
		//col = 7, row = 2
		//->1,2
		//subCol = 6, ro = 0 = tl.
		//
		//cout<<"tl col ="<<startColumn<<"tl row ="<<startRow<<endl;
		bool isRemoved = false;
		for(int i = startColumn; i < startColumn+boardRoot; ++i){// columns then rows...6->8
			
			//board[x][y]

			for(int j = startRow; j<startRow+boardRoot; ++j){
				
				//cout<<"current col ="<<i<<"current row ="<<j<<endl;
				set<int>& currentSet = board[i][j];//x,y column,row.
	
						
				if(i != column && j != row){
					
					removeFromSet(i,j,value,currentSet);
					
					if(removeFromSet(j,i,value,currentSet)){// if this is true...
						// then make this true.
						isRemoved = true;					
								
					}
					
				}	
						
							
			}
			
			
		}	
		return isRemoved;// nothing changed.	

	}
	
	private:bool removeFromRow(const int& row, const int& column, const int& value){	
		
		bool isRemoved = false;
		for(int i = 0;i<boardSize;++i){// iterating through the columns, ironically.
			
			set<int>& currentSet = board[i][row];// always at the same row of our values row.
			
			if(i!=column){// row will be the same, goes in row.
				//removeFromSet(row,i,value,currentSet);
					
				if(removeFromSet(row,column,value,currentSet)){
					
					isRemoved = true;					
								
				}
					
			}	
				
		}
		
		return isRemoved;
	}
		
	private:bool removeFromColumn(const int& row, const int& column, const int& value){

		
		//set<int>& currentRow;
		//cout<<"checking column"<<column<<endl;
		
		bool isRemoved = false;

		for(int i = 0; i<boardSize;++i){// iterating through the rows.
			set<int>& currentRow = board[column][i];
			if(i != row){
				// column will be the same.
				//removeFromSet(i,column,value,currentRow);
					
				if(removeFromSet(row,column,value,currentRow)){
					
					isRemoved = true;					
								
				}
					
			}				
			
		}// keep going through the rows anyway.
		
		return isRemoved;
			
	}
	
	
	
	private: bool removeFromSet(const int& row, const int& column, const int& value, set<int>& numSet){
		
		//bool isRemoved = false;
		for(int number: numSet){
			
			if(value == number){// only one identifiable number with the value in the set.

				//cout<<"found:"<<number<<"and"<<value<<endl;
				
				numSet.erase(value);// removing value.
				// possible boolean here???
				//cout<<"remaining"<<endl

				
				return true;
			}
							
			
		}
		/**
		cout<<"remaining:";
		for(int number: numSet){
			
			cout<<number<<",";			
			
		}
		cout<<endl;*/
		return false; // value not in there.
		
		//cout<<"failed the set test, value != to any element in set: "<<value<<endl
		
	}
	






	public: int getSquare(const int& row, const int& col)const{
		
		if((row<0 || row>boardSize-1)||(col<0 || col>boardSize-1)){
			
			cout<<"invalid row and column entry for square"<<endl;
			return -1;			
			
		}
		vector<set<int>> rowsVector = board[col];

		set<int> rowSet = rowsVector[row];
		
		set<int>::iterator rowSetIter = rowSet.begin();

		int value = *rowSetIter;

		if(rowSet.size() == 1){// can only have one actual value, can only get size == to 1

			//int value = rowSet.get();
			

			if(value >= 1 && value <= boardSize){
			
				return value;			
			
			}		
		
		}
		// if greater than one, then not entered???
		/*
		if(rowSet.size()>0){
			for(int num: rowSet){
				num = *rowSetIter;
				cout<<"getting number "<<num<<endl;
				++rowSetIter;
			}
			
		} else {
			
			cout<<"no numbers"<<endl;			
					
		}
		*/
		return -1;
	}

	
	public: void printGrid()const{
			
		for(int i = 0; i< boardSize;++i){
			cout<<"[";
			for(int j = 0; j<boardSize;++j){
				
				cout<<placedValues[j][i]<<",";				
			
			}
					
		cout<<"]"<<endl;
		}		
			
	}

	public: void printBoard()const{
		
		// we are looking for what is already used.
		//set<int> comparisonSet;
		// get the set of each square, and print the missing value.
		
		cout<<"making grid sets"<<endl;
		for(int i = 0; i< boardSize; ++i){
			cout<<"row"<<i;
			for(int j = 0; j<boardSize; ++j){
				
				set<int> rowSet = board[j][i];
				cout<<"{";
				for(int num : rowSet){
				
					cout<<num<<",";			
			
				}
				
				cout<<"},";
	
			}			
			cout<<endl;		
		}
		cout<<endl;
		for(int i = 0; i<boardSize; ++i){
			
			for(int j =0; j<boardSize; ++j){
				set<int> numSet = board[j][i];
				
				//cout<<"i ="<<i<<", j ="<<j<<"size:"<<board.size();
				if(numSet.size() == 1){
					
					cout<<getSquare(i,j);
				//} else if(board[i][j]){
					
									
				} else if(numSet.size() <= 8){
					
					cout<<"/";				
				
				} else {
					
					cout<<"x";					
									
				}
			}			
			cout<<endl;
		}		
		
	}

	// PART 5C
	
	public:
	/**
	*	checking if the board was solved.
	*/
	
	virtual bool isSolution() const override{
		
		
		set<int> currentSet;
		for(int i = 0; i<boardSize;++i){
			
			for(int j = 0; j<boardSize;++j){
				
				currentSet = board[j][i];// GOING ACROSS FIRST

				if(currentSet.size() != 1){
					//cout<<"unsolved"<<endl;
					return false;					
					
				}
											
			}			
			
		}
		//cout<<"solved"<<endl;
		return true;

	}    

    	virtual vector<unique_ptr<Searchable> > successors() const override{
		//WATCHOUT FOR CONST
		// maybe need a pointer.
		//int atRow = 0;

		//bool isFirstRow = false;
		vector<unique_ptr<Searchable> > possibleBoards;
		
		unique_ptr<Searchable> uBoardPtr;
		//set<int>* setPtr;
		//vector<set<int>> column;
		//set<int> rowSet;
		//Sudoku* copyBoard = nullptr;
		bool isSolvable = false;
		//FIND THE LEFTMOST SQUARE FOR EACH SET GREATER THAN ONE....
		int leftMostColgtOne = 0;
		bool foundOnRow = false;
		int jCol = 0;
		int iRow =0;
		//cout<<"method entered"<<endl;


		for(int i = 0; i<boardSize;++i){

			for(int j = 0; j<boardSize;++j){// get each column

				if(board[j][i].size() > 1){
					
					//cout<<"column = "<<j<<" row = "<<i<<endl;
					jCol = j;
					iRow = i;
					i == boardSize;
					break;
				}
			}
		}

		for(int numTest : board[jCol][iRow]){
			//cout<<"currentNum"<<numTest<<endl;
			Sudoku* copyBoard = new Sudoku(*this);

						
			isSolvable = copyBoard->setSquare(iRow,jCol,numTest);// for each number at the given co-ordinate.row,col,value
						
			if(isSolvable){

				//cout<<"isSolvable = "<<isSolvable<<endl;
				uBoardPtr.reset(copyBoard);
							//uBoardPtr->printBoard();
							// constantly being added. so never nullptr, in line with not empty.
				possibleBoards.push_back(std::move(uBoardPtr));
							//cout<<"pointers in vector"<<possibleBoards.size()<<endl;
						
			} else {
				//cout<<"isNotSolvable = "<<isSolvable<<endl;
				delete copyBoard;// deletes our boardPtr										
			}	

		}
		// end condition
		//cout<<"returning"<<endl;
		return possibleBoards;// if we found one, and then did stuff to it, this should all end automatically.
							
		//end forloop
	}
	
		
    	virtual void write(ostream & o)const override{
		
		//printBoard();			
		
	}

    	
    	virtual int heuristicValue() const override {// for now.
        	// what is this???
		
		if(!isSolution()){

			int count = 0;

			for(int i = 0; i<boardSize ;++i){
				
				for(int j = 0; j<boardSize ;++j){
					
					if(placedValues[j][i] != 0){// value was place there.
					
						++count;						
			
					}					
				
				}				
							
			}
			//cout<<"Returning count for h:"<<count<<endl;
			return count;
		} 
		//cout<<"Solved, h = 0"<<endl;
		return 0;			
				
   	}
	
};


#endif
