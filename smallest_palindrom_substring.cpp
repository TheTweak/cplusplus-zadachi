#include <iostream>
#include <string_view>
#include <string>

using namespace std;

bool is_palindrom(string_view& sv) {
  for (int i = 0; i < sv.size() / 2; i++) {
    if (sv.at(static_cast<size_t>(i)) != sv.at(sv.size() - 1 - static_cast<size_t>(i))) {
      return false;
    }
  }
  return true;
}

string_view find_palindrom(string_view& sv) {
  string_view result;
  for (size_t size = 1; size < 4; size++) {
    for (size_t i = 0; i + size < sv.size(); i++) {
      string_view sub_str = sv.substr(i, size + 1);
      if ((result.empty() || sub_str < result) &&
          is_palindrom(sub_str)) {
        result = sub_str;
      }
    }
    if (!result.empty()) {
      break;
    }
  }
  if (result.empty()) {
    result = "-1";
  }
  return result;
}

int main() {
  string in;
  cin >> in;
  string_view sv = in;
  cout << find_palindrom(sv) << '\n';
}

