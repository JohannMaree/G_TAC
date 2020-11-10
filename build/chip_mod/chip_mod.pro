T1 = DefineNumber[4.2, Name "Simulation/BC_Temperature1_T1", Label "T1"];
F1 = DefineNumber[16, Name "Simulation/BC_HeatFlux1_F1", Label "F1"];
Q1 = DefineNumber[20, Name "Simulation/HeatGeneration1_Q1", Label "Q1"];
G1 = DefineNumber[0.8, Name "Simulation/TempDisc1_G1", Label "G1"];
G2 = DefineNumber[0.4, Name "Simulation/TempDisc2_G2", Label "G2"];
G3 = DefineNumber[0.1, Name "Simulation/TempDisc3_G3", Label "G3"];
G4 = DefineNumber[0.2, Name "Simulation/TempDisc4_G4", Label "G4"];
G5 = DefineNumber[0.1, Name "Simulation/TempDisc5_G5", Label "G5"];
kPCB0 = DefineNumber[170, Name "Simulation/PCB0_conductivity_kPCB0", Label "kPCB0"];
kDIE = DefineNumber[200, Name "Simulation/DIE_conductivity_kDIE", Label "kDIE"];
kBOT = DefineNumber[400, Name "Simulation/BOT_conductivity_kBOT", Label "kBOT"];
kM1 = DefineNumber[160, Name "Simulation/M1_conductivity_kM1", Label "kM1"];
kM0 = DefineNumber[160, Name "Simulation/M0_conductivity_kM0", Label "kM0"];
kI0 = DefineNumber[300, Name "Simulation/I0_conductivity_kI0", Label "kI0"];
kPCB1 = DefineNumber[170, Name "Simulation/PCB1_conductivity_kPCB1", Label "kPCB1"];
kTOP = DefineNumber[2, Name "Simulation/TOP_conductivity_kTOP", Label "kTOP"];
kTOP_P = {0, kTOP/2,
		8, kTOP,
		12, kTOP*2};
kWB = DefineNumber[10, Name "Simulation/WB_conductivity_kWB", Label "kWB"];
kWB_P = {0, kWB,
		4, kWB/2,
		8, kWB/3,
		16, kWB/4};
hTinf = DefineNumber[10, Name "Simulation/AmbientConvectionTemperature_hTinf", Label "hTinf"];
hPCB0 = DefineNumber[20, Name "Simulation/PCB0_ConvectionCoefficient_hPCB0", Label "hPCB0"];
hDIE = DefineNumber[30, Name "Simulation/DIE_ConvectionCoefficient_hDIE", Label "hDIE"];
hPCB1 = DefineNumber[10, Name "Simulation/PCB1_ConvectionCoefficient_hPCB1", Label "hPCB1"];
hTOP = DefineNumber[10, Name "Simulation/TOP_ConvectionCoefficient_hTOP", Label "hTOP"];
F2 = DefineNumber[-200, Name "Simulation/HeatFluxCryoCooling_F2", Label "F2"];
rTinf = DefineNumber[70, Name "Simulation/RadiationEmissiveSurfaceTemperature_rTinf", Label "rTinf"];
NL_eps = DefineNumber[1e-08, Name "NL_Iteration/_NL_eps", Label "NL_eps"];
NL_rel = DefineNumber[1e-08, Name "NL_Iteration/_NL_rel", Label "NL_rel"];
NL_loop = DefineNumber[50, Name "NL_Iteration/_NL_loop", Label "NL_loop"];



