# Telegram Json Parser

This is a (very) simple CLI tool to parser and search for messages in a json file exported from Telegram with [simdjson](https://github.com/simdjson/simdjson).

It should work for mac and linux. I don't have a windows machine.

## Why don't you just use the built-in search function in Telegram?
The built-in search function in Telegram is awful for Chinese because it only considers words between spaces/plunctuation as a word. For example, if you have a message "你好，世界", the built-in search function returns nothing if you search for "你" or "世". The only way to find this message is to search for "你好" or "世界". This program solves this problem by parsing the json file and searching for the keyword in the message.


## Usage

1. Download the official Telegram desktop client [official Telegram client](https://desktop.telegram.org/) . As far as I know, this is not supported by any third party clients.

2. Export your chat history. You can do this by going to the chat you want to export, click on the three dots on the top right corner, and select "Export Chat History". Export the chat as a JSON file. Remember to select the option to exclude media files if you don't want to export them.

3. Clone the repo and compile the program with `c++ -o main main.cpp simdjson.cpp -std=c++11 ` or downlaod the compiled binary from the release page.

4. Run the program `./main <path to json file>`

5. Search for messages by typing the keyword you want to search for. 

6. Type 'exit' to exit the program.