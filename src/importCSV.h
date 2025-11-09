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

  long long team0gold =0;
  long long team1gold =0;

  int totalKills =0;
  long long totalGold =0;
  long long totalDmgChamp =0;
  int killDiff =0; // team0 - team1
  long long goldDiff =0; // team0 - team1
  long long dmgDiff =0; // team0 - team1

};
using namespace std;
inline int ExcelToIndex(const std::string& label){ //i have excel columns so just converting to int
  long long v=0;
  for(char c:label){
    if(std::isspace((unsigned char)c)){
      continue;
    }
    int d=std::toupper((unsigned char)c)-'A'+1;
    if(d<1||d>26){
      return -1;
    }
    v=v*26+d;
  }
  return (int)(v-1);
}

template<typename T>
inline T parseNum(const std::string& s){
  if(s.empty()){
    return (T)0;
  }
  std::istringstream iss(s);
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

inline vector<Matchdata> loadMatchData(const std::string& filepath,size_t max_rows=(size_t)-1){
  std::ifstream file(filepath);
  if(!file.is_open()){
    throw std::runtime_error("Failed to open file");
  }


}
#endif // IMPORTCSV_H