//translate([2, 0, 0])

$fn=90;
difference(){
    union(){


      translate([-150,-300,0])
        cube(size=[300,350,5]);
    rotate([90,180,180])
        scale([1.2, 0.08, 1])
        rotate([180, 90,0])
        translate([120,40,1100])
  
    import("pelvis.stl");
    }  
 translate([-150,-300,0])
   cube(size=[300,350,5]);
        
}
  
    

     
       

