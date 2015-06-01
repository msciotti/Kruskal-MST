
void initial(vector<set<int> >& sos, int n){
	int i;
	sos.clear();
	for (i = 0; i < n; i++){
		set<int> nextSet;
		nextSet.insert(i);
		sos.push_back(nextSet);
	}
}
// http://msdn.microsoft.com/en-us/library/wx2e62zc.aspx
template <typename C, class T>
bool findit(const C& c, T val) {
	//cout << "Trying find() on value " << val << endl;
	auto result = c.find(val);
	return (result != c.end());
}

vector<set<int>>::iterator findSet(vector<set<int> >& sos, int i){
	vector<set<int>>::iterator it;
	//cout << "Looking for set with element " << i << "....";
	for (it = sos.begin(); it != sos.end(); it++)
		if (findit(*it, i)){
		//cout << " found it\n";
		return it;
		}
	cout << "ERROR...didn't find what we were looking for: " << i << "\n";
	return it;
}

//With respect to efficiency, compare this merge to a merge using other set implementations
void merge(vector<set<int>> & sos, vector<set<int>>::iterator pit,
	vector<set<int>>::iterator qit){
	set<int> & first = *pit, second = *qit;
	first.insert(second.begin(), second.end());
	sos.erase(qit);
}
inline bool equal(vector<set<int>>::iterator pit,
	vector<set<int>>::iterator qit){
	return (pit == qit);
}
