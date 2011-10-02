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

#include "networkbase.h"

Networkbase::Networkbase(Networkbase::NetworkAddressType  addresstype, Networkbase::NetworkProtocolType protocol, int port)
{
  this->socket_descriptor = socket(addresstype, protocol, 0); 
  if(socket_descriptor == -1)
    throw std::string("exception");
  addr.sin_family = addresstype;
  addr.sin_port = port;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
}
