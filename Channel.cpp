#include "Server.hpp"
#include <sstream>

Channel::Channel(Server *server, string name, Client *moderator) {
	this->server = server;
	this->name = name;
	this->moderator = moderator;
	isItClosedToOutside = false;
	limit = MAX_CLIENTS;
}

const string	&Channel::getName(void) const {
	return name;
}

const string	&Channel::getTopic(void) const {
	return topic;
}

Client	*Channel::getModerator(void) {
	return moderator;
}

string	Channel::getUsers(void) {
	string	users = "";
	size_t	i = 0;

	for (; i < clients.size(); i++) {
		if (clients[i] == moderator->getNickname())
			users += "@";
		users += clients[i] + " ";
	}
	return users;
}

void	Channel::addClient(string str) {
	clients.push_back(str);
}

void	Channel::deleteClient(string str, int flag) {
	size_t	i = 0;
	Client	*client;

	for (; i < clients.size(); i++)
		if (clients[i] == str) {
			clients.erase(clients.begin() + i);
			if (moderator->getNickname() == str && clients.size())
				moderator = server->getClient(clients[0]);
			for (i = 0; i < clients.size(); i++)
			{
				client = server->getClient(clients[i]);
				if (flag)
				{
					if (!client->getIsNC())
						writeln(client->getFd(), RPL_PRIVMSG(str, name, "Leaving from this channel"));
					else
						writeln(client->getFd(), "(" + name + ")<" + str + "> Leaving from this channel");
				}
			}
			return showTable();
		}
}

void	Channel::changeNameClient(string str, string new_str) {
	size_t	i = 0;

	for (; i < clients.size(); i++)
		if (clients[i] == str) {
			clients[i] = new_str;
			return ;
		}
}

bool	Channel::inClients(string str) {
	size_t	i = 0;
	for (; i < clients.size(); i++)
		if (clients[i] == str)
			return true;
	return false;
}

void	Channel::setTopic(string topic) {
	this->topic = topic;
}

void	Channel::printTopic(string client) {
	if (!server->getClient(client)->getIsNC())
		writeln(server->getClient(client)->getFd(), RPL_PRIVMSG("hexchat", name, topic));
	else
		writeln(server->getClient(client)->getFd(), "(" + name + ")<hexchat> " + topic);
}

void	Channel::info(int fd) {
	size_t	i = 0;
	writeln(fd, "Channel : " + name);
	for (; i < clients.size(); i++)
	{
		ostringstream oss; // itoa
		oss << i + 1;
		if (moderator->getNickname() == clients[i])
			writeln(fd, oss.str() + ". Client : " + clients[i] + " <moderator>");
		else
			writeln(fd, oss.str() + ". Client : " + clients[i]);
	}
}

void	Channel::showTable(void) {
	Client	*client;
	string	users = getUsers();
	size_t	i = 0;

	for (; i < clients.size(); i++) {
		client = server->getClient(clients[i]);
		if (!client->getIsNC())
			writeln(client->getFd(), RPL_NAMREPLY(client->getNickname(), name, users));
	}
}

void	Channel::setLimit(int limit) {
	this->limit = limit;
	size_t	i;
	for (i = clients.size() - 1; clients.size() > (size_t)limit; i--) {
		if (clients[i] == moderator->getNickname())
			continue ;
		server->getClient(clients[i])->deleteChannel(name, 0);
		if (!server->getClient(clients[i])->getIsNC())
			writeln(server->getClient(clients[i])->getFd(), ":" + moderator->getNickname() + " KICK " + name + " " + clients[i] + " :server is full!!\r");
		else
			writeln(server->getClient(clients[i])->getFd(), "You have been kicked from " + name + " by " + moderator->getNickname() + "(server is full!!)");
	}
}

int		Channel::getLimit(void) {
	return limit;
}

int		Channel::size(void) {
	return clients.size();
}

void	Channel::setLock(string password) {
	this->password = password;
}

bool	Channel::isMatchPassword(string password) {
	if (this->password == "")
		return true;
	return this->password == password;
}

void	Channel::setIsItClosedToOutside(bool isItClosedToOutside) {
	this->isItClosedToOutside = isItClosedToOutside;
}

bool	Channel::getIsItClosedToOutside(void) {
	return isItClosedToOutside;
}
