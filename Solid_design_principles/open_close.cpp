#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum class Color
{
	red,
	green,
	blue
};

enum class Size
{
	small,
	medium,
	large
};

struct Product
{
	string name;
	Color color;
	Size size;
};

struct ProductFilter
{
	static vector<Product*> by_color(vector<Product*> items, Color color) {
		vector<Product*> result;
		for (auto& i : items) {
			if (i->color == color) {
				result.push_back(i);
			}
		}
		return result;
	}

	static vector<Product*> by_size(vector<Product*> items, Size size) {
		vector<Product*> result;
		for (auto& i : items) {
			if (i->size == size) {
				result.push_back(i);
			}
		}
		return result;
	}
};

template <typename T>
struct Specification
{
	virtual bool is_satisfied(T* item) = 0;
};

template <typename T>
struct Filter
{
	virtual vector<T*> filter(const vector<T*> items, struct Specification<T>& spec) = 0;
};

template <typename T>
struct andSpecification : Specification<T>
{
	Specification<T>& first;
	Specification<T>& second;
	andSpecification(Specification<T>& first, Specification<T>&second) : first(first), second(second) {}
	bool is_satisfied(T* item) {
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

struct BetterFilter : Filter<Product>
{
	static vector<Product*> filter(const vector<Product*> items, struct Specification<Product>& spec) {
		vector<Product*> result;
		for (const auto& i : items) {
			if (spec.is_satisfied(i)) {
				result.push_back(i);
			}
		}
		return result;
	}
};

struct ColorSpecification : Specification<Product>
{
	Color color;
	ColorSpecification(Color color) : color(color) {}
	bool is_satisfied(Product* item) {
		return item->color == color;
	}
	
};

struct SizeSpecification : Specification<Product>
{
	Size size;
	SizeSpecification(Size size) : size(size) {}
	bool is_satisfied(Product* item) {
		return item->size == size;
	}
};

int main() {
	struct Product apple { "Apple", Color::green, Size::small };
	struct Product tree { "Tree", Color::green, Size::large };
	struct Product house { "House", Color::blue, Size::large };

	vector<Product*> items{ &apple, &tree, &house };
	ColorSpecification green(Color::green);
	for (auto& item : BetterFilter::filter(items, green)) {
		cout << item->name << " is green" << endl;
	}
	SizeSpecification large(Size::large);
	andSpecification<Product> greenAndLarge(green, large);
	for (auto& item : BetterFilter::filter(items, greenAndLarge)) {
		cout << item->name << " is green and large" << endl;
	}
	return 0;
}