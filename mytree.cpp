#include "tree.hpp"

int target_depth;
const int max_depth = 10;

bool is_hidden_entry(dirent *entry) {
  return entry->d_name[0] == '.';
}

void print_vertical_bar(std::vector<bool> need_bits, int depth) {
  for (int i = 0; i < depth; i++) {
    printf("%s  ", need_bits[i] ? vertical_bar : " ");
  }
}

int get_dir_entries(std::string path, std::vector<File>& entries) {
  DIR *dir = opendir(path.c_str());
  dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    // 特殊ファイルは含まない
    if (!is_hidden_entry(entry)) 
      entries.push_back(File(entry));
  }

  closedir(dir);
  return entries.size();
}

void print_dir_entries(std::string path, int depth, std::vector<bool> need_vbar_bits) {
  std::vector<File> entries;
  
  int num_entries = get_dir_entries(path, entries);

  for (File& file: entries) {
    num_entries--;

    // 縦棒の表示
    print_vertical_bar(need_vbar_bits, depth);

    printf("%s", num_entries == 0 ? half_branch : branch);
    printf("%s ", horizontal_bar);
    file.printName();
    printf("\n");

    if (!file.isDirectory()) continue;

    std::vector<bool> new_bits = need_vbar_bits;
    new_bits.push_back(num_entries != 0);

    // 指定した深さ以下なら以降の中身を表示
    if (depth + 1 <= target_depth) {
      print_dir_entries(path + "/" + file.getName(), depth + 1, new_bits);
    }
  }
}

int main(int argc, char *argv[]) {
  std::string dir_path;
  DIR *dir;

  if (argc < 2) {
    dir_path = ".";
  }
  else {
    dir_path = std::string(argv[1]);
    int len = dir_path.size();
    // 末尾に/があれば消去
    if (dir_path[dir_path.size() - 1] == '/') {
      dir_path.erase(len - 1);
    }
  }

  if (argc == 3) {
    target_depth = atoi(argv[2]);
  }
  else {
    target_depth = max_depth;
  }

  std::vector<bool> need_vbar_bits;
  printf("\x1b[34m%s\x1b[39m\n", dir_path.c_str());
  print_dir_entries(dir_path, 0, need_vbar_bits);

  return 0;
}