Group {
	sPCB1_bot = Region[{1043}];
	sPCB1_top = Region[{1044}];
	sPCB1_extSides = Region[{1045}];
	sI0_bot = Region[{1991}];
	sI0_top = Region[{1992}];
	sPCB0_bot = Region[{11000}];
	sPCB0_top = Region[{12000}];
	sPCB0_north = Region[{13000}];
	sPCB0_sides = Region[{14000}];
	sBOT_t38 = Region[{20000}];
	sBOT_bot21 = Region[{21000}];
	sBOT_top22 = Region[{22000}];
	sDIE_o31 = Region[{31000}];
	sDIE_o32 = Region[{32000}];
	sDIE_extSides = Region[{33000}];
	sDIE_i41 = Region[{41000}];
	sDIE_i42 = Region[{42000}];
	sM0bot_51 = Region[{48000}];
	sM0top_52 = Region[{49000}];
	sM1_botExt = Region[{50003}];
	sM1_botInt = Region[{50004}];
	sM1_topExt = Region[{50013}];
	sM1_topInt = Region[{50014}];
	sWB_Inner = Region[{60001}];
	sWB_Outer = Region[{60002}];
	sTOP_bot = Region[{60005}];
	sTOP_top = Region[{60006}];
	sTOP_CTm = Region[{61003}];
	sTOP_NCTm = Region[{62003}];
	vPCB0 = Region[{1}];
	vBOT = Region[{2}];
	vDIEext = Region[{3}];
	vDIEint = Region[{4}];
	vM0 = Region[{5}];
	vPCB1 = Region[{82}];
	vM1_Ext = Region[{50000}];
	vM1_Int = Region[{50001}];
	vWB_nc = Region[{60003}];
	vWB_c = Region[{60004}];
	vTOP_C = Region[{61000}];
	vTOP_NC = Region[{62000}];
	vI0 = Region[{199:234}];
	Disc_Surf1 = Region[{sBOT_bot21}];
	Disc_Vol1 = Region[{vBOT}];
	Disc_Dom1 = Region[{Disc_Surf1,Disc_Vol1}];
	Disc_Surf2 = Region[{sM0bot_51}];
	Disc_Vol2 = Region[{vM0}];
	Disc_Dom2 = Region[{Disc_Surf2,Disc_Vol2}];
	Disc_Surf3 = Region[{sPCB1_bot}];
	Disc_Vol3 = Region[{vPCB1}];
	Disc_Dom3 = Region[{Disc_Surf3,Disc_Vol3}];
	Disc_Surf4 = Region[{sM1_botExt}];
	Disc_Vol4 = Region[{vM1_Ext}];
	Disc_Dom4 = Region[{Disc_Surf4,Disc_Vol4}];
	Disc_Surf5 = Region[{sM1_botInt}];
	Disc_Vol5 = Region[{vM1_Int}];
	Disc_Dom5 = Region[{Disc_Surf5,Disc_Vol5}];
	Disc_Surf6 = Region[{60005}];
	Disc_Vol6 = Region[{vTOP_C}];
	Disc_Dom6 = Region[{Disc_Surf6,Disc_Vol6}];
	Disc_Surf7 = Region[{60005}];
	Disc_Vol7 = Region[{vTOP_NC}];
	Disc_Dom7 = Region[{Disc_Surf7,Disc_Vol7}];

	Cond_Regions = Region[{vPCB0,vBOT,vDIEext,vDIEint,vM0,vPCB1,vM1_Ext,vM1_Int,vI0}];
	qGen_Regions = Region[{vTOP_C}];
	Flux_Regions = Region[{sPCB0_bot,sTOP_CTm}];
	Temp_Regions = Region[{sPCB0_north}];
	Disc_Domains = Region[{Disc_Dom1,Disc_Dom2,Disc_Dom3,Disc_Dom4,Disc_Dom5,Disc_Dom6,Disc_Dom7}];
	NL_Cond_Regions = Region[{vWB_nc,vWB_c,vTOP_C,vTOP_NC}];
	Domain_H_gradT = Region[{Cond_Regions,qGen_Regions,Flux_Regions,Temp_Regions,Disc_Domains,NL_Cond_Regions}];
}


