#ifndef SERVER
#define SERVER
#include "Channel.hpp"

class Server {

	public:

		Server(int port, string password);
		~Server(void);

		void		serverLoop(void);
		bool		acceptClient();
		void		acceptClientContinue(vector<string> &cmds, string &cmd, int index, bool is_nc);
		bool		controlUsername(string &username) const;
		bool		controlNickname(string nickname) const;
		void		controlMSG(char *buffer);
		Channel		*getChannel(string channel);
		Client		*getClient(string client);
		void		setOpen(bool is_open);
		void		exec(string buffer, int index);
		void		modeError(int index, string channel);

		//commands
		void	controlPassword(vector<string> &cmds, int index);
		void	setUser(vector<string> &cmds, int index);
		void	setNick(vector<string> &cmds, int index);
		void	printInfo(int index);
		void	joinChannel(vector<string> &cmds, int index);
		void	leaveChannel(string buffer, int index);
		void	modeChannel(string buffer, int index);
		void	kickClient(string buffer, int index);
		void	sendPrivmsg(char *buffer, int index);
		void	exitClient(vector<string> &cmds, int index);
		void	printChannelInfo(int fd);
		void	inviteClient(string buffer, int index);
		void	changeTopicOrPrint(string buffer, int index);
		void	who(string buffer, int index);
		void	printCommands(vector<string> &cmds, int fd);

	private:

		vector<Channel>	channels;
		vector<Client>	clients;
		sockaddr_in		serverAddr;
		pollfd			pollFds[MAX_CLIENTS + 1];
		string			password;
		int				is_open;
		int				port;
		int				serverSocket;
		int				num_of_client;

};

#endif
