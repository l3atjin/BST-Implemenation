#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include "csvstream.h"
#include <map>
#include <istream>
#include <set>
#include <vector>

using namespace std;

class Classifier
{
private:
	map<string, set<string>> posts;
	int num_posts;
	set<string> words;

public:
	Classifier(map<string, set<string>> posts_in, int count_in, set<string> words_in)
		: posts(posts_in), num_posts(count_in), words(words_in) {}

	/*void print()
	{
		for (auto it : input) {
			auto tag = it.first; //key
			auto content = it.second; //value
			set<string> temp;
			temp = unique_words(content);
			cout << tag << " " << content << "\n";
			cout << "Vocab size: " << temp.size() << endl;
		}
		cout << "Num of Posts: " << num_posts << endl;
		cout << "Num of uniqie words: " << words.size() << endl;

		for (int i = 0; i < num_posts; i++)
		{
			cout << "Post " << i << endl;
			for (auto it = posts.at(i).begin(); it != posts.at(i).end(); it++)
			{
				cout << *it << " ";
			}
			cout << endl;
		}
	}

	int numPostsWord(string str)
	{
		int count = 0;
		for (int i = 0; i < num_posts; i++)
		{
			if (posts.at(i).find(str) != posts.at(i).end())
			{
				count++;
			}
		}
		return count;
	}

	int numPostsLabel(string str)
	{
		int count = 0;
		for (int i = 0; i < num_posts; i++)
		{
			if (posts.at(i).find(str) != posts.at(i).end())
			{
				count++;
			}
		}
		return count;
	}*/

	set<string> unique_words(const string& str) {
		// Fancy modern C++ and STL way to do it
		istringstream source{ str };
		return { istream_iterator<string>{source},
				istream_iterator<string>{} };
	}

};

set<string> unique_words(const string& str) {
	// Fancy modern C++ and STL way to do it
	istringstream source{ str };
	return { istream_iterator<string>{source},
			istream_iterator<string>{} };
}

int main(int argc, char* argv[])
{
	/*if (argc > 3)
	{
		if (argc == 4 && argv[3] != "--debug")
		{
			cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
			return 1;
		}
		cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
		return 1;
	}*/
	cout.precision(3);

	map<string, string> words;

	csvstream trainIn(argv[1]);
	//csvstream testIn(argv[2]);

	set<string> uniqueWords;
	vector<string> labels;

	map<string, set<string>> posts;
	while (trainIn >> words)
	{
		cout << words["tag"] << endl;
		set<string> temp = unique_words(words["content"]);
		string temp1 = words["tag"];
		posts.insert({ temp1, temp });
		for (auto it = temp.begin(); it != temp.end(); it++)
		{
			uniqueWords.insert(*it);
		}
	}

	Classifier classifier(posts, posts.size(), uniqueWords);

	for (auto it = posts.begin(); it != posts.end(); it++)
	{
		cout << *it["euchre"] << " ";
	}

	//classifier.print();





	/*if (!trainIn)

	{
		cout << "Error opening file: " << argv[1] << endl;
		return 1;
	}
	else if (!testIn)
	{
		cout << "Error opening file: " << argv[2] << endl;
		return 1;
	}*/
}