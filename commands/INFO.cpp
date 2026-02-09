#include "../Server.hpp"

void	Server::printInfo(int index) {
	clients[index - 1].printInfo();
}
