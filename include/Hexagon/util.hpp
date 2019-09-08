#pragma once

#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t
#include <vector>

std::string::size_type rfind_first_not_of(const std::string& s, const std::string& delims, std::string::size_type pos);

std::string::size_type rfind_first_of(const std::string& s, const std::string& delims, std::string::size_type pos);

int find_whitespace(std::string &string, int current_cursor_position);

int find_non_whitespace(std::string &string, int current_cursor_position);

int rfind_whitespace(std::string &string, int current_cursor_position);

int rfind_non_whitespace(std::string &string, int current_cursor_position);

bool read_file(std::vector<std::string> &lines, std::string filename);

bool save_file(std::vector<std::string> &lines, std::string filename);

std::string resource_path(std::vector<std::string> components, std::string filename="");

