// Elohim Jackson
// CS-300 DS&A
// Project2
// 10/16/2022

// enhanced version 06/04/2023

# include <iostream>
# include <iomanip>
# include <string>
# include <vector>
# include <sstream>
# include <fstream>

using namespace std;

// Course Struct
struct Course {
    string courseNum;
    string courseName;

    vector<string> PreReqs;

    Course() {};
    //constructor with 2 values the course number and course name
    Course(string aCourseNum, string aCourseName) {
        courseNum = aCourseNum;
        courseName = aCourseName;
    }
    //constructor with prereqs
    Course(string aCourseNum, string aCourseName, vector<string> prereqs) {
        courseNum = aCourseNum;
        courseName = aCourseName;
        vector<string> PreReqs = prereqs;
    }
};

// Node constructor
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course acourse) : Node() {
        this->course = acourse;
    }
};


// Binary Search Tree Class
// This is how the node will operate inOrder and postOrder recursion
class BST {
private:
    Node* root;
    void addNode(Course acourse, Node* node);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void printCourse(Node* node, string courseNum);

public:
    BST();
    void InOrder();
    void PostOrder();
    void PrintCourse(string courseNum);
    bool loadData();
    bool validatePreReqs(Course course);
    void insert(Course course);
};

BST::BST() {
    root = nullptr;
}

//inOrder
void BST::InOrder() {
    this->inOrder(root);
}

//postOrder
void BST::PostOrder() {
    this->postOrder(root);
}



//Print course
void BST::PrintCourse(string courseNum) {
    this->printCourse(root, courseNum);
}


// Insert a New Node
void BST::insert(Course course) {
    //if root is empty
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(course, root);
    }
}


// Add Node to Binary Search Tree

void BST::addNode(Course acourse, Node* node) {

    //if current node is larger than passed courseNum
    if (node->course.courseNum.compare(acourse.courseNum) > 0) {
        //if there is no left node
        if (node->left == nullptr) {
            node->left = new Node(acourse);
        }
        //recurse down left side
        else {
            this->addNode(acourse, node->left);
        }
    }
    //if current node is smaller than passed courseNum
    else {
        //if there is no right node
        if (node->right == nullptr) {
            node->right = new Node(acourse);
        }
        //recurse down right side
        else {
            this->addNode(acourse, node->right);
        }
    }
}


// Print Courses inOrder
void BST::inOrder(Node* node) {

    if (node != nullptr) {
        //recurse down left side
        inOrder(node->left);
        //print course information at current node
        cout << "Course number: " << node->course.courseNum;
        cout << " Course name: " << node->course.courseName;
        cout << " Prerequisite(s): ";
        //iterate through vector to print
        for (int i = 0; i < node->course.PreReqs.size(); ++i) {
            cout << node->course.PreReqs[i] << " ";
        }
        if (node->course.PreReqs.size() == 0) {
            cout << "None" << endl;
        }

        //recurse down right side
        inOrder(node->right);
    }
    return;
}


// Print courses in postOrder
void BST::postOrder(Node* node) {

    if (node != nullptr) {
        return;
        
        //recurse on the left side of tree first
        postOrder(node->left);

        //recurse on right side of tree
        postOrder(node->right);

        //print course information at current node
        cout << "Course number: " << node->course.courseNum;
        cout << " Course name: " << node->course.courseName;
        cout << " Prerequisite(s): ";
        //iterate through vector to print
        for (int i = 0; i < node->course.PreReqs.size(); ++i) {
            cout << node->course.PreReqs[i] << " ";
        }
        if (node->course.PreReqs.size() == 0) {
            cout << "None" << endl;
        }

     
    }
    return 0;
}


