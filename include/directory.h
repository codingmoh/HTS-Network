/*
 <one line to give the program's name and a brief idea of what it does.>
 Copyright (C) <year>  <name of author>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <string>
#include <vector>
#include <map>
#include "mail.h"
#include "listmessage.h"
#include "messageexception.h"

struct stat;
class Directory
{
   
public:
   bool fileexists(std::string);
   std::string pool_path_;
   Directory(std::string path);
   bool adduserdirectory(std::string);
   void savemessage(Mail&);
   Listmessage getmessages(Listmessage&);
   Mail getmessage(std::string, int);
   void removemessage(std::string, int);

private:
   bool exists(std::string);
   bool existspoolpathOtherwiseCreate();
   bool existsuserdir(std::string);
   bool existsuserdirOtherwiseCreate(std::string);
   bool existsmaildir(std::string, std::string);
   bool existsmaildirOtherwiseCreate(std::string, std::string);
   std::string getfreemessagenumber(std::string);
   bool create(std::string);
   int getdir(std::string, std::vector<int> &);
};

#endif // DIRECTORY_H
