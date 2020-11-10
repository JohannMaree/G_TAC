
FLcooling = DefineNumber[0, Choices{0="Cryo_Cooler",1="Helium_Immersion"}, Name "Simulation/Cooling System"];

BC_T1 = DefineNumber[4.2, Name "Simulation/Temperature", Help "Dirichlet Temp_1", Label "T1 K"];
BC_F1 = DefineNumber[16, Name "Simulation/Surface_Flux/HeatInFlux", Help "Flux1", Label "F1"];
BC_Q1 = DefineNumber[20, Name "Simulation/Heat_Gen/Qgeneration1", Help "Qgen1", Label "Q1"];
			
BC_G1 = DefineNumber[0.8, Name "Simulation/Temp Gap TOP", Help "Tdisc1", Label "G1"];
BC_G2 = DefineNumber[0.4, Name "Simulation/Temp Gap BOT", Help "Tdisc2", Label "G2"];
BC_G3 = DefineNumber[0.1, Name "Simulation/Temp Gap PCB1", Help "Tdisc3", Label "G3"];
BC_G4 = DefineNumber[0.2, Name "Simulation/Temp Gap M1", Help "Tdisc4", Label "G4"];
BC_G5 = DefineNumber[0.1, Name "Simulation/Temp Gap M0", Help "Tdisc5", Label "G5"];

C_CondPCB0 = DefineNumber[170, Name "Simulation/Conduction/PCB0",
            Help "k conductivity constant", Label "k PCB0"];
C_CondDIE = DefineNumber[200, Name "Simulation/Conduction/DIE",
            Help "k conductivity constant", Label "k DIE"];
C_CondBOT = DefineNumber[400, Name "Simulation/Conduction/BOT",
            Help "k conductivity constant", Label "k BOT"];
C_CondM1 = DefineNumber[160, Name "Simulation/Conduction/M1",
            Help "k conductivity constant", Label "k M1"];
C_CondM0 = DefineNumber[160, Name "Simulation/Conduction/M0",
            Help "k conductivity constant", Label "k M0"];
C_CondI0 = DefineNumber[300, Name "Simulation/Conduction/I0",
            Help "k conductivity constant", Label "k I0"];
C_CondPCB1 = DefineNumber[170, Name "Simulation/Conduction/PCB1",
            Help "k conductivity constant", Label "k PCB1"];
C_CondTOP = DefineNumber[2, Name "Simulation/Conduction/TOP",
            Help "k conductivity constant", Label "k TOP"];
C_CondWB = DefineNumber[10, Name "Simulation/Conduction/WB",
            Help "k conductivity constant", Label "k WB"];

/*If ( FLcooling )
	H_Tinf = DefineNumber[10, Name "Simulation/Convection/Fluid Inf Temperature",
							Help "Infinite Temp_1", Label "Tinf", Visible FLcooling];
	H_ConvPCB0 = DefineNumber[20, Name "Simulation/Convection/PCB0 conv coeff",
							Help "h convection coefficient", Label "h_PCB0", Visible FLcooling];
    H_ConvDIE = DefineNumber[30, Name "Simulation/Convection/DIE conv coeff",
							Help "h convection coefficient", Label "h_DIE", Visible FLcooling];
	H_ConvPCB1 = DefineNumber[10, Name "Simulation/Convection/PCB1 conv coeff",
							Help "h convection coefficient", Label "h_PCB1", Visible FLcooling];
	H_ConvTOP = DefineNumber[10, Name "Simulation/Convection/TOP conv coeff",
							Help "h convection coefficient", Label "h_TOP", Visible FLcooling];
*/ //Else
	BC_F2 = DefineNumber[-200, Name "Simulation/Surface_Flux/Bottom_OutFlux",
							Help "Flux2", Label "F2", Visible !FLcooling];
	R_Tinf = DefineNumber[70, Name "Simulation/Convection/Radiation Emission Sur Temperature",
							Help "Rad Surface Temp_1", Label "Tsur", Visible !FLcooling];

//Nonlinear Conduction Constants
NL_eps = 1e-6;  //Absolute Error Tolerance Target
NL_rel = 1e-5;  //Relative Error Tolerance Target
NL_max = 50;    //max iterations

