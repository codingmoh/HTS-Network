

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

Ldaplogin::Ldaplogin(std::string host, std::string user, std::string password, int version, std::string base)
{
   ldap_host = host;
   ldap_user = user;
   ldap_password = password;
   searchbase = base;
   ldap_version = version;


}


bool Ldaplogin::checkuser(std::string user)
{
   // ueberpruefen ob user gebannt ist
}

bool Ldaplogin::loginuser(std::string user, std::string password)
{
   this->ldapBind(ldap_user, ldap_password);

   std::cout << "checkuser " << user << ":" << password << std::endl;

   std::string filter = "(uid=" + user + ")";

   struct berval cred;
   cred.bv_val = const_cast<char*>(password.c_str()); // my password
   cred.bv_len = strlen(cred.bv_val) * sizeof(char);

   struct berval *servercredp;

   LDAPMessage *result, *e; /* LDAP result handle */
   char *dn;
   int count_entries;
   int rc;


   char *attribs[2];
   attribs[0] = strdup("uid");
   attribs[1] = NULL;

   rc = ldap_search_ext_s(ld, this->searchbase.c_str(), LDAP_SCOPE_SUBTREE, filter.c_str(), attribs, 0, NULL, NULL, NULL, 0, &result);
   delete attribs[0];
   delete attribs[1];

   if (rc != LDAP_SUCCESS)
   {
      std::cout << "LDAP search error:" << ldap_err2string(rc) << std::endl;
      ldap_msgfree(result);
      this->ldapUnbind();
      return false;
   }

   count_entries = ldap_count_entries(ld, result);

   if (count_entries != 1)
   {
      std::cout << "user nicht vorhanden" << std::endl;
      ldap_msgfree(result);
      this->ldapUnbind();
      return false;
   }

   e = ldap_first_entry(ld, result);

   dn = ldap_get_dn(ld, e);
   std::cout << dn << std::endl;

   ldap_msgfree(result);

   rc = ldap_sasl_bind_s(ld, dn, LDAP_SASL_SIMPLE, &cred, NULL, NULL, &servercredp);
   this->ldapUnbind();

   if (rc != LDAP_SUCCESS)
   {
      std::cout << "Password not correct:" << ldap_err2string(rc) << std::endl;
      return false;
   }

   else
   {
      std::cout << "Login erfolgreich" << std::endl;
      return true;
   }
}

void Ldaplogin::ldapBind(std::string user, std::string password)
{
   ldap_initialize(&ld, this->ldap_host.c_str());

   if (ld == NULL) /*LDAP-Initialisierung*/
   {
      std::cout << "ldap_init failed" << std::endl;
      exit(1);
   }

   struct berval *servercredp;

   struct berval cred;

   cred.bv_val = const_cast<char*>(password.c_str()); // my password

   cred.bv_len = strlen(cred.bv_val) * sizeof(char);


   ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &ldap_version);

   int rc = ldap_sasl_bind_s(ld, user.c_str(), LDAP_SASL_SIMPLE, &cred, NULL, NULL, &servercredp);

   if (rc != LDAP_SUCCESS)
   {
      std::cout << "LDAP error:" << ldap_err2string(rc) << std::endl;
      exit(1);
   }

   else
   {
      std::cout << "LDAP connected" << std::endl;
   }
}

void Ldaplogin::ldapUnbind()
{
   // ueberpruefen ob user gebannt ist
   ldap_unbind_ext(ld, NULL, NULL);
   std::cout << "aus" << std::endl;
}
