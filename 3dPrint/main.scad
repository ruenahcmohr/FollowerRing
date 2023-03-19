
 outline = "main.dxf";


 
 L0 = 2;
 
 L1 = 8;
 
 
 L2 = 2;
 
 L3 = 8; 
 
 L4 = 5;
 L5 = 20;
 
 L6 = 9.5;
 L7 = 5;

 L10 = 7; 
 L11 = 8;

 L20 = 1;
 L22 = 0.5;
  
 L30 = 2;
 L31 = 50;
 
 L40 = 15;
 
 L50 = 3;
 L51 = 30;

L91 = 5;
L100 = 11;

difference() {
union() {
      linear_extrude(height=L0, convexity=5) {
       import(file=outline, layer="0", $fn=188);
     }
     
     translate([0,0,L0-0.001])
     linear_extrude(height=L1, convexity=5) {
       import(file=outline, layer="1", $fn=188);
     }
     
 }  
     
     translate([0,55,(L0+L1)/2])
     rotate([0,90,0])
     cylinder(h = 150, r =1.50, $fn=90, center=true);
 
     translate([0,-55,(L0+L1)/2])
     rotate([0,90,0])
     cylinder(h = 150, r =1.50, $fn=90, center=true);    
     
     // tiedown holes
     translate([-60,-10,(L0+L1)])
     rotate([90,0,0])
     linear_extrude(height=L91, convexity=5) {
       import(file=outline, layer="91", $fn=188);
     }
 
      translate([-60,-30,(L0+L1)])
     rotate([90,0,0])
     linear_extrude(height=L91, convexity=5) {
       import(file=outline, layer="91", $fn=188);
     }
     
     translate([60,-10,(L0+L1)])
     rotate([90,0,0])
     linear_extrude(height=L91, convexity=5) {
       import(file=outline, layer="91", $fn=188);
     }
 
     translate([60,-30,(L0+L1)])
     rotate([90,0,0])
     linear_extrude(height=L91, convexity=5) {
       import(file=outline, layer="91", $fn=188);
     }   
     
     translate([40,-53,(L0+L1)])
     rotate([0,90,0])
     linear_extrude(height=L91, convexity=5) {
       import(file=outline, layer="91", $fn=188);
     }    
     
     translate([-30,-53,(L0+L1)])
     rotate([0,90,0])
     linear_extrude(height=L91, convexity=5) {
       import(file=outline, layer="91", $fn=188);
     }     
 } 
     
/*
      rotate_extrude( convexity=5, $fn=248) {
       import(file=outline, layer="10", $fn=248);
     } 


     //2x dovetail
     translate([-40.64,0,L10/2])
     rotate([-90,90,-90])    
     linear_extrude(height=L20, convexity=5) {
       import(file=outline, layer="20", $fn=188);
     }
 } // end of the union
 
     
     // 3x bolt
     color([1,0,0])
  translate([0,-0.005,50])
  rotate([-90,0,0]) {
     linear_extrude(height=L30, convexity=5) {
       import(file=outline, layer="30", $fn=188);
     }
     
     translate([0,0,L30-0.006])
     linear_extrude(height=L31, convexity=5) {
       import(file=outline, layer="31", $fn=188);
     }
 }
 
  // 4x side bolt
 color([0, 1, 0])
      translate([0,0,57.005])
      linear_extrude(height=L40, convexity=5) {
       import(file=outline, layer="40", $fn=188);
     }
 
     




  translate([0,0,L0+L1])
     linear_extrude(height=L2, convexity=5) {
       import(file=outline, layer="2", $fn=188);
     }




     translate([10, -0, 25/2])
     rotate([0,90,0])
     cylinder(h = 40, r =2.0, $fn=100, center=true);

}
*/
