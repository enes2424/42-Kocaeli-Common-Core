#include "../Server.hpp"

void	Server::inviteClient(string buffer, int index) {
	string	tmp = clearSpacesFromStartandEnd(6, buffer);
	if (tmp.find(" ") == string::npos)
		return writeln(pollFds[index].fd, "Usage: INVITE <nickname> #<channel name>, invite other client");
	string	nickname = tmp.substr(0, tmp.find(" "));
	string	channel = convertToUppercaseString(clearSpacesFromStartandEnd(tmp.find(" "), tmp));
	if (channel.find(" ") != string::npos || channel[0] != '#' || channel.length() < 2)
		return writeln(pollFds[index].fd, "Usage: INVITE <nickname> #<channel name>, invite other client");
	if (!getChannel(channel))
		return writeln(pollFds[index].fd, "No such channel found!!");
	if (!clients[index - 1].inChannel(channel))
		return writeln(pollFds[index].fd, "You are not on this channel!!");
	Client *client = getClient(nickname);
	if (!client)
		return writeln(pollFds[index].fd, "No such client exists");
	if (client->inChannel(channel))
		return writeln(pollFds[index].fd, "Client is already on this channel!!");
	if (!client->getIsNC())
		writeln(client->getFd(), RPL_INVITE(clients[index - 1].getNickname(), nickname, channel));
	else
		writeln(client->getFd(), "You have been invited to " + channel + " by " + clients[index - 1].getNickname());
	writeln(client->getFd(), "Please to join this channel, you should write -> join " + channel);
}
