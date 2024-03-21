// Define the jet geometry
Point(1) = {0, 0, 0, 1.0}; // Define a point at the origin
Point(2) = {7, 0, 0, 1.0}; // Define a point 10 units away from the origin along the x-axis
Point(3) = {7, 1.2, 0, 1.0}; // Define a point 2 units above the x-axis
Point(4) = {0, 1.2, 0, 1.0}; // Define a point 2 units above the origin

Line(1) = {1, 2}; // Create a line between points 1 and 2 (bottom of the jet)
Line(2) = {2, 3}; // Create a line between points 2 and 3 (top of the jet)
Line(3) = {3, 4}; // Create a line between points 3 and 4 (right side of the jet)
Line(4) = {4, 1}; // Create a line between points 4 and 1 (left side of the jet)

Line Loop(1) = {1, 2, 3, 4}; // Create a loop consisting of the four lines
Plane Surface(1) = {1}; // Create a surface from the line loop

// Define mesh settings
Mesh.CharacteristicLengthMin = 0.1; // Set the minimum mesh size
Mesh.CharacteristicLengthMax = 1.0; // Set the maximum mesh size

//+
Transfinite Surface {1};
Transfinite Curve {4, 2} = 80 Using Progression 1;
Transfinite Curve {3, 1} = 100 Using Progression 1;
Transfinite Surface {3};
Recombine Surface {1,3};

//+
Physical Curve("inlet", 8) = {4};
Physical Curve("outlet", 9) = {2};
Physical Curve("walls", 10) = {1,3};
Physical Curve("symmetry", 11) = {1};
Physical Surface("fluid", 1) = {1};
