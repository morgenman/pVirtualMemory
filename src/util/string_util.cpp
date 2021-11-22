#include "string_util.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

namespace str_util {

string trim_left(const string& orig) {
  size_t nonWhiteSpace = orig.find_first_not_of(" \t\n\r");
  if (nonWhiteSpace == string::npos) return "";
  return orig.substr(nonWhiteSpace);
}

string trim_right(const string& orig) {
  size_t nonWhiteSpace = orig.find_last_not_of(" \t\n\r");
  if (nonWhiteSpace == string::npos) return "";
  return orig.substr(0, nonWhiteSpace + 1);
}

string string_globally_replace(const string& orig, const string& to_be_replaced,
                               const string& replacement) {
  string result = orig;
  auto pos = result.find(to_be_replaced);
  while (pos != string::npos) {
    result.replace(pos, to_be_replaced.length(), replacement);
    pos = pos + replacement.length();
    pos = result.find(to_be_replaced, pos);
  }

  return result;
}

string intern_escaped_string(const string& orig) {
  string result;
  // Non-standard for loop: < rather than !=; can increment twice (string ends
  // with \)
  for (size_t i = 0; i < orig.length(); ++i) {
    if (orig[i] == '\\') {
      i++;
      auto ch = (i < orig.length()) ? orig[i] : '\0';

      switch (ch) {
        case '0':
          result += '\0';
          break;
        case 'a':
          result += '\a';
          break;
        case 'b':
          result += '\b';
          break;
        case 'f':
          result += '\f';
          break;
        case 'n':
          result += '\n';
          break;
        case 'r':
          result += '\r';
          break;
        case 't':
          result += '\t';
          break;
        case 'v':
          result += '\v';
          break;
        case '\'':
          result += '\'';
          break;
        case '\"':
          result += '\"';
          break;
        default:
          if (i < orig.length()) result += ch;
      }
    } else
      result += orig[i];
  }
  return result;
}

bool is_hex_digit_string(string const& str) {
  return ((str.compare(0, 2, "0x") == 0) || (str.compare(0, 2, "0X") == 0)) &&
         (str.length() > 2) &&
         (str.find_first_not_of("0123456789abcdefABCDEF", 2) == string::npos);
}

string intern_hex_encoded_string(string const& hex_str) {
  string str;
  if (is_hex_digit_string(hex_str) && (hex_str.length() % 2 == 0)) {
    char hexData[3];
    hexData[2] = '\0';
    for (size_t i = 2; i < hex_str.length(); i += 2) {
      hexData[0] = hex_str[i];
      hexData[1] = hex_str[i + 1];
      str += static_cast<char>(strtol(hexData, 0, 16));
    }
  }
  return str;
}

istream& get_hex_string(istream& is, string& str) {
  string hex_str;
  if (is.bad()) cout << "already bad!!!" << endl;
  if ((is >> hex_str) && (hex_str.length() % 2 == 0) &&
      is_hex_digit_string(hex_str)) {
    str = hex_str;  // empty the string
  } else {
    cout << "hs " << hex_str << endl;
    // we do not know why things are bad but man are they bad. If stream is
    // okay and there is something in the string, put the string back on the
    // stream
    if (is.good()) {
      for (size_t i = 0; i < hex_str.length(); i++) is.unget();
      is.setstate(ios_base::failbit);
    }
  }
  return is;
}

istream& get_quoted_string(istream& is, string& str, char openQ, char closeQ,
                           char delim) {
  char ch;
  // get first non-whitespace character
  if ((is >> skipws >> ch) && (ch == openQ)) {
    // past the leading quote; read to the next one
    str.clear();  // empty the result string now
    while ((is >> noskipws >> ch) && (ch != closeQ) && (ch != delim)) {
      str += ch;
      if (ch == '\\') {  // handle escaped character
        if (is >> noskipws >> ch) {
          str += ch;
        } else {
          break;
        }
      }  // handle escape
    }
    if (ch != closeQ) {
      // no proper closing quote mark so set the logical fail
      // bit on the input stream unless there is already a set error
      if (is.good()) is.setstate(ios_base::failbit);
    }
  } else {
    // whitespace is gone; there was no openQ so unget ch and logical error
    // unless there is a previous IO error
    if (is.good()) {
      is.unget();
      is.setstate(ios_base::failbit);
    }
  }
  return is;
}
}  // namespace str_util
