
Include "bot_mod.geo";

	lc_pcb0 = 4e-4;

//{Geometry Defintions

	Point(1) = {-0.025, 0.012, -0.001, lc_pcb0};			//modified
	Point(2) = {-0.025, -0.012, -0.001, lc_pcb0};			//modified
	Point(3) = {0.025, -0.012, -0.001, lc_pcb0};			//modified
	Point(4) = {0.025, 0.012, -0.001, lc_pcb0};			//modified
	Point(5) = {-0.025, 0.012, 0.00025, lc_pcb0};		//modified
	Point(6) = {-0.025, -0.012, 0.00025, lc_pcb0};		//modified
	Point(7) = {0.025, -0.012, 0.00025, lc_pcb0};		//modified
	Point(8) = {0.025, 0.012, 0.00025, lc_pcb0};		//modified
	
	Line(1) = {1, 2};
	Line(2) = {2, 3};
	Line(3) = {3, 4};
	Line(4) = {4, 1};
	Line(5) = {5, 6};
	Line(6) = {6, 7};
	Line(7) = {7, 8};
	Line(8) = {8, 5};
	Line(9) = {1, 5};
	Line(10) = {2, 6};
	Line(11) = {3, 7};
	Line(12) = {4, 8};
	
	Line Loop(29323) = {1, 2, 3, 4};
	Line Loop(29324) = {5, 6, 7, 8};
	Line Loop(29325) = {1, 10, -5, -9};
	Line Loop(29326) = {2, 11, -6, -10};
	Line Loop(29327) = {3, 12, -7, -11};
	Line Loop(29328) = {4, 9, -8, -12};
	
	Plane Surface(1) = {29323};
	
	Plane Surface(3) = {29325};
	Plane Surface(4) = {29326};
	Plane Surface(5) = {29327};
	Plane Surface(6) = {29328};
	
	Plane Surface(2) = {29324,29329,29330,29589};						//modified
	
	Surface Loop(14300) = {1, 2, 3, 4, 5, 6, 7, 40000, 263};			//modified
	Volume(1) = {14300};
	
	Physical Volume("vPCB0",1) = {1};
	Physical Surface("sPCB0_bot",11000) = {1};
	Physical Surface("sPCB0_top",12000) = {2,40000};
	Physical Surface("sPCB0_north",13000) = {5};
	Physical Surface("sPCB0_sides",14000) = {3,4,5,6};
	
//}

