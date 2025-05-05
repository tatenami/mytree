#ifndef TREE_H
#define TREE_H

#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>

#include <sys/types.h>
#include <dirent.h>

extern const char vertical_bar[];   // 縦棒
extern const char horizontal_bar[]; // 横棒
extern const char branch[];         // 枝分かれ棒
extern const char half_branch[];    // 半枝分かれ棒

class File {
 protected:
  std::string name_;
  int type_;

 public:
  File(dirent *entry);
  void printName();
  bool isDirectory();
  std::string getName();
};

#endif // TREE_H