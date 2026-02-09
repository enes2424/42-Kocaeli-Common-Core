#include "Utils.hpp"

void	writeln(int fd, string str) {
	send(fd, (str + "\n").c_str(), str.length() + 1, 0);
}

string	clearSpacesFromStartandEnd(int index, string str) {
	char	*tmp = (char *)str.c_str() + index;
	char	*tmp2;

	while (*tmp == ' ')
		tmp++;
	if (!*tmp)
		return tmp;
	tmp2 = tmp;
	while (*tmp2)
		tmp2++;
	tmp2--;
	while (*tmp2 == ' ')
		tmp2--;
	*(tmp2 + 1) = 0;
	return tmp;
}

string		convertToUppercaseString(string str) {
	char	*tmp = (char *)str.c_str();

	while (*tmp)
	{
		if (*tmp >= 'a' && *tmp <= 'z')
			*tmp = *tmp - 32;
		tmp++;
	}
	return str;
}

vector<string>	special_split(string str) {
	vector<string>	ret;
	int				j, i = 0;


	for (; str[i]; i++) {
		if (str[i] == ':') {
			if (ret.size() == 0) {
				vector<string>	tmp;
				tmp.push_back("");
				return tmp;
			}
			break ;
		}
		if (str[i] != ' ') {
			for (j = i + 1; str[j] && str[j] != ' ' && str[j] != ':'; j++);
			if (ret.size() == 0)
				ret.push_back(str.substr(0, j));
			else
				ret.push_back(str.substr(i, j - i));
			i = j - 1;
		}
	}
	for (; str[i]; i++) {
		if (str[i] != ':') {
			for (j = i + 1; str[j] && str[j] != ':'; j++);
			ret.push_back(str.substr(i, j - i));
			i = j - 1;
		}
	}
	if (ret.size() == 0) {
		vector<string>	tmp;
		tmp.push_back("");
		return tmp;
	}
	return ret;
}
