#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
using namespace std;

enum class Relationship
{
	parent,
	child,
	sibling
};

struct Person
{
	string name;
};

struct RelationshipBrowser
{
	virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser
{
	vector<tuple<Person, Relationship, Person>> relations;

	void add_parent_and_child(const Person& parent, const Person& child) {
		relations.push_back({ parent, Relationship::parent, child });
		relations.push_back({ child, Relationship::child, parent });
	}

	vector<Person> find_all_children_of(const string& name) {
		vector<Person> result;
		for (auto& [first, rel, second] : relations) {
			if (first.name == name && rel == Relationship::parent)
			{
				result.push_back(second);
			}
		}
		return result;
	}
};

struct Research
{
	Research(RelationshipBrowser& browser)
	{
		for (auto& child : browser.find_all_children_of("John"))
		{
			cout << "John has a child called " << child.name << endl;
		}
	}
};

int main() {
	struct Person parent{ "John" };
	struct Person child{ "Chris" }, child2{ "Matt" };

	Relationships relationships;
	relationships.add_parent_and_child(parent, child);
	relationships.add_parent_and_child(parent, child2);

	Research _(relationships);
	return 0;
}