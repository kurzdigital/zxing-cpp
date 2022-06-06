/*
* Copyright 2022 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ByteArray.h"

namespace ZXing {

enum class ECI : int;
enum class CharacterSet;

enum class ContentType { Text, Binary, Mixed, GS1, ISO15434, UnknownECI };

std::string ToString(ContentType type);

struct SymbologyIdentifier
{
	char code = 0, modifier = 0;
	int eciModifierOffset = 0;

	std::string toString(bool hasECI = false) const
	{
		return code ? ']' + std::string(1, code) + static_cast<char>(modifier + eciModifierOffset * hasECI) : std::string();
	}
};

class Content
{
	template <typename FUNC>
	void ForEachECIBlock(FUNC f) const;

	void switchEncoding(ECI eci, bool isECI);

public:
	struct Encoding
	{
		ECI eci;
		int pos;
	};

	ByteArray binary;
	std::vector<Encoding> encodings;
	std::string hintedCharset;
	std::string applicationIndicator;
	SymbologyIdentifier symbology;
	bool hasECI = false;

	Content();
	Content(ByteArray&& binary);

	void switchEncoding(ECI eci) { switchEncoding(eci, true); }
	void switchEncoding(CharacterSet cs);

	void reserve(int count) { binary.reserve(binary.size() + count); }

	void push_back(uint8_t val) { binary.push_back(val); }
	void append(const std::string& str) { binary.insert(binary.end(), str.begin(), str.end()); }
	void append(const ByteArray& bytes) { binary.insert(binary.end(), bytes.begin(), bytes.end()); }

	void operator+=(char val) { push_back(val); }
	void operator+=(const std::string& str) { append(str); }

	void erase(int pos, int n);
	void insert(int pos, const std::string& str);

	bool empty() const { return binary.empty(); }
	bool canProcess() const;

	std::wstring text() const;
	std::string utf8Protocol() const;
	ByteArray binaryECI() const;
	CharacterSet guessEncoding() const;
	ContentType type() const;
};

} // ZXing
