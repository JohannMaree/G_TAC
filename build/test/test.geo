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
  v=newv; Volume(newv) = {sl};

Return
//}

If(!Fl_Dimension3)    //2D
//Create entities from smallest to largest

  Xcenter=X1/2;
  Ycenter=Y1/2;

  //Inner Quad 
  _xC = Xcenter - (X2/2);
  _yC = Ycenter - (Y2/2);
  _zC = 0;
  _xL = X2;
  _yL = Y2;
  _lc = Lc2;
  Call Create_Quad;
  
  ss=news; 
  Plane Surface(news) = {ll};
  sRec2 = ss;
  llrec2 = lines[];
  ll2 = ll;

  //Wireframe
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
  lW = newll;
  Curve Loop(lW) = {wlines[]};
  ssW = news;
  Plane Surface(news) = {lW};
  
  //Outer Quad
  _xC = 0;
  _yC = 0;
  _zC = 0;
  _xL = X1;
  _yL = Y1;
  _lc = Lc1;
  Call Create_Quad;

  llRec1 = lines[];
  ssN = news;
  Plane Surface(news) = {ll, -lW, -ll2};
  sRec1N = ssN;

  Physical Line("bound1",100) = {llRec1[]};
  Physical Line("bound2",101) = {llrec2[]};
  Physical Line("boundW",102) = {wlines[]};
  
  Physical Surface("Rec1",1000) = {sRec1N};
  Physical Surface("Rec2",1001) = {sRec2};
  Physical Surface("Wire",1002) = {ssW};

Else                //3D
  

EndIf
