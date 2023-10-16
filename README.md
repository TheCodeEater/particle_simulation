#Definitions
We shall use some naming conventions in this file

1) Component: a set of classes along with their headers that define a logical component of the program. 

#Building the targets

The program allows two build options for the main executable
1) Graphics only: the program uses only a GUI (implement as a component)
2) Terminal: the root cling interpreter is attached to the program, along with gui
3) Lib only: the components are built separately and can be loaded into other programs, in root cling from the system terminal