#include <tgbot/tgbot.h> 
#include <iostream>
#include <string>
#include <map>

using TgBot;

class Bot : public TgBot::Bot
{
public:
	Bot(){};
	Bot(std::string tg_api) {};		
	
	
private:
	Bot bot;
	std::string tg_api = "7674686019:AAE2yBaPzhdgz8UH8pvnMXypVBUjJSaipzQ";
   	static int users = 0;

};
