//
//  MultiplyMatrix.cpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 11/7/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#include "MultiplyMatrix.hpp"

utils::MultiplyMatrix::MultiplyMatrix(Matrix *a, Matrix *b){
    this->a = a;
    this->b = b;
    
    if(a->getNumCols() != b->getNumRows()){
        cerr << a->getNumRows() << "a != " << b->getNumCols() << "b" << endl;
        assert(false);
    }
    this->c = new Matrix(a->getNumRows(), b->getNumCols(), false);
    
}
//testcode input
Matrix *utils::MultiplyMatrix::execute(){
    for(int i = 0; i < a->getNumRows(); i++){
        for(int j = 0; j < b->getNumCols(); j++){
            for(int k = 0; k < b->getNumRows(); k++){
                double p = this->a->getValue(i, k) * this->b->getValue(k, j);
                double newVal = this->c->getValue(i, j) + p;
                this->c->setValue(i, j, newVal);
            }
        }
    }
    
    return this->c;
}

