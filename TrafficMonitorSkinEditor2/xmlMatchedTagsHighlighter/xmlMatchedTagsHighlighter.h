﻿// This file is part of Notepad++ project
// Copyright (C)2020 Don HO <don.h@free.fr>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid      
// misunderstandings, we consider an application to constitute a          
// "derivative work" for the purpose of this license if it does any of the
// following:                                                             
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
// This file is part of Notepad++ project
// Copyright (C)2021 Don HO <don.h@free.fr>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#pragma once

#include <string>
#include <vector>

class CScintillaEditView;


class XmlMatchedTagsHighlighter {
public:
	explicit XmlMatchedTagsHighlighter(CScintillaEditView *pEditView):_pEditView(pEditView){};
	void tagMatch(bool doHiliteAttr);
	
private:
	CScintillaEditView *_pEditView;
	
	struct XmlMatchedTagsPos {
		int tagOpenStart;
		int tagNameEnd;
		int tagOpenEnd;

		int tagCloseStart;
		int tagCloseEnd;
	};

	struct FindResult {
		int start;
		int end;
		bool success;
	};
	
	bool getXmlMatchedTagsPos(XmlMatchedTagsPos & tagsPos);

	// Allowed whitespace characters in XML
	bool isWhitespace(int ch) { return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'; }

	FindResult findText(const char *text, int start, int end, int flags = 0);
	FindResult findOpenTag(const std::string& tagName, int start, int end);
	FindResult findCloseTag(const std::string& tagName, int start, int end);
	int findCloseAngle(int startPosition, int endPosition);
	
	//std::vector< std::pair<int, int> > getAttributesPos(int start, int end);
	
};
