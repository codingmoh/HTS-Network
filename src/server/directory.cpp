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
#include <sstream>
#include <iostream>
#include <fstream>
Directory::Directory(std::string path) {
	pool_path = path;
	existspoolpathOtherwiseCreate();
}

void Directory::savemessage(Mail& msg) {
	std::cout << "savemessage" << std::endl;

	adduserdirectory(msg._receiver);

	std::string messagenumber = getfreemessagenumber(msg._receiver);
	std::cout << messagenumber << std::endl;
	existsmaildirOtherwiseCreate(msg._receiver, messagenumber);

	std::string file = pool_path + "/" + msg._receiver + "/" + messagenumber
			+ "/message.txt";

	std::ofstream myfile(file.c_str());
	boost::archive::text_oarchive oa(myfile);
	oa << msg;
	myfile.close();

	/**std::ifstream myfile2(file.c_str());
	Mail  msg2;
	boost::archive::text_iarchive ia(myfile2);
	ia >> msg2;
	std::cout<<msg2._sender<<std::endl;
	myfile2.close();**/
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
bool Directory::existsmaildirOtherwiseCreate(std::string receiver,
		std::string messagenumber) {
	if (exists(pool_path + "/" + receiver + "/" + messagenumber) == 0) {
		std::cout << "dosomething3" << std::endl;
		create(pool_path + "/" + receiver + "/" + messagenumber);
		return 0;
	} else {
		std::cout << "donothing3" << std::endl;
		return 1;
	}
}

std::string Directory::getfreemessagenumber(std::string receiver) {
	int i = 0;
	while (true) {
		std::ostringstream sin;
		sin << i;
		std::string val = sin.str();
		if (exists(pool_path + "/" + receiver + "/" + val) == 0) {
			return val;
		}
		i++;
	}
}

bool Directory::exists(std::string path) {
	DIR *pDir;
	bool bExists = false;

	pDir = opendir(path.c_str());

	if (pDir != NULL) {
		bExists = true;
		(void) closedir(pDir);
	}

	return bExists;

}
void Directory::create(std::string path) {

	mkdir(path.c_str(), 0777);
}
