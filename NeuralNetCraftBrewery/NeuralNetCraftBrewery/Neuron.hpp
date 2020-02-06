//
//  Neuron.hpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 8/21/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#ifndef Neuron_hpp
#define Neuron_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Neuron{
public:
    
    Neuron(double val);
    
    void setVal(double v);
    
    // Fast Sigmoid Function; given a neuron value, id like to determine an activation where F(x) = x / (1 + |x|)
    void activate();
    
    // Derivative for fast sigmoid function; f'(x) = F(x) * (1-F(x))
    void derive();
    
    //getters
    double getVal() {return this->val; }
    double getActivatedVal() {return this->activatedVal; }
    double getDerivedVal(){return this->derivedVal; }
    
    
private:
    //current value of the neuron
    double val;
    //squishes current value to a value between 0-1.  Like normalization & makes it easier to compute
    double activatedVal;
    //approximate derivative of the activated value.  For training
    double derivedVal;
};


#endif /* Neuron_hpp */
