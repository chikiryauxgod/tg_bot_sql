#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        pqxx::connection c("dbname=northwind user=postgres password=1337 hostaddr=127.0.0.1.10.255.255.254 port=5432");

        std::cout << "Connection to: " << c.dbname() << std::endl;

        pqxx::work tx{c};

        pqxx::result r = tx.exec("SELECT first_name, employee_id FROM employees ORDER BY employee_id");

        for (const auto &row : r) {
            std::string name = row[0].as<std::string>();
            int id = row[1].as<int>();

            std::cout << name << " имет id " << id << ".\n";
        }

    }
    catch (const std::exception &e) {
        std::cerr << "Connection trouble: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

