kO = DefineNumber[100, Name "Analysis/K_Outer_kO", Label "kO", MAX 600, MIN 0];
kI = DefineNumber[200, Name "Analysis/K_Inner_kI", Label "kI", MAX 1000, MIN 0, STEP 2];
kW = DefineNumber[800, Name "Analysis/K_Wire_kW", Label "kW", MAX 1000, MIN 0, STEP 4];
h = DefineNumber[25, Name "Analysis/_h", Label "h"];
Tinf = DefineNumber[80, Name "Analysis/_Tinf", Label "Tinf"];
Tfix = DefineNumber[40, Name "Analysis/_Tfix", Label "Tfix"];
Qflux = DefineNumber[400, Name "Analysis/_Qflux", Label "Qflux"];
QgenWire = DefineNumber[200, Name "Analysis/_QgenWire", Label "QgenWire"];
QgenInner = DefineNumber[0, Name "Analysis/_QgenInner", Label "QgenInner"];
TdWire = DefineNumber[8, Name "Analysis/_TdWire", Label "TdWire"];



Group {
	innerB = Region[{1}];
	innerT = Region[{2}];
	innerS = Region[{3}];
	innerE = Region[{4}];
	innerN = Region[{5}];
	innerW = Region[{6}];
	outerT = Region[{11}];
	outerB = Region[{12}];
	outerS = Region[{13}];
	outerE = Region[{14}];
	outerN = Region[{15}];
	outerW = Region[{16}];
	wireB = Region[{21}];
	vol1 = Region[{1001}];
	vol2 = Region[{1002}];
	vol3 = Region[{1003}];
	Disc_Surf1 = Region[{innerB}];
	Disc_Vol1 = Region[{vol2}];
	Disc_Dom1 = Region[{Disc_Surf1,Disc_Vol1}];
	Disc_Surf2 = Region[{wireB}];
	Disc_Vol2 = Region[{vol3}];
	Disc_Dom2 = Region[{Disc_Surf2,Disc_Vol2}];

	Cond_Elements = Region[{vol1,vol2,vol3}];
	qGen_Regions = Region[{vol2,vol3}];
	Flux_Regions = Region[{innerT}];
	Temp_Regions = Region[{outerB}];
	Disc_Domains = Region[{Disc_Dom1,Disc_Dom2}];
	Domain_H_grad_T = Region[{Cond_Elements,qGen_Regions,Flux_Regions,Temp_Regions,Disc_Domains}];
}


Function {
	Flux[innerT] = Qflux;
	condK[vol1] = kO;
	condK[vol2] = kI;
	qGen[vol2] = QgenInner;
	condK[vol3] = kW;
	qGen[vol3] = QgenWire;
}


Constraint {
	{ Name setT_BC; Type Assign;
		Case {
			{ Region outerB; Value Tfix; }
		}
	}
	{ Name setT_disc; Type Assign;
		Case {
			{ Region Disc_Surf1; Value +4; }
			{ Region Disc_Surf2; Value TdWire; }
		}
	}
}


FunctionSpace {
	{ Name H_grad_T_fspace; Type Form0;
		BasisFunction {
			{ Name sN; NameOfCoef T_Node; Function BF_Node; Support Domain_H_grad_T; Entity NodesOf[All]; }
			{ Name sNdc1; NameOfCoef Tdc1; Function BF_Node; Support Disc_Dom1; Entity NodesOf[Disc_Surf1]; }
			{ Name sNdc2; NameOfCoef Tdc2; Function BF_Node; Support Disc_Dom2; Entity NodesOf[Disc_Surf2]; }
		}
		SubSpace {
			{ Name Tcont; NameOfBasisFunction {sN}; }
			{ Name Tdisc1; NameOfBasisFunction {sNdc1}; }
			{ Name Tdisc2; NameOfBasisFunction {sNdc2}; }
		}
		Constraint {
			{ NameOfCoef T_Node; EntityType NodesOf; NameOfConstraint setT_BC; }
			{ NameOfCoef Tdc1; EntityType NodesOf; NameOfConstraint setT_disc; }
			{ NameOfCoef Tdc2; EntityType NodesOf; NameOfConstraint setT_disc; }
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
			{ Name Tcn; Type Local; NameOfSpace H_grad_T_fspace[Tcont]; }
			{ Name Tdc1; Type Local; NameOfSpace H_grad_T_fspace[Tdisc1]; }
			{ Name Tdc2; Type Local; NameOfSpace H_grad_T_fspace[Tdisc2]; }
		}
		Equation {
			Integral { [ condK[] * Dof{d T} , {d T} ];
				In Cond_Elements; Jacobian VolumeJac; Integration GaussIntegra; }
			Integral { [ -qGen[] , {T} ];
				In qGen_Regions; Jacobian VolumeJac; Integration GaussIntegra; }
			Integral { [ -Flux[] , {T} ];
				In Flux_Regions; Jacobian SurfaceJac; Integration GaussIntegra; }
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
				Term{[ {T} ]; In Domain_H_grad_T; Jacobian VolumeJac; }
			}}
			{ Name q; Value {
				Term{[ -{d T} ]; In Domain_H_grad_T; Jacobian VolumeJac; }
			}}
			{ Name Qgen; Value {
				Term{[ qGen[] ]; In Domain_H_grad_T; Jacobian VolumeJac; }
			}}
			{ Name Tcn; Value {
				Term{[ {Tcn} ]; In Domain_H_grad_T; Jacobian VolumeJac; }
			}}
			{ Name Tdc1; Value {
				Term{[ {Tdc1} ]; In Disc_Domains; Jacobian VolumeJac; }
			}}
			{ Name Tdc2; Value {
				Term{[ {Tdc2} ]; In Disc_Domains; Jacobian VolumeJac; }
			}}
		}
	}
}


PostOperation {
	{ Name def_HeatMap; NameOfPostProcessing def_Thermals;
		Operation {
			Print[T, OnElementsOf Domain_H_grad_T, File "T_map.pos"];
			Print[q, OnElementsOf Domain_H_grad_T, File "q_map.pos"];
			Print[Tcn, OnElementsOf Domain_H_grad_T, File "Tcn_map.pos"];
			Print[Tdc1, OnElementsOf Disc_Domains, File "Tdc_map.pos"];
			Print[Tdc2, OnElementsOf Disc_Domains, File "Tdc_map.pos"];
		}
	}
}


