#include "Server.hpp"
#include <sstream>

Client::Client(void) {
	connect = false;
	has_pass = false;
	has_nick = false;
	has_user = false;
}

void	Client::setServer(Server *server) {
	this->server = server;
}

void	Client::printInfo() {
	writeln(clientSocket, "Nickname -> " + nickname);
	writeln(clientSocket, "Username -> " + username);
	writeln(clientSocket, "Hostname -> " + hostname);
	writeln(clientSocket, "Servername -> " + servername);
	writeln(clientSocket, "Realname -> " + realname);
	if (channels.size()) {
		size_t	i = 0;
		writeln(clientSocket, "  CHANNELS");
		for (; i < channels.size(); i++) {
			ostringstream oss;
			oss << i + 1;
			writeln(clientSocket, oss.str() + ". Channel : " + channels[i]);
		}
	}
}

void	Client::setIsNC(bool is_nc) {
	this->is_nc = is_nc;
}

bool	Client::getIsNC(void) const {
	return is_nc;
}

void	Client::setUser(string username, string hostname, string servername, string realname) {
	has_user = true;
	if (!connect && has_nick) {
		connect = true;
		cout << "New connection established: " << nickname << endl;
	}
	this->username = username;
	this->hostname = hostname;
	this->servername = servername;
	this->realname = realname;
}

const string	&Client::getUsername(void) const {
	return username;
}

void	Client::setNickname(string nickname, int flag) {
	if (flag) {
		size_t	i = 0;

		for (; i < channels.size(); i++)
			server->getChannel(channels[i])->changeNameClient(this->nickname, nickname);
		has_nick = true;
		if (!connect && has_user) {
			connect = true;
			cout << "New connection established: " << nickname << endl;
		}
	}
	this->nickname = nickname;
}

const string	&Client::getNickname(void) const {
	return nickname;
}

int		Client::getFd(void) {
	return clientSocket;
}

void	Client::addChannel(string channel) {
	channels.push_back(channel);
}

void	Client::deleteChannel(string channel, int flag) {
	size_t	i = 0;

	server->getChannel(channel)->deleteClient(nickname, flag);
	for (; i < channels.size(); i++)
		if (channels[i] == channel) {
			channels.erase(channels.begin() + i);
			break ;
		}
	if (flag)
		cout << nickname << " left from " << channel << " channel" << endl;
	else
		cout << nickname << " was kicked from " << channel << " channel" << endl;
}

void	Client::allDeleteChannel() {
	while (channels.size())
		deleteChannel(channels[0], 1);
}

bool	Client::inChannel(string channel) {
	size_t	i = 0;

	for (; i < channels.size(); i++)
		if (channels[i] == channel)
			return true;
	return false;
}

bool	Client::isConnect(void) const {
	return connect;
}

void	Client::disConnect(void) {
	connect = false;
	has_pass = false;
	has_nick = false;
	has_user = false;
}

void	Client::controlConnect(int fd) {
	if (!has_pass)
		return writeln(fd, "No connection: to connect, write -> PASS <password>");
	if (!has_nick && !has_user)
		return writeln(fd, "No connection: to connect, write -> NICK <nickname>\n                                    USER <username> <hostname> <servername> <realname>");
	if (!has_nick)
		return writeln(fd, "No connection: to connect, write -> NICK <nickname>");
	if (!has_user)
		return writeln(fd, "No connection: to connect, write -> USER <username> <hostname> <servername> <realname>");
}

void	Client::confirmPassword(int fd) {
	writeln(fd, "Correct password");
	clientSocket = fd;
	has_pass = true;
}

bool	Client::hasPass(void) const {
	return has_pass;
}

bool	Client::hasUser(void) const {
	return has_user;
}

bool	Client::hasNick(void) const {
	return has_nick;
}
