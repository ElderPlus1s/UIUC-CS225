#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	Quadtree();
	Quadtree(PNG &sourse, int resolution);
	Quadtree(Quadtree &other);
	Quadtree &operator=(Quadtree &other);
	~Quadtree();

	void buildTree(PNG const &source, int resolution);

	RGBAPixel getPixel(int x, int y) const;

	PNG decompress() const;

	void clockwiseRotate();


	void prune(int tolerance);
	int pruneSize(int tolerance) const;
	int idealPrune(int numLeaves) const;

	
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree


	int resolution;

	void disposeSubTree(QuadtreeNode *&curNode);
	void copySubTree(QuadtreeNode *&secondNode, QuadtreeNode *&firstNode);
	void buildSubTree(QuadtreeNode *&curNode, PNG const &source, int x, int y, int resolution);
	RGBAPixel getPixelImpl(QuadtreeNode *curNode, int x, int y, int resolution)const;


	void clockwiseRotateImpl(QuadtreeNode *curNode);
	
	void pruneImpl(int tolerance, QuadtreeNode *curNode);


	bool canPrune(QuadtreeNode* node, int resolution) const;
	bool canPruneImpl(QuadtreeNode *root, QuadtreeNode *curNode, int resolution) const;

	int pruneSizeImpl(QuadtreeNode *curNode, int resolution) const;

	int binSearch(int numLeaves, int low, int high)const;

	bool isLeaf(QuadtreeNode * node) const;
	
	
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
