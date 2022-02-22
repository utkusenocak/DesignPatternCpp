#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Journal
{
	string title;
	vector<string> entries;

	Journal(const string& title) : title(title) {}
	void add_entry(const string& entry) {
		static int count = 1;
		entries.push_back(to_string(count++) + ": " + entry);
	}
};

struct PersistanceManager
{
	static void save(const Journal& j, const string& filename) {
		ofstream ofs(filename);
		for (auto& e : j.entries) {
			ofs << e << endl;
		}
		ofs.close();
	}
};

int main() {
	struct Journal journal("Dear Diary");
	journal.add_entry("I ate a bug");
	journal.add_entry("I cried today");

	PersistanceManager::save(journal, "jounal.txt");
	return 0;
}