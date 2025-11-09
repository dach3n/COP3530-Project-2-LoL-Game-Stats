//
// Created by lrpau on 11/8/2025.
//

#ifndef IMPORTCSV_H
#define IMPORTCSV_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <iostream>

struct Matchdata{
  int gameduration=0; //game time in seconds - col E
  int team0kills=0; //col BNO
  int team1kills=0; //col BOR
  long long team0gold=0;
  long long team1gold=0;
  int totalKills=0;
  long long totalGold=0;
  long long totalChampDmg=0;
  int killDiff =0; // team0-team1
  long long goldDiff=0; // team0-team1
  long long dmgDiff=0; // team0-team1
};
using namespace std;

inline int ExcelToIndex(const string& label){ //i have excel columns so just converting to int
  long long v=0;
  for(char c:label){
    if(isspace((unsigned char)c)){
      continue;
    }
    int d=toupper((unsigned char)c)-'A'+1;
    if(d<1||d>26){
      return -1;
    }
    v=v*26+d;
  }
  return (int)(v-1);
}

template<typename T>
inline T parseNum(const string& s){
  if(s.empty()){
    return (T)0;
  }
  istringstream iss(s);
  long double v=0;
  iss>>v;
  if(!iss){
    return (T)0;
  }
  return (T)v;
}

inline vector<string> readHeaders(const string& line) {
  vector<string>result;
  string current;
  bool quoted = false;

  for (size_t i = 0; i < line.size(); ++i) {
    char ch=line[i];
    if (quoted){
      if (ch=='"') {
        if (i+1<line.size() && line[i + 1] == '"') { current.push_back('"'); ++i; }
        else { quoted=false; }
      } else {
        current.push_back(ch);
      }
    } else {
      if (ch == '"') {
        quoted = true;
      } else if(ch == ',') {
       result.push_back(current);
        current.clear();
      } else if(ch != '\r') {
        current.push_back(ch);
      }
    }
  }
 result.push_back(current);
  return result;
}
inline vector<string> CSVsplit(const string& line){
  vector<string> result;
  string current;
  bool inQuotes=false;
  for(size_t i=0;i<line.size();++i){
    char ch=line[i];
    if(inQuotes){
      if(ch=='"'){
        if(i+1<line.size()&&line[i+1]=='"'){
          current.push_back('"');
          ++i;
        }
        else{
          inQuotes=false;
        }
      }
      else{
        current.push_back(ch);
      }
    }
    else{
      if(ch=='"'){
        inQuotes=true;
      }
      else if(ch==','){
        result.push_back(current);
        current.clear();
      }
      else if(ch!='\r'){
        current.push_back(ch);
      }
    }
  }
  result.push_back(current);
  return result;
}

inline vector<Matchdata> loadMatchData(const string& filepath,size_t max_rows=(size_t)-1){
  ifstream file(filepath);
  if(!file.is_open()){
    throw runtime_error("Failed to open file");
  }
  string line;
  if(!getline(file,line)){
    throw runtime_error("Empty file");
  }
  auto headers=CSVsplit(line);
  cout<<"CSV headers: "<<headers.size()<<endl;
  const int gameDur=ExcelToIndex("E");
  const int t0kills=ExcelToIndex("BNO");
  const int t1kills=ExcelToIndex("BOR");
  const string goldcolumns[10]={"BD","HR","OF","UT","ABH","AHV","AOJ","AUX","BBK","BHY"};
  int goldIndex[10];
  const string dmgcolumns[10]={"FC","LQ","SE","YS","AFG","ALU","ASI","AYW","BFJ","BLX"};
  int dmgIndex[10];
  const string teamcolumns[10]={"EW","LK","RY","YM","AFA","ALO","ASC","AYQ","BFD","BLR"};
  int teamIndex[10];
  for(int i=0;i<10;i++){
    goldIndex[i]=ExcelToIndex(goldcolumns[i]);
    dmgIndex[i]=ExcelToIndex(dmgcolumns[i]);
    teamIndex[i]=ExcelToIndex(teamcolumns[i]);
  }
  vector<Matchdata> d;
  d.reserve(100000); //pre allocate memory to speed this up a little bit
  size_t row=0;
  while(row<max_rows&&getline(file,line)){
    if(line.empty()){
      continue;
    }
    auto cells=CSVsplit(line);
    if(cells.size()<=teamIndex[9]){
      continue;
    }
    size_t need=max({gameDur,t0kills,t1kills});
    if(cells.size()<=need){
      continue;
    }
    Matchdata md;
    md.gameduration=parseNum<int>(cells[gameDur]);
    md.team0kills=parseNum<int>(cells[t0kills]);
    md.team1kills=parseNum<int>(cells[t1kills]);
    long long t0gld=0;
    long long t1gld=0;
    long long t0dmg=0;
    long long t1dmg=0;
    for(int i=0;i<10;i++){
      int goldindex=goldIndex[i];
      int dmgindex=dmgIndex[i];
      int teamindex=teamIndex[i];

      size_t np=max({goldindex,dmgindex,teamindex});
      if(cells.size()<=np){
        continue;
      }
      int teamId=parseNum<int>(cells[teamindex]);
      long long gold=parseNum<long long>(cells[goldindex]);
      long long dmg=parseNum<long long>(cells[dmgindex]);
      bool team0=(teamId==100)||(teamId!=200&&i<5);
      if(team0){
        t0gld+=gold;
        t0dmg+=dmg;
        }
      else{
          t1gld+=gold;
          t1dmg+=dmg;
       }
       }
       md.team0gold=t0gld;
       md.team1gold=t1gld;
       md.totalKills=md.team0kills+md.team1kills;
       md.totalGold=md.team0gold+md.team1gold;
       md.totalChampDmg=t0dmg+t1dmg;
       md.killDiff=md.team0kills-md.team1kills;
       md.goldDiff=md.team0gold-md.team1gold;
       md.dmgDiff=t0dmg-t1dmg;
       d.push_back(md);
       row++;
    }
  cout<<"CSV Loaded "<<d.size()<<" matches from file: "<<filepath<<endl;
  return d;
  }
#endif // IMPORTCSV_H