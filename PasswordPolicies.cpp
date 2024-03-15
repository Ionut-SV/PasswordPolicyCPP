#include<iostream>
#include<string>
#include<vector>
#include<cstdint>
#include <algorithm>

using namespace std;

class Policy{
    protected:
        bool isChecked;
    public:
        virtual void check(const string & password)=0;
        bool getCheck()const{
            return isChecked;
        }
};

class LengthPolicy : public Policy{
     private:
        uint16_t minLength;
        uint16_t maxLength;
    public:
        LengthPolicy(uint16_t min):minLength(min),maxLength(255){
        }
        LengthPolicy(uint16_t min,uint16_t max):minLength(min),maxLength(max){
        }
        void check(const string & password){
            isChecked=false;
            if((password.size()>=minLength) && (password.size()<=maxLength))
                isChecked   =  true;
        }
};

class ClassPolicy : public Policy{
    private:
        uint16_t minClassCount;
    public:
        ClassPolicy(uint16_t    min):minClassCount(min){
        }
        void check(const string &password){
        int count=0;
        isChecked=false;
        int l=0,c=0,L=0,other=0;
            for(int i=0;i<password.size();i++){
                if(islower(password[i]))
                    l++;
                 if(isupper(password[i]))
                    L++;
                 if (isdigit(password[i]))
                    c++;
                if(!isalnum(password[i]))    
                    other++;
            }    
            if(l>0)
                count++;
            if(c>0)
                count++;
            if(L>0)
                count++;
            if(other>0)
                count++;
            
                
            if(count >= minClassCount) 
                isChecked = true;
            
           
                
        }
    
};    

class IncludePolicy:public Policy{
    private:
        char characterType;
    public:
        IncludePolicy(char car):characterType(car){ 
        }
        void check(const string& password){
            isChecked=false;
            for(int i=0;i<password.size();i++){
                if(islower(characterType)   && islower(password[i]))
                    isChecked=true;
                else    if(isupper(characterType)   &&  islower(password[i]))
                    isChecked=true;
                else    if(isdigit(characterType)   &&  isdigit(password[i]))
                    isChecked=true;
                else    if(!isalnum(characterType)  &&  !isalnum(password[i]))
                    isChecked=true;
            }  
        }    
};

class NotIncludePolicy:public Policy{
    private:
        char characterType;
    public:
        NotIncludePolicy(char car):characterType(car){
        }
        void check(const string& password){
            isChecked=true;
            for(int i=0;i<password.size();i++){
                if(islower(characterType)   && islower(password[i]))
                    isChecked=false;
                  else  if(isupper(characterType)   &&  islower(password[i]))
                    isChecked=false;
                   else if(isdigit(characterType)   &&  isdigit(password.at(i)))
                    isChecked=false;
                    else    if(!isalnum(characterType)  &&  !isalnum(password[i]))
                    isChecked=false;
            } 

        }    
};

class RepetitionPolicy:public Policy{
    private:
        uint16_t maxCount;
    public:
        RepetitionPolicy(uint16_t maxc):maxCount(maxc){
        }
        void check(const string & password){
            int rep=0;
            isChecked = true;
            for(int i=0;i<password.size()-1;i++){
                    if (password[i]==password[i+1])
                        rep++;
                    else{
                        if(rep+1>maxCount)
                            isChecked = false;
                        rep=0;    
                        }
            }            

        }    
};

class ConsecutivePolicy :public Policy{
    private:
        uint16_t maxCount;
    public:
        ConsecutivePolicy (uint16_t maxc):maxCount(maxc){
        }
        void check(const string& password){
            int rep=0;
            isChecked=true;
            for(int i=0;i<password.size()-1;i++){
               
                    if (password[i]+1==password[i+1])
                        rep++;
                    else{
                        if (rep+1>maxCount)
                            isChecked=false;
                        rep=0;
                    }

                
            }
        }
};

string checkPassword(string password,vector <Policy*> v){
    int bec=0;
    for(int i=0;i<v.size();i++){
        v[i]->check(password); 
    }    
    for(int i=0;i<v.size();i++){    
        if (v[i]->getCheck() == false)
            bec++;
    }
    if (bec==0)
        return "OK";
    return "NOK";    
}

int main(){
    int n,min,max;
    string password;
    string policy;
    char car;
    cin>>n;
     vector < Policy *  > v;
    for(int i=0;i<n;i++){
        cin>>policy;
        if(policy   ==  "length"){
            cin>>min;
            if(!scanf("%d",&max))
                v.push_back(new LengthPolicy(min));
            else
                v.push_back(new LengthPolicy(min,max));
                
        }
        
        if(policy == "class"){
            cin>>min;
            v.push_back(new ClassPolicy(min));
        }
        
        if(policy == "include"){
            cin>>car;
            v.push_back(new IncludePolicy(car));
        }
        if(policy == "ninclude"){
            cin>>car;
            v.push_back(new NotIncludePolicy(car));
        }
        if(policy == "repetition"){
            cin>>min;
            v.push_back(new RepetitionPolicy(min));
        }
        if(policy == "consecutive"){
            cin>>min;
            v.push_back(new ConsecutivePolicy(min));
        }
    }
    
    while(cin>>password){
            cout<<checkPassword(password,v)<<'\n';
            
    }
    return 0;
    
}