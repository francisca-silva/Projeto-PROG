#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Player_info{
	string name;
	int score;
};

void scoreboard(int num_maze){
	
	//vector <vector <char>> score_info(0,vector<char> (22));
    // vector <string> score_info(1);
    vector <Player_info> score_info;
    Player_info 
	string filename, line;
	// ler o ficheiro
	ifstream in_stream;
	int i = 0;

	if (num_maze > 9) filename = "Scoreboard_" + to_string(num_maze) + ".txt";
	else filename = "Scoreboard_0" + to_string(num_maze) + ".txt";

	in_stream.open(filename);

    if (!in_stream) {
		ofstream newfile;
		newfile.open(filename);
		newfile.close();
	}
	in_stream.close();

	in_stream.open(filename);
/*
	while(getline(in_stream, score_info[i])) {
        score_info.push_back(score_info[0]);
		i++;
        score_info[i] = '                      ';
	}
    score_info.erase(score_info.begin() + score_info.size() - 1);

    for (int j = 0; j < score_info.size(); j++){
        cout << score_info[j] << endl;	
    } 	
	*/
    while(getline(in_stream, line)) {
        if (line[-1] == 'e' || line[-1] == '-') continue;
        score_info.name = line.substr(0,15);        
		score_info.score = line.substr(18,4);
        cout << score_info.name << endl << score_info.name << endl;
        line = '                      ';
	}
    //score_info.erase(score_info.begin() + score_info.size() - 1);
	
	in_stream.close();
	
	
	// trabalhar os dados
	
	// voltar a escrever(mostrar ao utilizador tambem)
}

int main() {
    //scoreboard(1);





    return 0;
}




