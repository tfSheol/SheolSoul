#include "MySoul.h"#include "Data.h"std::string		strCapitalize(const char str[]){    char		ret[256];    int                 i;    int                 n;    i = -1;    n = -1;    while (str[++i])    {        if (str[i] >= 'a' && str[i] <= 'z')            ret[++n] = str[i] - ' ';        else            ret[++n] = str[i];    }    ret[++n] = '\0';    return (ret);}std::string		urlEncode(std::string str){    char		ret[256];    int                 i;    int                 n;    i = -1;    n = -1;    std::cout << str << std::endl;    while (str[++i])    {        if (str[i] == 32)        {            ret[++n] = '%';            ret[++n] = '2';            ret[++n] = '0';        }        else            ret[++n] = str[i];    }    ret[++n] = '\0';    return (ret);}int                     main(){    std::string         username("USERNAME");    std::string         password("PASSWORD");    char                loca[256];    std::string         location;    MySoul		soul;    std::cout << "Location : ";    std::cin.getline(loca, 256);    if (loca[0] == '\0')        location = urlEncode(strCapitalize(std::string(LOCATION_DEFAULT).c_str()));    else        location = urlEncode(strCapitalize(loca));    std::cout << ">>>>> " << location << " <<<<<" << std::endl;    while (1)    {        if (!soul.init(location, username, password, "163.5.42.2", 4242))        {            if (soul.run())                std::cout << "Reconecting ..." << std::endl;        }    }    return (false);}