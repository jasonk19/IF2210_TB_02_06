#include "Exception.hpp"

Exception::Exception(){
    this->message = "No message";
}

Exception::Exception(string message){
    this->message = message;
}

void Exception::setMessage(string message){
    this->message = message;
}

string Exception::getMessage() const{
    return this->message;
}
