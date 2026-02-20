#pragma once

#include <string>

struct cliInfo {
  cliInfo() = default;

public:
  const std::string getMenuTitle() const { return this->MENU_TITLE; }

  const std::string getPromptOption() const { return this->PROMPT_OPTION; }

  const std::string getPromptInputPath() const {
    return this->PROMPT_INPUT_PATH;
  }

  const std::string getMsgInvalidOption() const {
    return this->MSG_INVALID_OPTION;
  }

  const std::string getMsgGoodbye() const { return this->MSG_GOODBYE; }

  const std::string getEncodeSuffix() const { return this->ENCODE_SUFFIX; }

  const std::string getDecodeSuffix() const { return this->DECODE_SUFFIX; }

  const std::string getEncodeExtension() const {
    return this->ENCODE_EXTENSION;
  }

  const std::string getDecodeExtension() const {
    return this->DECODE_EXTENSION;
  }

private:
  const std::string MENU_TITLE = "Choose an action:";
  const std::string PROMPT_OPTION = "Enter option number: ";
  const std::string PROMPT_INPUT_PATH = "Enter input file path: ";

  const std::string MSG_INVALID_OPTION = "Invalid option. Try again.";
  const std::string MSG_GOODBYE = "Goodbye.";

  const std::string ENCODE_SUFFIX = "_encoded";
  const std::string DECODE_SUFFIX = "_decoded";

  const std::string ENCODE_EXTENSION = ".hec";
  const std::string DECODE_EXTENSION = ".txt";
};
