#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

void get_md5_hash(const std::string str, std::string &result);

void parse_html_uri(const std::string& s, std::vector<std::string>& parsed);

std::string get_date_and_time();

bool is_number(const std::string& s);

#endif // UTIL_H
