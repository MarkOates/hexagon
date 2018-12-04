#pragma once



#include <string>
#include <vector>



class GitLinesModifiedExtractor
{
private:
   std::string filename;
   std::vector<int> lines_modified;
   bool executed;

public:
   GitLinesModifiedExtractor(std::string filename);
   ~GitLinesModifiedExtractor();

   void execute();
   std::vector<int> get_lines_modified();
};



