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

#include "directory.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
Directory::Directory(std::string path) {
	pool_path = path;
	existspoolpathOtherwiseCreate();
}

void Directory::savemessage(Mail& message){
	std::cout<<"oha"<<std::endl;
}

Directory * Directory::adduserdirectory(std::string user) {
	std::cout << user << std::endl;
	existspoolpathOtherwiseCreate();
	existsuserdirOtherwiseCreate(user);

}

bool Directory::existspoolpathOtherwiseCreate() {
	if (exists(pool_path) == 0) {
		std::cout << "dosomething" << std::endl;
		create( pool_path);
		return 0;
	} else {
		std::cout << "donothing" << std::endl;
		return 1;
	}
}
bool Directory::existsuserdirOtherwiseCreate(std::string user) {
	if (exists(pool_path + "/" + user) == 0) {
		std::cout << "dosomething2" << std::endl;
		create(pool_path + "/" + user);
		return 0;
	} else {
		std::cout << "donothing2" << std::endl;
		return 1;
	}
}

bool Directory::exists(std::string path) {
	char pa[100]; //path
	for (int i = 0; i <= path.size(); i++) {
		pa[i] = path[i];
	}

	DIR *pDir;
	bool bExists = false;

	pDir = opendir(pa);

	if (pDir != NULL) {
		bExists = true;
		(void) closedir(pDir);
	}

	return bExists;

}
void Directory::create(std::string path) {
	char pa[100]; //path
	for (int i = 0; i <= path.size(); i++) {
		pa[i] = path[i];
	}
	mkdir(pa, 0777);
}
