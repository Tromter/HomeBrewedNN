//
//  MatrixToVector.cpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 11/7/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#include "MatrixToVector.hpp"

utils::MatrixToVector::MatrixToVector(Matrix *a){
    this->a = a;
}

vector<double> *utils::MatrixToVector::execute(){
    
    for(int r = 0; r < a->getNumRows(); r++){
        for(int c = 0; c < a->getNumCols(); c++){
            this->result->push_back(a->getValue(r, c));
        }
    }
    return this->result;
}

