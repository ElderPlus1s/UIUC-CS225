

//interface 1
template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{

	if (first[curDim] == second[curDim])
		return first < second;
	else
		return first[curDim] < second[curDim];
}

//interface 2
template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
	int dist_new = 0;
	int dist_old = 0;
	for (int i = 0; i < Dim; i++) {
		dist_new += (potential[i] - target[i])*(potential[i] - target[i]);
		dist_old += (currentBest[i] - target[i])*(currentBest[i] - target[i]);
	}

	if (dist_new == dist_old) {
		return potential < currentBest;
	}
	else
		return dist_new < dist_old;
}
//interface 3
template<int Dim>
KDTree<Dim>::KDTree(const std::vector< Point<Dim> > & newPoints)
{
	if (newPoints.size() <= 0)
		return;


	points = newPoints;
	build_sub_tree(0, points.size() - 1, 0);
}

//use  [left, right]  ,then  mid = left + (right - left) / 2;
template<int Dim>
void KDTree<Dim>::build_sub_tree(int left, int right, int d) {
	if (left > right) {
		return;
	}	
		int mid = left + (right - left) / 2;
		quick_nth_element(left, right, mid, d);
		if (left < mid)
			build_sub_tree(left, mid - 1, (d + 1) % Dim);
		if (mid < right)
			build_sub_tree(mid + 1, right, (d + 1) % Dim);
	
}


template<int Dim>
void KDTree<Dim>::quick_nth_element(int left, int right, int nth, int d) {
	if (left > right) {
		return;
	}

	int pivot = left + (right - left) / 2;
	pivot = partition(left, right, pivot, d);

	if (pivot == nth) {
		return;
	}
	else if (pivot < nth) {
		quick_nth_element(pivot + 1, right, nth, d);
	}
	else { 
		quick_nth_element(left, pivot - 1, nth, d);
	}

}


template<int Dim>
int KDTree<Dim>::partition(int left, int right, int pivot, int d) {
	Point<Dim> value = points[pivot];

	swap(pivot, right);
	//swap all points less than pivot to the left part which has LESS_POS elements 
	int less_pos = left;
	for (int i = left; i < right; i++) {
		if (smallerDimVal(points[i], value, d) || points[i] == value) {
			swap(i, less_pos);
			less_pos++;
		}
	}
	swap(right, less_pos);
	return less_pos;
}


template<int Dim>
void KDTree<Dim>::swap(int left, int right) {
	Point<Dim> temp = points[left];
	points[left] = points[right];
	points[right] = temp;
}

//interface 4
template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
	
	if (points.size() <= 0) 
	{
		return Point<Dim>();
	}
	// [0,size-1] then mid = (0+size-1)/2
	Point<Dim> root = points[(points.size() - 1) / 2];
	return nearest_neighbor(query, root, 0, points.size() - 1, 0);
}


template<int Dim>
Point<Dim> KDTree<Dim>::nearest_neighbor(const Point<Dim> &query, const Point<Dim> &candidate, int left, int right, int d) const {
	Point<Dim> nearest = candidate;
	if (left >= right) {
		if (shouldReplace(query, nearest, points[left])) {
			nearest = points[left];
			return nearest;
		}
		nearest = candidate;
		return nearest;
	}
	//indentify whether we go back from a right sub-tree
	bool isFromRightTree = false;
	int mid = left + (right-left) / 2;

	if (smallerDimVal(query, points[mid], d) && (left < mid)) {
		nearest = nearest_neighbor(query, nearest, left, mid - 1, (d + 1) % Dim);
		isFromRightTree = false;
	}
	if (smallerDimVal(points[mid], query, d) && (right > mid)) {
		nearest = nearest_neighbor(query, nearest, mid + 1, right, (d + 1) % Dim);
		isFromRightTree = true;
	}

	if (shouldReplace(query, nearest, points[mid])) {
		nearest = points[mid];
	}

	int d_radius = (points[mid][d] - query[d])*(points[mid][d] - query[d]);
	
	int radius = 0;
	for (int i = 0; i < Dim; i++) {
		radius = radius + (query[i] - nearest[i])*(query[i] - nearest[i]);
	}

	if (d_radius <= radius)
	{
		if (!isFromRightTree && (right > mid))
			nearest = nearest_neighbor(query, nearest, mid + 1, right, (d + 1) % Dim);
		if (isFromRightTree && (left < mid))
			nearest = nearest_neighbor(query, nearest, left, mid - 1, (d + 1) % Dim);
	}
	return nearest;
}
