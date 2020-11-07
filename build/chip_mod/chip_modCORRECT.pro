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
		6, kTOP,
		12, kTOP*2};
kWB = DefineNumber[10, Name "Simulation/WB_conductivity_kWB", Label "kWB"];
kWB_P = {0, kWB,
		4, kWB/2,
		8, kWB/3,
		16, kWB/4};
		
//hTinf = DefineNumber[10, Name "Simulation/AmbientConvectionTemperature_hTinf", Label "hTinf"];
//hPCB0 = DefineNumber[20, Name "Simulation/PCB0_ConvectionCoefficient_hPCB0", Label "hPCB0"];
//hDIE = DefineNumber[30, Name "Simulation/DIE_ConvectionCoefficient_hDIE", Label "hDIE"];
//hPCB1 = DefineNumber[10, Name "Simulation/PCB1_ConvectionCoefficient_hPCB1", Label "hPCB1"];
//hTOP = DefineNumber[10, Name "Simulation/TOP_ConvectionCoefficient_hTOP", Label "hTOP"];

//rTinf = DefineNumber[70, Name "Simulation/RadiationEmissiveSurfaceTemperature_rTinf", Label "rTinf"];
F2 = DefineNumber[-200, Name "Simulation/HeatFluxCryoCooling_F2", Label "F2"];


NL_eps = DefineNumber[1e-6, Name "NL_Iteration/_NL_eps", Label "NL_eps"];
NL_rel = DefineNumber[1e-5, Name "NL_Iteration/_NL_rel", Label "NL_rel"];
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
	vTOP = Region[{61000,62000}];
	vI0 = Region[{199:234}];
	vWB = Region[{313}];
	
	//PCB0_TOP Discont G2
	Disc_Surf1 = Region[{sBOT_bot21, sDIE_i41}];
	Disc_Vol1 = Region[{vBOT,vDIEint}];
	Disc_Dom1 = Region[{Disc_Surf1,Disc_Vol1}];
	
	//M0 Discont G5
	Disc_Surf2 = Region[{sM0bot_51}];
	Disc_Vol2 = Region[{vM0}];
	Disc_Dom2 = Region[{Disc_Surf2,Disc_Vol2}];
	
	//PCB1_BOT Discont G3
	Disc_Surf3 = Region[{sPCB1_bot}];
	Disc_Vol3 = Region[{vPCB1}];
	Disc_Dom3 = Region[{Disc_Surf3,Disc_Vol3}];
	
	//M1 Discont G4
	Disc_Surf4 = Region[{sM1_botExt,sM1_botInt}];
	Disc_Vol4 = Region[{vM1_Ext,vM1_Int}];
	Disc_Dom4 = Region[{Disc_Surf4,Disc_Vol4}];
	
	//TOP_BOT Discont G1
	Disc_Surf6 = Region[{sTOP_bot}];
	Disc_Vol6 = Region[{vTOP}];
	Disc_Dom6 = Region[{Disc_Surf6,Disc_Vol6}];

	Cond_Elements = Region[{vPCB0,vBOT,vDIEext,vDIEint,vM0,vPCB1,vM1_Ext,vM1_Int,vI0}];
	qGen_Regions = Region[{vTOP_C}];
	Flux_Regions = Region[{sPCB0_bot,sTOP_CTm,sTOP_NCTm}];
	Disc_Domains = Region[{Disc_Dom1,Disc_Dom2,Disc_Dom3,Disc_Dom4,Disc_Dom6}];
	NL_Cond_Regions = Region[{vWB,vTOP}];
	
	Domain_H_grad_T = Region[{Cond_Elements,qGen_Regions,Flux_Regions,Disc_Domains,NL_Cond_Regions}];
}


