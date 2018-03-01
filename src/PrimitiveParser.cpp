#include "PrimitiveParser.hpp"

void PrimitiveParser::setTokenDescriptors(std::vector<PrimitiveTokenDescriptor>& descriptors)
{
	_primitiveTokenDescriptors = descriptors;
}

void PrimitiveParser::parsePrimitiveFromLine(const std::string& line, Primitive& parsedPrimitive)
{
	parsedPrimitive.primitiveType = PrimitiveType::UNKNOWN;

	std::vector<std::string> tokens;
	_tokenizeLine(line, tokens);

	if (!tokens.size())
		return;

	parsedPrimitive.primitiveType = _getPrimitiveType(tokens[0]);

	const auto primitiveTokenDesc = _primitiveTokenDescriptors[parsedPrimitive.primitiveType];

	if (parsedPrimitive.primitiveType == PrimitiveType::UNKNOWN || tokens.size() != (1 + primitiveTokenDesc.parameters.size()))
	{
		parsedPrimitive.primitiveType = PrimitiveType::UNKNOWN;
		return;
	}

	unsigned int index = 0;
	for (const auto param : primitiveTokenDesc.parameters)
	{
		PrimitiveParam p;
		p.type = param;

		switch (param)
		{
			case TokenType::FLOAT:
				p._float = std::stof(tokens[1 + index]);
				break;
			case TokenType::CHAR:
				p._char = tokens[1 + index][0];
				break;
			case TokenType::INT:
				p._int = std::stoi(tokens[1 + index]);
				break;
		}

		parsedPrimitive.params.push_back(p);

		++index;
	}
}

void PrimitiveParser::_split(std::string str, std::string delimiters, std::vector<std::string>& results)
{
	_tokenizer.set(str, delimiters);
	results = _tokenizer.split();
}

void PrimitiveParser::_splitStringToLines(std::string str, std::vector<std::string>& lines)
{
	_split(str, "\n", lines);
}

void PrimitiveParser::_tokenizeLine(std::string line, std::vector<std::string>& tokens)
{
	_split(line, " \t", tokens);
}

PrimitiveType PrimitiveParser::_getPrimitiveType(std::string name) const
{
	for (const auto desc : _primitiveTokenDescriptors)
	{
		if (name.compare(desc.primitiveName) == 0)
			return desc.primitiveType;
	}

	return PrimitiveType::UNKNOWN;
}

void PrimitiveParser:: parsePrimitivesFromText(const std::string& multipleLines, std::vector<Primitive>& parsedPrimitives)
{
	std::vector<std::string> lines;
	
	_splitStringToLines(multipleLines, lines);

	for(const auto line : lines)
	{
		Primitive p;
		parsePrimitiveFromLine(line, p);
		if(p.primitiveType!=PrimitiveType::UNKNOWN)
			parsedPrimitives.push_back(p);
	}
}