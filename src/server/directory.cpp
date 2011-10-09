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
#include <boost/lexical_cast.hpp>

Directory::Directory(std::string path)
{
	pool_path = path;
	existspoolpathOtherwiseCreate();
}

bool Directory::savemessage(Mail& msg)
{
	if (adduserdirectory(msg._receiver) == 1)
	{

		std::string messagenumber = getfreemessagenumber(msg._receiver);
		if (existsmaildirOtherwiseCreate(msg._receiver, messagenumber))
		{

			std::string file = pool_path + "/" + msg._receiver + "/"
					+ messagenumber + "/message.txt";

			std::ofstream myfile(file.c_str());
			boost::archive::text_oarchive oa(myfile);
			oa << msg;
			myfile.close();

			return 1;
		}
		else
		{
			return 0; //fehler beim erstellen des usermailordners
		}
	}
	else
	{
		return 0; //fehler beim erstellen des userordners
	}

	/**std::ifstream myfile2(file.c_str());
	 Mail  msg2;
	 boost::archive::text_iarchive ia(myfile2);
	 ia >> msg2;
	 std::cout<<"-------------"<<msg2._msg<<std::endl;
	 myfile2.close();**/
}
bool Directory::removemessage(std::string from, int number)
{
	if (from.size() < 1 || from.size() > 8 || number < 0)
	{
		return 0; //parameterfehler
	}
	std::ostringstream tmp;
	tmp << number;
	std::string messagenumber = tmp.str();
	if (existsuserdir(from) == 1)
	{
		if (existsmaildir(from, messagenumber) == 1)
		{

			std::string file = pool_path + "/" + from + "/" + messagenumber;
			std::string command = "rm -r " + file;
			if (system(command.c_str()) == 0)
			{
				std::cout << "remove messagenumber <" << number << "> from <"
						<< from << "> (" << file << ")" << std::endl;
				return 1;
			}
			else
			{
				return 0; //fehler beim loeschen
			}

		}
		else
		{
			return 0; //mail existiert nicht
		}
	}
	else
	{
		return 0; //user existiert nicht
	}
}
Mail* Directory::getmessage(std::string from, int number)
{
	/**std::ostringstream tmp;
	 tmp << number;
	 std::string messagenumber = tmp.str();**/

	//std::string messagenumber = std::string(buffer);

	std::string messagenumber = boost::lexical_cast<std::string>(number);

	if (existsuserdir(from) == 1)
	{

		if (existsmaildir(from, messagenumber) == 1)
		{

			std::string file = pool_path + "/" + from + "/" + messagenumber
					+ "/message.txt";
			if (fileexists(file) == 1)
			{

				std::ifstream myfile(file.c_str());
				Mail* msg = new Mail();
				boost::archive::text_iarchive ia(myfile);
				ia >> *msg;
				myfile.close();
				return msg;
			}
			else
			{
				//message nicht vorhanden
			}
		}
		else
		{
			// mailordner existiert nicht
		}
	}
	else
	{
		// user existiert nicht
	}
}

Mail** Directory::getmessages(std::string from)
{

	if (existsuserdir(from) == 1)
	{
		std::vector<int> files = std::vector<int>();
		std::string userpath = pool_path + "/" + from;
		getdir(userpath, files);
		sort(files.begin(), files.end());

		Mail ** msgs = new Mail*[files.size()];

		for (unsigned int i = 0; i < files.size(); i++)
		{

			msgs[i] = getmessage(from, files[i]);
			msgs[i]->_number = files[i];
		}
		return msgs;
	}
	else
	{
		// user existiert nicht
	}
}

bool Directory::adduserdirectory(std::string user)
{
	if (existspoolpathOtherwiseCreate() == 1)
	{
		if (existsuserdirOtherwiseCreate(user) == 1)
		{
			return 1;
		}
		else
		{
			return 0; //fehler beim erstellen des userverzeichnisses
		}
	}
	else
	{
		return 0; // fehler beim erstellen des poolverzeichnisses
	}
}

bool Directory::existspoolpathOtherwiseCreate()
{
	if (exists(pool_path) == 0)
	{
		return create(pool_path);
	}
	else
	{
		return 1; //poolpath vorhanden
	}
}
bool Directory::existsuserdirOtherwiseCreate(std::string user)
{
	if (existsuserdir(user) == 0)
	{
		return create(pool_path + "/" + user);
	}
	else
	{
		return 1; //userpath vorhanden
	}
}
bool Directory::existsmaildirOtherwiseCreate(std::string receiver,
		std::string messagenumber)
{
	if (existsmaildir(receiver, messagenumber) == 0)
	{
		return create(pool_path + "/" + receiver + "/" + messagenumber);
	}
	else
	{
		return 1; //usermailpath vorhanden
	}
}
bool Directory::existsuserdir(std::string user)
{
	if (exists(pool_path + "/" + user) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
bool Directory::existsmaildir(std::string receiver, std::string messagenumber)
{
	if (exists(pool_path + "/" + receiver + "/" + messagenumber) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
std::string Directory::getfreemessagenumber(std::string receiver)
{
	int i = 0;
	while (true)
	{
		std::ostringstream tmp;
		tmp << i;
		std::string val = tmp.str();
		if (exists(pool_path + "/" + receiver + "/" + val) == 0)
		{
			return val;
		}
		i++;
	}
}

bool Directory::exists(std::string path)
{
	DIR *pDir;
	bool bExists = false;

	pDir = opendir(path.c_str());

	if (pDir != NULL)
	{
		bExists = true;
		(void) closedir(pDir);
	}

	return bExists;

}
bool Directory::fileexists(std::string path)
{
	bool flag = false;
	std::fstream fin;
	fin.open(path.c_str());
	if (fin.is_open())
	{
		std::cout << "file exists" << std::endl;
		flag = true;
	}
	fin.close();
	return flag;
}
bool Directory::create(std::string path)
{
	if (mkdir(path.c_str(), 0777) != 0)
	{
		return 0;
	}
	else
	{
		std::cout << "mkdir <" << path << ">" << std::endl;
		return 1; //alles ok beim erstellen des ordners}
	}
}
int Directory::getdir(std::string dir, std::vector<int> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL)
	{
		std::cout << "Error(" << errno << ") opening " << dir << std::endl;
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		if (std::string(dirp->d_name) != ".")
		{
			if (std::string(dirp->d_name) != "..")
			{
				files.push_back(atoi(dirp->d_name));
			}
		}
	}
	closedir(dp);
	return 0;
}