Group{
	
	//{pcb0.geo
		Sur_PCB0bot = Region[{11000}];
		Sur_PCB0top = Region[{12000}];
		Sur_PCB0north = Region[{13000}];
		Sur_PCB0sides = Region[{14000}];
		Sur_PCB0 = Region[{Sur_PCB0bot,Sur_PCB0top,Sur_PCB0north, Sur_PCB0sides}];
		Vol_PCB0 = Region[{1}];
	//}
	
	//{die.geo
		Sur_DIE_botOuter = Region[{31000}];
		Sur_DIE_botInner = Region[{41000}];
		Sur_DIE_topOuter = Region[{32000}];
		Sur_DIE_topInner = Region[{42000}];
		Sur_DIE_extSides = Region[{33000}];
		Sur_DIEtop = Region[{Sur_DIE_topInner,Sur_DIE_topOuter}];
		Sur_DIEbot = Region[{Sur_DIE_botInner,Sur_DIE_botOuter}];
		Sur_DIE = Region[{Sur_DIEtop,Sur_DIEbot, Sur_DIE_extSides}];
		Vol_DIEouter = Region[{3}];
		Vol_DIEinner = Region[{4}];
		Vol_DIE = Region[{Vol_DIEinner,Vol_DIEouter}];
	//}
	
	//{bot.geo
		Sur_BOTbot = Region[{21000}];
		Sur_BOTtop = Region[{22000}];
		Sur_BOT = Region[{Sur_BOTbot, Sur_BOTtop}];
		Vol_BOT = Region[{2}];	
	//}
	
	//{m1.geo
		Sur_M1_botOuter = Region[{50003}];
		Sur_M1_botInner = Region[{50004}];
		Sur_M1_topOuter = Region[{50013}];
		Sur_M1_topInner = Region[{50014}];
		Sur_M1top = Region[{Sur_M1_topInner,Sur_M1_topOuter}];
		Sur_M1bot = Region[{Sur_M1_botInner,Sur_M1_botOuter}];
		Sur_M1 = Region[{Sur_M1top,Sur_M1bot}];
		Vol_M1outer = Region[{50000}];
		Vol_M1inner = Region[{50001}];
		Vol_M1 = Region[{Vol_M1inner,Vol_M1outer}];	
	//}
	
	//{m0.geo
		Sur_M0bot = Region[{48000}];
		Sur_M0top = Region[{49000}];
		Sur_M0 = Region[{Sur_M0bot,Sur_M0top}];
		Vol_M0 = Region[{5}];	
	//}
	
	//{i0.geo
		Sur_I0bot = Region[{1991}];
		Sur_I0top = Region[{1992}];
		Sur_I0 = Region[{Sur_I0bot,Sur_I0top}];
		Vol_I0 = Region[{199:234}];	
	//}
	
	//{pcb1.geo
		Sur_PCB1bot = Region[{1043}];
		Sur_PCB1top = Region[{1044}];
		Sur_PCB1sides = Region[{1045}];
		Sur_PCB1 = Region[{Sur_PCB1bot, Sur_PCB1top}];
		Vol_PCB1 = Region[{82}];
	//}
	
	//{top.geo
		Sur_TOPtop = Region[{60006}];
		Sur_TOPcTm = Region[{61003}];
		Sur_TOPncTm = Region[{62003}];
		Sur_TOPbot = Region[{60005}];
		Sur_TOPtm = Region[{Sur_TOPcTm, Sur_TOPncTm}];
		Sur_TOP = Region[{Sur_TOPtm, Sur_TOPbot, Sur_TOPtop}];
		Vol_TOP_C = Region[{61000}];				
		Vol_TOP_NC = Region[{62000}];
		Vol_TOP = Region[{Vol_TOP_C, Vol_TOP_NC}];
	//}
	
	//{wb.geo
		Sur_WBi = Region[{60001}];
		Sur_WBo = Region[{60002}];
		Sur_WB = Region[{Sur_WBi,Sur_WBo}];
		Vol_WB = Region[{313}];
	//}
	
	Sur_Disc1 = Region[{ Sur_TOPbot }];
	Vol_Disc1 = Region[{ Vol_TOP }];
	Dom_Disc1 = Region[{ Vol_Disc1, Sur_Disc1 }];
	
	Sur_Disc2 = Region[{ Sur_BOTbot, Sur_DIE_botInner }];
	Vol_Disc2 = Region[{ Vol_BOT, Vol_DIEinner  }];
	Dom_Disc2 = Region[{ Vol_Disc2, Sur_Disc2 }];
	
	Sur_Disc3 = Region[{ Sur_PCB1bot }];
	Vol_Disc3 = Region[{ Vol_PCB1 }];
	Dom_Disc3 = Region[{ Vol_Disc3, Sur_Disc3 }];
	
	Sur_Disc4 = Region[{ Sur_M1bot }];
	Vol_Disc4 = Region[{ Vol_M1 }];
	Dom_Disc4 = Region[{ Vol_Disc4, Sur_Disc4 }];
	
	Sur_Disc5 = Region[{ Sur_M0bot }];
	Vol_Disc5 = Region[{ Vol_M0 }];
	Dom_Disc5 = Region[{ Vol_Disc5, Sur_Disc5 }];
	
	Dom_Disc = Region[{Dom_Disc1,Dom_Disc2,Dom_Disc3,Dom_Disc4,Dom_Disc5}];
	
	Vol_Gen = Region[{Vol_TOP_C}];
	
	Vol_Cond = Region[{ Vol_PCB0, Vol_DIE, Vol_BOT, Vol_M1, Vol_M0,  Vol_I0, Vol_PCB1 /*,Vol_TOP ,Vol_WB*/ }];
	Vol_NL_Cond = Region[{ Vol_TOP, Vol_WB }];
	
	If(!FLcooling)						//CryoCooler System
		
		//Boundary Conditions
		Sur_Dir = Region[{Sur_PCB0north}];
		
		Sur_Neu = Region[{	Sur_PCB0bot,
							Sur_TOPtm }];
		
		//Sur_Rad = Region[{	Sur_TOPtop,
		//					Sur_PCB1top,
		//					Sur_PCB0top}];
		Sur_Rad = Region[{}];
		Sur_Conv = Region[{}];
		
	Else								//Helium Cooling System
		
		//Boundary Conditions
		Sur_Dir = Region[{Sur_PCB0sides}];
		
		Sur_Conv = Region[{	Sur_PCB0bot, 
							Sur_PCB0sides,
							Sur_PCB0top,
							Sur_DIE_extSides,
							Sur_PCB1top,
							Sur_PCB1sides,
							Sur_TOPtop }];
		
		Sur_Neu = Region[{Sur_TOPtm}];
		
		Sur_Rad = Region[{}];
		
	EndIf
	
	Dom_Hgrad_T = Region[{ Sur_Dir, Sur_Neu, Sur_Conv, Sur_Rad, Vol_Cond, Vol_NL_Cond, Dom_Disc }];
	
}

