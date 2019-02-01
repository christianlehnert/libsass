#ifndef SASS_UTIL_H
#define SASS_UTIL_H

// sass.hpp must go before all system headers to get the
// __EXTENSIONS__ fix on Solaris.
#include "sass.hpp"

#include "sass/base.h"
#include "ast_fwd_decl.hpp"

#include <cstring>
#include <vector>
#include <string>
#include <assert.h>
#include <math.h>

#define SASS_ASSERT(cond, msg) assert(cond && msg)

namespace Sass {

  template <typename T>
  T clip(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
  }

  template <typename T>
  T absmod(const T& n, const T& r) {
    T m = std::fmod(n, r);
    if (m < 0.0) m += r;
    return m;
  }

  double round(double val, size_t precision = 0);
  double sass_strtod(const char* str);
  const char* safe_str(const char *, const char* = "");
  void free_string_array(char **);
  char **copy_strings(const std::vector<std::string>&, char ***, int = 0);
  std::string read_css_string(const std::string& str, bool css = true);
  std::string evacuate_escapes(const std::string& str);
  std::string string_to_output(const std::string& str);
  std::string comment_to_string(const std::string& text);
  std::string read_hex_escapes(const std::string& str);
  std::string escape_string(const std::string& str);
  void newline_to_space(std::string& str);

  std::string quote(const std::string&, char q = 0);
  std::string unquote(const std::string&, char* q = 0, bool keep_utf8_sequences = false, bool strict = true);
  char detect_best_quotemark(const char* s, char qm = '"');

  bool is_hex_doublet(double n);
  bool is_color_doublet(double r, double g, double b);

  bool peek_linefeed(const char* start);

  // Returns true iff `elements` ⊆ `container`.
  template <typename C, typename T>
  bool contains_all(C container, T elements) {
    for (const auto &el : elements) {
      if (container.find(el) == container.end()) return false;
    }
    return true;
  }

  // C++20 `starts_with` equivalent.
  // See https://en.cppreference.com/w/cpp/string/basic_string/starts_with
  inline bool starts_with(const std::string& str, const char* prefix, size_t prefix_len) {
    return str.compare(0, prefix_len, prefix) == 0;
  }

  inline bool starts_with(const std::string& str, const char* prefix) {
    return starts_with(str, prefix, std::strlen(prefix));
  }

  // C++20 `ends_with` equivalent.
  // See https://en.cppreference.com/w/cpp/string/basic_string/ends_with
  inline bool ends_with(const std::string& str, const std::string& suffix) {
    return suffix.size() <= str.size() && std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
  }

  inline bool ends_with(const std::string& str, const char* suffix, size_t suffix_len) {
    if (suffix_len > str.size()) return false;
    const char* suffix_it = suffix + suffix_len;
    const char* str_it = str.c_str() + str.size();
    while (suffix_it != suffix) if (*(--suffix_it) != *(--str_it)) return false;
    return true;
  }

  inline bool ends_with(const std::string& str, const char* suffix) {
    return ends_with(str, suffix, std::strlen(suffix));
  }

  namespace Util {

    std::string rtrim(const std::string& str);

    std::string normalize_underscores(const std::string& str);
    std::string normalize_decimals(const std::string& str);

    bool isPrintable(Ruleset_Ptr r, Sass_Output_Style style = NESTED);
    bool isPrintable(Supports_Block_Ptr r, Sass_Output_Style style = NESTED);
    bool isPrintable(Media_Block_Ptr r, Sass_Output_Style style = NESTED);
    bool isPrintable(Comment_Ptr b, Sass_Output_Style style = NESTED);
    bool isPrintable(Block_Obj b, Sass_Output_Style style = NESTED);
    bool isPrintable(String_Constant_Ptr s, Sass_Output_Style style = NESTED);
    bool isPrintable(String_Quoted_Ptr s, Sass_Output_Style style = NESTED);
    bool isPrintable(Declaration_Ptr d, Sass_Output_Style style = NESTED);
    bool isAscii(const char chr);

  }
}
#endif
