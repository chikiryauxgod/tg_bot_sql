# Telegram Bot на C++ с PostgreSQL

Этот проект представляет собой Telegram-бота, написанного на C++ с использованием библиотеки [TgBot](https://github.com/reo7sp/tgbot-cpp) и базы данных PostgreSQL. Бот принимает команды и сохраняет сообщения пользователей в базе данных.

---
## 🚀 Установка и настройка

### 1. Установка зависимостей
Перед началом работы установите необходимые пакеты:

#### WSL (Ubuntu):
```sh
sudo apt update && sudo apt install -y cmake g++ libboost-all-dev libpqxx-dev libtgbot-dev
```

#### Windows:
Установите PostgreSQL [отсюда](https://www.postgresql.org/download/windows/).

---
## 🛠 Настройка PostgreSQL (Windows)

1. Запустите **pgAdmin** и создайте базу данных:
   - **Имя БД**: `dbname`
   - **Пользователь**: `postgres`
   - **Пароль**: `password`

2. Создайте таблицу `messages`:

```sql
CREATE TABLE messages (
    id SERIAL PRIMARY KEY,
    chat_id BIGINT NOT NULL,
    message TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

3. Разрешите подключение из WSL, изменив файл `pg_hba.conf`:
   - Откройте `C:\Program Files\PostgreSQL\<версия>\data\pg_hba.conf`.
   - Добавьте строку в конец:
     ```
     host    all             all             0.0.0.0/0               md5
     ```

4. Разрешите доступ ко всем IP в `postgresql.conf`:
   - Откройте `C:\Program Files\PostgreSQL\<version>\data\postgresql.conf`.
   - Найдите `listen_addresses` и установите:
     ```
     listen_addresses = '*'
     ```
   - Перезапустите PostgreSQL через **pgAdmin** или `services.msc`.

---
## 🌍 Настройка переменных окружения

Добавьте переменные окружения в WSL:
```sh
echo "export TELEGRAM_BOT_TOKEN='token'" >> ~/.bashrc
echo "export DB_CONNECTION='dbname=dbname user=postgres password=password hostaddr=address port=5432'" >> ~/.bashrc
source ~/.bashrc
```
*(где `address` — IP Windows = `ipconfig` -> `Ethernet adapter vEthernet`)*

---
## ⚙️ Сборка и запуск бота

```sh
g++ bot.cpp -o test --std=c++14 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread -lpqxx -lpq
```

---
## 🔥 Использование

После запуска бот должен написать в консоли его имя. В Telegram отправьте команду `/start` или любое сообщение, и оно сохранится в БД.

---
