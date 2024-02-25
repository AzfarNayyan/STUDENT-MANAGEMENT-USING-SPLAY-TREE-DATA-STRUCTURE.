//AZFAR NAYYAN 
//BSE-3C
//22L-7886 
//DS ASSIGNMENT 04


#include<iostream>
#include<vector>
#include<Windows.h>
#include<string>

using namespace std;

class StudentList;
class Student;

template<class T>
class SpecialBST
{

private:

	struct Node
	{
		T data;
		Node* right;
		Node* left;
		Node* parent;
	public:
		Node()
		{
			left = right = parent = nullptr;
		}
		Node(T e)
		{
			data = e;
			left = right = parent = nullptr;
		}
	};

	Node* root;

	void leftRotate(Node* node)
	{
		Node* child = node->right;
		node->right = child->left;

		if (child->left != nullptr)
		{
			child->left->parent = node;
		}
		child->parent = node->parent;
		if (node->parent == nullptr)
		{
			this->root = child;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = child;
		}
		else
		{
			node->parent->right = child;
		}

		child->left = node;
		node->parent = child;
	}

	void rightRotate(Node* node)
	{
		Node* child = node->left;
		node->left = child->right;

		if (child->right != nullptr)
		{
			child->right->parent = node;
		}
		child->parent = node->parent;
		if (node->parent == nullptr)
		{
			this->root = child;
		}
		else if (node == node->parent->right)
		{
			node->parent->right = child;
		}
		else
		{
			node->parent->left = child;
		}

		child->right = node;
		node->parent = child;
	}

	void SPLAY_NODE_TO_ROOT(Node* node)
	{
		if (!node) return;

		while (node->parent)
		{
			if (!node->parent->parent)
			{
				if (node == node->parent->left)//ZIG ROTATION CASE.
				{
					rightRotate(node->parent);
				}
				else //ZAG ROTATION CASE.
				{
					leftRotate(node->parent);
				}
			}
			else if (node == node->parent->left && node->parent == node->parent->parent->left) //ZIG-ZIG ROTATION CASE.
			{
				rightRotate(node->parent->parent);
				rightRotate(node->parent);
			}
			else if (node == node->parent->right && node->parent == node->parent->parent->right) //ZAG-ZAG ROTATION CASE.
			{
				leftRotate(node->parent->parent);
				leftRotate(node->parent);
			}
			else if (node == node->parent->right && node->parent == node->parent->parent->left) //ZIG-ZAG ROTATION CASE.
			{
				leftRotate(node->parent);
				rightRotate(node->parent);
			}
			else //ZAG-ZIG ROTATION CASE.
			{
				rightRotate(node->parent);
				leftRotate(node->parent);
			}
		}
	}

	void deleteR(Node*& node, int r);

	void getPredecessor(Node* node, int& e)
	{
		while (node->right != NULL)
			node = node->right;

		e = node->data.rollNO;
	}

	void deleteNode(Node*& node)
	{
		int r;
		Node* temp = node;

		if (node->left == NULL)
		{
			node = node->right;
			SPLAY_NODE_TO_ROOT(temp->parent);
			delete temp;
		}
		else if (node->right == NULL)
		{
			node = node->left;
			SPLAY_NODE_TO_ROOT(temp->parent);
			delete temp;
		}
		else
		{
			getPredecessor(node->left, r);
			node->data.rollNO = r;
			deleteR(node->left, r);
		}
	}

	void inOrderR(Node* node)
	{
		if (node)
		{
			inOrderR(node->left);
			node->data.print();
			inOrderR(node->right);
		}
	}

	void destroy(Node* node)
	{
		if (node == nullptr) return;

		destroy(node->left);
		destroy(node->right);

		delete node;
	}