Function {
	condK[sPCB1_bot] = Tensor[kPCB1/2,0,0,0,kPCB1,0,0,0,kPCB1*2];
	condK[sPCB1_top] = Tensor[kPCB1/2,0,0,0,kPCB1,0,0,0,kPCB1*2];
	condK[sPCB1_extSides] = Tensor[kPCB1/2,0,0,0,kPCB1,0,0,0,kPCB1*2];
	condK[sI0_bot] = kI0;
	condK[sI0_top] = kI0;
	condK[sPCB0_bot] = Tensor[kPCB0/2,0,0,0,kPCB0,0,0,0,kPCB0*2];
	Flux[sPCB0_bot] = F2;
	condK[sPCB0_top] = Tensor[kPCB0/2,0,0,0,kPCB0,0,0,0,kPCB0*2];
	condK[sPCB0_north] = Tensor[kPCB0/2,0,0,0,kPCB0,0,0,0,kPCB0*2];
	condK[sPCB0_sides] = Tensor[kPCB0/2,0,0,0,kPCB0,0,0,0,kPCB0*2];
	condK[sBOT_t38] = kBOT;
	condK[sBOT_bot21] = kBOT;
	condK[sBOT_top22] = kBOT;
	condK[sDIE_o31] = kDIE;
	condK[sDIE_o32] = kDIE;
	condK[sDIE_extSides] = kDIE;
	condK[sDIE_i41] = kDIE;
	condK[sDIE_i42] = kDIE;
	condK[sM0bot_51] = kM0;
	condK[sM0top_52] = kM0;
	condK[sM1_botExt] = kM1;
	condK[sM1_botInt] = kM1;
	condK[sM1_topExt] = kM1;
	condK[sM1_topInt] = kM1;
	NL_condK[sWB_Inner] = InterpolationLinear[$1]{List[kWB_P]};
	NL_condK[sWB_Outer] = InterpolationLinear[$1]{List[kWB_P]};
	NL_condK[sTOP_bot] = InterpolationLinear[$1]{List[kTOP_P]};
	NL_condK[sTOP_top] = InterpolationLinear[$1]{List[kTOP_P]};
	NL_condK[sTOP_CTm] = InterpolationLinear[$1]{List[kTOP_P]};
	Flux[sTOP_CTm] = F1;
	NL_condK[sTOP_NCTm] = InterpolationLinear[$1]{List[kTOP_P]};
	condK[vPCB0] = Tensor[kPCB0/2,0,0,0,kPCB0,0,0,0,kPCB0*2];
	condK[vBOT] = kBOT;
	condK[vDIEext] = kDIE;
	condK[vDIEint] = kDIE;
	condK[vM0] = kM0;
	condK[vPCB1] = Tensor[kPCB1/2,0,0,0,kPCB1,0,0,0,kPCB1*2];
	condK[vM1_Ext] = kM1;
	condK[vM1_Int] = kM1;
	NL_condK[vWB_nc] = InterpolationLinear[$1]{List[kWB_P]};
	NL_condK[vWB_c] = InterpolationLinear[$1]{List[kWB_P]};
	NL_condK[vTOP_C] = InterpolationLinear[$1]{List[kTOP_P]};
	qGen[vTOP_C] = Q1;
	NL_condK[vTOP_NC] = InterpolationLinear[$1]{List[kTOP_P]};
	condK[vI0] = kI0;
}


Constraint {
	{ Name setT_BC; Type Assign;
		Case {
			{ Region sPCB0_north; Value T1; }
		}
	}
	{ Name setT_disc; Type Assign;
		Case {
			{ Region Disc_Surf1; Value G2; }
			{ Region Disc_Surf2; Value G5; }
			{ Region Disc_Surf3; Value G3; }
			{ Region Disc_Surf4; Value G4; }
			{ Region Disc_Surf5; Value G4; }
			{ Region Disc_Surf6; Value G1; }
			{ Region Disc_Surf7; Value G1; }
		}
	}
}


