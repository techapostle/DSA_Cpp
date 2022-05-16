#include <iostream>
#include <queue>
using namespace std;
/********************************************************************/
/*                                                                  */
/*  A3: Binary Search Tree                                          */
/*                                                                  */
/*  Author1 Name: <Matthew Lee> 117715185                           */
/*      - class/function list/main author                           */
/*  Author2 Name: <Kian Dadkhah Shokrollahi> 119369205              */
/*      - main checker                                              */
/*                                                                  */
/********************************************************************/

/* This class implements a Threaded Binary Tree. A threaded binary search tree is a binary search tree where 
 * the pointers that are normally nullptrs would instead be used to point at the next smallest (left pointer) 
 * or the next biggest (right pointer) node in the tree. These pointers are called threads. 
 * These threads make it easier to iterate through the tree. It also implements an iterator and a const iterator
 * inner class to handle the operations involving iterators.
 * */
template <class T>
class ThreadedTree{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;

		bool leftThread;
		bool rightThread;
		Node(const T& data=T{},Node* left=nullptr, Node* right=nullptr){
			data_ = data;
			left_ = left;
			right_ = right;
			leftThread = false;
			rightThread = false;
		}
	};
	Node* root_;
	int size_;
	void print(const Node* rt, int lvl)const{
		//This function won't be tested, but you may find it useful to implement this so 
		//that you can see what the tree looks like.  lvl will allow you to use dashes to 
		//better show shape of tree.  Feel free to modify this to print in any way that will
		//help you debug.  Feel free to copy the pretty print function from lab 8 that will draw
		//the tree (though it won't draw threads)
	}

