// Gmsh project created on Fri Mar 29 22:19:31 2024
Point(1) = {0, 0, 0, 1.0}; 
Point(2) = {1, 0, 0, 1.0}; 
Point(3) = {1, 4, 0, 1.0}; 
Point(4) = {0, 4, 0, 1.0}; 

Line(1) = {1, 2}; 
Line(2) = {2, 3}; 
Line(3) = {3, 4}; 
Line(4) = {4, 1}; 

Curve Loop(1) = {1, 2, 3, 4}; 


Plane Surface(1)= {1};
Transfinite Curve {4, 2} = 170;
Transfinite Curve {3, 1} = 44;
Transfinite Surface {3};
Recombine Surface {1,3};

Physical Curve("farfield", 9) = {1,3};
Physical Curve("plate", 10) = {2,4};
Physical Surface("fluid", 1) = {1};
Mesh 2;
