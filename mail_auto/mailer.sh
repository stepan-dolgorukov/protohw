#!/usr/bin/env bash

export SMTP_SERVER
export SMTP_SERVER_PORT
export SENDER
export PASSWORD
export RECIPIENT
export MESSAGE_FILE

echo "Server: $SMTP_SERVER"
echo "Port: $SMTP_SERVER_PORT"
echo "From: $SENDER"
echo "To: $RECIPIENT"
echo "Message File: $MESSAGE_FILE"

sleep 5.0s

B64_SENDER=`base64 <<< $SENDER`
B64_PASSWORD=`base64 <<< $PASSWORD`

(
sleep 1s
echo "ehlo test"
sleep 1s
echo "auth login"
sleep 1s
echo "$B64_SENDER"
sleep 1s
echo "$B64_PASSWORD"
sleep 1s
echo "mail from:<$SENDER>"
sleep 1s
echo "rcpt to:<$RECIPIENT>"
sleep 1s
echo "data"
sleep 1s
cat $MESSAGE_FILE
sleep 1s
echo "."
) | openssl s_client -connect "$SMTP_SERVER:$SMTP_SERVER_PORT" -crlf