public:
	class const_iterator{
	protected:
		Node* currNode;
		const ThreadedTree* threadTree;
		const_iterator(Node* c, const ThreadedTree* tree) {
			currNode = c; 
			threadTree = tree;
		}
	public:
		const_iterator(){
			currNode = nullptr;
			threadTree = nullptr;
		}
		const_iterator operator++(int){
			const_iterator it=*this;
			if (this->currNode->rightThread == false) {
				if (this->currNode->right_ != nullptr) {
					this->currNode = this->currNode->right_;
					while (this->currNode->left_ && this->currNode->leftThread == false) {
						this->currNode = this->currNode->left_;
					}
				}
			}
			else {
				this->currNode = this->currNode->right_;
			}
			return it;
		}
		const_iterator operator--(int){
			const_iterator it = *this;
			if (this->currNode) {
				if (this->currNode->leftThread == false) {
					if (this->currNode->left_ != nullptr) {
						this->currNode = this->currNode->left_;
						while (this->currNode->right_ && this->currNode->rightThread == false) {
							this->currNode = this->currNode->right_;
						}
					}
				}
				else {
					this->currNode = this->currNode->left_;
				}
			}
			else {
				this->currNode = this->threadTree->root_;
				while (this->currNode->right_) {
					this->currNode = this->currNode->right_;
				}
			}
			return it;
		}
		const_iterator operator++(){
			if (this->currNode->rightThread == false) {
				if (this->currNode->right_ != nullptr) {
					this->currNode = this->currNode->right_;
					while (this->currNode->left_ && this->currNode->leftThread == false) {
						this->currNode = this->currNode->left_;
					}
				}
			}
			else {
				this->currNode = this->currNode->right_;
			}
			return *this;
		}
		const_iterator operator--(){
			if (this->currNode) {
				if (this->currNode->leftThread == false) {
					if (this->currNode->left_ != nullptr) {
						this->currNode = this->currNode->left_;
						while (this->currNode->right_ && this->currNode->rightThread == false) {
							this->currNode = this->currNode->right_;
						}
					}
				}
				else {
					this->currNode = this->currNode->left_;
				}
			}
			else {
				this->currNode = this->threadTree->root_;
				while (this->currNode->right_) {
					this->currNode = this->currNode->right_;
				}
			}
			return *this;
		}
		const T& operator*() const{
			return currNode->data_;
		}
		bool operator==(const const_iterator& rhs) const{
			return currNode == rhs.currNode;
		}
		bool operator!=(const const_iterator& rhs) const{
			return currNode != rhs.currNode;
		}
		friend class ThreadedTree;
	};
	class iterator:public const_iterator{
		iterator(Node* c, ThreadedTree* tree) :const_iterator(c, tree) { }
	public:
		iterator():const_iterator(){
		}
		const T& operator*() const{
			return this->currNode->data_;
		}
		T& operator*(){
			return this->currNode->data_;
		}
		iterator operator++(int){
			iterator it = *this;
			if (this->currNode->rightThread == false) {
				if (this->currNode->right_ != nullptr) {
					this->currNode = this->currNode->right_;
					while (this->currNode->left_ && this->currNode->leftThread == false) {
						this->currNode = this->currNode->left_;
					}
				}
			}
			else {
				this->currNode = this->currNode->right_;
			}
			return it;
		}
		iterator operator--(int) {
			iterator it= *this;
			if (this->currNode) {
				if (this->currNode->leftThread == false) {
					if (this->currNode->left_ != nullptr) {
						this->currNode = this->currNode->left_;
						while (this->currNode->right_ && this->currNode->rightThread == false) {
							this->currNode = this->currNode->right_;
						}
					}
				}
				else {
					this->currNode = this->currNode->left_;
				}
			}
			else {
				this->currNode = this->threadTree->root_;
				while (this->currNode->right_) {
					this->currNode = this->currNode->right_;
				}
			}
			return it;
		
		}
		iterator operator++(){
			if (this->currNode->rightThread == false) {
				if (this->currNode->right_ != nullptr) {
					this->currNode = this->currNode->right_;
					while (this->currNode->left_ && this->currNode->leftThread == false) {
						this->currNode = this->currNode->left_;
					}
				}
			}
			else {
				this->currNode = this->currNode->right_;
			}
			return *this;
		}
		iterator operator--() {
			if (this->currNode) {
				if (this->currNode->leftThread == false) {
					if (this->currNode->left_ != nullptr) {
						this->currNode = this->currNode->left_;
						while (this->currNode->right_ && this->currNode->rightThread == false) {
							this->currNode = this->currNode->right_;
						}
					}
				}
				else {
					this->currNode = this->currNode->left_;
				}
			}
			else {
				this->currNode = this->threadTree->root_;
				while (this->currNode->right_) {
					this->currNode = this->currNode->right_;
				}
			}
			return *this;
		}

		friend class ThreadedTree;
	};

  /* Default Constructor
   * */
	ThreadedTree(){
		root_ = nullptr;
		size_ = 0;
	}

  /* The function inserts the data into the tree. You may assume there will not be duplicates added.
   * */
	void insert(const T& data){
		if (root_ == nullptr) {
			root_ = new Node(data);
			size_++;
		}
		else {
      //set to true when once we insert the node
			bool isInserted = false;
      //used to iterate through nodes
			Node* curr = root_;

			bool smallest = true;
			bool largest = true;

			Node* nextSmall = root_;
			Node* nextLarge = root_;
			while (!isInserted) {
				if (data < curr->data_) {
					largest = false;
					//data belongs in left subtree because it is 
					//smaller than current node
					if (curr->data_ < nextSmall->data_) {
						nextSmall = curr;
					}
					nextLarge = curr;

					if (curr->left_ && curr->leftThread == false) {
						curr = curr->left_;
					}
					else {
						curr->left_ = new Node(data);
						curr->leftThread = false;
						isInserted = true;
						size_++;
						if (curr->left_) {
							curr->left_->right_ = nextLarge;
							curr->left_->rightThread = true;
							if (!smallest) {
								curr->left_->left_ = nextSmall;
								curr->left_->leftThread = true;
							}
						}

					}
				}
				else {
					nextSmall = curr;
					smallest = false;
					if (nextLarge->data_ < curr->data_)
						nextLarge = curr;
					if (curr->rightThread == false && curr->right_ )
						curr = curr->right_;
					else {
						curr->right_ = new Node(data);
						curr->rightThread = false;
						isInserted = true;
						size_++;
						if (curr->right_) {
							curr->right_->left_ = nextSmall;
							curr->right_->leftThread = true;
							if (!largest) {
								curr->right_->right_ = nextLarge;
								curr->right_->rightThread = true;
							}
						}
					}	
				}
			}
		}
	}

  /* this function accepts a value, key and returns an iterator/const_iterator
   * to the node containing that value. If key is not found, function returns end()/cend();
   * */
	iterator find(const T& key){
    //used  to iterate through tree
		Node* curr = root_;
    //true if we find it false if we haven't yet
		bool found = false;

		//loop until we either find it or we have no more tree
		while (!found && curr) {
			if (key == curr->data_) {
				found = true;
			}
			else if (key < curr->data_) {
				if (curr->leftThread == true)
					curr = nullptr;
				else
					curr = curr->left_;
			}
			else {
				if (curr->rightThread == true)
					curr = nullptr;
				else
					curr = curr->right_;
			}
		}
		return iterator(curr, this);
	}

  /*
   * this function accepts a value, key and returns an iterator/const_iterator to the node containing that value.
   * If key is not found, function returns end()/cend();
   * */
	const_iterator find(const T& key) const{
    //used  to iterate through tree
		Node* curr = root_;
    //true if we find it false if we haven't yet
		bool found = false;

		//loop until we either find it or we have no more tree
		while (!found && curr) {
			if (key == curr->data_) {
				found = true;
			}
			else if (key < curr->data_) {
				if (curr->leftThread == true)
					curr = nullptr;
				else
				curr = curr->left_;
			}
			else {
				if (curr->rightThread == true)
					curr = nullptr;
				else
				curr = curr->right_;
			}
		}
		return const_iterator(curr, this);
	}
	iterator begin(){
		iterator it;
		if (root_) {
			it.currNode = root_;
			while (it.currNode->left_ != nullptr)
				it.currNode = it.currNode->left_;
		}
		return it;
	}
	iterator end(){
		iterator it(nullptr,this);
		return it;
	}
	const_iterator cbegin()const{
		const_iterator it;
		if (root_) {
			it.currNode = root_;
			while (it.currNode->left_ != nullptr)
				it.currNode = it.currNode->left_;
		}
		return it;
	}
	const_iterator cend() const{
		const_iterator it(nullptr, this);
		return it;
	}
	void inOrderPrint(const Node* subtree) const {
		//base case is we have an empty tree... in that case we do nothing
		//and exit the function
		if (subtree != nullptr) {


			//values in left_ are smaller, we need to print them all first
			inOrderPrint(subtree->left_);

			//print value in current node
			std::cout << subtree->data_ << std::endl;

			//values in right_ are bigger, we need to print them all after we
			//print current node
			inOrderPrint(subtree->right_);
		}
	}

	void print() const{
		//inOrderPrint(root_);
		queue<Node*> theNodes;  
    //we assume the queue class has these functions
		//push(), pop(), front(), isEmpty()
		//prime queue
		if (root_) {
			theNodes.push(root_);
		}
		//while we have nodes to deal with
		while (!theNodes.empty()) {
			//deal with first node and remove it from queue
			Node* curr = theNodes.front();
			theNodes.pop();
			if (curr->left_ && curr->leftThread == false) {
				//if the current node has a left child add it to queue
				theNodes.push(curr->left_);
			}
			if (curr->right_ && curr->rightThread == false) {
				//if the current node has a right child add it to queue
				theNodes.push(curr->right_);
			}
			//print the current node's data
			std::cout << curr->data_ << " ";

			if (curr->left_) {
				std::cout << curr->left_->data_ << " ";
			}

			if (curr->right_) {
				std::cout << curr->right_->data_;
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

  /* This function returns the number of values stored in the tree.
   * */
	int size() const{
		//return inOrderSize(root_);
		return size_;
	}

  /*This function returns true if the tree has no values stored, false otherwise.
   * */
	bool empty() const{
		return root_ == nullptr;
	}

  /*This function recurses through a given subtree, checking if its incoming argument (the subtree) is valid.
   * Once it finds a node with no children, it returns nothing, and destroys the parent of that node.
   * */
  void destroyRecursive(Node* subtree) {
		if (subtree != nullptr && subtree->leftThread == false && subtree->rightThread ==false) {
			destroyRecursive(subtree->left_);
			destroyRecursive(subtree->right_);
			delete subtree;
		}
	}

  /* Destructor
   * */
	~ThreadedTree(){
		destroyRecursive(root_);
	}
};
