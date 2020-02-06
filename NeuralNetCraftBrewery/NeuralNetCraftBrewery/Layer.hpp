//
//  Layer.hpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 8/25/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#ifndef Layer_hpp
#define Layer_hpp

#include <stdio.h>
#include <iostream>
#include "Neuron.hpp"
#include <vector>
#include "Matrix.hpp"

using namespace std;

class Layer
{
public:
    Layer(int size);
    
    void setVal(int i, double v);
    
    Matrix *matrixifyVals();
    Matrix *matrixifyActivatedVals();
    Matrix *matrixifyDerivedVals();
    
    vector<Neuron *> getNeurons() {return this->neurons;};
    void setNeurons(vector<Neuron *> neurons){this->neurons = neurons;};
private:
    int size;
    
    vector<Neuron *> neurons;
};

#endif /* Layer_hpp */
