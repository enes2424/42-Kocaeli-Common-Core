#include "Server.hpp"
#include <csignal>

bool	arg_control(int argc, char **argv, int &port, string &password)
{
	int	i;

	if (argc != 3) {
		cerr << "Argumants error!!" << endl;
		cerr << "Your executable will be run as follows:" << endl;
		cerr << "./ircserv <port> <password>" << endl;
		return false;
	}
	password = argv[2];
	if (password.find(" ") != string::npos) {
		cerr << "Password can't include space!!" << endl;
		return false;
	}
	for (i = 0; argv[1][i]; i++) {
		if (argv[1][i] < '0' || argv[1][i] > '9') {
			cerr << "Port can't include not digit character!!" << endl;
			return false;
		}
		port = port * 10 + argv[1][i] - 48;
		if (port > 65535)
		{
			cerr << "Port range cannot be exceeded!!" << endl;
			return false;
		}
	}
	if (port == 0)
	{
		cerr << "Port range cannot be exceeded!!" << endl;
		return false;
	}
	return true;
}

Server	*server = NULL;

void	signal_handle(int key) {
	(void)key;
	server->setOpen(false);
	delete server;
	server = NULL;
}

int	main(int argc, char **argv)
{
	int		port = 0;
	string	password;

	signal(SIGINT, signal_handle);
	signal(SIGHUP, signal_handle);
	if (!arg_control(argc, argv, port, password))
		return 1;
	try {
		server = new Server(port, password);
		server->serverLoop();
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
	delete server;
	return 0;
}
