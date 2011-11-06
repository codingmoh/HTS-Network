#include "file.h"

File::File(std::string filename):filename_(filename)
{
  std::ifstream ifile(filename_.c_str());
  exists_ = ifile;
}
File::File()
{
  
}


  