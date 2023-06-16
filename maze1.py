import sys
from tkinter import Tk, filedialog

# Hàm kiểm tra giá trị trùng nhau trong mảng 2 chiều
def check_duplicate_values(maze):
    values = set()
    for row in maze:
        for value in row:
            if value in values:
                return True
            values.add(value)
    return False

# Định nghĩa cấu trúc điểm
class Point:
    def __init__(self, x, y, value):
        self.x = x
        self.y = y
        self.value = value

# Hàm đệ quy để tìm đường đi tốt nhất cho robot
def find_best_path(maze, visited, x, y, score):
    # Kiểm tra xem robot đã đi ra khỏi mê cung hay chưa
    if x < 0 or x >= len(maze) or y < 0 or y >= len(maze[0]):
        return

    # Kiểm tra xem ô hiện tại đã được đi qua hay chưa
    if visited[x][y]:
        return

    # Đánh dấu ô hiện tại đã được đi qua
    visited[x][y] = True

    # In giá trị của ô hiện tại
    print("Ô ({}, {}) - Giá trị: {}".format(x, y, score))

    # Tạo một danh sách các điểm xung quanh ô hiện tại
    points = []
    if x > 0 and not visited[x - 1][y]:
        points.append(Point(x - 1, y, maze[x - 1][y]))  # Ô trên
    if x < len(maze) - 1 and not visited[x + 1][y]:
        points.append(Point(x + 1, y, maze[x + 1][y]))  # Ô dưới
    if y > 0 and not visited[x][y - 1]:
        points.append(Point(x, y - 1, maze[x][y - 1]))  # Ô trái
    if y < len(maze[0]) - 1 and not visited[x][y + 1]:
        points.append(Point(x, y + 1, maze[x][y + 1]))  # Ô phải

    # Kiểm tra xem còn đường nào để đi hay không
    if len(points) == 0:
        return

    # Sắp xếp danh sách các điểm theo giá trị giảm dần
    points.sort(key=lambda p: p.value, reverse=True)

    # Kiểm tra xem các điểm có giá trị lớn hơn hay không
    if points[0].value <= score:
        return

    # Thử đi vào các ô xung quanh theo thứ tự từ điểm có giá trị lớn nhất
    for point in points:
        find_best_path(maze, visited, point.x, point.y, point.value)

# Hàm chính
def main():
    # Mở hộp thoại chọn file
    root = Tk()
    root.withdraw()
    file_path = filedialog.askopenfilename()

    # Đọc mảng từ file
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
    except IOError:
        print("Không thể đọc file!")
        return

    # Lấy kích thước mảng từ dòng đầu tiên
    size = lines[0].split()
    rows = int(size[0])
    cols = int(size[1])

    # Kiểm tra kích thước mảng
    if len(lines) - 1 != rows:
        print("Kích thước mảng không phù hợp!")
        return

    # Tạo một mảng visited để theo dõi các ô đã đi qua
    visited = [[False] * cols for _ in range(rows)]

    # Tạo một mảng maze để lưu giá trị của mê cung
    maze = []

    # Kiểm tra và lưu giá trị của mảng từ dòng thứ hai trở đi
    for line in lines[1:]:
        values = line.split()
        if len(values) != cols:
            print("Kích thước mảng không phù hợp!")
            return
        row = []
        for value in values:
            num = int(value)
            row.append(num)
        maze.append(row)

    # Kiểm tra giá trị trùng nhau trong mảng
    if check_duplicate_values(maze):
        print("Giá trị của mảng trùng nhau!")
        return

    # Vị trí ban đầu của robot
    start_x = 0
    start_y = 0

    # Gọi hàm đệ quy để tìm đường đi tốt nhất
    find_best_path(maze, visited, start_x, start_y, maze[start_x][start_y])

if __name__ == "__main__":
    main()
