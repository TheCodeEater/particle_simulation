# Basic high energy physics simulator
This program is designed to simulate a particle detector observing the traces of the following particles (and their associated antiparticles):

1) Pion 
2) Kaon 
3) Proton 

In addition, the program simulates the decay and resonance phenomenons of neutral Kaons (K0) by turning it into its decayment products.


# Naming conventions

1) Component: a set of classes along with their headers that define a logical component of the program. 

# Building the targets

The program allows two build options for the main executable
1) Graphics only: the program uses only a GUI (implement as a component)
2) Terminal: the root cling interpreter is attached to the program, along with gui
3) Lib only: the components are built separately and can be loaded into other programs, in root cling from the system terminal

The lib only approach allows the user to instantiate and interact with the simulation object. 
In a future version, a root macro using this objects may be provided
(alternatively, the function that runs the simulation can be compiled as a separated macro - still to decide)