		VRML 2 STL CONVERTER
		
		Introduction
	This is a prototype vrml converter which take a vrml(virtual reality mark up language) file with extention (.wrl) and convert to stl format.
	
	Table of content
	
1 What is a geometry converter	
2 What is vrml
3 Compiling and running converter
4 How to use converter

  
  		WHAT IS A GEOMETRY CONVERTER
  	This is a program which convert a CAD file from one format to another. This is very essential to CAD software since it gives them the ability to import and work with file from other CAD software with extentions, that is different from thiers.
  	
  	
  		WHAT IS VRML
  	This is web3d standard for CAD file that can be veiwer on web browsers with the addition of some plugins and they have the .wrl extention and have primitives like cone, cylinder etc and support for polygonal representation like indexedfaceset, indexedlineset etc.
  	
  	
		COMPILING AND RUNNING CONVERTER
	To compile to this program just cd to the converter directory and run the "make" command. This would automaticaly compile the code and give and output called test.
	To run the program enter the command
	./testt then name of file to be converted
	Example
	./testt protofiles/snowman.wrl
	This would produce an stl file called output.stl in a the cadtest folder.
	
	 
	 	HOW TO USE CONVERTER
	 In terminal type:
	 ./testt protofiles/snowman.wrl
	 This convert the file snowman.wrl to output.stl in the cadtest folder. All vrml file are found in the protofiles folder.
	 
	 	DISCLAIMER
	 This is a prototype converter and has not be subjected to robust test so the author is not responsible for any damages cuased by this program or insufficiency.
	 Copyright (C) 2015 Djimeli Konrad

  	
