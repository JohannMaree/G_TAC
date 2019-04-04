kO = DefineNumber[100, Name "Analysis/K_Outer_kO", Label "kO", MAX 600, MIN 0];
kI = DefineNumber[200, Name "Analysis/K_Inner_kI", Label "kI", MAX 1000, MIN 0, STEP 2];
kW = DefineNumber[800, Name "Analysis/K_Wire_kW", Label "kW", MAX 1000, MIN 0, STEP 4];
h = DefineNumber[25, Name "Analysis/H_convec_h", Label "h"];
Tinf = DefineNumber[80, Name "Analysis/Tinf_Convec_Tinf", Label "Tinf"];
Tfix = DefineNumber[40, Name "Analysis/FixTemp_Tfix", Label "Tfix"];
Qflux = DefineNumber[60, Name "Analysis/HeatFlux_Qflux", Label "Qflux"];
Qgen1 = DefineNumber[200, Name "Analysis/HeatGenWire_Qgen1", Label "Qgen1"];
Qgen2 = DefineNumber[0, Name "Analysis/HeatGenSQU_Qgen2", Label "Qgen2"];



Group {
	bound1 = Region[100];
	bound2 = Region[101];
	Rec1 = Region[1000];
	Rec2 = Region[1001];
	Wire = Region[1002];
	Cond_Elements = Region[{Rec1,Rec2,Wire}];
	Conv_Elements = Region[{Rec2}];
	qGen_Elements = Region[{Wire}];
	Flux_Elements = Region[{bound2,Rec2}];
	Temp_Elements = Region[{bound1}];
	Domain_Hgrad_T = Region[{Cond_Elements,Conv_Elements,qGen_Elements,Flux_Elements,Temp_Elements}];
}


Function {
	Flux[bound2] = Qgen2;
	condK[Rec1] = kO;
	condK[Rec2] = kI;
	convH[Rec2] = h;
	TinfConv[Rec2] = Tinf;
	Flux[Rec2] = Qflux;
	condK[Wire] = kW;
	qGen[Wire] = Qgen1;
}


Constraint {
	{ Name Type1BC; Type Assign;
		Case {
			{ Region bound1; Value Tfix; }
		}
	}
}


FunctionSpace {
	{ Name Hgrad_Tspace; Type Form0;
		BasisFunction {
			{ Name sN; NameOfCoef T_Node; Function BF_Node; Support Domain_Hgrad_T; Entity NodesOf[All]; }
		}
		Constraint {
			{ NameOfCoef T_Node; EntityType NodesOf; NameOfConstraint Type1BC; }
		}
	}
}


Jacobian {
	{ Name Volume;
		Case {
			{ Region All; Jacobian Vol; }
		}
	}
	{ Name Surface;
		Case {
			{ Region All; Jacobian Sur; }
		}
	}
}


Integration {
	{ Name Integra; 
		Case {
			{ Type Gauss;
				Case{
					{ GeoElement Point;			NumberOfPoints 1; }
					{ GeoElement Line;			NumberOfPoints 3; }
					{ GeoElement Triangle;		NumberOfPoints 4; }
					{ GeoElement Quadrangle;	NumberOfPoints 4; }
				}
			}
		}
	}
}


Formulation {
	{ Name def_ThermalForm; Type FemEquation;
		Quantity {
			{ Name T; Type Local; NameOfSpace Hgrad_Tspace; }
		}
		Equation {
			Integral { [ condK[] * Dof{d T} , {d T} ];
				In Cond_Elements; Jacobian Volume; Integration Integra; }
			Integral { [ convH[] * Dof{T} , {T} ];
				In Conv_Elements; Jacobian Surface; Integration Integra; }
			Integral { [ -convH[] * TinfConv[] , {T} ];
				In Conv_Elements; Jacobian Surface; Integration Integra; }
			Integral { [ -qGen[] , {T} ];
				In qGen_Elements; Jacobian Volume; Integration Integra; }
			Integral { [ -Flux[] , {T} ];
				In Flux_Elements; Jacobian Surface; Integration Integra; }
		}
	}
}


Resolution {
	{ Name def_ThermalRes;
		System {
			{ Name def_System; NameOfFormulation def_ThermalForm; }
		}
		Operation {
			Generate[def_System];
			Solve[def_System];
			SaveSolution[def_System];
		}
	}
}


PostProcessing {
	{ Name def_Thermals; NameOfFormulation def_ThermalForm;
		Quantity {
			{ Name T; Value {
				Term{[ {T} ]; In Domain_Hgrad_T; Jacobian Volume; }
			}}
			{ Name q; Value {
				Term{[ -{d T} ]; In Domain_Hgrad_T; Jacobian Volume; }
			}}
			{ Name Qgen; Value {
				Term{[ qGen[] ]; In Domain_Hgrad_T; Jacobian Volume; }
			}}
		}
	}
}


PostOperation {
	{ Name def_HeatMap; NameOfPostProcessing def_Thermals;
		Operation {
			Print[T, OnElementsOf Domain_Hgrad_T, File "T_map.pos"];
			Print[q, OnElementsOf Domain_Hgrad_T, File "q_map.pos"];
		}
	}
}


