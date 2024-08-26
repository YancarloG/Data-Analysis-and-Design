/*
 * Name: Yancarlo Guzman
 * Class: CS300 SNHU
 * Date: August 15, 2024
 * 
 * Description:
 * This program loads course data from a CSV file into a Binary Search Tree (BST).
 * It alows us to interact with the program through a menu, where we can load the data,
 * display all courses, find and display a specific course, and exit the program.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Structure to represent a Course
struct Course {
    string courseId;           // Unique identifier for the course
    string courseName;         // Name of the course
    vector<string> prerequisites; // List of prerequisites for the course

    // Constructor to initialize course data
    Course(string id = "", string name = "") : courseId(id), courseName(name) {}
};

// Node structure for the Binary Search Tree
struct Node {
    Course course; // Course data stored in the node
    Node* left;    // Pointer to the left child
    Node* right;   // Pointer to the right child

    // Constructor to initialize the node with a course
    Node(Course crs) : course(crs), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class to manage courses
class BinarySearchTree {
private:
    Node* root; // Root node of the BST

    // Helper function to insert a course into the BST
    void insert(Node*& node, Course course) {
        if (node == nullptr) {
            node = new Node(course); // Create a new node if the current one is empty
        } else if (course.courseId < node->course.courseId) {
            insert(node->left, course); // Recursively insert into the left subtree
        } else {
            insert(node->right, course); // Recursively insert into the right subtree
        }
    }

    // Helper function to display all courses in the BST (in-order traversal)
    void inOrder(Node* node) const {
        if (node == nullptr) return;

        inOrder(node->left); // Traverse left subtree
        cout << node->course.courseId << ", " << node->course.courseName << endl;
        inOrder(node->right); // Traverse right subtree
    }

    // Helper function to search for a specific course in the BST
    Node* search(Node* node, string courseId) const {
        if (node == nullptr || node->course.courseId == courseId) {
            return node; // Return the node if found, or nullptr if not found
        }

        if (courseId < node->course.courseId) {
            return search(node->left, courseId); // Search in the left subtree
        }

        return search(node->right, courseId); // Search in the right subtree
    }

public:
    // Constructor to initialize an empty BST
    BinarySearchTree() : root(nullptr) {}

    // Function to insert a course into the BST
    void InsertCourse(Course course) {
        insert(root, course);
    }

    // Function to display all courses in the BST
    void DisplayAllCourses() const {
        inOrder(root);
    }

    // Function to search and display a specific course by ID
    void DisplayCourse(string courseId) const {
        Node* node = search(root, courseId);
        if (node != nullptr) {
            cout << node->course.courseId << ", " << node->course.courseName << endl;
            cout << "Prerequisites: ";
            for (const string& prereq : node->course.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        } else {
            cout << "Course not found!" << endl;
        }
    }
};

// Function to load courses from a CSV file
void LoadCourses(string filename, BinarySearchTree& bst) {
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, prereq;
        getline(ss, id, ',');   // Extract the course ID
        getline(ss, name, ','); // Extract the course name

        Course course(id, name);

        // Extract the prerequisites
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        bst.InsertCourse(course); // Insert the course into the BST
    }

    file.close(); // Close the file
    cout << "Courses loaded successfully!" << endl;
}

// Function to display the menu and handle user input
void DisplayMenu(BinarySearchTree& bst) {
    int choice;
    string courseId;
    string filename;

    do {
        cout << "Menu:" << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the file name to load: ";
            cin >> filename;
            LoadCourses(filename, bst); // Load courses from the specified file
            break;
        case 2:
            bst.DisplayAllCourses(); // Display all courses in the BST
            break;
        case 3:
            cout << "Enter the course ID to search: ";
            cin >> courseId;
            bst.DisplayCourse(courseId); // Display the specific course by ID
            break;
        case 9:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
}

// Main function to run the program
int main() {
    BinarySearchTree bst; // Create an empty Binary Search Tree

    DisplayMenu(bst); // Display the menu and start the program

    return 0;
}
