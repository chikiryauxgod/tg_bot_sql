#include <exception>
#include <pqxx/result.hxx>
#include <pqxx/transaction.hxx>
#include <stdio.h>
#include <tgbot/tgbot.h>
#include <pqxx/pqxx>

int main() {
    TgBot::Bot bot("7674686019:AAE2yBaPzhdgz8UH8pvnMXypVBUjJSaipzQ");
	try {
		pqxx::connection c("dbname=northwind user=postgres password=1337 hostaddr=172.21.48.1 port=5432");
        std::cout << "Connection to: " << c.dbname() << std::endl;
		pqxx::work tx{c};
		
		pqxx::result r = tx.exec("SELECT first_name, employee_id FROM employees ORDER BY employee_id");
		for (const auto& row: r){
			std::string name = row[0].as<std::string>();
			int id = row[1].as<int>();
			std::cout << name << " has id: " << id << ".\n";			
			}
		
	}
   	catch (const std::exception &e) {
		std::cerr << "Connection trouble: " << e.what() << std::endl;
	}

    bot.getEvents().onCommand("start", [&bot, c](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
		});

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
		try {

		} catch (const std::exception &e) {
			std::cerr << "Wrong prompt: " << e.what() << std::endl; 
		}
    });


    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
