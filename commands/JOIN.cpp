#include "../Server.hpp"

void	Server::joinChannel(vector<string> &cmds, int index) {
	if (cmds.size() < 2)
		return writeln(pollFds[index].fd, ERR_NEEDMOREPARAMS(cmds[0]));
	if (cmds.size() > 3)
		return writeln(pollFds[index].fd, "Usage: JOIN #<channel name> [<password>], joins the channel");
	string	channel_name = cmds[1];
	string	password = "";
	if (cmds.size() == 3)
		password = cmds[2];
	if (channel_name.find(" ") != string::npos || channel_name.length() < 2 || channel_name[0] != '#')
		return writeln(pollFds[index].fd, ERR_NOSUCHCHANNEL(channel_name));
	if (password.find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Password can't include space");
	Channel	*channel;
	channel_name = convertToUppercaseString(channel_name);
	if (!(channel = getChannel(channel_name))) {
		channels.push_back(Channel(this, channel_name, &clients[index - 1]));
		channel = &channels[channels.size() - 1];
		cout << "create " << channel_name << " channel" << endl;
	}
	if (channel->inClients(clients[index - 1].getNickname()))
		return writeln(pollFds[index].fd, "You are already on this channel!!");
	if (!channel->isMatchPassword(password))
		return writeln(pollFds[index].fd, ERR_BADCHANNELKEY(channel_name));
	if (channel->getLimit() == channel->size())
		return writeln(pollFds[index].fd, ERR_CHANNELISFULL(channel_name));
	channel->addClient(clients[index - 1].getNickname());
	clients[index - 1].addChannel(channel->getName());
	if (!clients[index - 1].getIsNC()) {
		writeln(pollFds[index].fd, RPL_JOIN(clients[index - 1].getNickname(), channel_name));
		if (channel->getTopic().length())
			writeln(pollFds[index].fd, RPL_TOPIC(channel->getModerator()->getNickname(), channel_name, channel->getTopic()));
	}
	channel->showTable();
	cout << clients[index - 1].getNickname() << " join " << channel_name << " channel" << endl;
	size_t	i = 0;
	for (; i < clients.size(); i++) {
		if (clients[i].inChannel(convertToUppercaseString(channel_name)) && clients[i].getNickname() != clients[index - 1].getNickname()) {
			if (!clients[i].getIsNC())
				writeln(pollFds[i + 1].fd, RPL_PRIVMSG(clients[index - 1].getNickname(), channel_name, "join the channel"));
			else
				writeln(pollFds[i + 1].fd, "(" + channel_name + ")<" + clients[index - 1].getNickname() + "> join the channel");
		}
	}
}
