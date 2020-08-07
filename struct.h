
struct Node
{
		
	Node() { Parent = NULL; visited = false; xcoord = 0; ycoord = 0; isblack = true;}
	void setParent (Node* in) { Parent = in; return;}
	Node* getParent () { return Parent;}
	void setVisited() { visited = true; return;}
	void setUnvisited() { visited = false; return;}
	bool getVisited() { return visited;}
	void setXCoord (int x) { xcoord = x; return;}
	void setYCoord (int y) { ycoord = y; return;}
	int getXCoord () { return xcoord; }
	int getYCoord() { return ycoord; }
	bool getblack () { return isblack; }
	void setblack () { isblack = false; return;}
	private:
		Node* Parent;
		bool visited;
		int xcoord;
		int ycoord;
		bool isblack;

};
