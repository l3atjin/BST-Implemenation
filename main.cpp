#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include "csvstream.h"
#include <map>
#include <istream>
#include <set>
#include <vector>
#include <cstring>

using namespace std;

class Classifier
{
private:
	map<string, set<string>> input;
	set<string> words;
	vector<string> labels;
	vector<set <string>> posts;
	double num_posts;

public:
	Classifier(map<string, set<string>> input_in,
		set<string> words_in, 
		vector<set <string>> posts_in, 
		vector<string> labels_in)
	: input(input_in), words(words_in),
		labels(labels_in), 
		posts(posts_in) {
		num_posts = posts.size();
	}


	int howManyLabel(string &label)
	{
		int count = 0;
		for (unsigned int i = 0; i < labels.size(); i++)
		{
			if (label == labels.at(i))
			{
				count++;
			}
		}
		return count;
	}

	void freqCounter()
	{
		for (auto it = input.begin(); it != input.end(); it++)
		{
			set<string> sett = it->second;
			for (auto i = sett.begin(); i != sett.end(); i++)
			{
				cout << "  " << it->first << ":" << *i
					<< ", count = " << numPostsLabelWord(*i, it->first)
					<< ", log-likelihood = " << probWC(*i, it->first)
					<< endl;
			}
		}
		cout << endl;
	}

	void print(vector<string> &content, vector<string> &tags
	, vector<set<string>> &inPost, set<string> &inLabel)
	{
		int correct = 0;
		int total = 0;
		cout << "test data:" << endl;
		for (unsigned int i = 0; i < content.size(); i++)
		{
			cout << "  correct = " << tags.at(i) << ", predicted = "
				<< predict(inPost.at(i), inLabel).first << ", log-probability score = "
				<< predict(inPost.at(i), inLabel).second << endl;
			cout << "  content = " << content.at(i) << endl;
			cout << endl;
			if (tags.at(i) == predict(inPost.at(i), inLabel).first)
			{
				correct++;
			}
			total++;
		}
		cout << "performance: " << correct << " / " << total
			<< " posts predicted correctly" << endl;
		cout << endl;

	}

	double numPostsWord(string &str)
	{
		double count = 0;
		for (int i = 0; i < num_posts; i++)
		{
			if (posts.at(i).find(str) != posts.at(i).end())
			{
				count++;
			}
		}
		return count;
	}

	double numPostsLabel(string &str)
	{
		double count = 0;
		for (int i = 0; i < num_posts; i++)
		{
			if (labels.at(i) == str)
			{
				count++;
			}
		}
		return count;
	}

	double numPostsLabelWord(string word, string label)
	{
		double count = 0;
		for (int i = 0; i < num_posts; i++)
		{
			if (posts.at(i).find(word) != posts.at(i).end()
				&& labels.at(i) == label)
			{
				count++;
			}
		}
		return count;
	}

	double probC(string label)
	{
		return log(numPostsLabel(label) / labels.size());
	}

	double probWC(string word, string label)
	{
		double num1 = numPostsLabelWord(word, label);
		if (num1 == 0 && words.find(word) != words.end())
		{
			return log(numPostsWord(word) / num_posts);
		}
		else if (words.find(word) == words.end())
		{
			return log(1 / num_posts);
		}
		return log(num1 / howManyLabel(label));
	}

	double finalProb(string label, set<string> &post)
	{
		double sum = 0;
		for (auto it = post.begin(); it != post.end(); it++)
		{
			sum += probWC(*it, label);
		}
		return probC(label) + sum;
	}

	void report()
	{
		set<string> set;
		vector<int> freq;
		int count = 0;
		for (int i = 0; i < num_posts; i++)
		{
			set.insert(labels.at(i));
		}
		for (auto it = set.begin(); it != set.end(); it++)
		{
			for (int i = 0; i < num_posts; i++)
			{
				if (*it == labels.at(i))
				{
					count++;
				}
			}
			freq.push_back(count);
			count = 0;
		}
		cout << "classes:" << endl;
		int i = 0;
		for (auto it = set.begin(); it != set.end(); it++)
		{
			cout << "  " << *it << ", " << freq.at(i)
				<< " examples, log-prior = " << probC(*it) << endl;
			i++;
		}
		cout << "classifier parameters:" << endl;
		freqCounter();
	}

	pair<string, double> predict(set<string> &post, set<string> &labels)
	{
		double probMax = -10000000;
		string correctLabel;
		double prob;
		for (auto it = labels.begin(); it != labels.end(); it++)
		{
			prob = finalProb(*it, post);
			if (prob > probMax)
			{
				probMax = prob;
				correctLabel = *it;
			}
		}
		return { correctLabel, probMax };
	}
};

set<string> unique_words(const string& str) {
	// Fancy modern C++ and STL way to do it
	istringstream source{ str };
	return { istream_iterator<string>{source},
			istream_iterator<string>{} };
}

void printPost(set<string> input)
{
	for (auto it = input.begin(); it != input.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int checkInput(int argc, char* argv[])
{
	string str = "--debug";
	if (argc < 3 || argc > 4)
	{
		cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
		return 1;
	}
	if (argc == 4 && argv[3] != str)
	{
		cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
		return 1;
	}
	return 0;
}


int main(int argc, char* argv[])
{
	if (checkInput(argc, argv) == 1)
		return 1;
	cout.precision(3);
	csvstream trainIn(argv[1]);
	csvstream testIn(argv[2]);
	if (!trainIn){
		cout << "Error opening file: " << argv[1] << endl;
		return 1;
	}
	if (!testIn){
		cout << "Error opening file: " << argv[2] << endl;
		return 1;
	}
	vector<set <string>> posts, inputPosts;
	map<string, string> words;
	map<string, set<string>> map;
	set<string> inputLabels, uniqueWords;
	vector<string> content, tags, labels;
	if (argc == 4)
		cout << "training data:" << endl;
	while (trainIn >> words){
		if (argc == 4){
			cout << "  label = " << words["tag"] << ", content = " << words["content"]
				<< endl;
		}
		string temp1 = words["tag"];
		set<string> temp = unique_words(words["content"]);
		posts.push_back(temp);
		labels.push_back(temp1);	
		if (map.find(words["tag"]) != map.end())
			map.at(words["tag"]).insert(temp.begin(), temp.end());
		else
			map.insert({ words["tag"], temp });
		for (auto it = temp.begin(); it != temp.end(); it++ )
			uniqueWords.insert(*it);
	}
	cout << "trained on " << posts.size() << " examples" << endl;
	if (argc == 4)
		cout << "vocabulary size = " << uniqueWords.size() << endl;
	cout << endl;
	Classifier classifier(map, uniqueWords, posts, labels);
	if (argc == 4)
		classifier.report();
	while (testIn >> words){
		tags.push_back(words["tag"]);
		content.push_back(words["content"]);
		set<string> temp = unique_words(words["content"]);
		inputPosts.push_back(temp);
		string temp1 = words["tag"];
		inputLabels.insert(temp1);
	}
	classifier.print(content, tags, inputPosts, inputLabels);
}