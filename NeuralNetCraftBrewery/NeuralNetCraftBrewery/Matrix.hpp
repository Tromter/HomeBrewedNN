//
//  Matrix.hpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 8/25/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Matrix{
public:
    Matrix(int numRows, int numCols, bool isRandom);
    
    double generateRandomNumber();
    
    Matrix *transpose();
    
    void setValue(int r, int c, double v){ this->values.at(r).at(c) = v; }
    double getValue(int r, int c){ return this->values.at(r).at(c); }
    
    void printToConsole();
    
    int getNumRows() {return this->numRows;};
    int getNumCols() {return this->numCols;};
private:
    vector< vector<double> > values;
    
    int numRows;
    int numCols;
    
    
};


#endif /* Matrix_hpp */
