#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<list>
using namespace std;
string wordoftheday;
class Block{
public:
int day;
string item;
Block(int i){
day=i;
item=wordoftheday;
}
};
class Week{
public:
list<Block> b;
int num;
Week(int i){
num=i;
}
};
void SlotInWeek(int date);
int FindDate(string x, int i);
int ParseForDates(string x);
Week** w;
string* monAbbr; 
int* monCount;
int quarterStart;
int main(int argc, char *argv[]){
w=new Week*[15];
for(int i=0;i<15;i++){
Week x(i);
w[i]=&x;
}
string ma[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};
monAbbr=ma;
int mc[12]={0,31,59,90,120,151,181,212,243,273,304,334};
monCount=mc;
quarterStart=84;
ifstream thing;
thing.open(argv[1]);
list<string> ls;//=new list<string>();
string x;
cout<<"Check1\n";
while(getline(thing, x)){
SlotInWeek(FindDate(x, ParseForDates(x)));
}
cout<<"Check2\n";
fstream results;
results.open("output.txt");
results.clear();
cout<<"Check3\n";
for(int i=0;i<11;i++){
results << "Week "<< i << " " << w[i]->b.size()<<":\n";
while(!w[i]->b.empty()){
results << "Day "<<w[i]->b.front().day<<" "<<w[i]->b.front().item<<endl;
w[i]->b.pop_front();
}
}
}
int ParseForDates(string xx){
string x=xx;
for(int i=0; i<12; i++)
if(x.find(monAbbr[i])!=std::string::npos)
return i;
return -1;
}
int FindDate(string x, int i){
int date, truedate;
if(i==-1)
return -1;
else{
//__size_type t;
//date=stoi(x,t);
stringstream ss;
ss<<x;
string temp;
wordoftheday="";
while(!ss.eof()){
ss>>temp;
if(temp.back()==':')
temp.pop_back();
if(temp=="Midterm"||temp=="Homework"||temp=="HW"||temp=="Final"||temp=="Quiz"){
wordoftheday=temp;
}
else if(stringstream(temp)>>date)
break;
}
truedate=monCount[i]+date;
cout<<i<<" "<<monCount[i]<<" "<<truedate<<endl;
date=truedate-quarterStart;
cout<<"Check1.5\n";
return date;
}
}
void SlotInWeek(int date){
Block c(date%7);
cout<<date<<endl;
cout<<date/7<<endl;
if(date/7<15){
cout<<"HELLO "<<w[date/7]->num<<endl;
w[date/7]->b.insert(w[date/7]->b.begin(),c);
cout<<date/7;
}
}