	int size(Node* node)
	{
		if (node == NULL)
			return 0;
		else
			return(size(node->left) + 1 + size(node->right));
	}
	int height(Node* node)
	{
		if (node == NULL)
			return 0;
		else
		{
			int lheight = height(node->left);
			int rheight = height(node->right);

			if (lheight > rheight)
				return (lheight + 1);
			else
				return (rheight + 1);
		}
	}


public:
	SpecialBST()              // 1. DEFAULT CONSTRUCTOR.
	{
		root = nullptr;
	}
	bool insert(T e)              // 2. INSERTION WITH SPLAYING.
	{
		Node* node = new Node(e);

		Node* parent = nullptr;
		Node* child = this->root;

		while (child != nullptr)
		{
			parent = child;
			if (node->data.rollNO < child->data.rollNO)
			{
				child = child->left;
			}
			else if (node->data.rollNO == child->data.rollNO)
			{
				return false;
			}
			else
			{
				child = child->right;
			}
		}

		node->parent = parent;

		if (parent == nullptr)
		{
			root = node;
		}
		else if (node->data.rollNO < parent->data.rollNO)
		{
			parent->left = node;
		}
		else
		{
			parent->right = node;
		}

		SPLAY_NODE_TO_ROOT(node);
		return true;
	}
	bool search(int r)       // 3. SEARCHING WITH SPLAYING.
	{
		Node* temp_node = root;
		Node* prev_node = nullptr;
		bool flag = false;

		while (temp_node && !flag)
		{
			if (temp_node->data.rollNO == r)
			{
				flag = true;
				break;
			}
			else if (temp_node->data.rollNO > r)
			{
				prev_node = temp_node;
				temp_node = temp_node->left;
			}
			else
			{
				prev_node = temp_node;
				temp_node = temp_node->right;
			}

		}

		return flag;
	}
	void UPDATE(int nr, int oroll, string fn, string ln, int b, string d, float c)
	{
		Node* temp_node = root;
		Node* prev_node = nullptr;
		bool flag = false;

		while (temp_node && !flag)
		{
			if (temp_node->data.rollNO == oroll)
			{
				flag = true;
				temp_node->data.update(nr, fn, ln, b, d, c);
				break;
			}
			else if (temp_node->data.rollNO > oroll)
			{
				prev_node = temp_node;
				temp_node = temp_node->left;
			}
			else
			{
				prev_node = temp_node;
				temp_node = temp_node->right;
			}

		}

		if (flag == true) SPLAY_NODE_TO_ROOT(temp_node);
	}

	bool Delete(int r)        // 4. DELETING WITH SPLAYING.
	{
		bool flag = search(r);
		if (flag == true)
		{
			deleteR(root, r);
			cout << "NO STUDENT WITH ROLL " << r << " DELETED." << endl;
			return flag;
		}
		else
		{
			cout << "NO STUDENT WITH ROLL " << r << " DOES NOT EXISTS TO DELETE." << endl;
			return flag;
		}
	}

	void inOrderPrint()
	{
		int s = this->size(root);
		cout << "THE IN-ORDER PRINT IS: " << endl;
		cout << "==== TOTAL STUDENTS: " << s << " =========." << endl;
		inOrderR(root);
		cout << endl;
	}

	void ROOT()
	{
		root->data.print();
	}

	~SpecialBST()  // 7. DESTRUCTOR.
	{
		destroy(root);
	}
};
template<class T>
void SpecialBST<T>::deleteR(Node*& node, int r)
{
	if (r > node->data.rollNO)
		deleteR(node->right, r);
	else if (r < node->data.rollNO)
		deleteR(node->left, r);
	else
		deleteNode(node);
}


class Student
{
public:

	int rollNO;
	string firstName;
	string lastName;
	int batch;
	string department;
	float cgpa;

	Student() { };
	Student(int r, string fn, string ln, int b, string d, float c)
	{
		rollNO = r;
		firstName = fn;
		lastName = ln;
		batch = b;
		department = d;
		cgpa = c;
	}

	void print()
	{
		cout << "STUDENT DATA!" << endl;
		cout << "ROLL: " << rollNO << " FIRST NAME: " << firstName << " LAST NAME: " << lastName << endl;
		cout << "BATCH: " << batch << " DEP: " << department << " CGPA:" << cgpa << "." << endl;
		cout << "===========" << endl;
	}

	void update(int r, string fn, string ln, int b, string d, float c)
	{
		rollNO = r;
		firstName = fn;
		lastName = ln;
		batch = b;
		department = d;
		cgpa = c;
	}
};




