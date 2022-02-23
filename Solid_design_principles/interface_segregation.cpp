#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Document;

struct IPrinter
{
	virtual void print(Document& doc) = 0;
};

struct IScanner
{
	virtual void scan(Document& doc) = 0;
};

struct IFax
{
	virtual void fax(Document& doc) = 0;
};

struct Scanner : IScanner
{
	void scan(Document& doc) {

	}
};

struct Printer : IPrinter
{
	void print(Document& doc) {
		
	}
};

struct IMachine : IPrinter, IScanner {};

struct Machine : IMachine
{
	IPrinter& printer;
	IScanner& scanner;
	Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {}

	void print(Document& doc) {
		printer.print(doc);
	}

	void scan(Document& doc) {
		scanner.scan(doc);
	}
};

int main() {

	return 0;
}