Function{
	
	//Conduction
	kPCB0[] = Tensor[C_CondPCB0/2,0,0,		0,C_CondPCB0,0,		0,0,C_CondPCB0*2];
	
	k[Sur_PCB0] = kPCB0[];
	k[Vol_PCB0] = kPCB0[];
	
	k[Sur_DIE] = C_CondDIE;
	k[Vol_DIE] = C_CondDIE;
	
	k[Sur_BOT] = C_CondBOT;
	k[Vol_BOT] = C_CondBOT;
	
	k[Sur_M1] = C_CondM1;
	k[Vol_M1] = C_CondM1;
	
	k[Sur_M0] = C_CondM0;
	k[Vol_M0] = C_CondM0;
	
	k[Sur_I0] = C_CondI0;
	k[Vol_I0] = C_CondI0;
	
	kPCB1[] = Tensor[C_CondPCB1/2,0,0,		0,C_CondPCB1,0,		0,0,C_CondPCB1*2];
					
	k[Sur_PCB1] = kPCB1[];
	k[Vol_PCB1] = kPCB1[];
	
	/*
	k[Sur_TOP] = C_CondTOP;
	k[Vol_TOP] = C_CondTOP;
	*/
	klTOP = {0, C_CondTOP/2,
			6, C_CondTOP,
			12, C_CondTOP*2};
			
	nk[Sur_TOP] = InterpolationLinear[$1]{List[klTOP]};
	nk[Vol_TOP] = InterpolationLinear[$1]{List[klTOP]};
	
	klWB = {0, C_CondWB,
			4, C_CondWB/2,
			8, C_CondWB/3,
			16, C_CondWB/4};
			
	nk[Sur_WB] = InterpolationLinear[$1]{List[klWB]};
	nk[Vol_WB] = InterpolationLinear[$1]{List[klWB]};
	
	//Boundary Functions
	If(!FLcooling)
		
		Flux[Sur_TOPtm] = BC_F1;
		Flux[Sur_PCB0bot] = BC_F2;
		
		/*
		sb = 5.6703e-8;
		f[] = 1;
		ems = 0.4;		
		rad[Sur_Rad] = ems*sb*f[];
		
		Tinf[] = R_Tinf;
		*/
	Else
		
		Flux[Sur_TOPtm] = BC_F1;
	
		h[Sur_PCB0bot] =  H_ConvPCB0;
		h[Sur_PCB0sides] = H_ConvPCB0;
		h[Sur_PCB0top] = H_ConvPCB0;
		h[Sur_DIE_extSides] = H_ConvDIE;
		h[Sur_PCB1sides] = H_ConvPCB1;
		h[Sur_PCB1top] = H_ConvPCB1;
		h[Sur_TOPtop] = H_ConvTOP;
		
		Tinf[] = H_Tinf;
		
	EndIf
	
	//Heat Generation
	Qgen[Vol_TOP_C] = BC_Q1;
	
}

