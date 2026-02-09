#include "../Server.hpp"

void	Server::printCommands(vector<string> &cmds, int fd) {
	if (cmds.size() < 2)
		return writeln(fd, ERR_NEEDMOREPARAMS(cmds[0]));
	if (cmds.size() > 2 || convertToUppercaseString(cmds[1]) != "LS")
		return writeln(fd, "Usage: CAP LS, print command list");
	writeln(fd, "COMMANDS LIST\n--------\nCHANNELINFO\nINFO\nINVITE\nJOIN\nKICK\nMODE\nNICK\nPART\nPASS\nPRIVMSG\nTOPIC\nUSER\nWHO\nEXIT\nQUIT");
}
