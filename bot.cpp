#include <boost/asio/execution/execute.hpp>
#include <exception>
#include <pqxx/transaction.hxx>
#include <tgbot/tgbot.h> 
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <pqxx/pqxx>
#include <tgbot/types/Chat.h>
#include <tgbot/types/Message.h>

class DB_Manager
{
public:
	DB_Manager(const std::string& db_connection) : conn(db_connection)
	{
		if (!conn.is_open())
			std::cerr << "PostgreSQL canceling connection." << std::endl;
		else
			std::cout << "Connection to PostgreSQL is open." << std::endl;
	}
	
	bool SaveMsg(const std::string& msg, int chat_id)
	{
		try 
		{
			pqxx::work txn(conn); // transaction
			txn.exec_params("INSERT INTO MESSAGES (chat_id, message) VALUES ($1, $2);", chat_id, msg);
			txn.commit();
		} 
		catch (const std::exception& e) {
			std::cerr << "PostgreSQL error: " << e.what() << std::endl;
			return 1;
		}
		return 0;
	}

private:
	std::string db_connection = "";
	pqxx::connection conn;

};


class Command
{
public:
	virtual ~Command() {}
	virtual void execute(TgBot::Bot& bot, TgBot::Message::Ptr msg) = 0;

};

class StartCommand final : public Command
{
public:
	void execute(TgBot::Bot& bot, TgBot::Message::Ptr msg) override{
		bot.getApi().sendMessage(msg->chat->id, "Hi! I'm bot written in C++ includes PostgreSQL.");
	}
};

class EchoCommand final : public Command 
{
public:
	void execute(TgBot::Bot& bot, TgBot::Message::Ptr msg) override{
		bot.getApi().sendMessage(msg->chat->id, "You've wrote: " + msg->text);
	}
};

class CommandRouter
{
public:
	CommandRouter() {
		commands["/start"] = std::make_shared<StartCommand>(); 
	}
	std::shared_ptr<Command> get_cmd(const std::string& cmd_text)
	{
		auto it = commands.find(cmd_text);
		if (it != commands.end())
			return it->second;
		return std::make_shared<EchoCommand>();
	}
 
private:
	std::map<std::string, std::shared_ptr<Command>> commands;	
};

class MyBot
{ 
public:
	// MyBot(){};
	MyBot(const std::string& token, const std::string& db_connection) : bot(token), // db_Manager(db_connection), router(){
		SetupHandlers();
	};		

	
private:
	
	void SetupHandlers()
	{
		bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr msg)
		{
			if (msg->text.empty())
				return;
			db_mng.SaveMsg(msg->text, msg->chat->id);
			if (msg->text[0] == '/'){
				std::string cmd_text = msg->text.substr(0, msg->text.find(" "));
				auto command = router.get_cmd(cmd_text);
				command -> execute(bot, msg);
			}
		}
	}

	TgBot::Bot bot; // internal obj
	DB_Manager db_mng;
	CommandRouter router;	// 
	std::string token = "7674686019:AAE2yBaPzhdgz8UH8pvnMXypVBUjJSaipzQ";
   	static int users = 0;

};

int main()
{
	
	return 0;
}

