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
#include <string>
#include <vector>
#include <map>
#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "mail.h"

class Directory {
public:
<<<<<<< HEAD
  std::string pool_path;
  Directory(std::string path);
  Directory * adduserdirectory(std::string);
  void savemessage(Mail&);
<<<<<<< HEAD
  Mail*_getmessages();
=======
  Message** getmessages();

private:
  bool exists(std::string);
  bool existspoolpathOtherwiseCreate();
  bool existsuserdirOtherwiseCreate(std::string);
  void create(std::string);
>>>>>>> 1818878006b0a2a668f9baab888de7c475dc168d
=======
	std::string pool_path;
	Directory(std::string path);
	Directory * adduserdirectory(std::string);
	void savemessage(Mail&);
	Message** getmessages(std::string);
	Message* getmessage(std::string, int);

private:
	bool exists(std::string);
	bool existspoolpathOtherwiseCreate();
	bool existsuserdirOtherwiseCreate(std::string);
	bool existsmaildirOtherwiseCreate(std::string, std::string);
	std::string getfreemessagenumber(std::string);
<<<<<<< HEAD
<<<<<<< HEAD
	bool create(std::string);
>>>>>>> c17abc9de4c00f9423d6a809e1539161ba6353f7
=======
	void create(std::string);
>>>>>>> parent of c17abc9... m
=======
	void create(std::string);
>>>>>>> parent of c17abc9... m
};

#endif // DIRECTORY_H
