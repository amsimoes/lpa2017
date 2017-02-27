#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

void readInput(){
    int op_number;
    std::cin >> op_number;
    std::cout << "Operations number: " << op_number << " ";
    std::vector<std::pair<double,int> > machines;
    double prob;
    int cost;
    for(int i=0; i<op_number; i++){
        std::cin >> prob >> cost;
        machines.push_back(std::make_pair(prob,cost));
        std::cout << "Probability: " << machines.at(i).first << " " << "Cost: " << machines.at(i).second << "\n";
    }
    int success;
    std::cin >> success;
    std::cout << "Success rate: " << success;
}

int main(void){
    readInput();
}
