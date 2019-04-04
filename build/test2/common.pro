
Fl_Dimension3=DefineNumber[0, Name "Geo/1Dimension",
                           Choices{0="2D",1="3D"}];
						   
Fl_FluxSide=DefineNumber[0, Name "Geo/2Flux_Side",
						 Choices{0="TempLeft_FluxRight", 1="FluxLeft_TempRight"}];		 

Y=DefineNumber[4, Name "Geo/1RecLRM_Y"];
XL=DefineNumber[12, Name "Geo/2RecL_X"];
XR=DefineNumber[16, Name "Geo/3RecR_X"];
XM=DefineNumber[60, Name "Geo/4RecM_X"];

H1=DefineNumber[10, Name "Geo/RecLRM_Z", Visible Fl_Dimension3];

LcL=DefineNumber[1.6, Name "Geo/RecL_Lc"];
LcR=DefineNumber[1, Name "Geo/RecR_Lc"];
LcM=DefineNumber[0.4, Name "Geo/RecM_Lc"];

X0=12;
Y0=24;
Z0=0;

cX=X0 + XL + XM + XR;
cY=Y/2 + Y0;