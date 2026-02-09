#include "../Server.hpp"

void	Server::who(string buffer, int index) {
	string	channel_name = convertToUppercaseString(clearSpacesFromStartandEnd(3, buffer));
	if (channel_name.length() < 2 || channel_name[0] != '#' || channel_name.find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Usage: WHO #<channel name>, who are clients in channel");
	Channel	*channel;
	if (!(channel = getChannel(channel_name)))
		return writeln(pollFds[index].fd, "No such channel found!!");
	channel->info(pollFds[index].fd);
}
