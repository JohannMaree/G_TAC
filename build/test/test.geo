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
  ll=newll; Curve Loop(ll) = {lines[]};

Return
//}

//{ CREATE HEXAHEDRON
Function Create_Hex

  p1=newp; Point(newp)={_xC,_yC,_zC,_lc};
  p2=newp; Point(newp)={_xC+_xL,_yC,_zC,_lc};
  p3=newp; Point(newp)={_xC+_xL,_yC+_yL,_zC,_lc};
  p4=newp; Point(newp)={_xC,_yC+_yL,_zC,_lc};
  p5=newp; Point(newp)={_xC,_yC,_zC+_zL,_lc};
  p6=newp; Point(newp)={_xC+_xL,_yC,_zC+_zL,_lc};
  p7=newp; Point(newp)={_xC+_xL,_yC+_yL,_zC+_zL,_lc};
  p8=newp; Point(newp)={_xC,_yC+_yL,_zC+_zL,_lc};

  l1=newl; Line(newl)={p1,p2};
  l2=newl; Line(newl)={p2,p3};
  l3=newl; Line(newl)={p3,p4};
  l4=newl; Line(newl)={p4,p1};
  l5=newl; Line(newl)={p5,p6};
  l6=newl; Line(newl)={p6,p7};
  l7=newl; Line(newl)={p7,p8};
  l8=newl; Line(newl)={p8,p5};
  l15=newl; Line(newl)={p1,p5};
  l26=newl; Line(newl)={p2,p6};
  l37=newl; Line(newl)={p3,p7};
  l48=newl; Line(newl)={p4,p8};

  lines1[] = {l1,l2,l3,l4};
  lines2[] = {l5,l6,l7,l8};
  lines3[] = {l1,l26,-l5,-l15};
  lines4[] = {l2,l37,-l6,-l26};
  lines5[] = {l3,l48,-l7,-l37};
  lines6[] = {l4,l15,-l8,-l48};

  ll1=newll; Curve Loop(ll1) = {lines1[]};
  ll2=newll; Curve Loop(ll2) = {lines2[]};
  ll3=newll; Curve Loop(ll3) = {lines3[]};
  ll4=newll; Curve Loop(ll4) = {lines4[]};
  ll5=newll; Curve Loop(ll5) = {lines5[]};
  ll6=newll; Curve Loop(ll6) = {lines6[]};

  s1=news; Plane Surface(news) = {ll1};
  s2=news; Plane Surface(news) = {ll2};
  s3=news; Plane Surface(news) = {ll3};
  s4=news; Plane Surface(news) = {ll4};
  s5=news; Plane Surface(news) = {ll5};
  s6=news; Plane Surface(news) = {ll6};

  surfs[] = {s1,s2,s3,s4,s5,s6};
  sl=newsl; Surface Loop(newsl) = {surfs[]};

Return
//}


//Create entities from smallest to largest
Xcenter=X1/2;
Ycenter=Y1/2;

_xC = Xcenter - (X2/2);
_yC = Ycenter - (Y2/2);
_xL = X2;
_yL = Y2;
_lc = Lc2;
_zC = 0;
_zL = Z2;

//{Inner Quad 
If (!FL3D)
	
	Call Create_Quad;
	
	ss=news; Plane Surface(news) = {ll};
	sRec2 = ss;
	llRec2 = lines[];
	ll2 = ll;
	l21 = l1;
	l22 = l2;
	l23 = l3;
	l24 = l4;

Else

	Call Create_Hex;
	lla = ll1;
	s21 = s1;
	s22 = s2;
	s23 = s3;
	s24 = s4;
	s25 = s5;
	s26 = s6;
	vol2 = newv;
	Volume(newv) = {sl};
	
EndIf
//}

