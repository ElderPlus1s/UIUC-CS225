
#include "quadtree.h"
//mp5.1
//constructors 
Quadtree::Quadtree() {
	root = NULL;
	resolution = 1;
}

Quadtree::Quadtree(PNG &png, int resolution) {
	root = new QuadtreeNode();
	buildTree(png, resolution);
}


Quadtree::Quadtree(Quadtree &other) {
	resolution = other.resolution;
	copySubTree(other.root, root);
}

//destructor
Quadtree::~Quadtree() {
	disposeSubTree(root);
	this->resolution = 1;
}


void Quadtree::disposeSubTree(QuadtreeNode *&node) {
	if (node == NULL) {
		return;
	}

	disposeSubTree(node->nwChild);
	disposeSubTree(node->neChild);
	disposeSubTree(node->swChild);
	disposeSubTree(node->seChild);

	delete node;
	node = NULL;

	return;
}


//assignment Operator
Quadtree & Quadtree::operator=(Quadtree &other) {

	if (this != &other) {
		disposeSubTree(root);
		copySubTree(other.root, root);
		this->resolution = other.resolution;
	}
	return *this;
}

// copy a subtree from one node to another
void Quadtree::copySubTree(QuadtreeNode *&fromNode, QuadtreeNode *&toNode) {

	if (fromNode == NULL) {
		toNode = NULL;
		return;
	}

	toNode = new QuadtreeNode();
	toNode->element = fromNode->element;

	copySubTree(fromNode->neChild, toNode->neChild);
	copySubTree(fromNode->nwChild, toNode->nwChild);
	copySubTree(fromNode->seChild, toNode->seChild);
	copySubTree(fromNode->swChild, toNode->swChild);

	return;
}
/// interface
void Quadtree::buildTree(PNG const &png, int resolution) {
	if (root != NULL) {
		disposeSubTree(root);
	}

	this->resolution = resolution;
	buildSubTree(root, png, 0, 0, resolution);
}


void Quadtree::buildSubTree(QuadtreeNode *&subRoot, PNG const &png, int x, int y, int resolution) {

	if (resolution == 1) {
		subRoot = new QuadtreeNode();
		subRoot->element = *png(x, y);
		return;
	}

	subRoot = new QuadtreeNode();
	buildSubTree(subRoot->nwChild, png, x, y, resolution / 2);
	buildSubTree(subRoot->neChild, png, x + resolution / 2, y, resolution / 2);
	buildSubTree(subRoot->swChild, png, x, y + resolution / 2, resolution / 2);
	buildSubTree(subRoot->seChild, png, x + resolution / 2, y + resolution / 2, resolution / 2);

	if (subRoot->nwChild != NULL) {
		subRoot->element.red = (subRoot->nwChild->element.red + subRoot->neChild->element.red + subRoot->seChild->element.red + subRoot->swChild->element.red) / 4;
		subRoot->element.blue = (subRoot->nwChild->element.blue + subRoot->neChild->element.blue + subRoot->seChild->element.blue + subRoot->swChild->element.blue) / 4;
		subRoot->element.green = (subRoot->nwChild->element.green + subRoot->neChild->element.green + subRoot->seChild->element.green + subRoot->swChild->element.green) / 4;

	}


}
/// interface
RGBAPixel Quadtree::getPixel(int x, int y) const {
	if (root == NULL || x > resolution || y > resolution || x < 0 || y < 0) {
		return RGBAPixel();
	}
	else {
		return getPixelImpl(root, x, y, resolution);
	}
}


RGBAPixel Quadtree::getPixelImpl(QuadtreeNode *curNode, int x, int y, int resolution)const {
	if (curNode->nwChild == NULL || resolution == 1) {
		return curNode->element;
	}

	if (x < resolution / 2 && y < resolution / 2) {
		return getPixelImpl(curNode->nwChild, x, y, resolution / 2);
	}
	else if (x < resolution / 2 && y >= resolution / 2) {
		return getPixelImpl(curNode->swChild, x, y - resolution / 2, resolution / 2);
	}
	else if (x >= resolution / 2 && y < resolution / 2) {
		return getPixelImpl(curNode->neChild, x - resolution / 2, y, resolution / 2);
	}
	else {
		return getPixelImpl(curNode->seChild, x - resolution / 2, y - resolution / 2, resolution / 2);
	}
}
//interface
PNG Quadtree::decompress() const {
	if (root == NULL) {
		return PNG();
	}

	PNG result = PNG(resolution, resolution);
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			*result(i, j) = getPixel(i, j);
		}
	}
	return result;
}