Constraint{
	{ Name setTemp; Type Assign;
		Case{
			{ Region Sur_Dir; Value BC_T1; }
		}
	}
	{ Name setDisc; Type Assign;
		Case{
			{ Region Sur_Disc1; Value BC_G1; }
			{ Region Sur_Disc2; Value BC_G2; }
			{ Region Sur_Disc3; Value BC_G3; }
			{ Region Sur_Disc4; Value BC_G4; }
			{ Region Sur_Disc5; Value BC_G5; }
		}
	}
}

FunctionSpace{
	{ Name Hgrad_T; Type Form0;
		BasisFunction{
			{ Name sn; NameOfCoef Tn; Function BF_Node; Support Dom_Hgrad_T; Entity NodesOf[All]; }
			{ Name snD1; NameOfCoef TnD1; Function BF_Node; Support Dom_Disc1; Entity NodesOf[Sur_Disc1]; }
			{ Name snD2; NameOfCoef TnD2; Function BF_Node; Support Dom_Disc2; Entity NodesOf[Sur_Disc2]; }
			{ Name snD3; NameOfCoef TnD3; Function BF_Node; Support Dom_Disc3; Entity NodesOf[Sur_Disc3]; }
			{ Name snD4; NameOfCoef TnD4; Function BF_Node; Support Dom_Disc4; Entity NodesOf[Sur_Disc4]; }
			{ Name snD5; NameOfCoef TnD5; Function BF_Node; Support Dom_Disc5; Entity NodesOf[Sur_Disc5]; }
		}
		SubSpace{
			{ Name Tcon; NameOfBasisFunction {sn}; }
			{ Name Tdisc1; NameOfBasisFunction {snD1}; }
			{ Name Tdisc2; NameOfBasisFunction {snD2}; }
			{ Name Tdisc3; NameOfBasisFunction {snD3}; }
			{ Name Tdisc4; NameOfBasisFunction {snD4}; }
			{ Name Tdisc5; NameOfBasisFunction {snD5}; }
		}
		Constraint{
			{ NameOfCoef Tn; EntityType NodesOf; NameOfConstraint setTemp;}
			{ NameOfCoef TnD1; EntityType NodesOf; NameOfConstraint setDisc;}
			{ NameOfCoef TnD2; EntityType NodesOf; NameOfConstraint setDisc;}
			{ NameOfCoef TnD3; EntityType NodesOf; NameOfConstraint setDisc;}
			{ NameOfCoef TnD4; EntityType NodesOf; NameOfConstraint setDisc;}
			{ NameOfCoef TnD5; EntityType NodesOf; NameOfConstraint setDisc;}
		}
  }
}

Jacobian{
	{ Name Vol;
    Case{
      { Region All; Jacobian Vol;}
    }
  }
  { Name Sur;
    Case{
      { Region All; Jacobian Sur;}
    }
  }
}

Integration{
	{ Name Integra; Case{
		{ Type Gauss;
		  Case{
			{ GeoElement Point;      NumberOfPoints 1;}
			// 2D Elements
			{ GeoElement Line;       NumberOfPoints 3;}
			{ GeoElement Triangle;   NumberOfPoints 4;}
			{ GeoElement Quadrangle; NumberOfPoints 4;}
			// 3D Elements
			{ GeoElement Tetrahedron; NumberOfPoints 4;}
			{ GeoElement Hexahedron;  NumberOfPoints 6;}
			{ GeoElement Prism;       NumberOfPoints 6;}
		  }
		}
	}}
}

