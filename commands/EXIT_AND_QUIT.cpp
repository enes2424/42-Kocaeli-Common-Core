#include "../Server.hpp"

void	Server::exitClient(vector<string> &cmds, int index) {
	num_of_client--;
	clients[index - 1].allDeleteChannel();
	size_t	i = 0;
	for (; i < channels.size(); i++) // ??????
		if (channels[i].size() == 0) {
			cout << channels[i].getName() << " channel is deleted" << endl;
			channels.erase(channels.begin() + i);
			i--;
		}
	string	message = "Leaving";
	if (cmds.size() > 1)
		message = cmds[cmds.size() - 1];
	for (i = cmds.size() - 2; i > 0; i--)
		message = cmds[i] + " " + message;
	close(pollFds[index].fd);
	if (clients[index - 1].isConnect())
		cout << "Connection closed: " << clients[index - 1].getNickname() << ": " << message << endl;
	pollFds[index].fd = -1;
	clients[index - 1].disConnect();
}
