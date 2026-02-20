#pragma once

#include <string>
#include <vector>

struct appInfo {
  appInfo() = default;

public:
  const std::string getName() { return this->PROGRAM_NAME; }
  const std::string getVers() { return this->VERSION; }
  const std::vector<std::pair<int, std::string>> getOpts() {
    return this->OPTIONS;
  }

private:
  const std::string PROGRAM_NAME = "Huffman Coding File Encoder/Decoder";
  const std::string VERSION = "v0.0.7";
  const std::vector<std::pair<int, std::string>> OPTIONS = {
      {1, "Encode Files"},
      {2, "Decode files"},
      {3, "Quit"},
  };
};
