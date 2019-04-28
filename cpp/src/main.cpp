/**
 * @file        main.c
 * @author      Wong Tat Hang (Alex)    thwongaz@connect.ust.hk
 * @brief       main entry for mesh processing and generation system built for 
 *              ISDN2400, ISDN1003 and ISDN1005 integrative project
 * @note        slic3r PE has to be installed and added to PATH
 * @date        28/4/2019
 * 
 * @copyright   Copyright (c) 2019
 */

#include <iostream>
#include "main.hpp"
#include "pressure.hpp"
using namespace std;

int main()
{
    pressureGen();
    return 0;
}