#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <time.h>

void readInput(){
    int op_number;
    double prob;
    int cost;
    int budget;
    std::cin >> op_number;
    //std::cout << "Operations number: " << op_number << "\n";
    std::vector<std::pair<double,int> > machines; 
    for(int i=0; i<op_number; i++){
        std::cin >> prob >> cost;
        machines.push_back(std::make_pair(prob,cost));
        //std::cout << "Probability: " << machines.at(i).first << " " << "Cost: " << machines.at(i).second << "\n";
    }
    std::cin >> budget;
    //std::cout << "Budget: " << budget << "\n";
}

int main(void){
    std::ios::sync_with_stdio(false);
    readInput();
    return 0;
}
