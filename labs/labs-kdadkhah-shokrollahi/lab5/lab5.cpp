#include <stack>
#include <string>

using namespace std;

bool bracketCheck(const std::string& s){
  stack<char> st;
  for (size_t i = 0; i < s.length(); i++) {
    if (st.empty()) {
      st.push('\0');
    }
    if (s[i] == '[' || s[i] == '(' || s[i] == '{') {
      st.push(s[i]);
    }
    switch (s[i]) {
      case ']':
        if (!st.empty() && (st.top() == '(' || st.top() == '{') || st.top() == '\0') {
          return false;
        }
        st.pop();
        break;
      case ')':
        if (!st.empty() && (st.top() == '[' || st.top() == '{') || st.top() == '\0') {
          return false;
        }
        st.pop();
        break;
      case '}':
        if (!st.empty() && (st.top() == '(' || st.top() == '[') || st.top() == '\0') {
          return false;
        }
        st.pop();
        break;
    }
  }

  return st.size() == 1;
}

