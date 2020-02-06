//
//  NeuralNetwork.hpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 8/25/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Matrix.hpp"
#include <algorithm>
#include "Layer.hpp"
#include "MultiplyMatrix.hpp"
#include <vector>

using namespace std;

class NeuralNetwork{
public:
    NeuralNetwork(vector<int> topology);
    void setCurrentInput(vector<double> input);
    void setCurrentTarget(vector<double> target) { this->target = target; };
    void printToConsole();
    void feedForward();
    void backPropogation();
    void setError();
    
    Matrix *getNeuronMatrix(int index) {return this->layers.at(index)->matrixifyVals();};
    Matrix *getActivatedNeuronMatrix(int index) {return this->layers.at(index)->matrixifyActivatedVals();};
    Matrix *getDerivedNeuronMatrix(int index) {return this->layers.at(index)->matrixifyDerivedVals();};
    Matrix *getWeightMatrix(int index) {return this->weightMatrices.at(index);};
    
    void setNeuronValue(int layer_index,  int neuro_index, double val){this->layers.at(layer_index)->setVal(neuro_index, val);}
    void printInputToConsole();
    void printOutputToConsole();
    void printTargetToConsole();
    void printHistoricalErrors();
    
    double getTotalError() {return this->error;}
    vector<double> getErrors() {return this->errors;}
    
private:
    int topologySize;
    vector<int> topology;
    vector<Layer *> layers;
    vector<Matrix *> weightMatrices;
    vector<Matrix *> gradientMatrices;
    vector<double> input;
    vector<double> target;
    double error;
    vector<double> errors;
    vector<double> pastErrors;
};

#endif /* NeuralNetwork_hpp */