class StudentList
{
	SpecialBST<Student> myStudentList;

public:
	bool insertNewStudent(int r, string fn, string ln, int b, string d, float c)  //1. INSERTION FUNC.
	{
		Student* s = new Student(r, fn, ln, b, d, c);

		bool flag = myStudentList.insert(*s);

		if (flag == true)
		{
			cout << "STUDENT DATA INSERTED !!" << endl;
		}
		else if (flag == false)
		{
			cout << "ROLL NO ALREADY EXISTS AND DUPLICATION IS NOT ALLOWED!!" << endl;
		}

		return flag;
	} 
	bool deleteStudent(int r)   //2. DELETION FUNC.
	{
		bool flag = myStudentList.Delete(r);

		return flag;
	}
	void printALL() //3. PRINTING FUNC.
	{
		myStudentList.inOrderPrint();
	}
	void printROOT()  //4. ROOT PRINT.
	{
		cout << "THE ROOT TREE STUDENT IS: " << endl << endl;
		myStudentList.ROOT();
	}
	bool updateStudent(int nr, int oroll, string fn, string ln, int b, string d, float c)  //5. UPDATION FUNCTION.
	{
		if (oroll == nr)
		{
			bool flag = myStudentList.search(oroll);
			if (flag == true)
			{
				myStudentList.UPDATE(nr, oroll, fn, ln, b, d, c);
				cout << "STUDENT DATA UPDATED!!" << endl;
			}
			else
			{
				cout << "NO STUDENT EXISTS!!" << endl;
			}
		}
		else if (oroll != nr)
		{
			bool flag = myStudentList.search(nr);

			if (flag == true)
			{
				cout << "ROLL NO ALREADY EXISTS. (updation func)." << endl;
			}
			else
			{
				myStudentList.UPDATE(nr, oroll, fn, ln, b, d, c);
				cout << "STUDENT DATA UPDATED!!" << endl;
			}
		}

		return true;
	}
};




int main()
{
	StudentList studentList;

	int choice;
	int sleepTime = 1500;

	do {
		cout << "1. Insert New Student." << endl;
		cout << "2. Delete Student." << endl;
		cout << "3. Print All Students." << endl;
		cout << "4. Print Root Student." << endl;
		cout << "5. Update Student." << endl;
		cout << "6. Exit." << endl;

		cout << "Enter your choice: ";
		cin >> choice;


		if (choice == 1) 
		{
			int roll;
			string firstName, lastName, department;
			int batch;
			float cgpa;

			cout << "Enter Roll Number: ";
			cin >> roll;
			cout << "Enter First Name: ";
			cin >> firstName;
			cout << "Enter Last Name: ";
			cin >> lastName;
			cout << "Enter Batch: ";
			cin >> batch;
			cout << "Enter Department: ";
			cin >> department;
			cout << "Enter CGPA: ";
			cin >> cgpa;

			studentList.insertNewStudent(roll, firstName, lastName, batch, department, cgpa);

			Sleep(sleepTime);
			system("CLS");
		}
		else if (choice == 2) 
		{
			int roll;
			cout << "Enter Roll Number to Delete: ";
			cin >> roll;
			studentList.deleteStudent(roll);

			Sleep(sleepTime);
			system("CLS");
		}
		else if (choice == 3)
		{
			studentList.printALL();

			Sleep(sleepTime);
			system("CLS");
		}
		else if (choice == 4)
		{
			studentList.printROOT();

			Sleep(sleepTime);
			system("CLS");
		}
		else if (choice == 5) 
		{
			int newRoll, oldRoll;
			string newFirstName, newLastName, newDepartment;
			int newBatch;
			float newCgpa;

			cout << "Enter Old Roll Number: ";
			cin >> oldRoll;
			cout << "Enter New Roll Number: ";
			cin >> newRoll;
			cout << "Enter New First Name: ";
			cin >> newFirstName;
			cout << "Enter New Last Name: ";
			cin >> newLastName;
			cout << "Enter New Batch: ";
			cin >> newBatch;
			cout << "Enter New Department: ";
			cin >> newDepartment;
			cout << "Enter New CGPA: ";
			cin >> newCgpa;

			studentList.updateStudent(newRoll, oldRoll, newFirstName, newLastName, newBatch, newDepartment, newCgpa);

			Sleep(sleepTime);
			system("CLS");
		}
		else if (choice == 6) 
		{
			cout << "Exiting program." << endl;
			break;
		}
		else
		{
			cout << "Invalid choice. Please enter a valid option." << endl;
			Sleep(sleepTime);
			system("CLS");
		}

	} while (choice != 6);

	system("pause>0");
	return 0;


	//ds 04

}