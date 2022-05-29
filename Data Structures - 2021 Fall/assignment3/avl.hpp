struct AvlNode {
    int element;
	AvlNode *parent;
    AvlNode *left;
    AvlNode *right;
    int height;
	int balanceFactor;
	int state;

    AvlNode (const int & ele, AvlNode *lt, AvlNode *rt, AvlNode *pa, int h = 0, int bf = 0, int s = 0) {
        element = ele;
		parent = pa;
        left = lt;
        right = rt; 
		height = h;
		balanceFactor = bf;
		state = s;
    }
};
