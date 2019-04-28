include <param.scad>;
include <pressureMap.scad>;

loThrs = 40;
hiThrs = 50;

spacingX = padLength / pressureMapNumCol;
spacingY = padWidth / pressureMapNumRow;

for (i = [0:pressureMapNumCol - 1]) {
    for (j = [0:pressureMapNumRow - 1]) {
        if((pressureMap[i][j] >= loThrs) && (pressureMap[i][j] < hiThrs))
            translate([i * spacingX, j * spacingY, 0]) {
                cube([spacingX, spacingY, padHeight * 2], false);
        }        
    }
}