// Print course
void BST::printCourse(Node* node, string courseNum) {

    while (node != nullptr) {
        //if match is found
        if (node->course.courseNum.compare(courseNum) == 0) {
            cout << "Course number: " << node->course.courseNum;
            cout << "  Course name: " << node->course.courseName;
            cout << "  Prerequisite(s): ";
            //iterate through prereq vector to print
            for (int i = 0; i < node->course.PreReqs.size(); ++i) {
                cout << node->course.PreReqs[i] << " " << endl;
            }
            //if there are no prereqs
            if (node->course.PreReqs.size() == 0) {
                cout << "None" << endl;
            }
            return;
        }
        //if current course number is smaller than the one passed in
        else if (node->course.courseNum.compare(courseNum) > 0 && node->left != nullptr) {
            node = node->left;
        }
        //if current course number is larger than the one passed in
        else if (node->course.courseNum.compare(courseNum) < 0 && node->right != nullptr) {
            node = node->right;
        }
        else {
            cout << "Course not found." << endl;
            return;
        }
    }
    //error if tree is not loaded
    if (root == nullptr) {
        cout << "Error loading data." << endl;
        return;
    }
}


//Loads data from file
bool BST::loadData() {

    //use ifstream to open file
    ifstream file;
    file.open("Coursefile.txt");

    if (file.is_open()) {
        //while end of file is not reached
        while (!file.eof()) {
            //create a vector to hold line items
            vector<string> courseLine;
            //to parse line into vector
            string line;

            getline(file, line);

            while (line.length() > 0) {
                unsigned int delim = line.find(',');
                if (delim <= 99) {
                    courseLine.push_back(line.substr(0, delim));
                    line.erase(0, delim + 1);
                }
                //add item following last comma, then clear line
                else {
                    courseLine.push_back(line.substr(0, line.length()));
                    line = "";
                }
            }

            Course course;
            //assign course number and name

            course.courseNum = courseLine[0];
            course.courseName = courseLine[1];

            for (unsigned int i = 2; i < courseLine.size(); i++) {
                course.PreReqs.push_back(courseLine[i]);
            }
            //insert the course into bst
            insert(course);
        }
        return true;
    }
    if (!file) {
        cout << "ERROR file did not open properly" << endl;
        return false;
    }
    file.close();
}

bool BST::validatePreReqs(Course course) {
    Node* current = root;
    if (current->course.PreReqs.size() > 0) {
        //iterate through prerequisite vector
        for (int i = 0; i < course.PreReqs.size(); i++) {
            while (current != nullptr) {
                //if match is found
                if (course.PreReqs[i] == current->course.courseNum) {
                    return true;
                }
                //if course number is smaller than prerequisite
                else if (course.PreReqs[i].compare(current->course.courseNum) > 0 && current->left != nullptr) {
                    current = current->left;
                }
                //if course number is larger than prerequisite
                else if (course.PreReqs[i].compare(current->course.courseNum) < 0 && current->right != nullptr) {
                    current = current->right;
                }
                //if number is not found
                else {
                    cout << "Prerequisite not found. \n";
                    return false;
                }
            }
        }
    }
    else {
        //no prerequisites
        return true;
    }
}

int main()
{
    //create bst 
    BST* bst = new BST();
    //create a string variable to hold input (for case 3)
    string courseNum;
    //set choice to 0
    int choice = 0;

    //Menu loop that will iterate until user enters 4
    while (choice != 4) {
        
        cout << "Menu Options" << endl;
        cout << "[1]Load Data Structure" << endl;
        cout << "[2]Print Course List In Order" << endl;
        cout << "[3]Print Course List In Post Oder" << endl;;
        cout << "[4]Print Course" << endl;
        cout << "[5]Exit" << endl;
        cout << "Enter your option?" << endl;
        cin >> choice;

        //menu selections
        switch (choice) {
            //load data from file
        case 1:
            bst->loadData();
            break;
            //print sorted course information
        case 2:
            cout << "Print course list";
            bst->InOrder();
            cout << " " << endl;
            break;
            //search for course to display
        case 3:
            cout << "Print course list";
            bst->PostOrder();
            cout << " " << endl;
            break;
            //search for course to display
        case 4:
            cout << "Enter the course you would like to search: ";
            cin >> courseNum;
            bst->PrintCourse(courseNum);
            cout << " " << endl;
            break;
       //Exits menu
        case 5:
            break;
            //for invalid input
        default:
            cout << choice << " Enter a valid option" << endl;
        }
    }
    return 0;
}
