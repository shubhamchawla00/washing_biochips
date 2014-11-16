Algorithms for Automated Path Planning for Washing in Biochips
==============================================================

Residues left inside a Digital Microfluidic Biochip during its operation may affect the further operation leading to unexpected behavior. Modelling the Biochip structure into an undirected graph, algorithms can be designed for automated washing of the residues by efficient routing of a droplet inside the chip. These algorithms are also applicable in several other real world problems like New York Street Sweeping, Snow Clearing, Minimum Postmen Cover and Software Testing etc.

Usage Instructions for classical_implementation.cpp
=================================================== 

1. Number all the nodes as shown in fig6_numbered.jpg,  starting from 0
2. Write the input file as follows:
	- first line contains the source node no. and sink node no. separated by a space
	- second line contains no. of vertices V and no. of edges E separated by a space, E lines must follow after that
	- E lines,  each containing two integers X and Y, representing that there exists an edge betweeen X and Y
	3. compile classical_implementation.cpp using g++ to generate an executable file as:
		g++ classical_implementation.cpp -o ex
4. To generate results for BFS Labelling algorithm,  use the following command
	./ex < input.txt > output.txt
5. To generate results for Baseline algorithm,  use the following command
	./ex r < input.txt > output.txt
	option r represents randomized,  for Baseline.
6. The number of nodes is limited by 200 right now. To change that, change the #define SIZE 200 to desired value on line 12 of classical_implementation.cpp
For further clarification see fig6_numbered.jpg and input_fig6.txt.

	