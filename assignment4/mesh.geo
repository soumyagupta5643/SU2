
// Gmsh project created on Fri Mar 29 22:19:31 2024
Point(1) = {0, 0, 0, 1.0}; 
Point(2) = {1.2, 0, 0, 1.0}; 
Point(3) = {1.2, 7, 0, 1.0}; 
Point(4) = {0, 7, 0, 1.0}; 
 
Line(1) = {1, 2}; 
Line(2) = {2, 3}; 
Line(3) = {3, 4}; 
Line(4) = {4, 1}; 
 
Curve Loop(1) = {1, 2, 3, 4}; 
 
Plane Surface(1)= {1};
 
Transfinite Surface {1} = {4, 3, 2, 1};
Transfinite Line {1,2,-3,-4} = 50 Using Bump 0.15;
Recombine Surface {1};

Physical Curve("farfield", 9) = {2,4};
Physical Curve("symmetry", 10) = {3};
Physical Curve("wall", 11) = {1};
Physical Curve("inlet", 12) = {4};
Physical Curve("outlet", 13) = {2};

Physical Surface("fluid", 1) = {1};

Mesh 2;
