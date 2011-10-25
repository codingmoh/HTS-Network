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

#ifndef LDAPLOGIN_H
#define LDAPLOGIN_H
#include "messageexception.h"
#include <ldap.h>
#include <lber.h>

class Ldaplogin
{

public:
   Ldaplogin(std::string ldap_host, int port, std::string searchbase);
   
   bool loginuser(std::string, std::string);

private:
  LDAP *ld; /* LDAP resource handle */
  bool checkuser(std::string);
  std::string ldap_host;
  int ldap_port;
  std::string searchbase;

};

#endif // DIRECTORY_H
