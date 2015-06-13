		VRML 2 STL/G CONVERTER
		
		Introduction
	This is a prototype vrml converter which take a vrml(virtual reality mark up language) file with extention (.wrl) and convert to stl format which can then be converted brlcad(.g) using a the brlcad stl-g converter. It would futher be developed and merged into the brlcad source code where it would call the make bot function and then do direct convertion to .g format.
	
	Table of content
	
1 What is a geometry converter	
2 What is vrml
3 What is Brlcad
4 Compiling and running converter
5 Running brlcad
6 How to use converter
7 How to convert from vrml-g (vrml to brlcad)
8 How to veiw converted files

  
  		WHAT IS A GEOMETRY CONVERTER
  	This is a program which convert a CAD file from one format to another. This is very essential to CAD software since it gives them the ability to import and work with file from other CAD software with extentions, that is different from thiers.
  	
  	
  		WHAT IS VRML
  	This is web3d standard for CAD file that can be veiwer on web browsers with the addition of some plugins and they have the .wrl extention and have primitives like cone, cylinder etc and support for polygonal representation like indexedfaceset, indexedlineset etc.
  	
  	
  		WHAT IS BRLCAD
  	Brlcad stands for Balistic Research Laboratory Computer Aided Design.This is an open source organisation that is tasked with builing the brlcad software which is a CAD product, used to use to graphicaly design weapon and other utilities for the American army.Brlcad has support for various goemetry convertions some of which are stl and ply but do not yet have support for other like Autocad and Vrml.
  	
  	
		COMPILING AND RUNNING CONVERTER
	To compile to this program just cd to the converter directory and run the "make" command. This would automaticaly compile the code and give and output called test.
	To run the program enter the command
	./testt then name of file to be converted
	Example
	./testt protofiles/snowman.wrl
	This would produce an stl file called output.stl in a the cadtest folder.
	
	
		RUNNING BRLCAD
	To run brlcad enter the from the converter folder type in terminal:
	 cd brlcad/build/bin/
	 then
	 ./mged
	 
	 
	 	HOW TO USE CONVERTER
	 In terminal type:
	 ./testt protofiles/snowman.wrl
	 This convert the file snowman.wrl to output.stl in the cadtest folder. All vrml file are found in the protofiles folder.
	 
	 
	 	HOW TO CONVERT FROM VRML TO G	
	 	Since brlcad has an stl converter you can complete the convertion by
	 In terminal type:
	 - cd brlcad/build/bin/
	 - ./stl-g  ../../../cadtest/output.stl  ../../../cadtest/mystltest.g .This converts the stl file to .g file called mystltest.g.
	 
	 	HOW TO VEIW CONVERTED FILES
	 	While in the converter folder type in terminal:
	 - cd brlcad/build/bin/
	 - ./mged ../../../cadtest/mystltest.g . To open the file with mged. 
	 Since mged open with a terminal, in the mged terminal type the command: 
	 - draw all
	  to veiw the object in the file.
	 
	 
	 	DISCLAIMER
	 This is a prototype converter and has not be subjected to robust test so the author is not responsible for any damages cuased by this program or insufficiency.
	 Copyright (C) 2015 Djimeli Konrad

  	
