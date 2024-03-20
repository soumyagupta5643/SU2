#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Node {
    Point point;
    Node *left, *right;
    Node(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    Node* root;

    // Helper function to build the tree recursively
    Node* buildTree(vector<Point> points, int depth) {
        if (points.empty()) 
        return nullptr;

        int axis = depth % 2; // 2 for 2D space (x and y)
        int medianIdx = points.size() / 2;

        // Sort points based on current axis
        if (axis == 0) {
            sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
                return a.x < b.x;
            });
        } else {
            sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
                return a.y < b.y;
            });
        }

        // Create node with median point and recursively build subtrees
        Node* newNode = new Node(points[medianIdx]);
        newNode->left = buildTree(vector<Point> (points.begin(), points.begin() + medianIdx), depth + 1);
        newNode->right = buildTree(vector<Point> (points.begin() + medianIdx + 1, points.end()), depth + 1);

        return newNode;
    }

    // Helper function for nearest neighbor search
    void nearestNeighborUtil(Node* root, Point& target, Node*& nearest, double& minDist, int depth) {
        if (root == nullptr) 
        return;

        int axis = depth % 2; // 2 for 2D space (x and y)

        // Calculate distance between target and current point
        double dist = pow(root->point.x - target.x, 2) + pow(root->point.y - target.y, 2);

        // Update nearest neighbor if needed
        if (dist < minDist) {
            nearest = root;
            minDist = dist;
        }

        // Recursively search subtrees
        if (axis == 0) { // Compare x-coordinate
            if (target.x < root->point.x) {
                nearestNeighborUtil(root->left, target, nearest, minDist, depth + 1);
                if (target.x + sqrt(minDist) >= root->point.x)
                    nearestNeighborUtil(root->right, target, nearest, minDist, depth + 1);
            } else {
                nearestNeighborUtil(root->right, target, nearest, minDist, depth + 1);
                if (target.x - sqrt(minDist) <= root->point.x)
                    nearestNeighborUtil(root->left, target, nearest, minDist, depth + 1);
            }
        } else { // Compare y-coordinate
            if (target.y < root->point.y) {
                nearestNeighborUtil(root->left, target, nearest, minDist, depth + 1);
                if (target.y + sqrt(minDist) >= root->point.y)
                    nearestNeighborUtil(root->right, target, nearest, minDist, depth + 1);
            } else {
                nearestNeighborUtil(root->right, target, nearest, minDist, depth + 1);
                if (target.y - sqrt(minDist) <= root->point.y)
                    nearestNeighborUtil(root->left, target, nearest, minDist, depth + 1);
            }
        }
    }

public:
    KDTree(vector<Point>& points) {
        root = buildTree(points, 0);
    }

    // Function to find nearest neighbor to a given point
    Point nearestNeighbor(Point& target) {
        Node* nearest = nullptr;
        double minDist = 1e18;
        nearestNeighborUtil(root, target, nearest, minDist, 0);
        return nearest->point;
    }

};

int main() {
    vector<Point> points = {{2, 4}, {5, 4}, {9, 6}, {4, 9}, {8, 1}, {7, 2}};
    KDTree tree(points);

    Point target(3, 5);
    Point nearest = tree.nearestNeighbor(target);

    cout << "Nearest neighbor to (" << target.x << ", " << target.y << ") is (" << nearest.x << ", " << nearest.y << ")" << endl;

    return 0;
}
