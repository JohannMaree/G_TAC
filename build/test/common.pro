
//Geometry Parameters
Fl_Dimension3=DefineNumber[0, Name "Geo/1Dimension",
                          Choices {0="2D",1="3D"}];

X1=DefineNumber[100, Name "Geo/2Rec1_X"];
Y1=DefineNumber[160, Name "Geo/3Rec1_Y"];

X2=DefineNumber[40, Name "Geo/4Rec2_X"];
Y2=DefineNumber[80, Name "Geo/5Rec2_X"];

WW=DefineNumber[4, Name "Geo/WireWidth"];
WS=DefineNumber[12, Name "Geo/WireSpace"];

H1=DefineNumber[10, Name "Geo/Rec12_Z", Visible Fl_Dimension3];

Lc1=DefineNumber[8, Name "Geo/Rec1_Lc"];
Lc2=DefineNumber[4, Name "Geo/Rec2_Lc"];
LcW=DefineNumber[2, Name "Geo/Wire_Lc"];