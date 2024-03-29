#include <iostream>
using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++) {
		A[i] = '\0';
	}
}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) {
		B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

// return length of a given string A
int stringLength(const char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

// used to find if an input starts with a URL signature
bool startsWith(char* input, const char* comparator)
{
	int length = stringLength(comparator);
	if (stringLength(input) < length) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if (input[i] != comparator[i]) {
			return false;
		}
	}
	return true;
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;
	int size;
	void strCpy (char* A, char* B, int n);
public:
	myString ();
	myString(char* inpStr);
	myString (myString& B);
	bool findMax(myString& A, myString& B);
	int Size();
	char* getWord();
	bool operator == (myString& B);
	bool operator > (myString& B);
	bool operator < (myString& B);
	myString& operator = (myString& B);
	myString& operator = (char* B);
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// copy a given string
void myString::strCpy(char* A, char* B, int n)
{
	for (int i = 0; i < n; i++) {
		B[i] = A[i];
	}
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0')
		i++;
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j=0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy (B.strArray, size, strArray);
}

char* myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size () {
	return size;
}

 // overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
	 
	if (B == NULL) return *this;
	// get size of array passed in
	size = stringLength(B);
	strArray = new char[size];

	//delete contents of current array
	emptyString(strArray, size + 1);

	for (int j = 0; j < size; j++)
		strArray[j] = B[j];

	return *this;
	
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {

	
	strArray = NULL;
	size = B.Size();
	strArray = new char[size];
	emptyString(strArray, size + 1);
	strCpy( B.getWord(), strArray, size);
	
	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	if (B.Size() != this->Size()) {
		return false;
	}
	for (int i = 0; i < this->Size(); i++) {
		if (strArray[i] != B.getWord()[i]) {
			return false;
		}
	}
	return true;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {

	int smallestSize;
	if (size <= B.Size()) {
		smallestSize = size;
	}
	else {
		smallestSize = B.Size();
	}
	for (int i = 0; i < smallestSize; i++) {
		if (this->getWord()[i] < B.getWord()[i]) {
			return true;
		}
		if (this->getWord()[i] > B.getWord()[i]) {
			return false;
		}
		// if we are at the end of the smallest array and B.size is greater than size, then A is less than B, return true
		if (i == (smallestSize - 1)) {
			if (B.Size() > size) {
				return true;
			}
		}
	}
	return false;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {

	int smallestSize;
	if (size <= B.Size()) {
		smallestSize = size;
	}
	else {
		smallestSize = B.Size();
	}

	for (int i = 0; i < smallestSize; i++) {
		
		if (this->getWord()[i] > B.getWord()[i]) {
			
			return true;
		}
		if (this->getWord()[i] < B.getWord()[i]) {
			return false;
		}
		// if we are at the end of the smallest array and B.size is greater than size, then A is less than B, return false
		if (i == (smallestSize - 1)) {
			if (B.Size() > size) {
				return false;
			}
		}
	}
	return false;

}

// get one URL from redirected input and return it as a string
char* getNextURL () {
	char* str = new char[75]; //assumes a max URL size of 50
	emptyString (str, 75);

	int dollarCount = 0;
	char c;
	int i = 0;

	//read until the next white space or line-break 
		while (!cin.eof()) {
			cin.get(c);
			if (!cin.eof()) {
				if ((c != '\n') && (c != ' ')) {
					if (((c >= 'a') && (c <= 'z')) ||
						((c >= 'A') && (c <= 'Z')) ||
						((c >= '0') && (c <= '9')) ||
						(c >= ':') || (c >= '/') || (c >= '.') || (c >= '_'))
						str[i++] = c;
				}
				else if (((c == '\n') || (c == ' ')) && (i > 0)) {
					const char* http = "http://";
					const char* https = "https://";
					if ((startsWith(str, http) || startsWith(str, https))) {
						return str;
					}
					else {
						emptyString(str, 75);	
					}
					i = 0;
				}
				if (c == '$') dollarCount++;
				if (c != '$' && dollarCount > 0) dollarCount = 0;
				if (dollarCount == 4) {
					break;
				}
			}
		}
		return NULL;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class setOfURLs {
private:
	int binarySearchAndInsert (myString& u);
	int binarySearch(myString& wordToFind, int start, int end);
	//int binarySearch(myString& key, int top, int mid, int bottom);
	int removeBinarySearch(myString& word, int start, int end);
protected:
	myString* _URLs;
	int* _frequencies;
	int _size;

public:
	setOfURLs ();
	setOfURLs (int numOfWords);

	myString* get_Words();
	int* get_Freq();
	int get_size();

	void setSize(int i);

	void addURL (myString& u);//insert word w into the array _URLs - keep it sorted alphabetically
	void unsortedAddURL(myString& u);
	void sortFreq(); //sort words array based on frequency
	void sortURLs(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	setOfURLs* removeURLs(myString* URLsToFilterOut, int numURLsToFilterOut); //URLsToFilterOut from _URLs array
	~setOfURLs();
};

// default constructor - initializes with no words
setOfURLs::setOfURLs()
{
	_URLs = new myString[0];
	_frequencies = new int[0];
	_size = 0;

}

// non default constructor - initializes with a known number of words
setOfURLs::setOfURLs (int numOfWords)
{
	_size = numOfWords;
	_URLs = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

myString* setOfURLs::get_Words()
{
	return _URLs;
}

int* setOfURLs::get_Freq()
{
	return _frequencies;
}

int setOfURLs::get_size()
{
	return _size;
}

void setOfURLs::setSize(int i)
{
	_size = i;
}

// print the bag of words in dictionary format
void setOfURLs::display()
{
	cout << "mySetOfURLs: " << _size << " " << endl;
	for (int i = 0; i < _size; i++) {
		cout << get_Words()[i] << ": " << _frequencies[i] << endl;
	}
}

// sort the _URLs and _frequencies based on frequencies
void setOfURLs::sortFreq()
{
	sortURLs();
	myString urlTemp;
	int freqTemp;

	//selection sort
	for (int i = 0; i < _size; i++) {

		for (int j = i + 1; j < _size; j++) {

			if (_frequencies[i] > _frequencies[j]) {

				urlTemp = _URLs[i].getWord();
				freqTemp = _frequencies[i];

				_URLs[i] = _URLs[j].getWord();
				_frequencies[i] = _frequencies[j];

				_URLs[j] = urlTemp.getWord();
				_frequencies[j] = freqTemp;
			}
			if (_frequencies[i] == _frequencies[j]) {
				if (_URLs[i] > _URLs[j]) {
					urlTemp = _URLs[i].getWord();
					freqTemp = _frequencies[i];

					_URLs[i] = _URLs[j].getWord();
					_frequencies[i] = _frequencies[j];

					_URLs[j] = urlTemp.getWord();
					_frequencies[j] = freqTemp;
				}
			}
		}
	}
}

// sort the _URLs and _frequencies, alphabetically
void setOfURLs::sortURLs()
{
	//selection sort
	myString urlTemp;
	int freqTemp;

	for (int i = 0; i < _size; i++) {
		
		for (int j = i + 1; j < _size ; j++) {

			if (_URLs[i] > _URLs[j]) {

				urlTemp = _URLs[i].getWord();
				freqTemp = _frequencies[i];
				
				_URLs[i] = _URLs[j].getWord();
				_frequencies[i] = _frequencies[j];

				_URLs[j] = urlTemp.getWord();
				_frequencies[j] = freqTemp;
			}	
		}
	}
}

setOfURLs* setOfURLs::removeURLs(myString* URLsToFilterOut, int numURLsToFilterOut)
{
	//create arrays of new size;
	int tempSize = (get_size() - numURLsToFilterOut);
	myString* tempURLs = new myString[tempSize];
	int* tempFreq = new int[tempSize];
	
	int newIndex = 0;
	bool shouldAdd = true;

	for (int i = 0; i < get_size(); i++) {
		shouldAdd = true;

		// if the current URL value is contained in the filter out array, we don't add it to the new array
		for (int j = 0; j < numURLsToFilterOut; j++) {
			if (_URLs[i] == URLsToFilterOut[j]) {
				shouldAdd = false;
			}
		}

		if (shouldAdd == true) {
			tempURLs[newIndex] = _URLs[i];
			tempFreq[newIndex] = _frequencies[i];
			newIndex++;
		}
	}

	// assign arrays new values
	_URLs = tempURLs;
	_frequencies = tempFreq;

	// decrement size
	_size -= numURLsToFilterOut;
	sortURLs();

	return this;
}

setOfURLs::~setOfURLs()
{
	_size = 0;
	delete[] _URLs;
	delete[] _frequencies;
	
}

// to search for a given word in _URLs - returns 0 if not found, 1 if found
int setOfURLs::binarySearchAndInsert (myString& wordToFind)
{
	int result = binarySearch(wordToFind, 0, _size);

	// if not found, return 0
	if (result != -1) { 
		_frequencies[result]++;
		return 1;
		
	}
	// if found, increment frequencies and return 1
	else {
		return 0;
	}
}

int setOfURLs::binarySearch(myString& wordToFind, int start, int end)
{
	int left = 0;
	int right = _size - 1;
	int m = (left + right) / 2;

	while (left <= right) {
		
		if (_URLs[m] < wordToFind) {
			left = m + 1;
		}
		else if (_URLs[m] > wordToFind) {
			right = m -1;
		}
		else {
			return m;
		}
		m = (left + right) / 2;

	}
	return -1;

}

// method to add words to the setOfURLs object
void setOfURLs::addURL(myString & newWord)
{
	// if it's false, ie. 0, then we want to add the word to the end of the array.
	if (binarySearchAndInsert(newWord) == 0) {
		_size++;
		myString* newURLs = new myString[_size];
		int* newFreq = new int[_size];

		for (int i = 0; i < _size - 1; i++) {
			newURLs[i] = _URLs[i];
			newFreq[i] = _frequencies[i];
		}

		newURLs[_size - 1] = newWord;
		newFreq[_size - 1] = 1;
		
		_URLs = new myString[_size];
		_frequencies = new int[_size];

		_URLs = newURLs;
		_frequencies = newFreq;
	}
	if (_size > 1) {
		sortURLs();
	}	
}

void setOfURLs::unsortedAddURL(myString& newWord)
{
	_size++;
	myString* newURLs = new myString[_size];
	int* newFreq = new int[_size];

	for (int i = 0; i < _size - 1; i++) {
		newURLs[i] = _URLs[i];
		newFreq[i] = _frequencies[i];
	}

	newURLs[_size - 1] = newWord;
	newFreq[_size - 1] = 1;

	_URLs = new myString[_size];
	_frequencies = new int[_size];

	_URLs = newURLs;
	_frequencies = newFreq;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class URLLinks : setOfURLs{

	friend ostream& operator << (ostream& s, URLLinks& A);
protected:
	myString URL;
	int numLinks;
	URLLinks** hyperLinks;
	setOfURLs setOfSites;

public:
	URLLinks();
	URLLinks(myString& x, int n);
	~URLLinks();
	int getNumLinks();
	URLLinks* getHyperLink(int i);
	myString& getURL();
	void addSite(myString& t);
	void addNeighbor(URLLinks& link);
	void setNeighbors(int nei);
	int getSetOfSitesSize();
	myString* get_Words();
};

ostream& operator << (ostream& s, URLLinks& A)
{
	cout << A.URL << ":" << endl;
	for (int i = 0; i < A.numLinks; i++) {
		cout <<"** " << A.getHyperLink(i)->getURL() << endl;
	}
	return s;
}

URLLinks::URLLinks()
{
	myString* urlFiller = new myString();
	URL = *urlFiller;
	numLinks = 0;
	hyperLinks = NULL;
	setOfSites = *new setOfURLs();
}

URLLinks::URLLinks(myString& x, int n)
{
	URL = x;
	numLinks = 0;
	hyperLinks = NULL;
	setOfSites = *new setOfURLs();
}

myString& URLLinks::getURL()
{
	return URL;
}

int URLLinks::getNumLinks()
{
	return numLinks;
}

URLLinks* URLLinks::getHyperLink(int i)
{
	return hyperLinks[i];
}

URLLinks::~URLLinks()
{
	URL = NULL;
	numLinks = 0;
	delete[] hyperLinks;
}

void URLLinks::addSite(myString& t)
{
	setOfSites.unsortedAddURL(t);
	
}

void URLLinks::setNeighbors(int nei)
{
	hyperLinks = new URLLinks*[nei];
}

int URLLinks::getSetOfSitesSize()
{
	return setOfSites.get_size();
}

myString* URLLinks::get_Words()
{
	return setOfSites.get_Words();
}

void URLLinks::addNeighbor(URLLinks& link)
{
	hyperLinks[numLinks] = &link;
	numLinks++;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {

	int numURLsToFilterOut;
	char* url;
	myString* urlString;
	int numPages;
	int pageNo;
	int numNeighbors;
	int neighbor;

    //read the first number from the file that contains the number of stop words
	cin >> numURLsToFilterOut;
	cout << "Number of Stop words: " << numURLsToFilterOut << endl;
	myString* URLsToFilterOutList = new myString[numURLsToFilterOut];

	//read the stop words
	for (int i=0; i < numURLsToFilterOut; i++)
	{
		url = getNextURL ();
		URLsToFilterOutList[i] = url; //calls the overloaded = operator on myString class
	}

	//Now read a text and put them in the setOfURLs instance.
	setOfURLs* mySetOfURLs = new setOfURLs ();

	url = getNextURL (); 

	while (url != NULL)
	{
		urlString = new myString (url); //create a myString object with the URL
		(*mySetOfURLs).addURL(*urlString); //add URL to mySetOfURLs
		url = getNextURL ();	 
	}

	// this should display the URL and frequency;
	// note that becuase you are using binary search and insert the URLs will
	// be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*mySetOfURLs).display ();

	(*mySetOfURLs).sortFreq ();
	cout << endl;
	cout << "mySetOfURLs - Sorted based on frequency:" << endl;
	(*mySetOfURLs).display ();

	(*mySetOfURLs).sortURLs();
	cout << endl;
	cout << "mySetOfURLs - Sorted alphabetically:" << endl;
	(*mySetOfURLs).display ();

	setOfURLs* newSetOfURLs = (*mySetOfURLs).removeURLs(URLsToFilterOutList, numURLsToFilterOut); // new parameter added here
	cout << endl;
	cout << "newSetOfURLs - Sorted alphabetically:" << endl;
	(*newSetOfURLs).display();

	(*newSetOfURLs).sortFreq ();
	cout << endl;
	cout << "newSetOfURLs - Sorted based on frequency:" << endl;
	(*newSetOfURLs).display ();

	cin >> numPages;
	cout << endl << "Number of websites: " << numPages << endl;

	//construct an array to hold all of the URLLinks objects
	URLLinks* myLinkStructure = new URLLinks[numPages];

	// read all URL and store them in the myLinkStructure array of URLLink objects
	for (int i = 0; i < numPages; i++)
	{
		myString* nextURL = new myString(getNextURL());
		URLLinks* current = new URLLinks(*nextURL, 0);
		int size_URLLinks_bytes = sizeof(myLinkStructure[0]);
		memcpy(&myLinkStructure[i], current, size_URLLinks_bytes);
	}

	 //store the neighbours/hyperlinks
	for (int i = 0; i < numPages; i++)
	{
		 //read in the id and the amount of neighbors it has
		cin >> pageNo >> numNeighbors;
		
		// setNeighbors just allocates the space for the horizontal hyperLinks arrays
		myLinkStructure[i].setNeighbors(numNeighbors);

		for (int j = 0; j < numNeighbors; j++)
		{
			// read in the id of the neighbor
			cin >> neighbor;
			// addNeighbor adds the neighbors one at a time
			myLinkStructure[pageNo].addNeighbor((myLinkStructure[neighbor]));

			// we add the current URLLink URL to the neighbor's setOfSites
			myLinkStructure[neighbor].addSite(myLinkStructure[pageNo].getURL());
		}
	}

	//// display all URLLink objects using the overloaded << operator
	cout << endl << "~~~Webpages and the links they contain:" << endl;
	for (int i = 0; i < numPages; i++) {
		cout << myLinkStructure[i] << endl;
	}
	
	cout << "~~~~~Webpages contained as hyperLinks:" << endl;
	for (int i = 0; i < numPages; i++) {
		cout << myLinkStructure[i].getURL() << ": " << myLinkStructure[i].getSetOfSitesSize() << endl;
		for (int j = 0; j < myLinkStructure[i].getSetOfSitesSize(); j++) {
			cout << "** " << myLinkStructure[i].get_Words()[j] << endl;
		}
		cout << endl;
	}

	delete [] URLsToFilterOutList;
	delete mySetOfURLs;
	delete[] myLinkStructure;

	return 0;
}