#include "../Server.hpp"

void	Server::sendPrivmsg(char *buffer, int index) {
	size_t	index2 = string(buffer).find(":");
	size_t	i = 0;

	if (index2 == string::npos)
		return writeln(pollFds[index + 1].fd, "Usage: PRIVMSG <target> : <message>, sends private message");
	buffer[index2] = 0;
	string	target = clearSpacesFromStartandEnd(7, buffer);
	if (target[0] == '#') {
		target = convertToUppercaseString(target);
		if (!getChannel(target))
			return writeln(pollFds[index + 1].fd, "No such channel found!!");
		if (clients[index].inChannel(target) || !getChannel(target)->getIsItClosedToOutside()) {
			for (; i < clients.size(); i++)
				if (pollFds[i + 1].fd != -1 && clients[i].getNickname() != clients[index].getNickname() && clients[i].inChannel(target)) {
					if (!clients[i].getIsNC())
						writeln(pollFds[i + 1].fd, RPL_PRIVMSG(clients[index].getNickname(), target, string(buffer + index2 + 1)));
					else
						writeln(pollFds[i + 1].fd, "(" + target + ")<" + clients[index].getNickname() + "> " + (buffer + index2 + 1));
				}
		}
	}
	else {
		Client	*client = getClient(target);
		if (!client)
			return writeln(pollFds[index + 1].fd, "No such client exists");
		return writeln(client->getFd() , "<" + client->getNickname() + "> " + (buffer + index2 + 1));
	}
}
