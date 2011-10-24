

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

#include "ldaplogin.h"
#include <ldap.h>
#include <lber.h>

Ldaplogin::Ldaplogin(std::string host, int port, std::string base)
{
  ldap_host = host;
  ldap_port = port;
  searchbase = base;
}

bool
Ldaplogin::checkuser(std::string user)
{
  // ueberpruefen ob user gebannt ist
}
bool
Ldaplogin::loginuser(std::string user, std::string password)
{
  std::cout << "checkuser " << user <<":"<<password << std::endl;
  
//   LDAP *ld; /* LDAP resource handle */
//   LDAPMessage *result, *e; /* LDAP result handle */
//   BerElement *ber; /* array of attributes */
//   char *attribute;
//   char **vals;
//   struct berval cred;
//   cred.bv_val = NULL; // my password
//   cred.bv_len = 0;
// 
//   ldap_initialize(&ld, "ldap://ldap.technikum-wien.at");
//   if (ld == NULL) /*LDAP-Initialisierung*/
//     {
//       std::cout<<"ldap_init failed"<<std::endl;
//     }
//   int rc = ldap_sasl_bind_s(ld, searchbase.c_str(), LDAP_SASL_SIMPLE, &cred, NULL, NULL, NULL);
//   
//   if(rc!= LDAP_SUCCESS){
//       std::cout << "LDAP error:" << ldap_err2string(rc)<<std::endl;
//   }else{
//     std::cout <<"passt alles"<<std::endl;
//   }
  return false;
}
