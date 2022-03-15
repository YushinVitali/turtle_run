#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <string.h>

static void ToLower(char& symbol);
static void FillTable(char* str, size_t size,
					  std::unordered_map<char, size_t>& charCountTable);
static void ChangeSymbols(char* str, size_t size,
						  const std::unordered_map<char, size_t>& charCountTable);



void ConvertString(std::string& str) {
	std::unordered_map<char, size_t> charCountTable;

	for(auto& symbol : str) {
		ToLower(symbol);
		charCountTable[symbol] += 1;
	}

	for(auto& symbol : str) {
		symbol = charCountTable[symbol] > 1 ? ')' : '(';
	}
}


void ConvertStringWithSTL(std::string& str) {
	std::unordered_map<char, size_t> charCountTable;

	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c){ return std::tolower(c); });


	for(const auto& symbol : str) {
		charCountTable[symbol] += 1;
	}

	for(auto& symbol : str) {
		symbol = charCountTable[symbol] > 1 ? ')' : '(';
	}
}


void ConvertStringTwice(std::string& str) {
	const size_t begin{ 0 };
	const size_t end{ str.size() - 1 };

	std::unordered_map<char, size_t> charCountTable;
	char* data{ str.data() };

	const bool isEvenSize{ str.length() % 2 == 0 };
	const size_t middleIndex{ str.length() / 2 };

	for(size_t startIndex{ begin }, endIndex{ end };
			startIndex < endIndex; ++startIndex, --endIndex) {
		ToLower(data[startIndex]);
		ToLower(data[endIndex]);

		charCountTable[data[startIndex]] += 1;
		charCountTable[data[endIndex]] += 1;
	}

	if(!isEvenSize) {
		ToLower(data[middleIndex]);
		charCountTable[data[middleIndex]] += 1;
	}

	for(size_t startIndex{ begin }, endIndex{ end };
			startIndex < endIndex; ++startIndex, --endIndex) {
		data[startIndex] = charCountTable[data[startIndex]] > 1 ? ')' : '(';
		data[endIndex] = charCountTable[data[endIndex]] > 1 ? ')' : '(';
	}

	if(!isEvenSize) {
		data[middleIndex] = charCountTable[data[middleIndex]] > 1 ? ')' : '(';
	}
}


void ConvertStringRecursive(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c){ return std::tolower(c); });

	std::unordered_map<char, size_t> charCountTable;

	FillTable(str.data(), str.size(), charCountTable);
	ChangeSymbols(str.data(), str.size(), charCountTable);
}



static void ToLower(char& symbol) {
	const uint8_t symbolCode{ static_cast<uint8_t>(symbol) };

	// ASCII code of the uppercase letter A.
	const uint8_t ASCIICodeA{ 65 };

	// ASCII code of the uppercase letter Z.
	const uint8_t ASCIICodeZ{ 90 };

	// The difference between the ASCII character codes of the
	//	uppercase letter A and the lowercase letter a.
	const uint8_t diffASCIICodes{ 32 };

	if(ASCIICodeA <= symbolCode && symbolCode <= ASCIICodeZ) {
		symbol = static_cast<char>(symbolCode + diffASCIICodes);
	}
}


static void FillTable(char* str, size_t size,
					  std::unordered_map<char, size_t>& charCountTable) {
	if(size == 1) {
		charCountTable[*str] += 1;
		return;
	}
	if(size < 1) {
		return;
	}

	const size_t middle{ size / 2 };

	FillTable(str, middle, charCountTable);
	FillTable(str + middle, size - middle, charCountTable);
}


static void ChangeSymbols(char* str, size_t size,
						  const std::unordered_map<char, size_t>& charCountTable) {
	if(size == 1) {
		const auto symbol{ charCountTable.find(*str) };
		if(symbol != charCountTable.end()) {
			*str = symbol->second > 1 ? ')' : '(';
		}
		return;
	}

	if(size < 1) {
		return;
	}

	const size_t middle{ size / 2 };

	ChangeSymbols(str, middle, charCountTable);
	ChangeSymbols(str + middle, size - middle, charCountTable);
}
