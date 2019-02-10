
Include "common.pro";

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
  ss=news; Plane Surface(news) = {ll};

Return

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

If(!Fl_Dimension)    //2D
  _xC = 0;
  _yC = 0;
  _zC = 0;
  _xL = X1;
  _yL = Y1;
  _lc = Lc1;
  Call Create_Quad;
  sRec1 = ss;
  lRec1R = l2;

/*  _xC = -X2;
  _yC = 0;
  _zC = 0;
  _xL = X2;
  _yL = Y1;
  _lc = Lc2;
  Call Create_Quad;
  sRec2 = ss;
  lRec2L = l4; */

  p5=newp; Point(newp)={-X2,0,0,Lc2};
  p6=newp; Point(newp)={-X2,Y1,0,Lc2};
  l5=newl; Line(newl)={p5,p1};
  l6=newl; Line(newl)={p4,p6};
  l7=newl; Line(newl)={p6,p5};
  lines2[]={l5,-l4,l6,l7};
  ll2=newll; Curve Loop(ll2) = {lines2[]};
  sRec2=news; Plane Surface(news) = {ll2};
  lRec2L=l7;

  Physical Line("R1",100) = {lRec1R};
  Physical Line("L2",101) = {lRec2L};
  Physical Surface("Rec1",1000) = {sRec1};
  Physical Surface("Rec2",1001) = {sRec2};

Else                //3D
  _xC = 0;
  _yC = 0;
  _zC = 0;
  _xL = X1;
  _yL = Y1;
  _zL = H1;
  _lc = Lc1;
  Call Create_Hex;
  f1_4 = s4;
  v1 = v;

  _xC = -X2;
  _yC = 0;
  _zC = 0;
  _xL = X2;
  _yL = Y1;
  _zL = H1;
  _lc = Lc2;
  Call Create_Hex;
  f2_6 = s6;
  v2 = v;

  Physical Surface("R1",100) = {f1_4};
  Physical Surface("L2",101) = {f2_6};
  Physical Volume("Hex1",1000) = {v1};
  Physical Volume("Hex2",1001) = {v2};

EndIf
