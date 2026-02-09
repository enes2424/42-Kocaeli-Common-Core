#include "../Server.hpp"

void	Server::modeChannel(string buffer, int index) {
	string	tmp = clearSpacesFromStartandEnd(0, buffer.substr(buffer.find(" ")));
	if (!clients[index - 1].getIsNC() && tmp[0] != '#')
		return writeln(pollFds[index].fd, "mode is only used in the channel without channel name");
	if (tmp.length() == 0 || tmp[0] != '#')
		return writeln(pollFds[index].fd, string("Usage: MODE #<channel>, doesn't do anything\nUsage:") +
			" MODE #<channel> (+|-)n, set permissions for outside messages\nUsage: MODE #<channel> -l," +
			" remove limit\nUsage: MODE #<channel> +l <positive num>, set a channel limit\nUsage: MODE #<ch" +
			"annel> -k, remove channel key\nUsage: MODE #<channel> +k <password>, set a channel key");
	string	channel_name = convertToUppercaseString(tmp);
	if (channel_name.find(" ") != string::npos)
		channel_name = channel_name.substr(0, channel_name.find(" "));
	Channel	*channel;
	if (!(channel = getChannel(channel_name)))
		return writeln(pollFds[index].fd, "No such channel found!!");
	if (!clients[index - 1].inChannel(channel_name))
		return writeln(pollFds[index].fd, "You are not on this channel!!");
	if (tmp.find(" ") == string::npos) {
		writeln(pollFds[index].fd, "Usage: MODE #<channel>, doesn't do anything");
		writeln(pollFds[index].fd, "Usage: MODE #<channel> (+|-)n, set permissions for outside messages");
		writeln(pollFds[index].fd, "Usage: MODE #<channel> -l, remove limit");
		writeln(pollFds[index].fd, "Usage: MODE #<channel> +l <positive num>, set a channel limit");
		writeln(pollFds[index].fd, "Usage: MODE #<channel> -k, remove channel key");
		writeln(pollFds[index].fd, "Usage: MODE #<channel> +k <password>, set a channel key");
		return ;
	}
	if (&clients[index - 1] != channel->getModerator()) {
		if (!clients[index - 1].getIsNC())
			return writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel_name, "You are not moderator!!"));
		else
			return writeln(pollFds[index].fd, "(" + channel_name + ")<hexchat> You are not moderator!!");
	}
	string	mode = clearSpacesFromStartandEnd(tmp.find(" "), tmp);
	tmp = "";
	if (mode.find(" ") != string::npos)
	{
		tmp = clearSpacesFromStartandEnd(mode.find(" "), mode);
		mode = clearSpacesFromStartandEnd(0, mode.substr(0, mode.find(" ")));
	}
	if (mode == "+k")
	{
		if (tmp.length() == 0)
			return modeError(index, channel_name);
		channel->setLock(tmp);
	}
	else if (mode == "-k")
	{
		if (tmp.length() != 0)
			return modeError(index, channel_name);
		channel->setLock("");
	}
	else if (mode == "+l")
	{
		if (tmp.length() == 0)
			return modeError(index, channel_name);
		size_t	num = 0, i;
		for (i = 0; i < tmp.length(); i++) {
			if (tmp[i] < '0' || tmp[i] > '9')
				return modeError(index, channel_name);
			num = num * 10 + tmp[i] - 48;
			if (num >= MAX_CLIENTS)
			{
				if (!clients[index - 1].getIsNC())
					return writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel_name, "This number already exceeds the server limit!!"));
				else
					return writeln(pollFds[index].fd, "(" + channel_name + ")<hexchat> This number already exceeds the server limit!!");
			}
		}
		if (num == 0)
			return modeError(index, channel_name);
		channel->setLimit(num);
	}
	else if (mode == "-l")
	{
		if (tmp.length() != 0)
			modeError(index, channel_name);
		channel->setLimit(MAX_CLIENTS);
	}
	else if (mode == "+n" || mode == "-n")
	{
		if (tmp.length() != 0)
			modeError(index, channel_name);
		channel->setIsItClosedToOutside(mode == "+n");
	}
	else
		modeError(index, channel_name);
}

void	Server::modeError(int index, string channel) {
	if (!clients[index - 1].getIsNC())
	{
		writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel, "Usage: MODE #<channel>, doesn't do anything"));
		writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel, "Usage: MODE #<channel> (+|-)n, set permissions for outside messages"));
		writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel, "Usage: MODE #<channel> -l, remove limit"));
		writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel, "Usage: MODE #<channel> +l <positive num>, set a channel limit"));
		writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel, "Usage: MODE #<channel> -k, remove channel key"));
		writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel, "Usage: MODE #<channel> +k <password>, set a channel key"));
		return ;
	}
	writeln(pollFds[index].fd, "(" + channel + ")<hexchat> Usage: MODE #<channel>, doesn't do anything");
	writeln(pollFds[index].fd, "(" + channel + ")<hexchat> Usage: MODE #<channel> (+|-)n, set permissions for outside messages");
	writeln(pollFds[index].fd, "(" + channel + ")<hexchat> Usage: MODE #<channel> -l, remove limit");
	writeln(pollFds[index].fd, "(" + channel + ")<hexchat> Usage: MODE #<channel> +l <positive num>, set a channel limit");
	writeln(pollFds[index].fd, "(" + channel + ")<hexchat> Usage: MODE #<channel> -k, remove channel key");
	writeln(pollFds[index].fd, "(" + channel + ")<hexchat> Usage: MODE #<channel> +k <password>, set a channel key");
}
