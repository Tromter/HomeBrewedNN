//
//  main.cpp
//  NeuralNetCraftBrewery
//
//  Created by Turner Romey on 8/21/19.
//  Followed the Development Log from DevLogs for Creating a C++ Neural Network
///DevLog :: www.youtube.com/channel/UCg9rw36CJztvSEjmei0hSPQ
// For NYU Tandon MLC use and other instructional purposes; shared with club to understand Neural Network Fundamentals


//1:: Implement a Neuron Class that has the capability of accepting a double new_value, changing new_val to an activated_val, and changing activated_val to the derived_val.  Functions are used to activate new_value using the fast signmoid function (forces new_value to be from 0-1) and to get derived_val of activated_val (using derivative of fast sigmoid function).

//2:: Implement Layer, Matrix, and Neural Network Classes to store, modify, and accept Neurons

//3:: Update and Feed Forward Functions in Neural Network

//4:: Determining a Neural Networks Error by creating a setError method in the NeuralNetwork class

//5:: Implement Back-Propogation and Training the Neural Network

//6:: Implement Quadratic Cost Function and Validating Back Propogation





#include <iostream>
#include "Neuron.hpp"
#include "Matrix.hpp"
#include "NeuralNetwork.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    //Test code;
    //1::
//    cout << "Hello, World!\n";
//    cout << endl;
//    cout << "Test Val for Neuron: " << endl;
//    double test;
//    cin >> test;
    
    //2::
//    Matrix *m = new Matrix(3, 2, true);
//    m->printToConsole();
//
//    cout << "====================" << endl;
//
//    Matrix *mT = m->transpose();
//    mT->printToConsole();
    
    //build display 1::
//    Neuron *n = new Neuron(test);
//    cout << endl;
//    cout << "Val: " << n->getVal() << endl;
//    cout << "Activated Val: " << n->getActivatedVal() << endl;
//    cout << "Derived Val: " << n->getDerivedVal() << endl;
//

    //3:: - 6::
    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);
    
    vector<double> input;
    input.push_back(1);
    input.push_back(0);
    input.push_back(1);
    
    NeuralNetwork *nn = new NeuralNetwork(topology);
    
    nn->setCurrentInput(input);
    nn->setCurrentTarget(input);
    
    // training process
    for (int i = 0; i <= 1000; i++){
        cout << "Epoch: " << i << endl;
        nn->feedForward();
        nn->setError();
        cout << "Total Error: " << nn->getTotalError() << endl;
        nn->backPropogation();
        
        cout << "================" << endl;
        cout << "OUTPUT: ";
        nn->printOutputToConsole();
        
        cout << "INPUT: ";
        nn->printInputToConsole();
        
        cout << "TARGET: ";
        nn->printTargetToConsole();
        cout << "================" << endl;
        cout << endl;
    }
   
    //Export to Excel to see graph of training
    //nn->printHistoricalErrors();
    
    return 0;
}