//{Wireframe
  pW1=newp; Point(newp)={_xC - WW - WS, _yC - WW - WS,0,LcW};
  pW2=newp; Point(newp)={_xC - WW - WS, _yC + Y2 + WS,0,LcW};
  pW3=newp; Point(newp)={_xC - WS, _yC + Y2 + WS,0,LcW};
  pW4=newp; Point(newp)={_xC - WS, _yC - WS,0,LcW};
  pW5=newp; Point(newp)={_xC + WS + X2, _yC - WS,0,LcW};
  pW6=newp; Point(newp)={_xC + WS + X2, _yC + Y2 + WS,0,LcW};
  pW7=newp; Point(newp)={_xC + WW + WS + X2, _yC + Y2 + WS,0,LcW};
  pW8=newp; Point(newp)={_xC + WW + WS + X2, _yC - WW - WS,0,LcW};
  
  lw1=newl; Line(newl) = {pW1,pW2};
  lw2=newl; Line(newl) = {pW2,pW3};
  lw3=newl; Line(newl) = {pW3,pW4};
  lw4=newl; Line(newl) = {pW4,pW5};
  lw5=newl; Line(newl) = {pW5,pW6};
  lw6=newl; Line(newl) = {pW6,pW7};
  lw7=newl; Line(newl) = {pW7,pW8};
  lw8=newl; Line(newl) = {pW8,pW1};
  
  wlines[] = {lw1,lw2,lw3,lw4,lw5,lw6,lw7,lw8};
  llb = newll; Curve Loop(llb) = {wlines[]};
  ssW_bot = news; Plane Surface(news) = {llb};

If (FL3D)
	
  pW11=newp; Point(newp)={_xC - WW - WS, _yC - WW - WS,WZ,LcW};
  pW12=newp; Point(newp)={_xC - WW - WS, _yC + Y2 + WS,WZ,LcW};
  pW13=newp; Point(newp)={_xC - WS, _yC + Y2 + WS,WZ,LcW};
  pW14=newp; Point(newp)={_xC - WS, _yC - WS,WZ,LcW};
  pW15=newp; Point(newp)={_xC + WS + X2, _yC - WS,WZ,LcW};
  pW16=newp; Point(newp)={_xC + WS + X2, _yC + Y2 + WS,WZ,LcW};
  pW17=newp; Point(newp)={_xC + WW + WS + X2, _yC + Y2 + WS,WZ,LcW};
  pW18=newp; Point(newp)={_xC + WW + WS + X2, _yC - WW - WS,WZ,LcW};
  
  lw11=newl; Line(newl) = {pW11,pW12};
  lw12=newl; Line(newl) = {pW12,pW13};
  lw13=newl; Line(newl) = {pW13,pW14};
  lw14=newl; Line(newl) = {pW14,pW15};
  lw15=newl; Line(newl) = {pW15,pW16};
  lw16=newl; Line(newl) = {pW16,pW17};
  lw17=newl; Line(newl) = {pW17,pW18};
  lw18=newl; Line(newl) = {pW18,pW11};
  
  lw21=newl; Line(newl) = {pW1,pW11};
  lw22=newl; Line(newl) = {pW2,pW12};
  lw23=newl; Line(newl) = {pW3,pW13};
  lw24=newl; Line(newl) = {pW4,pW14};
  lw25=newl; Line(newl) = {pW5,pW15};
  lw26=newl; Line(newl) = {pW6,pW16};
  lw27=newl; Line(newl) = {pW7,pW17};
  lw28=newl; Line(newl) = {pW8,pW18};
  
  llt = newll; Curve Loop(llt) = {lw11,lw12,lw13,lw14,lw15,lw16,lw17,lw18};
  ll1 = newll; Curve Loop(ll1) = {lw1,lw22,-lw11,-lw21};
  ll2 = newll; Curve Loop(ll2) = {lw2,lw23,-lw12,-lw22};
  ll3 = newll; Curve Loop(ll3) = {lw3,lw24,-lw13,-lw23};
  ll4 = newll; Curve Loop(ll4) = {lw4,lw25,-lw14,-lw24};
  ll5 = newll; Curve Loop(ll5) = {lw5,lw26,-lw15,-lw25};
  ll6 = newll; Curve Loop(ll6) = {lw6,lw27,-lw16,-lw26};
  ll7 = newll; Curve Loop(ll7) = {lw7,lw28,-lw17,-lw27};
  ll8 = newll; Curve Loop(ll8) = {lw8,lw21,-lw18,-lw28};
  
  ssW_top = news; Plane Surface(news) = {llt};
  sW1 = news; Plane Surface(news) = {ll1};
  sW2 = news; Plane Surface(news) = {ll2};
  sW3 = news; Plane Surface(news) = {ll3};
  sW4 = news; Plane Surface(news) = {ll4};
  sW5 = news; Plane Surface(news) = {ll5};
  sW6 = news; Plane Surface(news) = {ll6};
  sW7 = news; Plane Surface(news) = {ll7};
  sW8 = news; Plane Surface(news) = {ll8};
  
  sSL = newsl; Surface Loop(newsl) = {sW1,sW2,sW3,sW4,sW5,sW6,sW7,sW8,ssW_bot,ssW_top};
  volW = newv; Volume(newv) = {sSL};

