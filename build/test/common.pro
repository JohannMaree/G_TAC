
//Geometry Parameters
Fl_Dimension=DefineNumber[0, Name "Geo/1Dimension",
                          Choices {0="2D",1="3D"}];

X1=DefineNumber[10, Name "Geo/2Rec1_X"];
Y1=DefineNumber[10, Name "Geo/3Rec12_Y"];
X2=DefineNumber[40, Name "Geo/4Rec2_X"];
H1=DefineNumber[10, Name "Geo/5Rec12_Z", Visible Fl_Dimension];

Lc1=DefineNumber[1, Name "Geo/6Rec1_Lc"];
Lc2=DefineNumber[1, Name "Geo/7Rec2_Lc"];
