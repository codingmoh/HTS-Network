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
   Ldaplogin(std::string ost, std::string user, std::string password, int version, std::string base);
   
   bool loginuser(std::string, std::string);

private:
  LDAP *ld; /* LDAP resource handle */
  bool checkuser(std::string);
  void ldapBind(std::string, std::string);
  void ldapUnbind();
  
  std::string ldap_host;
  std::string ldap_user;
  std::string ldap_password;
  std::string searchbase;
  int ldap_version;

};

#endif // DIRECTORY_H
