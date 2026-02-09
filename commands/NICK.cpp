#include "../Server.hpp"

void	Server::setNick(vector<string> &cmds, int index) {
	if (cmds.size() < 2)
		return writeln(pollFds[index].fd, ERR_NEEDMOREPARAMS(cmds[0]));
	if (cmds.size() > 2)
		return writeln(pollFds[index].fd, "Usage: NICK <nickname>, sets your nick");
	string	nickname = cmds[1];
	if (nickname[0] == '#')
		return writeln(pollFds[index].fd, "This nickname can't start #, because # is used in channels!!");
	if (nickname.find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Nickname can't include space");
	if (clients[index - 1].hasNick() && clients[index - 1].getNickname() == nickname)
		return writeln(pollFds[index].fd, "This nickname is already used by you");
	if (!controlNickname(nickname))
	{
		if (!clients[index - 1].hasNick()) {
			if (!clients[index - 1].getIsNC())
				writeln(pollFds[index].fd, RPL_NICK(clients[index - 1].getNickname(), clients[index - 1].getUsername(), nickname));
			clients[index - 1].setNickname(nickname, 0);
		}
		return writeln(pollFds[index].fd, ERR_NICKNAMEINUSE(nickname));
	}
	if (!clients[index - 1].getIsNC())
		writeln(pollFds[index].fd, RPL_NICK(clients[index - 1].getNickname(), clients[index - 1].getUsername(), nickname));
	if (clients[index - 1].hasNick())
		cout << clients[index - 1].getNickname() << " changed its name to " << nickname << endl;
	else
		writeln(pollFds[index].fd, "nickname accepted");
	clients[index - 1].setNickname(nickname, 1);
}
