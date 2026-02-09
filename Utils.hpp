#ifndef UTILS
#define UTILS
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/poll.h>
using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::exception;
using std::cerr;
using std::runtime_error;
using std::ostringstream;

#define RPL_NICK(nick, user, newnick)			":" + nick + "!" + user + "@127.0.0.1 NICK :" + newnick + "\r"
#define RPL_JOIN(nick, channel)					":" + nick + "!" + nick + "@127.0.0.1" + " JOIN " + channel + "\r"
#define RPL_INVITE(nick, channel, target)		":" + nick + "!" + nick + "@127.0.0.1 INVITE " + target + " " + channel + "\r"
#define RPL_PRIVMSG(nick, target, message)		":" + string(nick) + " PRIVMSG " + target + " :" + message + "\r"
#define RPL_PART(nick, channel)					":" + nick + " PART :" + channel + "\r"
#define RPL_KICK(nick, channel, target, reason)	":" + nick + " KICK " + channel + " " + target + " :" + reason + "\r"
#define RPL_TOPIC(nick, channel, topic)			":" + nick + "!" + nick + "@127.0.0.1" + " TOPIC " + channel + " :" + topic + "\r"
#define RPL_NAMREPLY(nick, channel, users)		": 353 " + nick + " = " + channel + " :" + users

#define ERR_NEEDMOREPARAMS(command)				": 461 : " + command + " :Not enough parameters" + "\r"
#define ERR_NICKNAMEINUSE(nick)					": 433 : " + nick + " :Nickname is already in use" + "\r"
#define ERR_NOSUCHCHANNEL(channel)				": 403 : " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(channel)				": 475 : " + channel + " :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(channel)				": 471 : " + channel + " :Cannot join channel (+l)"

#define ERR_ALREADYREGISTRED					": 462 : You may not reregister\r"
#define MAX_CLIENTS 100 /* istemcilerin maksimum değeri */

void			writeln(int fd, string str);
string			clearSpacesFromStartandEnd(int index, string str);
string			convertToUppercaseString(string str);
vector<string>	special_split(string str);

#endif
