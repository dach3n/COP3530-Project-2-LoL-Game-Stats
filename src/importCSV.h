//
// Created by lrpau on 11/8/2025.
//

#ifndef IMPORTCSV_H
#define IMPORTCSV_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

struct Matchdata{
    int gameduration=0;
    int team0kills=0;
    int team1kills=0;
    long long team0gold=0;
    long long team1gold=0;
    int totalKills=0;
    long long totalGold=0;
    long long totalChampDmg=0;
    int killDiff=0;
    long long goldDiff=0;
    long long dmgDiff=0;
};

inline std::vector<std::string> CSVsplit(const std::string& line){
    std::vector<std::string> result;
    std::string current;
    bool inQuotes=false;
    for(size_t i=0;i<line.size();++i){
        char ch=line[i];
        if(inQuotes){
            if(ch=='"'){
                if(i+1<line.size() && line[i+1]=='"'){
                    current.push_back('"');
                    ++i;
                }else{
                    inQuotes=false;
                }
            }else{
                current.push_back(ch);
            }
        }else{
            if(ch=='"'){
                inQuotes=true;
            }else if(ch==','){
                result.push_back(current);
                current.clear();
            }else if(ch!='\r'){
                current.push_back(ch);
            }
        }
    }
    result.push_back(current);
    return result;
}

inline int headerIndex(const std::vector<std::string>& headers,const std::string& name){
    for(size_t i=0;i<headers.size();++i){
        if(headers[i]==name){
            return static_cast<int>(i);
        }
    }
    return -1;
}

template<typename T>
inline T parseNum(const std::string& s){
    if(s.empty()){
        return static_cast<T>(0);
    }
    std::istringstream iss(s);
    long double v=0;
    iss>>v;
    if(!iss){
        return static_cast<T>(0);
    }
    return static_cast<T>(v);
}

inline std::vector<Matchdata> loadMatchData(const std::string& filepath,size_t max_rows=(size_t)-1){
    std::ifstream file(filepath);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file: "+filepath);
    }
    std::string line;
    if(!std::getline(file,line)){
        throw std::runtime_error("Empty file: "+filepath);
    }
    std::vector<std::string> headers=CSVsplit(line);
    std::cout<<"[CSV] Columns detected: "<<headers.size()<<std::endl;
    int idxGameDur=headerIndex(headers,"gameDuration");
    int idxT0Kills=headerIndex(headers,"team0ChampionKills");
    int idxT1Kills=headerIndex(headers,"team1ChampionKills");
    if(idxGameDur<0 || idxT0Kills<0 || idxT1Kills<0){
        throw std::runtime_error("Missing one of core headers");
    }
    int goldIdx[10];
    int dmgIdx[10];
    for(int i=0;i<10;++i){
        std::string gname="participant"+std::to_string(i)+"GoldEarned";
        std::string dname="participant"+std::to_string(i)+"TotalDamageDealtToChampions";
        goldIdx[i]=headerIndex(headers,gname);
        dmgIdx[i]=headerIndex(headers,dname);
        if(goldIdx[i]<0 || dmgIdx[i]<0){
            throw std::runtime_error("Missing participant columns for index "+std::to_string(i));
        }
    }
    std::vector<Matchdata> out;
    out.reserve(100000);
    size_t row=0;
    while(row<max_rows && std::getline(file,line)){
        if(line.empty()){
            continue;
        }
        std::vector<std::string> cells=CSVsplit(line);
        size_t need=(size_t)std::max({idxGameDur,idxT0Kills,idxT1Kills});
        if(cells.size()<=need){
            continue;
        }
        Matchdata md;
        md.gameduration=parseNum<int>(cells[idxGameDur]);
        md.team0kills=parseNum<int>(cells[idxT0Kills]);
        md.team1kills=parseNum<int>(cells[idxT1Kills]);
        long long t0g=0;
        long long t1g=0;
        long long t0d=0;
        long long t1d=0;
        for(int i=0;i<10;++i){
            int gi=goldIdx[i];
            int di=dmgIdx[i];
            if(cells.size()<=std::max(gi,di)){
                continue;
            }
            long long g=parseNum<long long>(cells[gi]);
            long long d=parseNum<long long>(cells[di]);
            if(i<5){
                t0g+=g;
                t0d+=d;
            }else{
                t1g+=g;
                t1d+=d;
            }
        }
        md.team0gold=t0g;
        md.team1gold=t1g;
        md.totalKills=md.team0kills+md.team1kills;
        md.totalGold=t0g+t1g;
        md.totalChampDmg=t0d+t1d;
        md.killDiff=md.team0kills-md.team1kills;
        md.goldDiff=t0g-t1g;
        md.dmgDiff=t0d-t1d;
        out.push_back(md);
        row=row+1;
    }
    std::cout<<"[CSV] Loaded "<<out.size()<<" matches from "<<filepath<<std::endl;
    return out;
}

#endif