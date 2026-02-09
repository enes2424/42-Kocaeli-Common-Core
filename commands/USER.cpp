#include "../Server.hpp"

void	Server::setUser(vector<string> &cmds, int index) {
	if (cmds.size() < 5)
		return writeln(pollFds[index].fd, ERR_NEEDMOREPARAMS(cmds[0]));
	if (cmds.size() > 5)
		return writeln(pollFds[index].fd, "Usage: USER <username> <hostname> <servername> <realname>, sets your user");
	if (cmds[1][0] == '#')
		return writeln(pollFds[index].fd, "This username can't start #, because # is used in channels!!");
	if (cmds[2][0] == '#')
		return writeln(pollFds[index].fd, "This hostname can't start #, because # is used in channels!!");
	if (cmds[3][0] == '#')
		return writeln(pollFds[index].fd, "This servername can't start #, because # is used in channels!!");
	if (cmds[4][0] == '#')
		return writeln(pollFds[index].fd, "This realname can't start #, because # is used in channels!!");
	if (cmds[1].find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Username can't include space");
	if (cmds[2].find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Hostname can't include space");
	if (cmds[3].find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Servername can't include space");
	if (clients[index - 1].isConnect())
		return writeln(pollFds[index].fd, ERR_ALREADYREGISTRED);
	if (clients[index - 1].hasUser())
		return writeln(pollFds[index].fd, "Username has already been entered");
	if (!controlUsername(cmds[1]))
		return writeln(pollFds[index].fd, "This username is already in use");
	clients[index - 1].setUser(cmds[1], cmds[2], cmds[3], cmds[4]);
	writeln(pollFds[index].fd, "username accepted");
}
