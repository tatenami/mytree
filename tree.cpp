#include "tree.hpp"

const char vertical_bar[] = "\u2502";  
const char horizontal_bar[] = "\u2500"; 
const char branch[] = "\u251c";         
const char half_branch[] = "\u2514";    

File::File(dirent *entry) {
  this->name_ = entry->d_name;
  this->type_ = entry->d_type;
}

void File::printName() {
  if (this->isDirectory()) {
    // 青色で表示
    printf("\x1b[34m%s\x1b[39m", name_.c_str());
  }
  else {
    printf("%s", this->name_.c_str());
  }
}

bool File::isDirectory() {
  return this->type_ == DT_DIR;
}

std::string File::getName() {
  return this->name_;
}