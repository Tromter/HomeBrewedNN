//
//  Neuron.cpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 8/21/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//


#include "Neuron.hpp"
#include <cmath>

using namespace std;

//Constructor

Neuron::Neuron(double val){
    this->val = val;
    activate();
    derive();
}

void Neuron::setVal(double val){
    this->val = val;
    activate();
    derive();
}


void Neuron::activate() {
    this->activatedVal = (this->val / (1+ abs(this->val)));
}

void Neuron::derive(){
    this->derivedVal = this->activatedVal * (1 - this->activatedVal);
}
