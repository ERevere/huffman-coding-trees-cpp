# Huffman Coding Trees (C++)

Huffman coding is a form of lossless compression which makes files smaller using the frequency with which characters appear in a message.

[![Desc](https://img.youtube.com/vi/JsTptu56GM8/maxresdefault.jpg)](https://youtu.be/JsTptu56GM8)

### [Watch this great description on YouTube](https://youtu.be/JsTptu56GM8)

## Usage

Create / Copy the .txt file to encode to root directory.

Then from root pwd
```bash
g++ -std=c++20 -O2 -Wall -Wextra \
  src/main.cpp src/encoder.cpp src/decoder.cpp \
  src/huffman_tree.cpp src/bit_io.cpp src/format.cpp \
  -I. -Iinclude -o huffman && ./huffman
```

## Contributing

Pull requests are welcome. For major changes, feel free to open an issue.