/*
 Colin McDaniel
 March 5, 2013
 
 This program gets nonnegative integers from the user and inserts them to a binary search tree, outputs some information regarding the tree, and then converts some numbers to binary code based on their place in the tree.
 */


#include<iostream>
#include<string>
#include<cassert>


using namespace std;


// Class declaration
class TreeIterator;


class TreeNode{
public:
    
    // Member functions
    void insert_node(TreeNode* new_node);
    void print_nodes() const;
    bool find(int value) const;
    
private:
    
    // Holds integer data for this node in tree
    int data;
    
    // This node's children
    TreeNode* left;
    TreeNode* right;
    
    // This node's parent node
    TreeNode* par;
    
    // Friend classes
    friend class BinarySearchTree;
    friend class TreeIterator;
};


class BinarySearchTree{
public:
    
    // Member functions
    BinarySearchTree();
    void insert(int data);
    void erase(int data);
    int count(int data) const;
    void print() const;
    int smallest();
    int largest();
    TreeIterator begin();
    string BinaryCode(int k);
    
private:
    
    // Top node in tree
    TreeNode* root;
};


class TreeIterator{
public:
    
    // Member functions
    int get() const;
    
    // Operator overloads
    TreeIterator operator++();
    TreeIterator operator++ (int unused);
    TreeIterator operator-- (int unused);
    TreeIterator& operator--();
    
private:
    
    // Points to specific node in tree; current position of iterator
    TreeNode* position;
    
    // Friend class
    friend class BinarySearchTree;
};



int main(){
    
    // Prompt user to input integers into a binary search tree
    cout << "Please input a set of distinct nonnegative numbers for a Tree, pressing Enter between each number (Enter -1 when you are finished):\n";
    int data = 0;
    BinarySearchTree bst;
    int counter = 0;
    while(data != -1){
        cin >> data;
        if(data != -1){
            bst.insert(data);
            counter++;
        }
    }
    
    // Prints maximum and minimum values and size of Tree
    cout << "\nThe maximum of the entries is: " << bst.largest() << endl;
    cout << "The minimum of the entries is: " << bst.smallest() << endl;
    cout << "The size of the List is: " << counter << endl << endl;
    
    // Prompts user to insert more integers to binary search tree
    data = 0;
    while(data != -1){
        cout << "Select a value for insertion (enter -1 when finished): ";
        cin >> data;
        if(data != -1){
            bst.insert(data);
            counter++;
        }
    }
    
    // Prints maximum and minimum values and size of updated Tree
    cout << "\nThe maximum of the entries is: " << bst.largest() << endl;
    cout << "The minimum of the entries is: " << bst.smallest() << endl;
    cout << "The size of the List is: " << counter << endl << endl;

    cout << "Where 0 is the next left child, and 1 is the next right child (2 means not found)..." << endl;
    
    // Prints the binary code for specific tree for integers 1-9
    for(int i = 1; i <= 9; i++)
        cout << "The binary code for the value " << i << " is: " << bst.BinaryCode(i) << endl;
    cout << endl;
    
    // Prompts user to enter data values to erase
    data = 0;
    while(data != -1){
        cout << "Select a value to erase (enter -1 when finished): ";
        cin >> data;
        if(data != -1)
            bst.erase(data);
    }
    cout << endl;
    
    // Prints the binary code for the updated tree for integers 1-9
    for(int i = 1; i <= 9; i++)
        cout << "The binary code for " << i << " is: " << bst.BinaryCode(i) << endl;
    
    cout << endl;
    return 0;
}



/** Inserts a node in the appropriate place after this node
 @param new_node Pointer to the data, node to be inserted
 */
void TreeNode::insert_node(TreeNode* new_node){
    if(new_node->data < data){          // insert on left side
        if(left == NULL){       // insert node (base case)
            left = new_node;
            new_node->par = this;
        }
        else                    // recursively call until empty spot on tree
            left->insert_node(new_node);    
    }
    else if(data < new_node->data){     // insert on right side
        if(right == NULL){      // insert node (base case)
            right = new_node;
            new_node->par = this;
        }
        else                    // recursively call until empty spot on tree
            right->insert_node(new_node);
    }
    return;
}


/** Prints nodes from left to right */
void TreeNode::print_nodes() const{
    
    // Recursive calls print left side of tree
    if(left != NULL)
        left->print_nodes();
    cout << data << endl;
    
    // Recursive calls print right side of tree
    if(right != NULL)
        right->print_nodes();
    
    return;
}


/** Returns a boolean based on if a given value is in the tree
@param value The valued to be searched for
@return boolean, whether value is in tree
*/
bool TreeNode::find(int value) const{
    if(value < data){           // look left
        if(left == NULL)
            return false;
        else        // keep looking left
            return left->find(value);
    }
    else if(data < value){      // look right
        if(right == NULL)
            return false;
        else        // keep looking right
            return right->find(value);
    }
    else
        return true;
}


/** Constructs an empty tree */
BinarySearchTree::BinarySearchTree(){
    root = NULL;
}


/** Inserts data to the tree
 @param data to insert
 */
void BinarySearchTree::insert(int data){
    
    // Create new node on tree
    TreeNode* new_node = new TreeNode;
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    
    // Insert to tree
    if(root == NULL){
        root = new_node;
        new_node->par = NULL;
    }
    else
        root->insert_node(new_node);
    
    return;
}


