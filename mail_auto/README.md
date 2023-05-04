# Скрипт для отправки писем по SMTP

## Пример использования

`(SENDER='vasya@gmail.com' PASSWORD='TOP-SECRET' RECIPIENT='petya@mail.ru' MESSAGE_FILE='message.eml' SMTP_SERVER='smtp.gmail.com' SMTP_SERVER_PORT=465 ./mailer.sh)`

В примере код запускается в subshell: код обособлен скобками.
Скобки образовали область видимости. Переменные не будут видны извне.