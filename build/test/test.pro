kR = DefineNumber[100, Name "Analysis/ThermCondCoeffRight_kR", Label "kR", MAX 600, MIN 0];
kL = DefineNumber[20, Name "Analysis/ThermCondCoeffLeft_kL", Label "kL", MAX 100, MIN 0];
h = DefineNumber[25, Name "Analysis/ThermalConvectionCoefficient_h", Label "h", MIN 0];
TINF = DefineNumber[80, Name "Analysis/InfiniteConvectionTemperature_TINF", Label "TINF"];
Tfix = DefineNumber[40, Name "Analysis/FixedTemperature_Tfix", Label "Tfix"];
Qflux = DefineNumber[60, Name "Analysis/HeatFlux_Qflux", Label "Qflux"];



Group {
	REC1 = Region[1000];
	REC2 = Region[1001];
	R1 = Region[100];
	L1 = Region[101];
	Cond_Elements = Region[{REC1,REC2}];
	Flux_Elements = Region[{L1}];
	Temp_Elements = Region[{R1}];
	Domain_Hgrad_T = Region[{Cond_Elements,Flux_Elements,Temp_Elements}];
}


Function {
	conK[REC1] = kR;
	conK[REC2] = kL;
	Flux[L1] = Qflux;
}


Constraint {
	{ Name Type1BC; Type Assign;
		Case {
			{ Region R1; Value Tfix; }
		}
	}
}


FunctionSpace {
	{ Name Hgrad_Tspace; Type Form0;
		BasisFunction {
			{ Name sN; NameOfCoef TN; Function BF_Node; Support Domain_Hgrad_T; Entity NodesOf[All]; }
		}
		Constraint {
			{ NameOfCoef TN; EntityType NodesOf; NameOfConstraint Type1BC; }
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
					{ GeoElement Point;		NumberOfPoints 1; }
					{ GeoElement Line;		NumberOfPoints 3; }
					{ GeoElement Triangle;		NumberOfPoints 4; }
					{ GeoElement Quadrangle;		NumberOfPoints 4; }
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
			Integral { [ conK[] * Dof{d T} , {d T} ];
				In Cond_Elements; Jacobian Volume; Integration Integra; }
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


