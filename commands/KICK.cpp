#include "../Server.hpp"

void	Server::kickClient(string buffer, int index) {
	string	channel_name, reason, target = clearSpacesFromStartandEnd(4, buffer);
	if (target.length() == 0 || target.find(" ") == string::npos || (channel_name = target.substr(0, target.find(" ")))[0] != '#'
		|| (channel_name = convertToUppercaseString(channel_name)).length() < 2 || (target = clearSpacesFromStartandEnd(target.find(" "), target)).length() == 0) {
		if (!clients[index - 1].getIsNC() && channel_name[0] != '#')
			return writeln(pollFds[index].fd, "kick is only used in the channel");
		return writeln(pollFds[index].fd, "Usage: KICK #<channel> <nick> [:<reason>], kick client");
	}
	Channel	*channel;
	if (!(channel = getChannel(channel_name)))
		return writeln(pollFds[index].fd, "No such channel found!!");
	if (!clients[index - 1].inChannel(channel_name))
		return writeln(pollFds[index].fd, "You are not on this channel!!");
	if (target.find(":") != string::npos) {
		reason = clearSpacesFromStartandEnd(target.find(":") + 1, target);
		target = clearSpacesFromStartandEnd(0, target.substr(0, target.find(":")));
	}
	if (!getClient(target))
	{
		if (!clients[index - 1].getIsNC())
			return writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel_name, "No such client found!!"));
		else
			return writeln(pollFds[index].fd, "(" + channel_name + ")<hexchat> No such client found!!");
	}
	if (&clients[index - 1] != channel->getModerator())
	{
		if (!clients[index - 1].getIsNC())
			return writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel_name, "You are not moderator!!"));
		else
			return writeln(pollFds[index].fd, "(" + channel_name + ")<hexchat> You are not moderator!!");
	}
	if (clients[index - 1].getNickname() == target)
	{
		if (!clients[index - 1].getIsNC())
			return writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel_name, "You can't kick yourself!!"));
		else
			return writeln(pollFds[index].fd, "(" + channel_name + ")<hexchat> You can't kick yourself!!");
	}
	if (!getClient(target)->inChannel(channel_name))
	{
		if (!clients[index - 1].getIsNC())
			return writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel_name, "This client is not available in this channel!!"));
		else
			return writeln(pollFds[index].fd, "(" + channel_name + ")<hexchat> This client is not available in this channel!!");
	}
	if (reason == "")
		reason = "without reason";
	if (!getClient(target)->getIsNC())
		writeln(getClient(target)->getFd(), RPL_KICK(clients[index - 1].getNickname(), channel_name, target, reason));
	else
		writeln(getClient(target)->getFd(), "You have been kicked from " + channel_name + " by " + clients[index - 1].getNickname() + "(" + reason + ")");
	getClient(target)->deleteChannel(channel_name, 0);
}
