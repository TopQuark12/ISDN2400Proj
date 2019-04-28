include <param.scad>;
include <pressureMap.scad>;

spacingX = padLength / pressureMapNumCol;
spacingY = padWidth / pressureMapNumRow;

for (i = [0:pressureMapNumCol - 1]) {
    for (j = [0:pressureMapNumRow - 1]) {
        translate([i * spacingX, j * spacingY, 0]) 
            cube([spacingX, spacingY, pressureMap[i][j]], false);
        
    }
}

echo(spacingX);
echo(spacingY);