#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

// Kiểm tra giá trị trùng nhau trong mảng 2 chiều
bool checkDuplicateValues(vector<vector<int>>& maze) {
    set<int> values;
    for (const auto& row : maze) {
        for (int value : row) {
            if (values.count(value) > 0) {
                return true;
            }
            values.insert(value);
        }
    }
    return false;
}

// Định nghĩa cấu trúc điểm
struct Point {
    int x;
    int y;
    int value;

    Point(int x, int y, int value) : x(x), y(y), value(value) {}
};

// Hàm đệ quy để tìm đường đi tốt nhất cho robot
void findBestPath(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y, int score) {
    // Kiểm tra xem robot đã đi ra khỏi mê cung hay chưa
    if (x < 0 || x >= maze.size() || y < 0 || y >= maze[0].size()) {
        return;
    }

    // Kiểm tra xem ô hiện tại đã được đi qua hay chưa
    if (visited[x][y]) {
        return;
    }

    // Đánh dấu ô hiện tại đã được đi qua
    visited[x][y] = true;

    // In giá trị của ô hiện tại
    cout << "Ô (" << x << ", " << y << ") - Giá trị: " << maze[x][y] << endl;

    // Tạo một danh sách các điểm xung quanh ô hiện tại
    vector<Point> points;
    if (x > 0 && !visited[x - 1][y]) {
        points.push_back(Point(x - 1, y, maze[x - 1][y]));  // Ô trên
    }
    if (x < maze.size() - 1 && !visited[x + 1][y]) {
        points.push_back(Point(x + 1, y, maze[x + 1][y]));  // Ô dưới
    }
    if (y > 0 && !visited[x][y - 1]) {
        points.push_back(Point(x, y - 1, maze[x][y - 1]));  // Ô trái
    }
    if (y < maze[0].size() - 1 && !visited[x][y + 1]) {
        points.push_back(Point(x, y + 1, maze[x][y + 1]));  // Ô phải
    }

    // Kiểm tra xem còn đường nào để đi hay không
    if (points.empty()) {
        return;
    }

    // Sắp xếp danh sách các điểm theo giá trị giảm dần
    sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return p1.value > p2.value;
    });

    // Kiểm tra xem các điểm có giá trị lớn hơn hay không
    if (points[0].value <= score) {
        return;
    }

    // Thử đi vào các ô xung quanh theo thứ tự từ điểm có giá trị lớn nhất
    for (const auto& point : points) {
        findBestPath(maze, visited, point.x, point.y, point.value);
    }
}

// Hàm chính
int main() {
    // Mở hộp thoại chọn file
    ifstream inputFile;
    inputFile.open("input.txt");

    // Đọc kích thước mảng từ file
    int rows, cols;
    inputFile >> rows >> cols;

    // Tạo một mảng visited để theo dõi các ô đã đi qua
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Tạo một mảng maze để lưu giá trị của mê cung
    vector<vector<int>> maze(rows, vector<int>(cols));

    // Kiểm tra và lưu giá trị của mảng từ file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inputFile >> maze[i][j];
        }
    }

    // Kiểm tra giá trị trùng nhau trong mảng
    if (checkDuplicateValues(maze)) {
        cout << "Giá trị của mảng trùng nhau!" << endl;
        return 0;
    }

    // Vị trí ban đầu của robot
    int startX = 0;
    int startY = 0;

    // Gọi hàm đệ quy để tìm đường đi tốt nhất
    findBestPath(maze, visited, startX, startY, maze[startX][startY]);

    return 0;
}
