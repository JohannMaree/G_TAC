# G_TAC
##### GetDP_Thermal Analysis Compiler

G_TAC is a command-line parametric input application intended to reduce the time & effort invested in generating similar, repeatable Finite Element Analyses (FEAs).
It compiles the C-style input files for the GetDP[(1)](#getdp) solver, and functions alongside Gmsh[(2)](#gmsh) to streamline the process as far as possible.

---
## Software Chain Interaction
![Process Flow](doc/images/G_TAC_ProcessFlow.png?raw=true)
### GetDP
GetDP[(1)](#1-getdp-getdpinfo)(*General environment for the treatment of Discrete Problems*) is a free, open source finite element solver capable of using mixed elements to solve de Rham complexes in one, two and three dimensions.
>"The main feature of GetDP is the closeness between the input data defining discrete problems( *ASCII data files (.pro)* ) and the symbolic mathematical expressions of these problems."

G_TAC is used to compile and generate the ASCII text data input(*.pro*) files required by GetDP.

### Gmsh
Gmsh[(2)](#2-gmsh-gmshinfo) is a free finite element mesh generator with a built-in CAD engine and post-processor. 
Gmsh is built around 4 modules: geometry, mesh, solver and post-processing. The specification of any input to these modules is done either interactively using the graphical user interface, in ASCII text files

G_TAC 

### ONELAB
ONELAB[(3)](#3-onelab-onelabinfo)(*Open Numerical Engineering LABoratory*) provides an open-source graphical user interface to the Gmsh and GetDP finite element software.
It allows for the seamless integration between the mesh generator and PDE solver.

---
## Features
- Associative region property definitions:
  - reduces user input required to generate input(*.pro*) files for workable thermal finite element analyses.
  - link variables/values to region properties
- Automatically generated Partial Differential Equations(PDEs)
- Default object definitions

## Instructions
- Download the latest snapshot of the ONELAB software bundle:
  - [Windows 64-bit](http://onelab.info/files/onelab-Windows64.zip)
  - [Windows 32-bit](http://onelab.info/files/onelab-Windows32.zip)



## References
#### 1. GetDP ([getdp.info](http://getdp.info))
>  C. Geuzaine. GetDP: a general finite-element solver for the de Rham complex. In PAMM Volume 7 Issue 1. Special Issue: Sixth International Congress on Industrial Applied Mathematics (ICIAM07) and GAMM Annual Meeting, Zürich 2007 (pp. 1010603–1010604). Wiley.

#### 2. Gmsh ([gmsh.info](http://gmsh.info))
> C. Geuzaine and J.-F. Remacle. Gmsh: a three-dimensional finite element mesh generator with built-in pre- and post-processing facilities. International Journal for Numerical Methods in Engineering 79(11), pp. 1309-1331, 2009

#### 3. ONELAB ([onelab.info](http://onelab.info))
