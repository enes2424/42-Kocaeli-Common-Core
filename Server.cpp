#include "Server.hpp"

Server::Server(int port, string password) : clients(MAX_CLIENTS) {
	this->port = port;
	this->password = password;
	num_of_client = 0;
	is_open = true;

	// Server socket oluşturma
	//                          IPV4        TCP
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw runtime_error("Socket creation failed!!");

	// SO_REUSEADDR seçeneğini ayarla
	int	optval = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		throw runtime_error("Set socket failed!!");

	// Server adresi ayarlama
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");

	// Server socketi bağlama
	if (::bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
		throw runtime_error("Bind failed!!");

	// Server socketi dinleme moduna geçirme
	if (listen(serverSocket, MAX_CLIENTS) == -1)
		throw runtime_error("Listen failed!!");

	cout << "Server listening on port " << port << endl;

	pollFds[0].fd = serverSocket;
	pollFds[0].events = POLLIN; //POLLIN, poll fonksiyonunun bir dosya tanımında okuma işlemi yapılabilir olduğunu belirten bir sabittir.
}

void	Server::setOpen(bool is_open) {
	this->is_open = is_open;
}

Server::~Server(void) {
	if (is_open)
		cout << "Server closed" << endl;
	int	i = 0;
	for (; i <= MAX_CLIENTS; i++)
		if (pollFds[i].fd != -1)
			close(pollFds[i].fd);
}

void	Server::serverLoop(void) {
	char	buffer[1000001];
	int		status;
	int		flag;
	int		i;

	for (i = 1; i <= MAX_CLIENTS; ++i)
	{
		pollFds[i].fd = -1;
		pollFds[i].events = POLLIN;
		clients[i - 1].setServer(this);
	}
	while (true) {
		if (num_of_client == 0)
			flag = 10000;
		else
			flag = -1;
		// poll fonksiyonu ile olayları bekleyin
		status = poll(pollFds, MAX_CLIENTS + 1, flag);
		if (!is_open)
			throw runtime_error("Server closed");
		if (status == -1)
			throw runtime_error("Poll failed!!");
		if (!status)
			return ;
		if (!acceptClient())
			return ;
		controlMSG(buffer);
	}
}

bool	Server::acceptClient(void)
{
	size_t			index;
	int				newSocket;

	// Yeni bir istemci bağlantısı var mı kontrol et
	if (pollFds[0].revents) {
		if ((newSocket = accept(serverSocket, NULL, NULL)) == -1) {
			cerr << "Accept failed!!" << endl;
			return false;
		}
		// Yeni istemciyi bulunabilir bir soket ile eşleştirin
		size_t i;
		for (i = 1; i <= MAX_CLIENTS; ++i) {
			if (pollFds[i].fd == -1) {
				index = i;
				break;
			}
		}
		if (i > MAX_CLIENTS) {
			cerr << "Server full!!" << endl;
			writeln(newSocket, "Server full!!");
			close(newSocket);
			return false;
		}
		pollFds[index].fd = newSocket;
		num_of_client++;
	}
	return true;
}

void	Server::acceptClientContinue(vector<string> &cmds, string &cmd, int index, bool is_nc) {
	clients[index - 1].setIsNC(is_nc);
	if (cmd == "CAP")
		return printCommands(cmds, pollFds[index].fd);
	if (cmd == "PASS")
		return controlPassword(cmds, index);
	if (clients[index - 1].hasPass()) {
		if (cmd == "NICK")
			return setNick(cmds, index);
		else if (cmd == "USER")
			return setUser(cmds, index);
	}
	if (cmd == "EXIT" || cmd == "QUIT")
		return exitClient(cmds, index);
	clients[index - 1].controlConnect(pollFds[index].fd);
}

bool	Server::controlUsername(string &username) const {
	size_t	i;

	for (i = 0; i < clients.size(); i++)
		if (clients[i].hasUser() && clients[i].getUsername() == username)
			return false;
	return true;
}

bool	Server::controlNickname(string nickname) const {
	size_t	i;

	for (i = 0; i < clients.size(); i++)
		if (clients[i].hasNick() && clients[i].getNickname() == nickname)
			return false;
	return true;
}

void	Server::controlMSG(char *buffer) {
	ssize_t	bytesRead;
	size_t	i;

	// Tüm istemcilere gelen verileri kontrol et
	for (i = 1; i <= MAX_CLIENTS; ++i)
		if (pollFds[i].revents) {
			// Veriyi al
			bytesRead = recv(pollFds[i].fd, buffer, 1000000, 0);
			if (bytesRead <= 0) {// Bağlantı kesildi veya hata oluştu
				vector<string>	tmp;
				tmp.push_back("QUIT");
				exitClient(tmp, i);
			}
			else {
				buffer[bytesRead] = 0;
				exec(buffer, i);
			}
		}
}

void	Server::exec(string buffer, int index) {
	string	tmp = buffer.substr(buffer.find("\n") + 1);
	bool	is_nc;

	if (buffer.find("\n") == string::npos) // ctrl + D
		tmp = ""; 
	else if (!(is_nc = !(buffer.find("\r") != string::npos))) // hexchat
		buffer = buffer.substr(0, buffer.find("\n") - 1);
	else
		buffer = buffer.substr(0, buffer.find("\n")); // nc
	vector<string>	cmds = special_split(buffer);
	string			cmd = convertToUppercaseString(cmds[0]);
	if (!clients[index - 1].isConnect())
		acceptClientContinue(cmds, cmd, index, is_nc);
	else if (cmd == "PRIVMSG")
		sendPrivmsg((char *)buffer.c_str(), index - 1);
	else if (cmd == "PASS")
		controlPassword(cmds, index);
	else if (cmd == "NICK")
		setNick(cmds, index);
	else if (cmd == "USER")
		setUser(cmds, index);
	else if (cmd == "INFO")
		printInfo(index);
	else if (cmd == "JOIN")
		joinChannel(cmds, index);
	else if (cmd == "PART")
		leaveChannel(buffer, index);
	else if (cmd == "KICK")
		kickClient(buffer, index);
	else if (cmd == "MODE")
		modeChannel(buffer, index);
	else if (cmd == "TOPIC")
		changeTopicOrPrint(buffer, index);
	else if (cmd == "WHO")
		who(buffer, index);
	else if (cmd == "INVITE")
		inviteClient(buffer, index);
	else if (cmd == "CHANNELINFO")
		printChannelInfo(pollFds[index].fd);
	else if (cmd == "CAP")
		printCommands(cmds, pollFds[index].fd);
	else if (cmd == "EXIT" || cmd == "QUIT")
		exitClient(cmds, index);
	else
		cout << "<" << clients[index - 1].getNickname() << "> " << buffer << endl;
	if (tmp.length())
		exec(tmp, index);
}

Channel		*Server::getChannel(string channel) {
	size_t	i;
	for (i = 0; i < channels.size(); i++)
		if (channel == channels[i].getName())
			return &channels[i];
	return NULL;
}

Client		*Server::getClient(string client) {
	size_t	i;
	for (i = 0; i < clients.size(); i++)
		if (client == clients[i].getNickname())
			return &clients[i];
	return NULL;
}
