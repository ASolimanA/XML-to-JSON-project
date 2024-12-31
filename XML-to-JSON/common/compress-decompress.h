#ifndef COMPRESS_H_
#define COMPRESS_H_

#include <string>

void compress(const std::string& input, const std::string& compressoutFile);
std::string decompress(const std::string& CompressedfilePath);
std::string minify(const std::string& xml);

#endif // !COMPRESS_H_