/** Erases data from tree
@param data to be erased
*/
void BinarySearchTree::erase(int data){
    
    // Find node to be removed and store data in to_be_removed
    TreeNode* to_be_removed = root;
    TreeNode* parent = NULL;
    bool found = false;
    while(!found && to_be_removed != NULL){
        if(to_be_removed->data < data){
            parent = to_be_removed;
            to_be_removed = to_be_removed->right;
        }
        else if(data < to_be_removed->data){
            parent = to_be_removed;
            to_be_removed = to_be_removed->left;
        }
        else
            found = true;
    }
    
    // If didn't find, return
    if(!found)
        return;
    
    // If one of the children is empty, use the other
    if(to_be_removed->left == NULL || to_be_removed->right == NULL){
        TreeNode* new_child;
        if(to_be_removed->left == NULL)
            new_child = to_be_removed->right;
        else
            new_child = to_be_removed->left;
        
        if(parent == NULL)      // found in root
            root = new_child;
        else if(parent->left == to_be_removed){
            parent->left = new_child;
        }
        else
            parent->right = new_child;
        
        // Set new_child's parent
        if(new_child != NULL)
            new_child->par = parent;
        
        // Delete to_be_removed
        delete to_be_removed;
        return;
    }
    
    // Neither subtree is empty: find largest child of the left subtree and store in smallest
    TreeNode* largest_parent = to_be_removed;
    TreeNode* largest = to_be_removed->left;
    while(largest->right != NULL){
        largest_parent = largest;
        largest = largest->right;
    }
    
    // Move contents, unlink child
    to_be_removed->data = largest->data;
    if(largest_parent == to_be_removed)
        largest_parent->left = largest->left;
    else
        largest_parent->right = largest->left;
    
    // Set "node to the left of largest"'s parent to largest_parent, relinking tree
    if(largest->left != NULL)
        largest->left->par = largest_parent;
    
    // Delete largest node in subtree which got moved to to_be_removed
    delete largest;
    
    return;
}


/** Counts the number of times a particular data value occurs in tree, either 0 or 1
@param data to be counted
@return number of occurrences of data value
*/
int BinarySearchTree::count(int data) const{
    if(root == NULL)
        return 0;
    else if(root->find(data))
        return 1;
    else
        return 0;
}


/** Prints the tree in ascending order */
void BinarySearchTree::print() const{
    if(root != NULL)
        root->print_nodes();
}


/** Gets the smallest data value in the tree
@return smallest value in tree
*/
int BinarySearchTree::smallest(){
    
    // Increment pos left as much as possible and return data value
    TreeIterator pos = this->begin();
    while(pos.position->left != NULL)
        ++pos;
    return pos.get();
}


/** Returns largest data value in the tree
 @return largest value in tree
 */
int BinarySearchTree::largest(){
    
    // Increment pos right as much as possible and return data value
    TreeIterator pos = this->begin();
    while(pos.position->right != NULL)
        pos++;
    return pos.get();
}


/** Top position of the iterator pointing to the root node
 @return iterator pointing to the root node
 */
TreeIterator BinarySearchTree::begin(){
    TreeIterator r;
    r.position = root;
    return r;
}


/** Gets the binary code for a specific integer
 @param k The integer to convert to binary code
 @return binary code of k dependent on tree structure
 */
string BinarySearchTree::BinaryCode(int k){
    string bin = "";
    
    // If integer not in tree, bin gets set to "2"
    if(root->find(k) == false)
        bin = "2";
    else{       // iterate through the tree recording the path as binary code in bin
        TreeIterator pos = this->begin();
        while(pos.get() != k){
            if(k < pos.get()){
                bin += "0";
                ++pos;
            }
            else if(k > pos.get()){
                bin += "1";
                pos++;
            }
        }
    }
    
    return bin;
}


/** Gets the data value of the node which the iterator points to
@return data value of what position is pointing to
*/
int TreeIterator::get() const{
    return this->position->data;
}


/** Prefix ++ operator overload, updates the TreeIterator by pointing to the left child and returns a clone of the original
@return clone of unmodified TreeIterator
*/
TreeIterator TreeIterator::operator++(){
    
    // Cause error if try to increment a pointer with the value NULL
    assert(position != NULL);
    
    TreeIterator clone = *this;
    position = position->left;
    return clone;
}


/** Postfix ++ operator overload, updates the TreeIterator by pointing to the right child and returns a clone of the original
@return clone of unmodified TreeIterator
*/
TreeIterator TreeIterator::operator++ (int unused){
    
    // Cause error if try to increment a pointer with the value NULL
    assert(position != NULL);
    
    TreeIterator clone = *this;
    position = position->right;
    return clone;
}


/** Postfix -- operator overload, updates the TreeIterator by pointing to the parent node and returns a clone of the original
@return clone of unmodified TreeIterator
*/
TreeIterator TreeIterator::operator-- (int unused){
    
    // Cause error if try to decrement the root node
    assert(position->par != NULL);
    
    TreeIterator clone = *this;
    position = position->par;
    return clone;
}


/** Prefix -- operator overload, updates the TreeIterator by pointing to the parent node and returns updated object
@return updated TreeIterator
*/
TreeIterator& TreeIterator::operator--(){
    
    // Cause error if try to decrement the root node
    assert(position->par != NULL);
    
    position = position->par;
    return *this;
}