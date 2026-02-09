#include "../Server.hpp"

void	Server::changeTopicOrPrint(string buffer, int index) {
	string	topic = clearSpacesFromStartandEnd(5, buffer);
	if (!clients[index - 1].getIsNC() && topic[0] != '#')
		return writeln(pollFds[index].fd, "topic is only used in the channel without channel name");
	string	channel_name = convertToUppercaseString(topic);
	if (topic.find(":") == string::npos) {
		if (channel_name[0] != '#' || channel_name.find(" ") != string::npos)
		{
			writeln(pollFds[index].fd, "Usage: TOPIC #<channel> :(: using in nc)<topic>, set topic");
			return writeln(pollFds[index].fd, "Usage: TOPIC #<channel>, print topic");
		}
		Channel	*channel;
		if (!(channel = getChannel(channel_name)))
			return writeln(pollFds[index].fd, "No such channel found!!");
		if (!clients[index - 1].inChannel(channel_name))
			return writeln(pollFds[index].fd, "You are not on this channel!!");
		return channel->printTopic(clients[index - 1].getNickname());
	}
	channel_name = clearSpacesFromStartandEnd(0, channel_name.substr(0, channel_name.find(":")));
	Channel	*channel;
	if (!(channel = getChannel(channel_name)))
		return writeln(pollFds[index].fd, "No such channel found!!");
	if (!clients[index - 1].inChannel(channel_name))
		return writeln(pollFds[index].fd, "You are not on this channel!!");
	if (&clients[index - 1] != channel->getModerator()) {
		if (!clients[index - 1].getIsNC())
			return writeln(pollFds[index].fd, RPL_PRIVMSG("hexchat", channel_name, "You are not moderator!!"));
		else
			return writeln(pollFds[index].fd, "(" + channel_name + ")<hexchat> You are not moderator!!");
	}
	topic = clearSpacesFromStartandEnd(topic.find(":") + 1, topic);
	size_t	i = 0;
	for (; i < clients.size(); i++) {
		if (clients[i].inChannel(channel_name)) {
			if (!clients[i].getIsNC())
				writeln(pollFds[i + 1].fd, RPL_TOPIC(clients[index - 1].getNickname(), channel_name, topic));
			else
				writeln(pollFds[i + 1].fd, clients[index - 1].getNickname() + " has changed the topic to: " + topic);
		}
	}
	channel->setTopic(topic);
}