Function {
	
	tPCB0[] = Tensor[kPCB0/2,0,0,	0,kPCB0,0,		0,0,kPCB0*2];
	condK[sPCB0_bot] = tPCB0[];
	condK[vPCB0] = tPCB0[];
	condK[sPCB0_top] = tPCB0[];
	condK[sPCB0_north] = tPCB0[];
	condK[sPCB0_sides] = tPCB0[];
	
	condK[sBOT_t38] = kBOT;
	condK[sBOT_bot21] = kBOT;
	condK[sBOT_top22] = kBOT;
	condK[vBOT] = kBOT;
	
	condK[sDIE_o31] = kDIE;
	condK[sDIE_o32] = kDIE;
	condK[sDIE_extSides] = kDIE;
	condK[sDIE_i41] = kDIE;
	condK[sDIE_i42] = kDIE;
	condK[vDIEext] = kDIE;
	condK[vDIEint] = kDIE;
	
	condK[sM1_botExt] = kM1;
	condK[sM1_botInt] = kM1;
	condK[sM1_topExt] = kM1;
	condK[sM1_topInt] = kM1;
	condK[vM1_Ext] = kM1;
	condK[vM1_Int] = kM1;
	
	condK[sM0bot_51] = kM0;
	condK[sM0top_52] = kM0;
	condK[vM0] = kM0;
	
	condK[sI0_bot] = kI0;
	condK[sI0_top] = kI0;
	condK[vI0] = kI0;
	
	tPCB1[] = Tensor[kPCB1/2,0,0,	0,kPCB1,0,		0,0,kPCB1*2];
	condK[vPCB1] = tPCB1[];
	condK[sPCB1_bot] = tPCB1[];
	condK[sPCB1_top] = tPCB1[];
	condK[sPCB1_extSides] = tPCB1[];
	
	NL_condK[sTOP_bot] = InterpolationLinear[$1]{List[kTOP_P]};
	NL_condK[sTOP_top] = InterpolationLinear[$1]{List[kTOP_P]};
	NL_condK[sTOP_CTm] = InterpolationLinear[$1]{List[kTOP_P]};
	NL_condK[sTOP_NCTm] = InterpolationLinear[$1]{List[kTOP_P]};
	NL_condK[vTOP] = InterpolationLinear[$1]{List[kTOP_P]};
	
	NL_condK[sWB_Inner] = InterpolationLinear[$1]{List[kWB_P]};
	NL_condK[sWB_Outer] = InterpolationLinear[$1]{List[kWB_P]};
	NL_condK[vWB] = InterpolationLinear[$1]{List[kWB_P]};
	
	Flux[sTOP_CTm] = F1;
	Flux[sTOP_NCTm] = F1;
	Flux[sPCB0_bot] = F2;
	
	qGen[vTOP_C] = Q1;
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
			{ Region Disc_Surf6; Value G1; }
		}
	}
}


FunctionSpace {
	{ Name H_grad_T_fspace; Type Form0;
		BasisFunction {
			{ Name sN; NameOfCoef T_Node; Function BF_Node; Support Domain_H_grad_T; Entity NodesOf[All]; }
			{ Name sNdc1; NameOfCoef Tdc1; Function BF_Node; Support Disc_Dom1; Entity NodesOf[Disc_Surf1]; }
			{ Name sNdc2; NameOfCoef Tdc2; Function BF_Node; Support Disc_Dom2; Entity NodesOf[Disc_Surf2]; }
			{ Name sNdc3; NameOfCoef Tdc3; Function BF_Node; Support Disc_Dom3; Entity NodesOf[Disc_Surf3]; }
			{ Name sNdc4; NameOfCoef Tdc4; Function BF_Node; Support Disc_Dom4; Entity NodesOf[Disc_Surf4]; }
			{ Name sNdc6; NameOfCoef Tdc6; Function BF_Node; Support Disc_Dom6; Entity NodesOf[Disc_Surf6]; }
		}
		SubSpace {
			{ Name Tcont; NameOfBasisFunction {sN}; }
			{ Name Tdisc1; NameOfBasisFunction {sNdc1}; }
			{ Name Tdisc2; NameOfBasisFunction {sNdc2}; }
			{ Name Tdisc3; NameOfBasisFunction {sNdc3}; }
			{ Name Tdisc4; NameOfBasisFunction {sNdc4}; }
			{ Name Tdisc6; NameOfBasisFunction {sNdc6}; }
		}
		Constraint {
			{ NameOfCoef T_Node; EntityType NodesOf; NameOfConstraint setT_BC; }
			{ NameOfCoef Tdc1; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc2; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc3; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc4; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc6; EntityType NodesOf; NameOfConstraint setT_disc; }
		}
	}
}


Jacobian {
	{ Name VolumeJac;
		Case {
			{ Region All; Jacobian Vol; }
		}
	}
	{ Name SurfaceJac;
		Case {
			{ Region All; Jacobian Sur; }
		}
	}
}


