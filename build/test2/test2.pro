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
kL_T = Tensor[
kL,0,0,
0,kL,0,
0,0,kL];
NL_eps = DefineNumber[1e-09, Name "NL_Iteration/_NL_eps", Label "NL_eps"];
NL_rel = DefineNumber[1e-09, Name "NL_Iteration/_NL_rel", Label "NL_rel"];
NL_loop = DefineNumber[30, Name "NL_Iteration/_NL_loop", Label "NL_loop"];



Group {
	boundL = Region[{100}];
	boundR = Region[{101}];
	RecL = Region[{1000}];
	RecR = Region[{1001}];
	RecM = Region[{1002}];
	boundL = Region[{100}];
	boundR = Region[{101}];
	RecL = Region[{1000}];
	RecR = Region[{1001}];
	RecM = Region[{1002}];

	Cond_Elements = Region[{RecL,RecR}];
	Flux_Regions = Region[{boundR}];
	Temp_Regions = Region[{boundL}];
	NL_Cond_Regions = Region[{RecM}];
	Domain_H_grad_T = Region[{Cond_Elements,Flux_Regions,Temp_Regions,NL_Cond_Regions}];
}


Function {
	Flux[boundR] = Fl;
	condK[RecL] = kL;
	condK[RecR] = kR;
	NL_condK[RecM] = InterpolationLinear[$1]{List[kM_NL]};
}


Constraint {
	{ Name setT_BC; Type Assign;
		Case {
			{ Region boundL; Value Tf; }
		}
	}
}


FunctionSpace {
	{ Name H_grad_T_fspace; Type Form0;
		BasisFunction {
			{ Name sN; NameOfCoef T_Node; Function BF_Node; Support Domain_H_grad_T; Entity NodesOf[All]; }
		}
		Constraint {
			{ NameOfCoef T_Node; EntityType NodesOf; NameOfConstraint setT_BC; }
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
				}
			}
		}
	}
}


Formulation {
	{ Name def_ThermalForm; Type FemEquation;
		Quantity {
			{ Name T; Type Local; NameOfSpace H_grad_T_fspace; }
		}
		Equation {
			Integral { [ condK[] * Dof{d T} , {d T} ];
				In Cond_Elements; Jacobian VolumeJac; Integration GaussIntegra; }
			Integral { [ -Flux[] , {T} ];
				In Flux_Regions; Jacobian SurfaceJac; Integration GaussIntegra; }
			Integral { [ NL_condK[ {T} ] * Dof{d T} , {d T} ];
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
			Evaluate[$iTeration = 0];

			Print[{$iTeration, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

			While[($res > NL_eps)&&($res/$res0 > NL_rel)&&($res/$res0 <= 1)&&($iTeration < NL_loop)]{

				Solve[def_NL_System];
				Generate[def_NL_System];
				GetResidual[def_NL_System, $res];
			Evaluate[$iTeration = $iTeration + 1];
			Print[{$iTeration, $res, $res/$res0}, Format "Residual %0.3g: abs %14.9e rel %14.9e"];

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
				Term{[ -{d T} ]; In Domain_H_grad_T; Jacobian VolumeJac; }
			}}
		}
	}
}


PostOperation {
	{ Name def_HeatMap; NameOfPostProcessing def_Thermals;
		Operation {
			Print[T, OnElementsOf Domain_H_grad_T, File "T_map.pos"];
			Print[q, OnElementsOf Domain_H_grad_T, File "q_map.pos"];
		}
	}
}


