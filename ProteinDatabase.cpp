#include <iostream>
#include <fstream>
#include <string>
#include "ProteinDatabase.h"

using namespace std;
namespace seneca
{
	ProteinDatabase::ProteinDatabase(const string file) : m_protein(nullptr) {
		std::ifstream in(file);
		if (!in) {
			std::cerr << "Cannot open file: " << file << std::endl;
			return;
		}

		std::string line;
		while (std::getline(in, line)) {
			if (line[0] == '>') {
				m_numStored++;
			}
		}
		m_protein = new std::string[m_numStored];

		// Read the file again to store the protein sequences
		in.clear();
		in.seekg(0);

		size_t currentIndex = 0;
		std::string currentProtein;
		while (std::getline(in, line)) {
			if (line[0] == '>') {
				if (!currentProtein.empty()) {
					m_protein[currentIndex++] = currentProtein;
					currentProtein.clear();
				}
			}
			else {
				currentProtein += line;
			}
		}

		if (!currentProtein.empty()) {
			m_protein[currentIndex++] = currentProtein;
		}
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& other)
	{
		m_protein = new string[other.m_numStored];
		for (size_t i = 0; i < other.m_numStored; i++)
		{
			m_protein[i] = other.m_protein[i];
		}
		m_numStored = other.m_numStored;
	}

	ProteinDatabase::~ProteinDatabase()
	{
		delete[] m_protein;
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& source)
	{
		if(this != &source)
		{
			delete[] m_protein;
			m_protein = new string[source.m_numStored];
			for (size_t i = 0; i < source.m_numStored; i++)
			{
				m_protein[i] = source.m_protein[i];
			}
			m_numStored = source.m_numStored;
		}
		return *this;
	}

	//Move constructor
	//ProteinDatabase::ProteinDatabase(ProteinDatabase&& source) 
	//{
	//	*this = move(source);
	//}
	ProteinDatabase::ProteinDatabase(ProteinDatabase&& source): m_protein(source.m_protein), m_numStored(source.m_numStored) {
		source.m_protein = nullptr;
		source.m_numStored = 0;
	}

	//Move assignment operator
	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& source) 
	{
		if(this != &source)
		{
			delete[] m_protein;
			//shallow copy
			m_numStored = source.m_numStored;
			source.m_numStored = 0;

			m_protein = source.m_protein;
			source.m_protein = nullptr;
		
		}
		return *this;
	}

	size_t ProteinDatabase::size() const
	{
		return m_numStored;
	}
	std::string ProteinDatabase::operator[](size_t i) const
	{
		return (i < m_numStored && m_protein != nullptr) ? m_protein[i] : "";
	}
}