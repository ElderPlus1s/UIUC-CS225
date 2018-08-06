/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    clear();
    /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    if (head == NULL){
        return;
    }

    ListNode * temp = head;
    ListNode * nxt = head -> next;

    while (temp!=NULL){
        
        temp-> prev = NULL;
        temp-> next = NULL;
        delete temp;
        temp = nxt; 

        if (temp!= NULL)
            nxt = temp -> next;
    }
    tail = NULL;
    length = 0;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    ListNode *temp = new ListNode(ndata);
    if (head == NULL){
        head -> prev = NULL;
        head -> next = NULL;
        head = temp;
        tail = head;
    }
    else {
        temp -> next = head;
        head -> prev = temp;
        head = temp;

    }
    length++;
    temp = NULL;

    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode * temp = new ListNode(ndata);
    if (head == NULL){
        head -> prev = NULL;
        head -> next = NULL;
        head = temp;
        tail = head;
    }
    else {
        temp -> prev = tail;
        tail -> next = temp;
        tail = temp;

    }
    length++;
    temp = NULL;

}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    if (startPoint == NULL || startPoint == endPoint || startPoint ->next == NULL)
        return ;
    ListNode * cur = startPoint;
    while (cur != endPoint) {
        cur ->prev = cur ->next;
        cur = cur ->next;
    }

    cur = startPoint;
    cur ->next = NULL;
    while (cur != endPoint) {
        cur ->prev ->next = cur;
        cur = cur ->prev;
    }
    endPoint ->prev = NULL;

    endPoint = startPoint;
    startPoint = cur;

    
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    if (head == NULL)
        return ;
    int cnt = 1;
    bool flag = false;
    ListNode * preTail = head, * curHead = head, * cur = head, * nxt = head ->next;
    while (cur != NULL) {
        if (cnt == n || cur == tail) {
            cur ->next = NULL;
            if (flag == false) {
                flag = true;
                reverse(head, cur);
                preTail = cur;
            }
            else {
                reverse(curHead, cur);
                preTail ->next = curHead;
                curHead ->prev = preTail;
                preTail = cur;
            }
            cur = nxt;
            curHead = cur;
            cnt = 1;
        }
        if (cur == tail) {
            cur ->next = NULL;
            if (flag == false) {
                flag = true;
                reverse(head, cur);
                preTail = cur;
            }
            else {
                reverse(curHead, cur);
                preTail ->next = curHead;
                curHead ->prev = preTail;
                preTail = cur;
            }
            cur = nxt;
            curHead = cur;
            cnt = 1;
        }
        cnt ++;
        cur = cur ->next;
        if (cur != NULL)
            nxt = cur ->next;
    }

    /*
    if (head == NULL){
        return;
    }
    ListNode * startPoint = head;
    ListNode * endPoint = head;

    while(startPoint->next != NULL && endPoint -> next != NULL){
        endPoint = startPoint;
        for (int i = 1; i < n; i ++){
            if (endPoint -> next != NULL){
                ListNode * nxt = endPoint->next;
                endPoint = nxt;
            }
            reverse(startPoint, endPoint);
            startPoint = endPoint -> next;
        }
    }
    */
    /// @todo Graded in MP3.1
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    if (head == NULL||head->next == NULL)
        return ;
    ListNode * cur = head;
    ListNode *tmp = cur ->next;
    while (cur ->next != tail) {
        cur = cur -> next;
        cur ->next = cur ->next ->next;
        cur ->next ->prev = cur;
        cur = cur ->next;

        tail ->next = tmp;
        tmp ->prev = tail;
        tail ->next = NULL;
        tail = tmp;
        cur = tmp;
    }

    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if (start == NULL || splitPoint == 0)
        return start;
    int cnt = 0;
    ListNode *tmp = start;
    while (cnt ++ < splitPoint) {
        tmp = tmp -> next;
    }
    tmp -> prev -> next = NULL;
    return tmp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    ListNode *tmp = new ListNode();
    ListNode *pf = first, *ps = second, *cur = tmp;
    while (pf != NULL && ps != NULL) {
        if (pf -> data < ps -> data) {
            cur -> next = pf;
            pf -> prev = cur;
            pf = pf -> next;
        }
        else {
            cur -> next = ps;
            ps -> prev = cur;
            ps = ps-> next;
        }
    }
    if (pf != NULL) {
        cur -> next = pf;
        pf -> prev = cur;
    }
    if (ps != NULL) {
        cur -> next = ps;
        ps -> prev = cur;
    }
    return tmp -> next;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    ListNode *pf = start;
    if (chainLength == 1) {
        start ->prev = start ->next = NULL;
        return start;
    }
    else {
        ListNode *ps = split(start, chainLength / 2);
        pf = mergesort(pf, chainLength / 2);
        ps = mergesort(ps, chainLength - chainLength / 2);
        pf = merge(pf, ps);
    }
    return pf;
}
