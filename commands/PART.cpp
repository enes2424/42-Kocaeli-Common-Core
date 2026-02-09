#include "../Server.hpp"

void	Server::leaveChannel(string buffer, int index) {
	size_t	index2 = string(buffer).find(":");

	if (index2 != string::npos)
		buffer[index2] = 0;
	string	channel_name = convertToUppercaseString(clearSpacesFromStartandEnd(4, buffer));
	if (channel_name.length() < 2 || channel_name[0] != '#' || channel_name.find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Usage: PART #<channel name> [: <message>], left the channel");
	Channel	*channel;
	if (!(channel = getChannel(channel_name)))
		return writeln(pollFds[index].fd, "No such channel found!!");
	if (!clients[index - 1].inChannel(channel_name))
		return writeln(pollFds[index].fd, "You are not on this channel!!");
	if (!clients[index - 1].getIsNC())
		writeln(pollFds[index].fd, RPL_PART(clients[index - 1].getNickname(), channel_name));
	clients[index - 1].deleteChannel(channel_name, 1);
	if (channel->size() == 0) {
		cout << channel_name << " channel is deleted" << endl;
		size_t	i = 0;
		for (; i < channels.size(); i++)
			if (&channels[i] == channel)
				return (void)channels.erase(channels.begin() + i);
	}
}

