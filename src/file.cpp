#include "file.h"

#include <sstream>
File::File(std::string filename):filename_(filename)
{
  std::ifstream ifile(filename_.c_str());
  exists_ = this->exists();
}
File::File()
{
  
}
void File::saveto(std::string to)
{
  
  std::cout << "hier "<< filename_<<std::endl;
  std::string datei = to + filename_;
  
  int i=1;
  while(fileexists(datei)==true){
    std::ostringstream tmp;
    tmp << i;
   std::string val = tmp.str();
    
    datei=to+val+"_"+filename_;
  }
  
  std::cout << datei <<std::endl;
  std::ofstream myfile(datei.c_str());
  
  std::cout << "open"<<std::endl;
  myfile << rawstr_;
  
  std::cout << "write"<<std::endl;
  myfile.close();
  
  
}

bool File::fileexists(std::string path)
{
   bool flag = false;
   std::fstream fin;
   fin.open(path.c_str());

   if (fin.is_open())
   {
      flag = true;
   }

   fin.close();

   return flag;
}
