

#ifndef FILE_H
#define FILE_H
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <fstream>
#include <iostream>

class File
{
  friend class boost::serialization::access;   
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    if(exists_)
    {
      
      std::ifstream ifs(filename_.c_str());
      std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
      rawstr_ = str;
      
      ar & rawstr_;
      
    }
  }
  
private:
  std::string filename_;
  bool exists_;
  std::string rawstr_;
public:
  File(std::string);
  bool exists()
  {
    return exists_;
  };
  File();
  
};

#endif