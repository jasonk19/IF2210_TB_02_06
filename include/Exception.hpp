#include <string>
using namespace std;

class Exception{
    private:
        string message;

    public:
        Exception();
        Exception(string message);
        
        void setMessage(string message);
        string getMessage() const;
};
