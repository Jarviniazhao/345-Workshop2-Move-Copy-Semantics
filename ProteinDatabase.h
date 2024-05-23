#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

namespace seneca
{
	class ProteinDatabase
	{
		std::string* m_protein;
		size_t m_numStored {};
	public:
		ProteinDatabase() : m_protein{} {};
		ProteinDatabase(const std::string);

		ProteinDatabase(const ProteinDatabase&);
		~ProteinDatabase();
		ProteinDatabase& operator=(const ProteinDatabase&);

		//Move constructor
		ProteinDatabase(ProteinDatabase&&);
		//Move assignment operator
		ProteinDatabase& operator=(ProteinDatabase&&);

		size_t size() const;
		std::string operator[](size_t) const;
	};

}


#endif
