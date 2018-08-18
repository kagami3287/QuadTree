QuadTree :
=======
This is a c++ Implementation of QuadTree. 

Quad Tree can be used to store and quickly retrieve any number of nearest neighbors of any given point. Currently this is implemented for 2D only. The critera used to define nearness is Euclidean Distance. 

This Data Struture provdes the following Big O(n)
* Insertion : **Log(N)
* Search    : **Log(N)

The Future :
==========
Depending on the reviews, I am planning to change the code such that, the following can be templated.

Distance Measure :
------
 * Euclidean
 * City Block
 * Chessoard
 * Quasi-Euclidean
 
 Dimentions :
 -------
 * Create a templatable code over dimentions (3D,4D and higher order).
 
 

Usage : 
=======
The Class "Quad" is the central figure in this work. 
Please follow the code in Main.cpp to get a feel of how to use the Library.

Installation :
=======
The project is created on Visual Studios. There are no required additional dependencies. 

License :
=======
This code is free to share, use, reuse, and modify according to the MIT license, see LICENSE.txt.

Reference :
=======
* [All Nearest Neighbours via Quadtrees](http://homepage.divms.uiowa.edu/~kvaradar/sp2012/daa/ann.pdf)
* [wikipedia](https://en.wikipedia.org/wiki/Quadtree)
