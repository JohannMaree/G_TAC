Include "common.pro";


//{ CREATE QUADRAHEDRON 
Function Create_Quad

  p1=newp; Point(newp)={_xC,_yC,_zC,_lc};
  p2=newp; Point(newp)={_xC+_xL,_yC,_zC,_lc};
  p3=newp; Point(newp)={_xC+_xL,_yC+_yL,_zC,_lc};
  p4=newp; Point(newp)={_xC,_yC+_yL,_zC,_lc};

  l1=newl; Line(newl)={p1,p2};
  l2=newl; Line(newl)={p2,p3};
  l3=newl; Line(newl)={p3,p4};
  l4=newl; Line(newl)={p4,p1};

  lines[] = {l1, l2, l3, l4};
  ll=newll; Curve Loop(newll) = {lines[]};

Return
//}

  //Left Quad
  _xC = X0;
  _yC = Y0;
  _zC = Z0;
  _xL = XL;
  _yL = Y;
  _lc = LcL;
  Call Create_Quad;

  ssL = news; Plane Surface(news) = {ll};
  lRecL = l4;
  lRecR = l2;
  lRecP2 = p2;
  lRecP3 = p3;
	
  //Right Quad
  _xC = X0 + XM + XL;
  _yC = Y0;
  _zC = Z0;
  _xL = XR;
  _yL = Y;
  _lc = LcR;
  Call Create_Quad;

  ssR = news; Plane Surface(news) = {ll};
  rRecR = l2;
  rRecL = l4;
  rRecP1 = p1;
  rRecP4 = p4;
  
  //Middle Quad
  l1=newl; Line(newl) = {lRecP2, rRecP1};
  l2=newl; Line(newl) = {rRecP4, lRecP3};
  lines[] = {l1, -rRecL, l2, -lRecR};
  ll=newll; Curve Loop(newll) = {lines[]};
  ssM = news; Plane Surface(news) = {ll};
  
  Characteristic Length {rRecP4, lRecP2} = LcM;
  
  
  //Collective Definitions
  Physical Line("boundL",100) = {lRecL};
  Physical Line("boundR",101) = {rRecR};
  
  Physical Surface("RecL",1000) = {ssL};
  Physical Surface("RecR",1001) = {ssR};
  Physical Surface("RecM",1002) = {ssM};

Physical Volume("VoL", 999) = {1000,1001,1002};

//If(Fl_Dimension3)    //3D
  
//EndIf

