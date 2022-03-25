#ifndef MAPPING_HPP
#define MAPPING_HPP

#include <map>
using namespace std;

template <class TK, class TC>
class Mapping{
    private:
        map<TK,TC> peta;
    public:
        TC getContent(TK key){
            auto it = peta.find(key);
            return it->second;
        }
        void setContent(TK key, TC content){
            peta.insert({key, content});
        }
        void removeKey(TK key){
            peta.erase(key);
        }
        int getSize(){
            return peta.size();
        }
        bool isIn(TK key){
            return peta.find(key) != peta.end();
        }

};

#endif