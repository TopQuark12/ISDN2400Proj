/**
 * @file        pressure.c
 * @author      Wong Tat Hang (Alex)    thwongaz@connect.ust.hk
 * @brief       parse pressure measurement data and produce pressure
 *              dependent modifier meshes
 * @note        openSCAD has to be installed and added to PATH
 * @date        28/4/2019
 * 
 * @copyright   Copyright (c) 2019
 */

#include "pressure.hpp"
#include "main.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int pressureGen() {

    ifstream presMap;
    presMap.open("input/pressureMap.txt", ios::in);
    #ifdef DEBUG_BUILD
    if(presMap.is_open()) {
        cout << "Pressure map found and opened \n";
    } else {
        cout << "Pressure map not found! \n";
        return 1;
    }
    #endif
    vector<vector<int>> map;
    string line;
    while (getline(presMap, line)) {
        map.push_back({});
        istringstream iss(line);
        int num;
        while(iss >> num){
            map.back().push_back(num);
        }
    }
    #ifdef DEBUG_BUILD
    for (auto i = map.begin(); i != map.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            cout << *j << '\t';
        }
        cout << '\n';
    }
    #endif
    presMap.close();
    return 0;
}