// CS302 Proj1
// Music database program
// Eli Carter and Kyle Anderson
// Some inspiration from the lab write up and stack overflow, cited when used

#include <iostream>
#include <sstream>
#include <iterator>
#include <map>
#include <string>
#include <fstream>


using namespace std;

string replace_w_spaces(string,string);
string seconds_to_mmss(int);

// struct inspiration from Plank write up
struct Song {
	string title;
	int time;
	int track;
};

struct Album {
	map <int, Song > songs;
	string name;
	int time;
	int nsongs;
};

struct Artist {
	map <string, Album > albums;
	string name;
	int time;
	int nsongs;
};

int main(int argc, char*argv[]){

	// gather input into data structures
	// File stufff
	string file_name = argv[1];
	ifstream fin;
	fin.open(file_name);

	stringstream ss;

	string title, time_str, artist_str, album_str, genre, track_str;
	int time_s = 0;
	int track_num;
	map <string, Artist> artists;

	while (fin >> title){
		// reading
		fin >> time_str;		
		fin >> artist_str;
		artist_str = replace_w_spaces(artist_str, " ");
		fin >> album_str;
		album_str = replace_w_spaces(album_str, " ");
		fin >> genre;
		genre = replace_w_spaces(genre, " ");
		fin >> track_str;
		title = replace_w_spaces(title, " ");

		
		ss.clear();
		//additional parsing for the numbers
		ss.str(track_str);
		ss >> track_num;
		ss.clear();
		ss.str(time_str.substr(0, time_str.find(':')));
		ss >> time_s;
		time_s *= 60;
		ss.clear();
		ss.str(time_str.substr(time_str.find(':')+1));
		int tmp_s;
		ss >> tmp_s;
		time_s += tmp_s;

		Song toAdd;
		toAdd.title = title;
		toAdd.time = time_s;
		toAdd.track = track_num;

		//if artist doesnt exist, add them
		if(artists.find(artist_str) == artists.end())
		{
			Artist artist_tmp;
			artist_tmp.name = artist_str;
			artist_tmp.time = 0;
			artist_tmp.nsongs = 0;
			artists[artist_str] = artist_tmp;
		}

		// if album doesn't exist, add it
		if((artists[artist_str].albums.find(album_str)) == artists[artist_str].albums.end())
		{
			Album album_tmp;
			album_tmp.name = album_str;
			album_tmp.time = 0;
			album_tmp.nsongs = 0;
			artists[artist_str].albums[album_str] = album_tmp;
		}

		// if song doesn't exist, add it
		if((artists[artist_str].albums[album_str].songs.find(track_num)) == artists[artist_str].albums[album_str].songs.end())
		{
			artists[artist_str].albums[album_str].songs[track_num] = toAdd;
			
			// add aggragate data
			artists[artist_str].albums[album_str].time += toAdd.time;
			artists[artist_str].albums[album_str].nsongs += 1;
			artists[artist_str].time += toAdd.time;
			artists[artist_str].nsongs += 1;
		}

	}

	map<string, Artist>::iterator it;
	map<string, Album>::iterator it2;
	map<int, Song>::iterator it3;

	for(it = artists.begin(); it != artists.end(); it++)
	{
		
		cout << it -> first << ": " << it->second.nsongs << ", " << seconds_to_mmss(it->second.time) << '\n';

		for(it2 = it -> second.albums.begin(); it2 != it -> second.albums.end(); it2++)
		{
			cout << "        " << it2 -> first << ": " << it2->second.nsongs << ", " << seconds_to_mmss(it2->second.time) << '\n';

			for(it3 = it2 -> second.songs.begin(); it3 != it2 -> second.songs.end(); it3++)
			{
				cout << "                " << it3 -> first << ". " << it3 -> second.title << ": " << seconds_to_mmss(it3 -> second.time) << '\n';
			}
		}

	}
	fin.close();
	return 0;
}

/*
 * borrowed heavily from stackoverflow post called "How to replace all occurances of 
 * a character in string?" for this function and idea
 */
string replace_w_spaces(string mutate, string to){
	for (unsigned int i = 0; i < mutate.length(); i++){
		if (mutate[i] == '_'){ 
			mutate.replace(i, 1, to);
		}
	}
	return mutate;
}

string seconds_to_mmss(int time){

	int minute = time / 60;
	int second = time % 60;
	string time_str;

	// found to_string on c++ stl reference
	if(second < 10)
	{
		time_str = to_string(minute) + ":0" + to_string(second);
	}
	else
	{
		time_str = to_string(minute) + ":" + to_string(second);
	}

	return time_str;
	
}
