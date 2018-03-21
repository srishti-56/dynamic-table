#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Node of suffix tree
class Node {


	public:		
		int nodeIdentifier;
		int startIndex;
		void initialize_node(int num);

		std::map<char, int> children;			//key is input character, value is nodeIdentifier number
};



// Functions

//Text processing 
void parseFile();
int writeStoryTitles(const std::string *str, int storyCount);
int writeSentence(const std::string str);

//Construction
void create();
int addChildNode(int parent_node, char ele);
void addRootNode();

/*

class Node {

	public:
		int pathFromRoot;
		int nodeEnd;
		int nodeStart;
		int suffixIndex;
		std::vector<int> title;
		int isFullStop;
		Node *prevFullStop;
		Node *parent;
		std::vector<Node> **children;
		std::map< char, int>  map;

};

*/