Formulation{
	{ Name ssThermal; Type FemEquation;
    Quantity{
		{ Name T; Type Local; NameOfSpace Hgrad_T;}
    }
    Equation{
        Galerkin{[ -k[]*Dof{d T} , {d T} ];
			In Vol_Cond; Jacobian Vol; Integration Integra;
        }
		Galerkin{[ -nk[{T}]*Dof{d T} , {d T} ];
			In Vol_NL_Cond; Jacobian Vol; Integration Integra;
		}
		Galerkin{[ -Qgen[] , {T} ];
			In Vol_Gen; Jacobian Vol; Integration Integra;
		}
		Galerkin{[ -Flux[] , {T} ];
			In Sur_Neu; Jacobian Sur; Integration Integra;
		}
		/*
		If(FLcooling)		//Helium Free Convection Immersion Cooling
			Galerkin{[ h[]*Dof{T} , {T} ];
				In Sur_Conv; Jacobian Sur; Integration Integra;
			}
			Galerkin{[ -h[]*Tinf[] , {T} ];
				In Sur_Conv; Jacobian Sur; Integration Integra;
			}
		Else				//CryoCooler Radiation Influx
			Galerkin{[ rad[]*(Dof{T})^4 , {T} ];
				In Sur_Rad; Jacobian Sur; Integration Integra;
			}
			Galerkin{[ -rad[]*(Tinf[])^4 , {T} ];
				In Sur_Rad; Jacobian Sur; Integration Integra;
			}
		EndIf
		*/
    }
  }
}

Resolution{
	{ Name fea;
		System{
		  { Name Thermal; NameOfFormulation ssThermal;}
		}
		Operation{
			InitSolution[Thermal];
			
			Generate[Thermal];
			Solve[Thermal];
			
			Generate[Thermal];
			GetResidual[Thermal, $res0];
			Evaluate[$res = $res0, $it = 0];
			
			Print[{$it, $res, $res/$res0}, Format "Residual %03g: abs %15.9e rel %15.9e"];
			
			While[	($res>NL_eps) && ($res/$res0 > NL_rel) && ($res/$res0 <= 1) && ($it < NL_max)]
			{	
				Solve[Thermal];
				Generate[Thermal];
				GetResidual[Thermal,  $res];
				Evaluate[$it = $it+1];
				Print[{$it, $res, $res/$res0}, Format "Residual %03g: abs %15.9e rel %15.9e"];
			}
			
			SaveSolution[Thermal];
		}
	}
}

PostProcessing{
	{ Name Tsolve; NameOfFormulation ssThermal;
		Quantity{
			{ Name T; Value{ Term{[ {T} ]; In Dom_Hgrad_T; Jacobian Vol; }}}
			{ Name qL; Value{ Term{[ -k[]*{d T} ]; In Vol_Cond; Jacobian Vol; }}}
			{ Name qNL; Value{ Term{[ -nk[{T}]*{d T} ]; In Vol_NL_Cond; Jacobian Vol; }}}
			{ Name qGen; Value{ Term{[ Qgen[] ]; In Vol_Gen; Jacobian Vol; }}}
			If(FLcooling)
				{ Name qConv; Value{ Term{[ h[]*{Grad T} ]; In Sur_Conv; Jacobian Sur; }}}
			Else
				{ Name qFlux; Value{ Term{[ Flux[] ]; In Sur_Neu; Jacobian Sur; }}}
			EndIf
		}
	}
}

PostOperation{
	{ Name HeatMap; NameOfPostProcessing Tsolve;
		Operation{
		  Print[T, OnElementsOf Dom_Hgrad_T, File "T.pos"];
		  Print[qL, OnElementsOf Dom_Hgrad_T, File "q.pos"];
		  Print[qNL, OnElementsOf Dom_Hgrad_T, File "q.pos"];
		  Print[qGen, OnElementsOf Dom_Hgrad_T, File "qG.pos"];
		  If(FLcooling)
			Print[qConv, OnElementsOf Dom_Hgrad_T, File "qC.pos"];
		  Else
			Print[qFlux, OnElementsOf Dom_Hgrad_T, File "qF.pos"];
		  EndIf
		}
	}
}