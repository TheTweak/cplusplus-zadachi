#include <iostream>
#include <utility>
#include <map>
#include <optional>

/*
 Find if all given figures (circles or rectangles) can be split equally by a single line.
 
 Solution: check if centers of all figures are collinear.
 
 input:
 
 N - number of figures
 
 then:
 T R X Y - where T=0 (circle) R=radius X, Y - coordinates of circle center
 T X1 Y1 X2 Y2 X3 Y3 X4 Y4 - where T=1 (rectangle) and then 4 vertices of rectangle in clockwise or counter-clockwise order
 
 output:
 
 Yes - if such line exists
 No - otherwise
 */

using namespace std;

using Point = pair<double, double>;

struct ComparePoints {
  Point origin;
  
  bool operator()(const Point& lhs, const Point& rhs) const {
    return (lhs.first - origin.first) * (rhs.second - origin.second) -
      (rhs.first - origin.first) * (lhs.second - origin.second) < 0;
  }
};

int main() {
  
  int n;
  cin >> n;
  if (n <= 2) {
    cout << "Yes\n";
    return 0;
  }
  
  optional<map<Point, int, ComparePoints>> counter;
  optional<Point> origin;
  for (int i = 0; i < n; i++) {
    int type;
    cin >> type;
    
    optional<Point> center;
    if (type == 0) {
      // circle
      double r, x, y;
      cin >> r >> x >> y;
      center = {x, y};
    } else if (type == 1) {
      // rectangle
      double x1, y1, x2, y2, x3, y3, x4, y4;
      cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
      center = {(x1 + x3) / 2.0, (y1 + y3) / 2.0};
    }
    
    if (!counter) {
      ComparePoints cp = {center.value()};
      counter = map<Point, int, ComparePoints>(cp);
      origin = center;
      continue;
    }
    
    if (center->first == origin->first &&
        center->second == origin->second) {
      continue;
    }
    
    counter.value()[center.value()]++;
    if (counter.value().size() > 1) {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
  return 0;
}

