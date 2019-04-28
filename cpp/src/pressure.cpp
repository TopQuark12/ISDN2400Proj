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
#include <algorithm>

using namespace std;

int pressureGen() {

    ifstream presMap;
    presMap.open("input/pressureMap.txt", ios::in);
    if(presMap.is_open()) {
        cout << "Pressure map found and opened \n";
    } else {
        cout << "Pressure map not found! \n";
        return 1;
    }
    vector<vector<int>> map;
    vector<int> lineLength;
    string line;
    int numLine = 0;
    while (getline(presMap, line)) {
        numLine++;
        map.push_back({});
        istringstream iss(line);
        int num;
        while(iss >> num){
            map.back().push_back(num);
        }
        lineLength.push_back(map.back().size());
    }
    if (numLine == 0) {
        cout << "Pressure map empty!!\n";
        return 2;
    }
    if (distance(lineLength.begin(), unique(lineLength.begin(), lineLength.end())) != 1)
    {
        cout << "Pressure map row length not consistent!!\n";
        return 3;
    }
    #ifdef DEBUG_BUILD
    cout << "Rows: " << numLine << '\n';
    cout << "Cols: " << lineLength[0] << '\n';
    cout << "Pressure map data: \n";
    for (auto i = map.begin(); i != map.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            cout << *j << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
    #endif
    presMap.close();
    return 0;
}