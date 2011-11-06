#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include "deletemessage.h"
#include "listmessage.h"
#include "messageexception.h"
#include "standard_messages.h"
#include "read.h"
#include "mail.h"
#include "login.h"
#include "file.h"
//#include "listmessageelement.h"
BOOST_CLASS_EXPORT(Deletemessage);
BOOST_CLASS_EXPORT(Listmessage);
BOOST_CLASS_EXPORT(MessageException);
BOOST_CLASS_EXPORT(standard_messages);
BOOST_CLASS_EXPORT(Read);
BOOST_CLASS_EXPORT(Mail);
BOOST_CLASS_EXPORT(Login);
BOOST_CLASS_EXPORT(File);
//BOOST_CLASS_EXPORT(ListMessageElement);