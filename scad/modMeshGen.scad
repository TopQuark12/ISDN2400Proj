// @file        modMeshGen.scad
// @author      Alex Wong Tat Hang
// @brief       modifier mesh generation scad script
// @note        loThres and hiThres should be used as parameters
// @warning     param.scad and pressureMap.scad must be created before this script is called
// @date        28/4/2019
// @copyright   Copyright (c) 2019

include <param.scad>;
include <pressureMap.scad>;

loThrs = 40;
hiThrs = 50;

spacingX = padWidth / pressureMapNumCol;
spacingY = padLength / pressureMapNumRow;

for (i = [0:pressureMapNumCol - 1]) {
    for (j = [0:pressureMapNumRow - 1]) {
        if((pressureMap[j][i] >= loThrs) && (pressureMap[j][i] < hiThrs))
            translate([i * spacingX, j * spacingY, 0]) {
                cube([spacingX, spacingY, padHeight + 1], false);
        }        
    }
}