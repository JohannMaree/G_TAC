//Geometry Parameters
FL3D = DefineNumber[0, Choices{0="2D",1="3D"}, Name "Dimension"];

X1=DefineNumber[100, Name "Geo/2Rec1_X"];
Y1=DefineNumber[160, Name "Geo/3Rec1_Y"];
Z1=DefineNumber[2, Name "Geo/4Rec1_Z"];

X2=DefineNumber[40, Name "Geo/5Rec2_X"];
Y2=DefineNumber[80, Name "Geo/6Rec2_Y"];
Z2=DefineNumber[4, Name "Geo/7Rec2_Z"];

WW=DefineNumber[4, Name "Geo/WireWidth"];
WS=DefineNumber[12, Name "Geo/WireSpace"];
WZ=DefineNumber[1, Name "Geo/WireZ"];

Lc1=DefineNumber[2, Name "GeoMesh/Rec1_Lc"];
Lc2=DefineNumber[1, Name "GeoMesh/Rec2_Lc"];
LcW=DefineNumber[1, Name "GeoMesh/Wire_Lc"];

Solver.AutoMesh = 1;
