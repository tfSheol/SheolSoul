#include "MySoul.h"
#include "md5.h"

MySoul::MySoul() : _nextCmd(0)
{
    _dico["salut"] = &MySoul::getInfos;
    _dico["rep"] = &MySoul::sendCmd;
    _dico["ping"] = &MySoul::saveCo;
    _log[1] = &MySoul::extUserLog;
    _log[2] = &MySoul::attach;
    _log[3] = &MySoul::state;
}

MySoul::~MySoul()
{
}

bool			MySoul::init(std::string location, std::string username, std::string password, std::string addr, int port)
{
    _username = username;
    _password = password;
    _location = location;
    if (_cli.connex(addr, port))
        return (true);
    return (false);
}

std::string		MySoul::strtockf(std::string str, char delim, int nb)
{
    size_t		i = -1;
    std::string         reply;
    int                 find = 0;

    if (str != "")
    {
        while (++i < str.length())
        {
            if (str[i] == delim)
                find += 1;
            if (find == nb && str[i] != delim)
                reply += str[i];
        }
    }
    return (reply);
}

bool			MySoul::sendCmd(std::string data)
{
    if ((strtockf(data, ' ', 1) == "002") || (strtockf(data, ' ', 1) == "001"))
        _nextCmd += 1;
    if (_log[_nextCmd] && (this->*_log[_nextCmd])())
        return (true);
    return (false);
}

bool			MySoul::getInfos(std::string data)
{
    char		buffer[512];

    _nbSocket = strtockf(data, ' ', 1);
    _md5Server = strtockf(data, ' ', 2);
    _hostClient = strtockf(data, ' ', 3);
    _portClient = strtockf(data, ' ', 4);
    _timestampServer = strtockf(data, ' ', 5);
    sprintf(buffer, "%s-%s/%s%s", 
                    _md5Server.c_str(), 
                    _hostClient.c_str(),
                    _portClient.c_str(),
                    _password.c_str());
    _myMD5 = md5(buffer);
    if (authAg())
        return (true);
    return (false);
}

bool			MySoul::saveCo(std::string data)
{
    std::string		reCo(strtockf(data, ' ', 1));

    if (_cli.sendData("ping " + reCo + "\r\n"))
        return (true);
    return (false);
}

bool			MySoul::authAg()
{
    if (_cli.sendData("auth_ag ext_user none none\r\n"))
        return (true);
    return (false);
}

bool			MySoul::extUserLog()
{
    if (_cli.sendData("ext_user_log " + _username + " " + _myMD5 + " SheolSoul " + _location + "\r\n"))
        return (true);
    return (false);
}

bool			MySoul::attach()
{
    if (_cli.sendData("attach\r\n"))
        return (true);
    return (false);
}

bool			MySoul::state()
{
    if (_cli.sendData("state actif:" + _timestampServer + "\r\n"))
        return (true);
    _nextCmd = 4;
    return (false);
}

bool			MySoul::run()
{
    while (1)
    {
        std::string	data;
        std::string	cmd;

        if ((data = _cli.recvData()) != "")
        {
            cmd = strtockf(data, ' ', 0);
            if (data != "")
                std::cout << "<< " << data << std::endl;
            if (_dico[cmd] && (this->*_dico[cmd])(data))
                return (true);
        }
    }
    return (false);
}