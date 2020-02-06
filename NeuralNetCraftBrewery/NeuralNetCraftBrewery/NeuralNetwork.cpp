//
//  NeuralNetwork.cpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 8/25/19.
//  Copyright © 2019 Turner Romey. All rights reserved.
//

#include "NeuralNetwork.hpp"


void NeuralNetwork::backPropogation(){
        
    vector<Matrix *> newWeights;
    Matrix *gradient;
    
    // output to hidden
    
    int outputLayerIndex = this->layers.size() - 1;
    Matrix *derivedValsYtoZ = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
    Matrix *gradientsYtoZ = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);
    cout << "errors " <<this->errors.size() << endl;
    for(int i = 0; i < this->errors.size(); i++){
        double d = derivedValsYtoZ->getValue(0, i);
        double e = this->errors.at(i);
        double g = d * e;
        gradientsYtoZ->setValue(0, i, g);
    }
    
    int lastHiddenLayerIndex = outputLayerIndex - 1;
    Layer *lastHiddenLayer = this->layers.at(lastHiddenLayerIndex);
    Matrix *weightsOutputToHidden = this->weightMatrices.at(outputLayerIndex - 1);
    Matrix *deltaOutputToHidden = (new utils::MultiplyMatrix(gradientsYtoZ->transpose(), lastHiddenLayer->matrixifyActivatedVals()))->execute()->transpose();
    
    Matrix *newWeightsOutputToHidden = new Matrix(deltaOutputToHidden->getNumRows(), deltaOutputToHidden->getNumCols(), false);
    
    for(int r = 0; r < deltaOutputToHidden->getNumRows(); r++){
        for(int c = 0; c < deltaOutputToHidden->getNumCols(); c++){
            double originalWeight = weightsOutputToHidden->getValue(r, c);
            double deltaWeight = deltaOutputToHidden->getValue(r, c);
            newWeightsOutputToHidden->setValue(r, c, (originalWeight - deltaWeight));
        }
    }
    
    newWeights.push_back(newWeightsOutputToHidden);
    gradient = new Matrix(gradientsYtoZ->getNumRows(), gradientsYtoZ->getNumCols(), false);
    
    for(int r = 0; r < gradientsYtoZ->getNumRows(); r++){
        for(int c = 0; c < gradientsYtoZ->getNumCols(); c++){
            gradient->setValue(r, c, gradientsYtoZ->getValue(r, c));
                               
        }
    }
    
    
    
    for(int i = (outputLayerIndex - 1); i > 0; i--){
        Layer *l = this->layers.at(i);
        Matrix *derivedHidden = l->matrixifyDerivedVals();
        Matrix *activatedHidden = l->matrixifyActivatedVals();
        Matrix *gradientsDerived = new Matrix(1, l->getNeurons().size(), false);
        
        Matrix *weightMatrix = this->weightMatrices.at(i);
        Matrix *originalWeight = this->weightMatrices.at(i - 1);
        
        for(int r = 0; r < weightMatrix->getNumRows(); r++){
            double sum = 0;
            for(int c = 0; c < weightMatrix->getNumCols(); c++){
                double p = gradient->getValue(0, c) * weightMatrix->getValue(r, c);
                sum += p;
            }
            
            double grad_val = sum * activatedHidden->getValue(0, r);
            gradientsDerived->setValue(0, r, grad_val);
        }
        Matrix *leftNeurons = (i - 1) == 0 ? this->layers.at(0)->matrixifyVals() : this->layers.at(i - 1)->matrixifyActivatedVals();
        Matrix *deltaWeights = (new utils::MultiplyMatrix(gradientsDerived->transpose(), leftNeurons))->execute()->transpose();
        
        Matrix *newWeightsHidden = new Matrix(deltaWeights->getNumRows(), deltaWeights->getNumCols(), false);
        
        for(int r = 0; r < newWeightsHidden->getNumRows(); r++){
            for(int c = 0; c < newWeightsHidden->getNumCols(); c++){
                double w = originalWeight->getValue(r, c);
                double d = deltaWeights->getValue(r, c);
                double n = w - d;
                newWeightsHidden->setValue(r, c, n);
            }
        }
        
        newWeights.push_back(newWeightsHidden);
        gradient = new Matrix(gradientsDerived->getNumRows(), gradientsDerived->getNumCols(), false);
        
        for(int r = 0; r < gradientsDerived->getNumRows(); r++){
            for(int c = 0; c < gradientsDerived->getNumCols(); c++){
                gradient->setValue(r, c, gradientsDerived->getValue(r, c));
            }
        }
        
        
        
    }
    
    reverse(newWeights.begin(), newWeights.end());
    this->weightMatrices = newWeights;
}

