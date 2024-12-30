#ifndef COMPRESS_H_
#define COMPRESS_H_

#include <string>

void compress(const std::string& input, const std::string& compressoutFile);
std::string decompress(const std::string& CompressedfilePath);

#endif // !COMPRESS_H_