Integration {
	{ Name GaussIntegra; 
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
	{ Name def_ThermalForm; Type FemEquation;
		Quantity {
			{ Name T; Type Local; NameOfSpace H_grad_T_fspace; }
			//{ Name Tcn; Type Local; NameOfSpace H_grad_T_fspace[Tcont]; }
			//{ Name Tdc1; Type Local; NameOfSpace H_grad_T_fspace[Tdisc1]; }
			//{ Name Tdc2; Type Local; NameOfSpace H_grad_T_fspace[Tdisc2]; }
			//{ Name Tdc3; Type Local; NameOfSpace H_grad_T_fspace[Tdisc3]; }
			//{ Name Tdc4; Type Local; NameOfSpace H_grad_T_fspace[Tdisc4]; }
			//{ Name Tdc6; Type Local; NameOfSpace H_grad_T_fspace[Tdisc6]; }
		}
		Equation {
			Galerkin { [ -condK[] * Dof{d T} , {d T} ];
				In Cond_Elements; Jacobian VolumeJac; Integration GaussIntegra; }
			Galerkin { [ -qGen[] , {T} ];
				In qGen_Regions; Jacobian VolumeJac; Integration GaussIntegra; }
			Galerkin { [ -Flux[] , {T} ];
				In Flux_Regions; Jacobian SurfaceJac; Integration GaussIntegra; }
			Galerkin { [ -NL_condK[{T}] * Dof{d T} , {d T} ];
				In NL_Cond_Regions; Jacobian VolumeJac; Integration GaussIntegra; }
		}
	}
}


Resolution {
	{ Name def_ThermalRes;
		System {
			{ Name def_NL_System; NameOfFormulation def_ThermalForm; }
		}
		Operation {
			InitSolution[def_NL_System];
			
			Generate[def_NL_System];
			Solve[def_NL_System];

			Generate[def_NL_System];
			GetResidual[def_NL_System, $res0];
			Evaluate[$res = $res0];
			Evaluate[$i = 0];

			Print[{$i, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

			While[ 	($res > NL_eps)&&
					($res/$res0 > NL_rel)&&
					($res/$res0 <= 1)&&
					($i < NL_loop)]{

				Solve[def_NL_System];
				Generate[def_NL_System];
				GetResidual[def_NL_System, $res];
				Evaluate[$i = $i + 1];
				Print[{$i, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

			}
			SaveSolution[def_NL_System];
		}
	}
}


PostProcessing {
	{ Name def_Thermals; NameOfFormulation def_ThermalForm;
		Quantity {
			{ Name T; Value {
				Term{[ {T} ]; In Domain_H_grad_T; Jacobian VolumeJac; }
			}}
			{ Name q; Value {
				Term{[ -condK[]*{d T} ]; In Cond_Elements; Jacobian VolumeJac; }
			}}
			{ Name qNL; Value {
				Term{[ -NL_condK[{T}]*{d T} ]; In NL_Cond_Regions; Jacobian VolumeJac; }
			}}
			{ Name Qgen; Value {
				Term{[ qGen[] ]; In qGen_Regions; Jacobian VolumeJac; }
			}}
			/*
			{ Name Tcn; Value {
				Term{[ {Tcn} ]; In Domain_H_grad_T; Jacobian VolumeJac; }
			}}
			{ Name Tdc1; Value {
				Term{[ {Tdc1} ]; In Disc_Dom1; Jacobian VolumeJac; }
			}}
			{ Name Tdc2; Value {
				Term{[ {Tdc2} ]; In Disc_Dom2; Jacobian VolumeJac; }
			}}
			{ Name Tdc3; Value {
				Term{[ {Tdc3} ]; In Disc_Dom3; Jacobian VolumeJac; }
			}}
			{ Name Tdc4; Value {
				Term{[ {Tdc4} ]; In Disc_Dom4; Jacobian VolumeJac; }
			}}
			{ Name Tdc6; Value {
				Term{[ {Tdc6} ]; In Disc_Dom6; Jacobian VolumeJac; }
			}}
			*/
		}
	}
}


PostOperation {
	{ Name def_HeatMap; NameOfPostProcessing def_Thermals;
		Operation {
			Print[T, OnElementsOf Domain_H_grad_T, File "T_map.pos"];
			Print[q, OnElementsOf Domain_H_grad_T, File "q_map.pos"];
			Print[qNL,OnElementsOf Domain_H_grad_T, File "q_map.pos"];
			Print[Qgen, OnElementsOf Domain_H_grad_T, File "qG.pos"];
			/*
			Print[Tcn, OnElementsOf Domain_H_grad_T, File "Tcn_map.pos"];
			Print[Tdc1, OnElementsOf Disc_Dom1, File "Tdc_map.pos"];
			Print[Tdc2, OnElementsOf Disc_Dom2, File "Tdc_map.pos"];
			Print[Tdc3, OnElementsOf Disc_Dom3, File "Tdc_map.pos"];
			Print[Tdc4, OnElementsOf Disc_Dom4, File "Tdc_map.pos"];
			Print[Tdc6, OnElementsOf Disc_Dom6, File "Tdc_map.pos"];
			*/
		}
	}
}


