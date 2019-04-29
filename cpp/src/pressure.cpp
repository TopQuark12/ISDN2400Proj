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

    int pressureRes;
    cout << "Enter the pressure resolution of modifier meshes: ";
    cin >> pressureRes;

    int infillLo = 10;
    int infillHi = 50;
    int infillInc = (infillHi - infillLo) / pressureRes;

    ifstream presMap;
    presMap.open("input/pressureMap.pres", ios::in);
    if(presMap.is_open()) {
        cout << "Pressure map found and opened \n";
    } else {
        cout << "Pressure map not found! \n";
        return 1;
    }
    vector<vector<float>> map;
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
    presMap.close();
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

    ofstream scad;
    scad.open("scad/pressureMap.scad", ios::out);
    scad << "// This file is auto generated by cpp/src/pressure.cpp\n";
    scad << "// using input/pressureMap.pres\n\n";
    scad << "pressureMap = [\n";
    for (auto i = map.begin(); i != map.end(); i++) {
        scad << "\t[";
        for (auto j = i->begin(); j != i->end(); j++) {
            scad << *j << ", ";
        }
        scad << "],\n";
    }
    scad << "];\n\n";
    scad << "pressureMapNumRow = " << numLine << ";\n";
    scad << "pressureMapNumCol = " << numLine << ";\n";
    scad.close();

    cout << "Pressure parsing sucessful\n";

    //vector<float> pressureThresh;
    float minPressure = numeric_limits<float>::max();
    float maxPressure = numeric_limits<float>::min();
    for (auto i = map.begin(); i != map.end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            minPressure = *j < minPressure ? *j : minPressure;
            maxPressure = *j > maxPressure ? *j : maxPressure;
        }
    }    
    
    #ifdef DEBUG_BUILD
    cout << "Min Pressure: " << minPressure << '\n';
    cout << "Max Pressure: " << maxPressure << '\n';
    #endif
    
    float pressureInc = (maxPressure - minPressure) / pressureRes;
    for (int i = 0; i < pressureRes; i++) {
        float lower = minPressure + i * pressureInc;
        float higher = minPressure + (i + 1) * pressureInc;
        ostringstream cmdString;
        cmdString << "openscad -D loThrs=" << lower << " -D hiThrs=" << higher
                  << " -o output/infill_" << infillLo + i * infillInc << ".stl scad/modMeshGen.scad\n";
        int exitCode = system(cmdString.str().c_str());
        #ifdef DEBUG_BUILD
        cout << cmdString.str();
        #endif
    }

    cout << "Modifier Mesh Generation Successful\n";

    return 0;
}