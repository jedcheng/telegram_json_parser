#include "simdjson.h"
#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <chrono> 

using namespace std::chrono; 
using namespace simdjson;
using namespace std;




int main(int argc, char *argv[]) {
    // Parse the arguments
    string_view file_name(argv[1]); /*file name*/
    string_view str_message;
    
    auto start = high_resolution_clock::now();

    // initlize the json parser
    ondemand::parser parser;
    padded_string json = padded_string::load(file_name);
    ondemand::document doc = parser.iterate(json);

    // get the messages
    ondemand::array messages = doc.find_field("messages").get_array();


    // initlize the vector to store the messages
    vector<string_view> messages_vector;

    for (auto value: messages){
        auto text = value.find_field("text");

        ondemand::json_type type = text.type();
        
        // If the message only contains text
        if (type == ondemand::json_type::string){
            auto error = text.get_string().get(str_message);
            messages_vector.push_back(string_view(str_message));
        }
        
        // the message might contain hyper links
        // the structure of the message would be different
        else if (type == ondemand::json_type::array){
            for (auto sub_value: text){
                auto error = sub_value.get_string().get(str_message);

                if (!error){
                    messages_vector.push_back(string_view(str_message));
                } 
            }
   
        }
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // convert the time to seconds
    double time_taken = duration.count() * 1e-6;
    cout << "Time taken by function: " << time_taken << " seconds" << endl;



    string str_keyword;
    string_view str_keyword_view;

    std::vector<std::string_view> result;

    while (true){
        cout << "Type the keyword you are looking for (type 'exit' to quit): ";
        getline(cin, str_keyword);

        str_keyword_view = string_view(str_keyword);

        if (str_keyword == "exit"){
            break;
        }


        

        for (auto& str: messages_vector){
            if (str.find(str_keyword_view) != string_view::npos){
                result.push_back(str);
            }
        }

        if (result.size() == 0){
            cout << "No result found" << endl;
        }
        else{
            cout << "Found " << result.size() << " results" << endl << endl << endl;
            for (auto& str: result){
                cout << str << endl;
            }
        }
        
        cout << endl << endl << endl;
        result.clear();

    }

}

    

