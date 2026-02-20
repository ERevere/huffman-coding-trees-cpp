# Huffman Coding Trees (C++)

Huffman coding is a form of lossless compression which makes files smaller using the frequency with which characters appear in a message.

<iframe width="560" height="315" src="https://www.youtube.com/embed/JsTptu56GM8?si=e_WQxR_ScJrE0ip2" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

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