EndIf
//}
  
//{Outer Quad
  _xC = 0;
  _yC = 0;
  _xL = X1;
  _yL = Y1;
  _lc = Lc1;
  zC = 0;
  _zL = -Z1;
  
If (!FL3D)
	
	Call Create_Quad;
	
	llRec1 = lines[];
	ssN = news; Plane Surface(news) = {ll, -llb, -ll2};
	sRec1N = ssN;
	l11 = l1;
	l12 = l2;
	l13 = l3;
	l14 = l4;
	
Else
	
	Call Create_Hex;
	
	s11 = s1;
	s12 = s2;
	s13 = s3;
	s14 = s4;
	s15 = s5;
	s16 = s6;
	
	sRec1N = news; Plane Surface(news) = {ll1, -llb, -lla};
	sl1 = newsl; Surface Loop(newsl) = {sRec1N, s12, s13, s14, s15, s16, ssW_bot, s21};
	vol1 = newv;
	Volume(newv) = {sl1};
	
EndIf
//}

If (!FL3D)
	
	Physical Line("innerS",1) = {l21};
	Physical Line("innerE",2) = {l22}; 
	Physical Line("innerN",3) = {l23};
	Physical Line("innerW",4) = {l24};
	
	Physical Line("outerS",11) = {l11};
	Physical Line("outerE",12) = {l12};
	Physical Line("outerN",13) = {l13};
	Physical Line("outerW",14) = {l14};

	Physical Line("bound1",101) = {llRec1[]};
	Physical Line("bound2",102) = {llRec2[]};
	Physical Line("boundW",103) = {wlines[]};
	  
	Physical Surface("Rec1",1001) = {sRec1N};
	Physical Surface("Rec2",1002) = {sRec2};
	Physical Surface("wireB",1003) = {ssW_bot};
	
	If (!FileExists("test2d.msh"))
		Mesh 2;
		Save "test2d.msh";
	EndIf
	
Else
	
	Physical Surface("innerB",1) = {s21};
	Physical Surface("innerT",2) = {s22};
	Physical Surface("innerS",3) = {s23};
	Physical Surface("innerE",4) = {s24};
	Physical Surface("innerN",5) = {s25};
	Physical Surface("innerW",6) = {s26};
	
	Physical Surface("outerT",11) = {sRec1N};
	Physical Surface("outerB",12) = {s12};
	Physical Surface("outerS",13) = {s13};
	Physical Surface("outerE",14) = {s14};
	Physical Surface("outerN",15) = {s15};
	Physical Surface("outerW",16) = {s16};
	
	Physical Surface("wireB",21) = {ssW_bot};

	Physical Volume("vol1",1001) = {vol1};
	Physical Volume("vol2",1002) = {vol2};
	Physical Volume("vol3",1003) = {volW};
	
	If (!FileExists("test3d.msh"))
		Mesh 3;
		Save "test3d.msh";
	EndIf
	
EndIf
