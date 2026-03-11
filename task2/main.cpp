#include <bits/stdc++.h>
using namespace std;

enum class loglevel { INFO, WARN, ERROR, DEBUG, UNKNOWN };

struct logentry{
    string TIME;
    string DATE;
    loglevel LEVEL;
    int USER;
    int LATENCY;
    string MESSAGE;
};

vector<logentry> objectcreator(){
    ifstream fin("tc3.log",ios::in);
    string line;
    vector<logentry> logs;
    while (getline(fin,line)){
        stringstream ss(line);
        logentry log;
        string time;
        string level;
        string user;
        string latency;
        ss>>time>>level>>user>>latency;
        log.DATE = time.substr(0,10);
        log.TIME = time.substr(11,8);
        if (level=="INFO"){
            log.LEVEL=loglevel::INFO;
        }
        else if (level=="WARN"){
            log.LEVEL=loglevel::WARN;
        }
        else if (level=="ERROR"){
            log.LEVEL=loglevel::ERROR;
        }
        else if (level=="DEBUG"){
            log.LEVEL=loglevel::DEBUG;
        }
        else{
            log.LEVEL= loglevel::UNKNOWN;
        }
        log.USER = stoi(user.substr(4));
        log.LATENCY = stoi(latency.substr(0, latency.size() - 2));
        ss>>ws;
        getline(ss,log.MESSAGE);
        log.MESSAGE.erase(0,1);
        log.MESSAGE.erase(log.MESSAGE.size()-1);
        logs.push_back(log);
    }
    return logs;
}

map<loglevel, long long> countperlevel(const vector<logentry>& logs){
    map<loglevel,long long> levelcount;
    for (const auto &log:logs){
        levelcount[log.LEVEL]++;
    }
    return levelcount;
}

double averagelatency(const vector<logentry>& logs){
    double avglatency=0;
    for (const auto &log:logs){
        avglatency+=log.LATENCY;
    }
    avglatency/=logs.size();
    return avglatency;
}

vector<int> top10users(const vector<logentry>& logs){
    unordered_map<int,long long> usercount;
    for (const auto &log:logs){
        usercount[log.USER]++;
    }
    vector<pair<int,long long>> totaldescorder;
    for (const auto &user:usercount){
        totaldescorder.push_back({user.first,user.second});
    }
    sort(totaldescorder.begin(), totaldescorder.end(), [](const auto& a, const auto& b){
        return a.second > b.second;
    });
    vector<int> top10;
    for (int i=0;i<10;i++){
        top10.push_back(totaldescorder[i].first);
    }
    return top10;
}

int latencyof95thpercentile(const vector<logentry>& logs){
    vector<int>latencies;
    for (const auto& log:logs){
        latencies.push_back(log.LATENCY);    
    }
    sort(latencies.begin(),latencies.end());
    size_t index = ceil(95.0*logs.size()/100)-1;
    int latency = latencies[index];
    return latency;
}

string leveltostring(loglevel level) {
    if (level==loglevel::INFO){
        return "INFO";
    }
    if (level==loglevel::WARN){
        return "WARN";
    }
    if (level==loglevel::ERROR){
        return "ERROR";
    }
    if (level==loglevel::DEBUG){
        return "DEBUG";
    }
    else{
        return "UNKNOWN";
    }
}

int main(){
    auto starttime1 =std::chrono::steady_clock::now();
    vector<logentry> logs = objectcreator();
    auto endtime1 =std::chrono::steady_clock::now();


    auto starttime2 =std::chrono::steady_clock::now();

    map<loglevel, long long> count_per_level = countperlevel(logs);
    for (auto p:count_per_level){
        cout<<leveltostring(p.first)<<" - "<<p.second<<endl;
    }
    double average_latency = averagelatency(logs);
    cout<<"Average Latency is = "<<average_latency<<endl;
    vector<int> top_10_users = top10users(logs);
    cout<<"Top 10 users are: "<<endl;
    for (int x:top_10_users){
        cout<<x<<endl;
    }
    int latency_of_95th_percentile = latencyof95thpercentile(logs);
    cout<<"Latency of 95th percentile is"<<latency_of_95th_percentile<<endl;

    auto endtime2 =std::chrono::steady_clock::now();


    auto parsetime = std::chrono::duration_cast<std::chrono::milliseconds>(endtime1 - starttime1);
    auto processingtime = std::chrono::duration_cast<std::chrono::milliseconds>(endtime2 - starttime2);
    cout<<"Parsing Time = "<<parsetime.count()<<"ms"<<endl;
    cout<<"Process Time = "<<processingtime.count()<<"ms"<<endl;
}



