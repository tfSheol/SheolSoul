#ifndef MYSOUL_H_
# define MYSOUL_H_

#include <map>
#include <string>
#include <sstream>
#include "MySocket.h"

class MySoul
{
private:
    MySocket                                                    _cli;
    std::map<std::string, bool (MySoul::*)(std::string)>	_dico;
    std::map<int, bool (MySoul::*)()>                           _log;
    int                                                         _nextCmd;
    std::string                                                 _username;
    std::string                                                 _password;
    std::string                                                 _location;

    /* Server data */
    std::string                                                 _nbSocket;
    std::string                                                 _md5Server;
    std::string                                                 _hostClient;
    std::string                                                 _portClient;
    std::string                                                 _timestampServer;

    /* Client Data */
    std::string                                                 _myMD5;
	
public:
    MySoul();
    ~MySoul();
    bool							init(std::string, std::string, std::string, std::string, int);
    std::string                                                 strtockf(std::string, char, int);
    bool							run();
    bool							saveCo(std::string);
    bool							getInfos(std::string);
    bool							sendCmd(std::string);
    bool							authAg();
    bool							extUserLog();
    bool							attach();
    bool							state();
};

#endif /* MYSOUL_H_ */