
Include "pcb1_mod.geo";
Include "m1_mod.geo";
	
	lc_die = 2e-4;
	
	Point(497) = {0.02, 0.01, 0.0002671, lc_die};			//modified
	Point(498) = {-0.02, 0.01, 0.0002671, lc_die};			//modified
	Point(499) = {-0.02, -0.01, 0.0002671, lc_die};			//modified
	Point(500) = {0.02, -0.01, 0.0002671, lc_die};			//modified
	Point(501) = {-0.0051, -0.0051, 0.0002671, lc_die}; 	//modified
	Point(502) = {-0.0051, 0.0051, 0.0002671, lc_die};		//modified
	Point(503) = {0.0051, 0.0051, 0.0002671, lc_die};		//modified
	Point(504) = {0.0051, -0.0051, 0.0002671, lc_die};		//modified
	Point(505) = {0.02, 0.01, 0.0006172, lc_die};
	Point(506) = {-0.02, 0.01, 0.0006172, lc_die};
	Point(507) = {-0.02, -0.01, 0.0006172, lc_die};
	Point(508) = {0.02, -0.01, 0.0006172, lc_die};
	Point(509) = {-0.0051, -0.0051, 0.0006172, lc_die};		//modified
	Point(510) = {-0.0051, 0.0051, 0.0006172, lc_die};		//modified
	Point(511) = {0.0051, 0.0051, 0.0006172, lc_die};		//modified
	Point(512) = {0.0051, -0.0051, 0.0006172, lc_die};		//modified
	Point(513) = {0.0025, 0.0025, 0.00025, lc_die};		//modified
	Point(514) = {-0.0025, 0.0025, 0.00025, lc_die};	//modified
	Point(515) = {-0.0025, -0.0025, 0.00025, lc_die};	//modified
	Point(516) = {0.0025, -0.0025, 0.00025, lc_die};	//modified
	Point(517) = {0.0025, 0.0025, 0.0006172, lc_die};
	Point(518) = {-0.0025, 0.0025, 0.0006172, lc_die};
	Point(519) = {-0.0025, -0.0025, 0.0006172, lc_die};
	Point(520) = {0.0025, -0.0025, 0.0006172, lc_die};
	
	Line(745) = {497, 498};
	Line(746) = {498, 499};
	Line(747) = {499, 500};
	Line(748) = {500, 497};
	Line(749) = {501, 502};
	Line(750) = {502, 503};
	Line(751) = {503, 504};
	Line(752) = {504, 501};
	Line(753) = {505, 506};
	Line(754) = {506, 507};
	Line(755) = {507, 508};
	Line(756) = {508, 505};
	Line(757) = {509, 510};
	Line(758) = {510, 511};
	Line(759) = {511, 512};
	Line(760) = {512, 509};
	Line(761) = {497, 505};
	Line(762) = {498, 506};
	Line(763) = {499, 507};
	Line(764) = {500, 508};
	Line(765) = {501, 509};
	Line(766) = {502, 510};
	Line(767) = {503, 511};
	Line(768) = {504, 512};
	Line(769) = {513, 514};
	Line(770) = {514, 515};
	Line(771) = {515, 516};
	Line(772) = {516, 513};
	Line(773) = {517, 518};
	Line(774) = {518, 519};
	Line(775) = {519, 520};
	Line(776) = {520, 517};
	Line(777) = {513, 517};
	Line(778) = {514, 518};
	Line(779) = {515, 519};
	Line(780) = {516, 520};
	
	Line Loop(29577) = {745, 746, 747, 748};
	Line Loop(29578) = {749, 750, 751, 752};
	Line Loop(29579) = {753, 754, 755, 756};
	Line Loop(29580) = {757, 758, 759, 760};
	Line Loop(29581) = {745, 762, -753, -761};
	Line Loop(29582) = {746, 763, -754, -762};
	Line Loop(29583) = {747, 764, -755, -763};
	Line Loop(29584) = {748, 761, -756, -764};
	Line Loop(29585) = {749, 766, -757, -765};
	Line Loop(29586) = {750, 767, -758, -766};
	Line Loop(29587) = {751, 768, -759, -767};
	Line Loop(29588) = {752, 765, -760, -768};
	Line Loop(29589) = {769, 770, 771, 772};
	Line Loop(29590) = {773, 774, 775, 776};
	Line Loop(29591) = {769, 778, -773, -777};
	Line Loop(29592) = {770, 779, -774, -778};
	Line Loop(29593) = {771, 780, -775, -779};
	Line Loop(29594) = {772, 777, -776, -780};

	
	Plane Surface(254) = {29579, 29580};
	Plane Surface(255) = {29581};
	Plane Surface(256) = {29582};
	Plane Surface(257) = {29583};
	Plane Surface(258) = {29584};
	Plane Surface(259) = {29585};
	Plane Surface(260) = {29586};
	Plane Surface(261) = {29587};
	Plane Surface(262) = {29588};
	Plane Surface(263) = {29589};
	
	Plane Surface(265) = {29591};
	Plane Surface(266) = {29592};
	Plane Surface(267) = {29593};
	Plane Surface(268) = {29594};
	
	
//{ Physical Definitions
	
	Plane Surface(264) = {	29590, 29595, 
							sM1_botExtLL()};		//modified
	
	Physical Surface("sDIE_i41",41000) = {263};
	Physical Surface("sDIE_i42",42000) = {264};
	
	
	
//}