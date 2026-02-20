#include <filesystem>
#include <iostream>
#include <limits>
#include <string>

#include "../include/huffman/app-info.h"
#include "../include/huffman/cli.h"
#include "../include/huffman/decoder.h"
#include "../include/huffman/encoded_data.h"
#include "../include/huffman/encoder.h"

int main() {
  auto info = std::make_unique<appInfo>();
  auto cli = std::make_unique<cliInfo>();

  while (true) {
    std::cout << info->getName() << " ( " << info->getVers() << " )\n";
    std::cout << cli->getMenuTitle() << '\n';

    for (const auto &opt : info->getOpts()) {
      std::cout << " " << opt.first << ") " << opt.second << '\n';
    }

    std::cout << cli->getPromptOption();
    char entry = 0;
    if (!(std::cin >> entry))
      return 1;
    uint8_t ch = (entry - '0');

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (ch == 3) {
      std::cout << cli->getMsgGoodbye() << '\n';
      return 0;
    }

    if (ch != 1 && ch != 2) {
      std::cout << cli->getMsgInvalidOption() << "\n\n";
      continue;
    }

    std::cout << cli->getPromptInputPath();
    std::string inPath;
    std::getline(std::cin, inPath);

    if (inPath.empty()) {
      std::cout << "Empty Path entered, try again. \n\n";
      continue;
    }

    const std::filesystem::path inP(inPath);
    const std::string base = inP.stem().string();
    const std::string outName =
        base + (ch == 1 ? cli->getEncodeSuffix() : cli->getDecodeSuffix()) +
        (ch == 1 ? cli->getEncodeExtension() : cli->getDecodeExtension());
    const std::string outPath = (inP.parent_path() / outName).string();

    try {
      if (ch == 1) {
        auto enc = std::make_unique<hec::hecEncoder>("");
        enc->encodeFile(inPath, outPath);
        std::cout << "Wrote encoded file: " << outPath << "\n\n";
      } else {
        auto dec = std::make_unique<hec::hecDecoder>(hec::EncodedData{});
        dec->decodeFile(inPath, outPath);
        std::cout << "Wrote decoded file: " << outPath << "\n\n";
      }
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << "\n\n";
    }
  }
}