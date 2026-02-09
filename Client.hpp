#ifndef CLIENT
#define CLIENT
#include "Utils.hpp"

class	Client {

	public:

		Client(void);
		void			setServer(class Server *server);
		void			printInfo(void);
		void			setIsNC(bool is_nc);
		bool			getIsNC(void) const;
		void			setUser(string username, string hostname, string servername, string realname);
		const string	&getUsername(void) const;
		void			setNickname(string nickname, int flag);
		const string	&getNickname(void) const;
		int				getFd(void);
		void			addChannel(string channel);
		void			deleteChannel(string channel, int flag);
		void			allDeleteChannel(void);
		void			confirmPassword(int fd);
		void			controlConnect(int fd);
		void			disConnect(void);
		bool			isConnect(void) const;
		bool			inChannel(string channel);
		bool			hasPass(void) const;
		bool			hasUser(void) const;
		bool			hasNick(void) const;

	private:

		vector<string>	channels;
		class Server	*server;
		string			nickname;
		string			username;
		string			hostname;
		string			servername;
		string			realname;
		bool			has_pass;
		bool			has_nick;
		bool			has_user;
		bool			connect;
		bool			is_nc;
		int				clientSocket;
};

#endif