//interface 
void Quadtree::clockwiseRotate() {
	if (root == NULL) {
		return;
	}
	clockwiseRotateImpl(root);
}


void Quadtree::clockwiseRotateImpl(QuadtreeNode *curNode) {
	if (curNode->nwChild == NULL) {
		return;
	}

	clockwiseRotateImpl(curNode->nwChild);
	clockwiseRotateImpl(curNode->neChild);
	clockwiseRotateImpl(curNode->swChild);
	clockwiseRotateImpl(curNode->seChild);

	QuadtreeNode *temp = curNode->nwChild;
	curNode->nwChild = curNode->swChild;
	curNode->swChild = curNode->seChild;
	curNode->seChild = curNode->neChild;
	curNode->neChild = temp;

}
// interface
void Quadtree::prune(int tolerance) {
	pruneImpl(tolerance, root);
}

void Quadtree::pruneImpl(int tolerance, QuadtreeNode *root) {
	if (root == NULL) {
		return;
	}

	if (root->nwChild == NULL || root->neChild == NULL || root->swChild == NULL || root->seChild == NULL) {
		return;
	}
	if (canPrune(root, tolerance))
	{
		disposeSubTree(root->nwChild);
		disposeSubTree(root->neChild);
		disposeSubTree(root->swChild);
		disposeSubTree(root->seChild);

		return;
	}
	pruneImpl(tolerance, root->nwChild);
	pruneImpl(tolerance, root->neChild);
	pruneImpl(tolerance, root->swChild);
	pruneImpl(tolerance, root->seChild);




}
bool Quadtree::canPrune(QuadtreeNode * root, int tolerance) const
{
	return canPruneImpl(root, root, tolerance);

}
bool Quadtree::canPruneImpl(QuadtreeNode *toPrune, QuadtreeNode *node, int tolerance) const {
	if (isLeaf(node))
	{
		int diff_red = toPrune->element.red - node->element.red;
		int diff_green = toPrune->element.green - node->element.green;
		int diff_blue = toPrune->element.blue - node->element.blue;
		int sq_diff = diff_red*diff_red + diff_green*diff_green + diff_blue*diff_blue;
		if (sq_diff <= tolerance) {
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		return canPruneImpl(toPrune, node->nwChild, tolerance) &&
			canPruneImpl(toPrune, node->neChild, tolerance) &&
			canPruneImpl(toPrune, node->swChild, tolerance) &&
			canPruneImpl(toPrune, node->seChild, tolerance);
	}

}
//interface
int Quadtree::pruneSize(int tolerance) const {
	return pruneSizeImpl(root, tolerance);
}


int Quadtree::pruneSizeImpl(QuadtreeNode *curNode, int tolerance) const {
	if (curNode == NULL) {
		return 0;
	}

	if (canPrune(curNode, tolerance)) {
		return 1;
	}

	else {
		return 	pruneSizeImpl(curNode->nwChild, tolerance) +
			pruneSizeImpl(curNode->neChild, tolerance) +
			pruneSizeImpl(curNode->swChild, tolerance) +
			pruneSizeImpl(curNode->seChild, tolerance);
	}


}

//interface
int Quadtree::idealPrune(int numLeaves) const {

	int low = 0, high = 3 * 255 * 255;
	return binSearch(numLeaves, low, high);
}

int Quadtree::binSearch(int numLeaves, int low, int high) const {
	if (low > high) {
		return low;
	}

	int mid = (low + high) / 2;
	int leaves = pruneSize(mid);
	if (leaves > numLeaves) {
		return binSearch(numLeaves, mid + 1, high);
	}
	else {
		return binSearch(numLeaves, low, mid - 1);
	}
}

bool Quadtree::isLeaf(QuadtreeNode* node) const
{
	return node->nwChild == NULL && node->neChild == NULL &&
		node->swChild == NULL && node->seChild == NULL;
}




