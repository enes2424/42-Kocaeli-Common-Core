#ifndef CHANNEL
#define CHANNEL
#include "Client.hpp"

class Channel {
	public:
		Channel(class Server *server, string name, Client *moderator);
		const string	&getName(void) const;
		const string	&getTopic(void) const;
		Client			*getModerator(void);
		string			getUsers(void);
		void			setLock(string password);
		bool			isMatchPassword(string password);
		void			addClient(string str);
		void			deleteClient(string str, int flag);
		void			changeNameClient(string str, string new_str);
		bool			inClients(string str);
		void			setIsItClosedToOutside(bool isItClosedToOutside);
		bool			getIsItClosedToOutside(void);
		void			setTopic(string topic);
		void			printTopic(string client);
		void			info(int fd);
		void			showTable(void);
		void			setLimit(int limit);
		int				getLimit(void);
		int				size(void);
	private:
		vector<string>	clients;
		class Server	*server;
		Client			*moderator;
		string			name;
		string			password;
		bool			isItClosedToOutside;
		int				limit;
		string			topic;

};

#endif
