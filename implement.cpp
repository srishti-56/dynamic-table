#include <fstream>
#include <sstream>
#include "header.h"
using namespace std;

// Global variables for suffix tree
int globalIndex;
int activeNode = 0;
int activeEdge = -1;
int activeLength = 0;	
int remainder = 1;
int nodeCount = 0; 			//increment while creating nodes

// Global array of nodes (suffix tree array)
std::vector<Node*> globalPointers;




// --------------------		Testing function 	 --------------------------------
void create(){

	string str = "t him.  ";
	/*for( char x : str){
		cout << (int) x << x << endl;
	}*/

	int n;
	cout << "Calling addNode() \n ";
	addRootNode();
	addChildNode(0, 'r');
	addChildNode(0, 'q');
	addChildNode(0,'a');

	for(int i = 0; i<nodeCount; i++){
		cout << "\n Node " << globalPointers[i]->nodeIdentifier;
	}
	//int children_count = globalPointers[0]->children.size();

	cout << endl;
}


// --------------------		Construct tree 	 --------------------------------

//Initializes a node in the tree
void Node::initialize_node(int num){

	//if(num != 0)			//not root
	this->nodeIdentifier = num;
	cout << "\n Created node " << nodeIdentifier << " successfully\n";

}

/*int to_insert(char ele){




}*/


//Interface function
void addRootNode(){
	cout << "Add root node \n";
	Node *obj = new Node;
	globalPointers.push_back(obj);
	obj->initialize_node(nodeCount);
	cout << "\n Node nodeIdentifier value is  " << globalPointers[nodeCount]->nodeIdentifier << " - Root \n";
	nodeCount++;

}

int addChildNode(int parent_node, char ele){
	// Create new node 
	Node *obj = new Node;
	// Add to global suffix array
	globalPointers.push_back(obj);
	// Initialize node with information
	obj->initialize_node(nodeCount);
	cout << "\n Node nodeIdentifier value is  " << globalPointers[nodeCount]->nodeIdentifier << " .";
	//Add information to parent
	globalPointers[parent_node]->children[ele] = globalPointers[nodeCount]->nodeIdentifier;

	// Increment node count to access later
	nodeCount++;

	//return(1);*/

}









// ---------------------	 Text processing	 --------------------------------

//Parse Input
void parseFile(){

	const char NEWLINE = 32;

	int storyNumber = 0;
	int titleFlag = 2;
	int endFlag = 0;         //If full stop, question mark, exclamation mark --> indicates end of sentance				
	int sentenceFlag = 0;
	int firstTitle = 1;
	int currStory = 0;
	string storyArray[350];

	//Open file
	ifstream storyFile;
	storyFile.open("AesopTalesTest.txt");

	while(!storyFile.eof()){
		string data, temp, title, sentence;
		sentence = "";

		//Get Line to fullStop
		while(std::getline(storyFile, data, '.') ){
			//Append lost fullStop
			data.append(".");
			std::stringstream ss(data);
			int v = 0;

			//cout << data << " : FULLSTOP" << endl;
			//cout << endl << data << ":are you empty " << endl << endl;
			//cout << "Parse sub text : " << endl << endl;

			//Get each line in fullStop line
			while( std::getline(ss, temp, '\n') ){

				sentenceFlag = 1;
				//cout << temp << " : " << " NEWLINE " << endl;

				if( temp.empty() || firstTitle == 1 || !(temp.find_first_not_of(' ') != std::string::npos)){
					
					if(firstTitle == 1){
						cout << temp << " : TITLE" << endl << endl;
						firstTitle = 0;
						sentenceFlag = 0;
						currStory++;
						storyArray[currStory] = temp;
						
					}

					else { 
						getline(ss, temp, '\n');
						v++;
						//first line
						//cout << temp << " v is : " << v << " should be 1. NEWLINE " << endl;

						if(temp.empty() || !(temp.find_first_not_of(' ') != std::string::npos)){
							getline(ss, temp, '\n');

							v++;
							//second line
							//cout <<  temp << " v is : " << v << " should be 2. NEWLINE " << endl;

						//cout << title << " : interMed TITLE" << endl << endl;
						}						
						
						if(temp.empty() || !(temp.find_first_not_of(' ') != std::string::npos)){
							getline(ss, temp, '\n');
							v++;
							//third line
							//cout << temp << " v is : " << v << " should be 3. NEWLINE " << endl;

						}
												
						if(v >= 2){
							while(temp.empty() || !(temp.find_first_not_of(' ') != std::string::npos))
								getline(ss,temp, '\n');

								cout << temp << " : TITLE" << endl << endl;
								currStory++;
								storyArray[currStory] = temp;
								v = 0;
								//cout << "\n\n\n\n Sentence up till now \n  :" << sentence << "\n\n";
								sentenceFlag = 0;
							}
						else{
							sentenceFlag = 1;
							v=0;
						}
					}
				}

				//If not a title, must be sentences
       			if(sentenceFlag == 1) {
       				v = 0;
       				//cout << "Checkif empty: " << temp << "-------" << endl << endl;

					if(temp.find_first_not_of(' ') != std::string::npos){
						// There's a non-space.
	       				//cout << "appending : ";
						sentence.append(temp);
	       				//cout << sentence << " : SENTENCE" << endl;
	       				//cout << temp <<  " fullstop string " << endl; 
	       				//sentence.erase(sentence.find_last_of('.'));
	       				if(temp.find_last_of('.') <= temp.length()){
							endFlag =1;
							//cout << "\nWHERE" << temp.find_last_of('.') << " : " << temp.length() << "\n";
							sentence.back();
							sentence.back();
						} 
						else{
							sentence.append(" ");

						}

       				}
       				sentenceFlag = 0;
       			}
       		}       			
		}

		int y = writeSentence(sentence);
    	if(y == 0)
    		cout << "Fail";
    	else 
    		cout << "Success!:)";
    }

    int x = writeStoryTitles(storyArray, currStory);
    if(x == 0)
    	cout << "Fail";
    else 
    	cout << "Success!:)";
}


//Save story titles
int writeStoryTitles(const std::string *str, int storyCount){

	ofstream storyTitles ("storyTitles.txt");
	if (storyTitles.is_open()){
		for(int i = 1; i<=storyCount; i++)
			storyTitles << i << ". " << str[i] << "\n" ;
	    storyTitles.close();
	    return(1);
	 }
	 else {
	 	cout << "Unable to open file";
	 	return 0;
	 }
}

//Write text to file
int writeSentence(const std::string str){

	ofstream storyWords ("storyWords.txt");
	if(storyWords.is_open()){
		storyWords << str << "\n";
		return 1;
	}
	 else {
	 	cout << "Unable to open file";
	 	return 0;
	 }
}