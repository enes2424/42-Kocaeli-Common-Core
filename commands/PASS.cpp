#include "../Server.hpp"

void	Server::controlPassword(vector<string> &cmds, int index) {
	if (cmds.size() < 2)
		return writeln(pollFds[index].fd, ERR_NEEDMOREPARAMS(cmds[0]));
	if (cmds.size() > 2)
		return writeln(pollFds[index].fd, "Usage: PASS <password>, enter password to connect server");
	if (cmds[1].find(" ") != string::npos)
		return writeln(pollFds[index].fd, "Password can't include space");
	if (clients[index - 1].isConnect())
		return writeln(pollFds[index].fd, ERR_ALREADYREGISTRED);
	if (clients[index - 1].hasPass())
		return writeln(pollFds[index].fd, "Password has already been entered");
	if (cmds[1] == password)
		return clients[index - 1].confirmPassword(pollFds[index].fd);
	return writeln(pollFds[index].fd, "Wrong password");
}
