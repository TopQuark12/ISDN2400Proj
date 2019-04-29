module cylinders(points, diameter, thickness){
    for (p=points){
        translate(p) cylinder(d=diameter, h=thickness, center=true);
    }
}
 
module plate(points, diameter, thickness, hole_diameter){
    difference(){
        hull() cylinders(points, diameter, thickness);
        cylinders(points, hole_diameter, thickness+1);
    }
}
 
module bar(length, width, thickness, hole_diameter){
    plate([[0,0,0], [length,0,0]], width, thickness, hole_diameter);
}