# G_TAC
##### GetDP_Thermal Analysis Compiler

G_TAC is a command-line parametric input application aimed at reducing the time & effort invested in generating similar, repeatable Finite Element Analyses (FEAs).
It compiles the C-style input files for the [GetDP](#getdp) solver and employs the [Gmsh](#gmsh) library to streamline the FEA process as much as possible.

---
## Software Chain Interaction
![Process Flow](doc/images/G_TAC_ProcessFlow.png?raw=true)
### GetDP
GetDP[(1)](#1-getdp-getdpinfo)(*General environment for the treatment of Discrete Problems*) is a free, open source finite element solver capable of using mixed elements to solve de Rham complexes in one, two and three dimensions.
>"The main feature of GetDP is the closeness between the input data defining discrete problems( *ASCII data files (.pro)* ) and the symbolic mathematical expressions of these problems."

G_TAC is used to compile and generate the C-style input files required by GetDP.

### Gmsh
Gmsh[(2)](#2-gmsh-gmshinfo) is an open source finite element mesh generator with a built-in CAD engine and post-processor.
It utilises script files(*.geo* extension) to define geometry and mesh constraints.

G_TAC has the option to employ the Gmsh C++ library to expedite the region definitions.

### ONELAB
ONELAB[(3)](#3-onelab-onelabinfo)(*Open Numerical Engineering LABoratory*) provides an open-source graphical user interface(GUI) to the Gmsh and GetDP finite element software.
It hosts the variables defined in both Gmsh and GetDP and allows for the seamless integration between the two.




## References
#### 1. GetDP ([getdp.info](http://getdp.info))
>  C. Geuzaine. GetDP: a general finite-element solver for the de Rham complex. In PAMM Volume 7 Issue 1. Special Issue: Sixth International Congress on Industrial Applied Mathematics (ICIAM07) and GAMM Annual Meeting, Zürich 2007 (pp. 1010603–1010604). Wiley.

#### 2. Gmsh ([gmsh.info](http://gmsh.info))
> C. Geuzaine and J.-F. Remacle. Gmsh: a three-dimensional finite element mesh generator with built-in pre- and post-processing facilities. International Journal for Numerical Methods in Engineering 79(11), pp. 1309-1331, 2009

#### 3. ONELAB ([onelab.info](http://onelab.info))