void NeuralNetwork::setCurrentInput(vector<double> input){
    this->input = input;
    
    for(int i = 0; i < input.size(); i++){
        this->layers.at(0)->setVal(i, input.at(i));
    }
}


void NeuralNetwork::feedForward(){
    for(int i = 0; i < (this->layers.size() - 1); i++){
        Matrix *a = this->getNeuronMatrix(i);
        
        if(i != 0){
            a = this->getActivatedNeuronMatrix(i);
        }
        Matrix *b = this->getWeightMatrix(i);
        Matrix *c = (new utils::MultiplyMatrix(a, b))->execute();
        
       // vector<double> vals;
        for(int c_index = 0; c_index < c->getNumCols(); c_index++){
            //vals.push_back(c->getValue(0, c_index));
            this->setNeuronValue(i+1, c_index, c->getValue(0, c_index));
        }
    }
}

void NeuralNetwork::printToConsole(){
    for(int i = 0; i < this->layers.size(); i++){
        cout<< "LAYER: " << i << endl;
        if(i == 0){
            Matrix *m = this->layers.at(i)->matrixifyVals();
            m->printToConsole();
        }
        else{
            Matrix *m = this->layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }
        cout << "===========================" << endl;
        if(i < this->layers.size() - 1){
            cout << "Weight Matrix: " << i << endl;
            this->getWeightMatrix(i)->printToConsole();
        }
        cout << "===========================" << endl;
        
        
    }
}

void NeuralNetwork::setError(){
    if(this->target.size() == 0){
        cerr<< "No target for this neural network" << endl;
        assert(false);
    }
    
    if(this->target.size() != this->layers.at(this->layers.size() - 1)->getNeurons().size()){
        cerr << "Target size is not the same as output layer size: " << this->layers.at(this->layers.size() - 1)->getNeurons().size() << endl;
        assert(false);
    }
    
    this->error = 0.00;
    this->errors.clear();
    int outputLayerIndex = this->layers.size() - 1;
    vector<Neuron *> outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();
    for (int i = 0; i < target.size(); i++){
        //cost function
        //(Simple Difference)
        double tempErr = (outputNeurons.at(i)->getActivatedVal() - target.at(i));
        //double tempErr = (target.at(i) - outputNeurons.at(i)->getActivatedVal());
        //(Quadratic Cost Function)
        //double tempErr = (outputNeurons.at(i)->getActivatedVal() - target.at(i));
        
        errors.push_back(tempErr);
        this->error += pow(tempErr, 2);
    }
    
    this->error = 0.5 * this->error;
    
    pastErrors.push_back(this->error);
    
}

void NeuralNetwork::printInputToConsole(){
    for(int i = 0; i < this->input.size(); i++){
        cout << this->input.at(i) << "\t";
    }
    cout << endl;
}

void NeuralNetwork::printTargetToConsole(){
    for(int i = 0; i < this->target.size(); i++){
        cout << this->target.at(i) << "\t";
    }
    cout << endl;
}

void NeuralNetwork::printOutputToConsole(){
    int indexOfOutput = this->layers.size() - 1;
    Matrix *outputValues = this->layers.at(indexOfOutput)->matrixifyActivatedVals();
    for(int c = 0; c < outputValues->getNumCols(); c++){
        cout << outputValues->getValue(0, c) << "\t";
    }
    cout << endl;
}

void NeuralNetwork::printHistoricalErrors(){
    for(int i = 0; i < this->pastErrors.size(); i ++){
        cout << this->pastErrors.at(i);
        if(i != this->pastErrors.size() - 1){
            cout << ',';
        }
    }
    cout << endl;
}


NeuralNetwork::NeuralNetwork(vector<int> topology){
    this->topology = topology;
    this->topologySize = topology.size();
    for(int i = 0; i < topologySize; i++){
        Layer *l = new Layer(topology.at(i));
        this->layers.push_back(l);
    }
    for(int i = 0; i < (topologySize - 1); i++){
        Matrix *m = new Matrix(topology.at(i), topology.at(i + 1), true);
        this->weightMatrices.push_back(m);
    }
};

