#pragma once

#include <vector>

#include "Tokenizer.hpp"
#include "TokenDescriptors.hpp"
#include "Primitive.hpp"

class Parser
{
public:
	void setTokenDescriptors(std::vector<PrimitiveTokenDescriptor>& descriptors);
	void parsePrimitiveFromLine(const std::string& line, Primitive& parsedPrimitive);
	void parsePrimitivesFromText(const std::string& multipleLines, std::vector<Primitive>& parsedPrimitives);

protected:
	void _split(std::string str, std::string delimiters, std::vector<std::string>& results);
	void _splitStringToLines(std::string str, std::vector<std::string>& lines);
	void _tokenizeLine(std::string line, std::vector<std::string>& tokens);

	PrimitiveType _getPrimitiveType(std::string name) const;

	std::vector<PrimitiveTokenDescriptor>	_primitiveTokenDescriptors;
	Tokenizer								_tokenizer;
};