FunctionSpace {
	{ Name H_gradT_funcSpace; Type Form0;
		BasisFunction {
			{ Name sN; NameOfCoef Tnode; Function BF_Node; Support Domain_H_gradT; Entity NodesOf[All]; }
			{ Name sNdc1; NameOfCoef Tdc1; Function BF_Node; Support Disc_Dom1; Entity NodesOf[Disc_Surf1]; }
			{ Name sNdc2; NameOfCoef Tdc2; Function BF_Node; Support Disc_Dom2; Entity NodesOf[Disc_Surf2]; }
			{ Name sNdc3; NameOfCoef Tdc3; Function BF_Node; Support Disc_Dom3; Entity NodesOf[Disc_Surf3]; }
			{ Name sNdc4; NameOfCoef Tdc4; Function BF_Node; Support Disc_Dom4; Entity NodesOf[Disc_Surf4]; }
			{ Name sNdc5; NameOfCoef Tdc5; Function BF_Node; Support Disc_Dom5; Entity NodesOf[Disc_Surf5]; }
			{ Name sNdc6; NameOfCoef Tdc6; Function BF_Node; Support Disc_Dom6; Entity NodesOf[Disc_Surf6]; }
			{ Name sNdc7; NameOfCoef Tdc7; Function BF_Node; Support Disc_Dom7; Entity NodesOf[Disc_Surf7]; }
		}
		SubSpace {
			{ Name Tcont; NameOfBasisFunction {sN}; }
			{ Name Tdisc1; NameOfBasisFunction {sNdc1}; }
			{ Name Tdisc2; NameOfBasisFunction {sNdc2}; }
			{ Name Tdisc3; NameOfBasisFunction {sNdc3}; }
			{ Name Tdisc4; NameOfBasisFunction {sNdc4}; }
			{ Name Tdisc5; NameOfBasisFunction {sNdc5}; }
			{ Name Tdisc6; NameOfBasisFunction {sNdc6}; }
			{ Name Tdisc7; NameOfBasisFunction {sNdc7}; }
		}
		Constraint {
			{ NameOfCoef Tnode; EntityType NodesOf; NameOfConstraint setT_BC; }
			{ NameOfCoef Tdc1; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc2; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc3; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc4; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc5; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc6; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc7; EntityType NodesOf; NameOfConstraint setT_disc; }
		}
	}
}


Jacobian {
	{ Name VolumeJacobian;
		Case {
			{ Region All; Jacobian Vol; }
		}
	}
	{ Name SurfaceJacobian;
		Case {
			{ Region All; Jacobian Sur; }
		}
	}
}


Integration {
	{ Name GaussIntegration; 
		Case {
			{ Type Gauss;
				Case{
					{ GeoElement Point;			NumberOfPoints 1; }
					{ GeoElement Line;			NumberOfPoints 3; }
					{ GeoElement Triangle;		NumberOfPoints 4; }
					{ GeoElement Quadrangle;	NumberOfPoints 4; }
					{ GeoElement Tetrahedron;	NumberOfPoints 4; }
					{ GeoElement Hexahedron;	NumberOfPoints 6; }
					{ GeoElement Prism;			NumberOfPoints 6; }
				}
			}
		}
	}
}


Formulation {
	{ Name thermal_Formulation; Type FemEquation;
		Quantity {
			{ Name T; Type Local; NameOfSpace H_gradT_funcSpace; }
			{ Name Tcn; Type Local; NameOfSpace H_gradT_funcSpace[Tcont]; }
			{ Name Tdc1; Type Local; NameOfSpace H_gradT_funcSpace[Tdisc1]; }
			{ Name Tdc2; Type Local; NameOfSpace H_gradT_funcSpace[Tdisc2]; }
			{ Name Tdc3; Type Local; NameOfSpace H_gradT_funcSpace[Tdisc3]; }
			{ Name Tdc4; Type Local; NameOfSpace H_gradT_funcSpace[Tdisc4]; }
			{ Name Tdc5; Type Local; NameOfSpace H_gradT_funcSpace[Tdisc5]; }
			{ Name Tdc6; Type Local; NameOfSpace H_gradT_funcSpace[Tdisc6]; }
			{ Name Tdc7; Type Local; NameOfSpace H_gradT_funcSpace[Tdisc7]; }
		}
		Equation {
			Galerkin { [ -condK[] * Dof{d T} , {d T} ];
				In Cond_Regions; Jacobian VolumeJacobian; Integration GaussIntegration; }
			Galerkin { [ -qGen[] , {T} ];
				In qGen_Regions; Jacobian VolumeJacobian; Integration GaussIntegration; }
			Galerkin { [ -Flux[] , {T} ];
				In Flux_Regions; Jacobian SurfaceJacobian; Integration GaussIntegration; }
			Galerkin { [ -NL_condK[ {T} ] * Dof{d T} , {d T} ];
				In NL_Cond_Regions; Jacobian VolumeJacobian; Integration GaussIntegration; }
		}
	}
}


