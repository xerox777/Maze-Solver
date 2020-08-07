#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include "EasyBMP_BMP.h"
#include "EasyBMP_VariousBMPutilities.h"
#include "EasyBMP_DataStructures.h"
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include "struct.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>

int fullsize = 0;
int wid = 0;
int heig = 0;

using namespace std;

BMP BFSearch (BMP & input, int startX, int startY, int endX, int endY, int count, const vector< vector<Node*> > img);

int main(int argc, char* argv[]) {
	BMP Tile;
	Tile.ReadFromFile("input.bmp");
	Tile.SetBitDepth(8);
	wid = Tile.TellWidth(); // ROWS
	heig = Tile.TellHeight(); // COLS
	size_t rows = wid;
	size_t cols = heig;
	fullsize = rows * cols;
	// Initialize the 2-d array for storing bmp img pixels
	// Size should be width x height
  	vector<vector<Node*> > data (rows, vector<Node*> (0)); 
	vector<int> color;
	// TODO Need to add 3 values (red, blue, green) per outer 
	// array element (first array[i] = another array with r,g,b 
	// values

	for (int i = 0; i < wid; i++) {
   	   data.push_back(vector<Node*>());
	   for (int j = 0; j < heig; j++) {
	     int r = (Tile(i, j) -> Red);
	     int g = (Tile(i, j) -> Green);
	     int b = (Tile(i, j) -> Blue);

	     Node* pixel = new Node();
	     if (r >= 200 && g >= 200 && b >= 200) {
		pixel->setXCoord(i);	// PIXEL IS WHITE
		pixel->setYCoord(j);
		pixel->setblack();	// SET ISBLACK TO FALSE
	     } else if (r <= 20 && g <= 20 && b <= 20) {
		pixel->setXCoord(i);	// PIXEL IS Black
		pixel->setYCoord(j);
	     }
	     data.at(i).push_back(pixel); // push color
   	  // if (data[i][j] == 1)
	    //cout << data[i][j] << "\n"; 
	 }

	}
	BMP outfile;
	outfile.SetSize(wid, heig);
	outfile.SetBitDepth(8);

	//Tile.SetBitDepth(8);
	
	for (int i = 0; i < wid; i++) {
		for (int j = 0; j < heig; j++) {
			if (data[i][j]->getblack() == true) {
			 	int x = data[i][j]->getXCoord();
				int y = data[i][j]->getYCoord();
				outfile(x, y) -> Red = 255;
			 	outfile(x, y) -> Blue = 0;
				outfile(x, y) -> Green = 0;
			 }
		}
	}
				
	// TODO set all appropriate pixel values to outfile BMP
	// start = (5, 5) & destination = (158, 158) [given
	// by professor]
	//outfile = 
	BFSearch (Tile, 158, 236, 158, 109, 1, data);
	//outfile.WriteToFile("out.bmp");
	return 0;

}


BMP BFSearch (BMP & input, int startX, int startY, int endX, int endY, int count, const vector< vector<Node*> > img) {
      // Initialize visited vector to be size of graph of img and
      // Populate it with 0's (1 = visited & 0 = not visitied yet)    
      // Set the start vertex to visited (1 - x and 1 - y)
      img.at(startX).at(startY)->setVisited();	// set start point visited to true
	vector< vector <int> > distance(wid, vector<int> (heig, 0));
	distance[startX][startY] = 1;
	queue<Node*> que;
        que.push(img[startX][startY]); 
	int num = 0;
	Node* next = new Node();
	bool solve = false;
	while (!que.empty()) {
		next = que.front();
		que.pop();
		next -> setVisited();
		int x = next -> getXCoord();
		int y = next -> getYCoord();
		if (x == endX && y == endY) {
			solve = true;
			break;
		}
		if (x+1 < wid && img[x+1][y]->getblack() == false && img[x+1][y] -> getVisited() == false) {
			img[x+1][y] -> setParent(next);
			que.push(img[x+1][y]);
			img[x+1][y]->setVisited();
		}
		if (y+1 < heig && img[x][y+1]->getblack() == false && img[x][y+1] -> getVisited() == false) {
			img[x][y+1] -> setParent(next);
			que.push(img[x][y+1]);
			img[x][y+1]->setVisited();
		}

		if (y-1 >= 0 && img[x][y-1]->getblack() == false && img[x][y-1] -> getVisited() == false) {
			img[x][y-1] -> setParent(next);
			que.push(img[x][y-1]);
			img[x][y-1] -> setVisited();
		}

		if (x-1 >= 0 && img[x-1][y]->getblack() == false && img[x-1][y] -> getVisited() == false) {
			img[x-1][y] -> setParent(next);
			que.push(img[x-1][y]);
			img[x-1][y] -> setVisited();
		}

		if (x+1 < wid && y+1 < heig && img[x+1][y+1]->getblack() == false && img[x+1][y+1] -> getVisited() == false) {
			img[x+1][y+1] -> setParent(next);
			que.push(img[x+1][y+1]);
			img[x+1][y+1] -> setVisited();
		}
		if (x-1 >= 0 && y+1 < heig && img[x-1][y+1]->getblack() == false && img[x-1][y+1] -> getVisited() == false) {
			img[x-1][y+1] -> setParent(next);
			que.push(img[x-1][y+1]);
			img[x-1][y+1] -> setVisited();
		}
		if (x+1 >= 0 && y-1 >= 0 && img[x+1][y-1]->getblack() == false && img[x+1][y-1] -> getVisited() == false) {
			img[x+1][y-1] -> setParent(next);
			que.push(img[x+1][y-1]);
			img[x+1][y-1] -> setVisited();
		}
		if (x-1 >= 0 && y-1 >= 0 && img[x-1][y-1]->getblack() == false && img[x-1][y-1] -> getVisited() == false) {
			img[x-1][y-1] -> setParent(next);
			que.push(img[x-1][y-1]);
			img[x-1][y-1] -> setVisited();
		}

	}
	
       BMP out;
       out.SetBitDepth(8);
       out.SetSize(wid, heig);
       for (int i = 0; i < wid; i ++) {
       	for (int j = 0; j < heig; j++) {
		out(i, j) -> Red = input(i, j) -> Red;
		out(i, j) -> Green = input(i, j) -> Green;
		out(i, j) -> Blue = input(i, j) -> Blue;
	 }
	}
	num = 0;
	Node* vertex = next;
	while (vertex -> getParent() != NULL) {
			//que.pop();
			cout << " Working...\n";
			num++;
			endX = vertex -> getXCoord();
			endY = vertex -> getYCoord();
			out(endX, endY) -> Red = 255;
			out(endX, endY) -> Blue = 0;
			out(endX, endY) -> Green = 0;
			vertex = vertex -> getParent();
			cout << endX << " " << endY << "\n";
		}
	
	//cout << que.front() << "\n";
       // Write changes to Bmp, then return it
       out.WriteToFile("me.bmp");
       return out;
}
