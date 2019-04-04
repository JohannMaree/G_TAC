kL = DefineNumber[160, Name "FEA/CondK_Left_kL", Label "kL"];
kR = DefineNumber[240, Name "FEA/CondK_Right_kR", Label "kR"];
Tf = DefineNumber[20, Name "FEA/Temp_BC_Tf", Label "Tf", MAX 300, MIN 0];
Fl = DefineNumber[200, Name "FEA/Flux_BC_Fl", Label "Fl"];
kM_NL = {0, 4,
		10, 8,
		100, 12,
		200, 16,
		500, 20,
		800, 32};
NL_eps = DefineNumber[1e-09, Name "NL_Iteration/_NL_eps", Label "NL_eps"];
NL_rel = DefineNumber[1e-09, Name "NL_Iteration/_NL_rel", Label "NL_rel"];
NL_loop = DefineNumber[30, Name "NL_Iteration/_NL_loop", Label "NL_loop"];



Group {
	boundL = Region[100];
	boundR = Region[101];
	RecL = Region[1000];
	RecR = Region[1001];
	RecM = Region[1002];

	Cond_Elements = Region[{RecL,RecR}];
	Flux_Elements = Region[{boundR}];
	Temp_Elements = Region[{boundL}];
	NL_Cond_Elements = Region[{RecM}];
	Domain_Hgrad_T = Region[{Cond_Elements,Flux_Elements,Temp_Elements,NL_Cond_Elements}];
}


Function {
	Flux[boundR] = Fl;
	condK[RecL] = kL;
	condK[RecR] = kR;
	NL_condK[RecM] = InterpolationLinear[$1]{List[kM_NL]};
}


Constraint {
	{ Name Type1BC; Type Assign;
		Case {
			{ Region boundL; Value Tf; }
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
			Integral { [ -Flux[] , {T} ];
				In Flux_Elements; Jacobian Surface; Integration Integra; }
			Integral { [ NL_condK[ {T} ] * Dof{d T} , {d T} ];
				In NL_Cond_Elements; Jacobian Volume; Integration Integra; }
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
			Evaluate[$iT = 0];

			Print[{$iT, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

			While[($res > NL_eps)&&($res/$res0 > NL_rel)&&($res/$res0 <= 1)&&($iT < NL_loop)]{

				Solve[def_NL_System];
				Generate[def_NL_System];
				GetResidual[def_NL_System, $res];
				Evaluate[$iT = $iT + 1];
				Print[{$iT, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

			}
			SaveSolution[def_NL_System];
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