Resolution {
	{ Name thermal_Resolution;
		System {
			{ Name thermal_System_NL; NameOfFormulation thermal_Formulation; }
		}
		Operation {
			InitSolution[thermal_System_NL];
			Generate[thermal_System_NL];
			Solve[thermal_System_NL];

			Generate[thermal_System_NL];
			GetResidual[thermal_System_NL, $res0];
			Evaluate[$res = $res0];
			Evaluate[$i = 0];

			Print[{$i, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

			While[($res > NL_eps)&&($res/$res0 > NL_rel)&&($res/$res0 <= 1)&&($i < NL_loop)]{

				Solve[thermal_System_NL];
				Generate[thermal_System_NL];
				GetResidual[thermal_System_NL, $res];
				Evaluate[$i = $i + 1];
				Print[{$i, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

			}
			SaveSolution[thermal_System_NL];
		}
	}
}


PostProcessing {
	{ Name thermal_PostProcess; NameOfFormulation thermal_Formulation;
		Quantity {
			{ Name T; Value {
				Term{[ {T} ]; In Domain_H_gradT; Jacobian VolumeJacobian; }
			}}
			{ Name q; Value {
				Term{[ -condK[]*{d T} ]; In Cond_Regions; Jacobian VolumeJacobian; }
			}}
			{ Name Qgen; Value {
				Term{[ qGen[] ]; In qGen_Regions; Jacobian VolumeJacobian; }
			}}
			{ Name qNL; Value {
				Term{[ -NL_condK[ {T} ]*{d T} ]; In NL_Cond_Regions; Jacobian VolumeJacobian; }
			}}
			{ Name Tcn; Value {
				Term{[ {Tcn} ]; In Domain_H_gradT; Jacobian VolumeJacobian; }
			}}
			{ Name Tdc1; Value {
				Term{[ {Tdc1} ]; In Disc_Domains; Jacobian VolumeJacobian; }
			}}
			{ Name Tdc2; Value {
				Term{[ {Tdc2} ]; In Disc_Domains; Jacobian VolumeJacobian; }
			}}
			{ Name Tdc3; Value {
				Term{[ {Tdc3} ]; In Disc_Domains; Jacobian VolumeJacobian; }
			}}
			{ Name Tdc4; Value {
				Term{[ {Tdc4} ]; In Disc_Domains; Jacobian VolumeJacobian; }
			}}
			{ Name Tdc5; Value {
				Term{[ {Tdc5} ]; In Disc_Domains; Jacobian VolumeJacobian; }
			}}
			{ Name Tdc6; Value {
				Term{[ {Tdc6} ]; In Disc_Domains; Jacobian VolumeJacobian; }
			}}
			{ Name Tdc7; Value {
				Term{[ {Tdc7} ]; In Disc_Domains; Jacobian VolumeJacobian; }
			}}
		}
	}
}


PostOperation {
	{ Name thermal_PostOperation; NameOfPostProcessing thermal_PostProcess;
		Operation {
			Print[T, OnElementsOf Domain_H_gradT, File "T_map.pos"];
			Print[q, OnElementsOf Cond_Regions, File "q_map.pos"];
			Print[Qgen, OnElementsOf qGen_Regions, File "Qgen_map.pos"];
			Print[qNL, OnElementsOf NL_Cond_Regions, File > "q_map.pos"];
			Print[Tcn, OnElementsOf Domain_H_gradT, File "Tcn_map.pos"];
			Print[Tdc1, OnElementsOf Disc_Dom1, File "Tdc_map.pos"];
			Print[Tdc2, OnElementsOf Disc_Dom2, File > "Tdc_map.pos"];
			Print[Tdc3, OnElementsOf Disc_Dom3, File > "Tdc_map.pos"];
			Print[Tdc4, OnElementsOf Disc_Dom4, File > "Tdc_map.pos"];
			Print[Tdc5, OnElementsOf Disc_Dom5, File > "Tdc_map.pos"];
			Print[Tdc6, OnElementsOf Disc_Dom6, File > "Tdc_map.pos"];
			Print[Tdc7, OnElementsOf Disc_Dom7, File > "Tdc_map.pos"];
		}
	}
}


