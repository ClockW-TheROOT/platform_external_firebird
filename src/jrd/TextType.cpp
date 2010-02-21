/*
 *      PROGRAM:        JRD Intl
 *      MODULE:         TextType.cpp
 *      DESCRIPTION:    International text support routines
 *
 * copyright (c) 1992, 1993 by Borland International
 */

/*************  history ************
*
*       COMPONENT: JRD  MODULE: INTL.CPP
*       generated by Marion V2.5     2/6/90
*       from dev              db        on 4-JAN-1995
*****************************************************************
*
*       PR	2002-06-02 Added ugly c hack in
*       intl_back_compat_alloc_func_lookup.
*       When someone has time we need to change the references to
*       return (void*) function to something more C++ like
*
*       42 4711 3 11 17  tamlin   2001
*       Added silly numbers before my name, and converted it to C++.
*
*       18850   daves   4-JAN-1995
*       Fix gds__alloc usage
*
*       18837   deej    31-DEC-1994
*       fixing up HARBOR_MERGE
*
*       18821   deej    27-DEC-1994
*       HARBOR MERGE
*
*       18789   jdavid  19-DEC-1994
*       Cast some functions
*
*       17508   jdavid  15-JUL-1994
*       Bring it up to date
*
*       17500   daves   13-JUL-1994
*       Bug 6645: Different calculation of partial keys
*
*       17202   katz    24-MAY-1994
*       PC_PLATFORM requires the .dll extension
*
*       17191   katz    23-MAY-1994
*       OS/2 requires the .dll extension
*
*       17180   katz    23-MAY-1994
*       Define location of DLL on OS/2
*
*       17149   katz    20-MAY-1994
*       In JRD, isc_arg_number arguments are SLONG's not int's
*
*       16633   daves   19-APR-1994
*       Bug 6202: International licensing uses INTERNATIONAL product code
*
*       16555   katz    17-APR-1994
*       The last argument of calls to ERR_post should be 0
*
*       16521   katz    14-APR-1994
*       Borland C needs a decorated symbol to lookup
*
*       16403   daves   8-APR-1994
*       Bug 6441: Emit an error whenever transliteration from ttype_binary attempted
*
*       16141   katz    28-MAR-1994
*       Don't declare return value from ISC_lookup_entrypoint as API_ROUTINE
*
 * The contents of this file are subject to the Interbase Public
 * License Version 1.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy
 * of the License at http://www.Inprise.com/IPL.html
 *
 * Software distributed under the License is distributed on an
 * "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
 * or implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code was created by Inprise Corporation
 * and its predecessors. Portions created by Inprise Corporation are
 * Copyright (C) Inprise Corporation.
 *
 * All Rights Reserved.
 * Contributor(s): ______________________________________.
 *
 * 2002.10.29 Sean Leyne - Removed obsolete "Netware" port
 *
 * 2002.10.30 Sean Leyne - Removed support for obsolete "PC_PLATFORM" define
 *
 * 2006.10.10 Adriano dos Santos Fernandes - refactored from intl.cpp
 *
*/

#include "firebird.h"
#include "gen/iberror.h"
#include "../jrd/jrd.h"
#include "../jrd/intl_classes.h"
#include "../jrd/IntlUtil.h"
#include "../common/classes/Aligner.h"


namespace Jrd {


TextType::TextType(TTYPE_ID _type, texttype *_tt, CharSet* _cs)
	: tt(_tt), cs(_cs), type(_type)
{
	canonical(cs->getSqlMatchAnyLength(), cs->getSqlMatchAny(),
		sizeof(ULONG), reinterpret_cast<UCHAR*>(&canonicalChars[CHAR_SQL_MATCH_ANY]));
	canonical(cs->getSqlMatchOneLength(), cs->getSqlMatchOne(),
		sizeof(ULONG), reinterpret_cast<UCHAR*>(&canonicalChars[CHAR_SQL_MATCH_ONE]));

	struct Conversion
	{
		USHORT code;
		int ch;
	};

	const Conversion conversions[] =
		{
			{'*', CHAR_ASTERISK},
			{'@', CHAR_AT},
			{'^', CHAR_CIRCUMFLEX},
			{':', CHAR_COLON},
			{',', CHAR_COMMA},
			{'=', CHAR_EQUAL},
			{'-', CHAR_MINUS},
			{'%', CHAR_PERCENT},
			{'+', CHAR_PLUS},
			{'?', CHAR_QUESTION_MARK},
			{' ', CHAR_SPACE},
			{'~', CHAR_TILDE},
			{'_', CHAR_UNDERLINE},
			{'|', CHAR_VERTICAL_BAR},
			{'"', CHAR_DOUBLE_QUOTE},
			{'{', CHAR_OPEN_BRACE},
			{'}', CHAR_CLOSE_BRACE},
			{'[', CHAR_OPEN_BRACKET},
			{']', CHAR_CLOSE_BRACKET},
			{'(', CHAR_OPEN_PAREN},
			{')', CHAR_CLOSE_PAREN},
			{'s', CHAR_LOWER_S},
			{'S', CHAR_UPPER_S}
		};

	for (int i = 0; i < FB_NELEM(conversions); i++)
	{
		UCHAR temp[sizeof(ULONG)];

		ULONG length = getCharSet()->getConvFromUnicode().convert(
			sizeof(USHORT), &conversions[i].code, sizeof(temp), temp);
		canonical(length, temp, sizeof(ULONG),
			reinterpret_cast<UCHAR*>(&canonicalChars[conversions[i].ch]));
	}

	struct Conversion2
	{
		const char* str;
		UCHAR* buffer;
	};

	const Conversion2 conversions2[] =
	{
		{"0123456789", reinterpret_cast<UCHAR*>(canonicalNumbers)},
		{"abcdefghijklmnopqrstuvwxyz", reinterpret_cast<UCHAR*>(canonicalLowerLetters)},
		{"ABCDEFGHIJKLMNOPQRSTUVWXYZ", reinterpret_cast<UCHAR*>(canonicalUpperLetters)},
		{" \t\v\r\n\f", reinterpret_cast<UCHAR*>(canonicalWhiteSpaces)}
	};

	for (int i = 0; i < FB_NELEM(conversions2); i++)
	{
		UCHAR temp[sizeof(ULONG)];

		for (const char* p = conversions2[i].str; *p; ++p)
		{
			USHORT code = static_cast<USHORT>(*p);
			ULONG length = getCharSet()->getConvFromUnicode().convert(sizeof(code), &code, sizeof(temp), temp);
			const size_t pos = (p - conversions2[i].str) * getCanonicalWidth();
			canonical(length, temp, sizeof(ULONG), &conversions2[i].buffer[pos]);
		}
	}
}


USHORT TextType::key_length(USHORT len)
{
	if (tt->texttype_fn_key_length)
		return (*tt->texttype_fn_key_length)(tt, len);

	if (getCharSet()->isMultiByte())
		return UnicodeUtil::utf16KeyLength(len);

	return len;
}


USHORT TextType::string_to_key(USHORT srcLen, const UCHAR* src,
							   USHORT dstLen, UCHAR* dst,
							   USHORT key_type)
{
	if (tt->texttype_fn_string_to_key)
		return (*tt->texttype_fn_string_to_key)(tt, srcLen, src, dstLen, dst, key_type);

	const UCHAR* space = getCharSet()->getSpace();
	BYTE spaceLength = getCharSet()->getSpaceLength();
	Firebird::HalfStaticArray<UCHAR, BUFFER_SMALL> utf16Str;
	UCHAR utf16Space[sizeof(ULONG)];

	if (getCharSet()->isMultiByte())
	{
		// convert src to UTF-16
		const ULONG utf16Length = getCharSet()->getConvToUnicode().convertLength(srcLen);

		srcLen = getCharSet()->getConvToUnicode().convert(srcLen, src,
					utf16Length, utf16Str.getBuffer(utf16Length));
		src = utf16Str.begin();

		// convert charset space to UTF-16
		spaceLength =
			getCharSet()->getConvToUnicode().convert(spaceLength, space, sizeof(utf16Space), utf16Space);
		fb_assert(spaceLength == 2);	// space character can't be surrogate for default string_to_key
		space = utf16Space;
	}

	if (tt->texttype_pad_option)
	{
		const UCHAR* pad;

		for (pad = src + srcLen - spaceLength; pad >= src; pad -= spaceLength)
		{
			if (memcmp(pad, space, spaceLength) != 0)
				break;
		}

		srcLen = pad - src + spaceLength;
	}

	if (getCharSet()->isMultiByte())
	{
		dstLen = UnicodeUtil::utf16ToKey(srcLen, Firebird::Aligner<USHORT>(src, srcLen), dstLen, dst);
	}
	else
	{
		if (dstLen >= srcLen)
		{
			memcpy(dst, src, srcLen);
			dstLen = srcLen;
		}
		else
			dstLen = INTL_BAD_KEY_LENGTH;
	}

	return dstLen;
}


SSHORT TextType::compare(ULONG len1, const UCHAR* str1, ULONG len2, const UCHAR* str2)
{
	INTL_BOOL error = false;

	if (tt->texttype_fn_compare)
		return (*tt->texttype_fn_compare)(tt, len1, str1, len2, str2, &error);

	const UCHAR* space = getCharSet()->getSpace();
	BYTE spaceLength = getCharSet()->getSpaceLength();
	Firebird::HalfStaticArray<UCHAR, BUFFER_SMALL> utf16Str1;
	Firebird::HalfStaticArray<UCHAR, BUFFER_SMALL> utf16Str2;
	UCHAR utf16Space[sizeof(ULONG)];

	if (getCharSet()->isMultiByte())
	{
		// convert str1 to UTF-16
		ULONG utf16Length = getCharSet()->getConvToUnicode().convertLength(len1);

		len1 = getCharSet()->getConvToUnicode().convert(len1, str1,
					utf16Length, utf16Str1.getBuffer(utf16Length));
		str1 = utf16Str1.begin();

		// convert str2 to UTF-16
		utf16Length = getCharSet()->getConvToUnicode().convertLength(len2);

		len2 = getCharSet()->getConvToUnicode().convert(len2, str2,
					utf16Length, utf16Str2.getBuffer(utf16Length));
		str2 = utf16Str2.begin();

		// convert charset space to UTF-16
		spaceLength =
			getCharSet()->getConvToUnicode().convert(spaceLength, space, sizeof(utf16Space), utf16Space);
		fb_assert(spaceLength == 2);	// space character can't be surrogate for default compare
		space = utf16Space;
	}

	if (tt->texttype_pad_option)
	{
		const UCHAR* pad;

		for (pad = str1 + len1 - spaceLength; pad >= str1; pad -= spaceLength)
		{
			if (memcmp(pad, space, spaceLength) != 0)
				break;
		}

		len1 = pad - str1 + spaceLength;

		for (pad = str2 + len2 - spaceLength; pad >= str2; pad -= spaceLength)
		{
			if (memcmp(pad, space, spaceLength) != 0)
				break;
		}

		len2 = pad - str2 + spaceLength;
	}

	if (getCharSet()->isMultiByte())
	{
		INTL_BOOL error_flag;
		return UnicodeUtil::utf16Compare(len1, Firebird::Aligner<USHORT>(str1, len1),
										 len2, Firebird::Aligner<USHORT>(str2, len2), &error_flag);
	}

	SSHORT cmp = memcmp(str1, str2, MIN(len1, len2));

	if (cmp == 0)
		cmp = (len1 < len2 ? -1 : (len1 > len2 ? 1 : 0));

	return cmp;
}


ULONG TextType::str_to_upper(ULONG srcLen, const UCHAR* src, ULONG dstLen, UCHAR* dst)
{
	if (tt->texttype_fn_str_to_upper)
		return (*tt->texttype_fn_str_to_upper)(tt, srcLen, src, dstLen, dst);

	return Firebird::IntlUtil::toUpper(getCharSet(), srcLen, src, dstLen, dst, NULL);
}


ULONG TextType::str_to_lower(ULONG srcLen, const UCHAR* src, ULONG dstLen, UCHAR* dst)
{
	if (tt->texttype_fn_str_to_lower)
		return (*tt->texttype_fn_str_to_lower)(tt, srcLen, src, dstLen, dst);

	return Firebird::IntlUtil::toLower(getCharSet(), srcLen, src, dstLen, dst, NULL);
}


ULONG TextType::canonical(ULONG srcLen, const UCHAR* src, ULONG dstLen, UCHAR* dst)
{
	if (tt->texttype_fn_canonical)
		return (*tt->texttype_fn_canonical)(tt, srcLen, src, dstLen, dst);

	if (getCharSet()->isMultiByte())
	{
		fb_assert(tt->texttype_canonical_width == sizeof(ULONG));

		Firebird::HalfStaticArray<UCHAR, BUFFER_SMALL> utf16_str;

		ULONG utf16_len = getCharSet()->getConvToUnicode().convertLength(srcLen);

		// convert to UTF-16
		utf16_len = getCharSet()->getConvToUnicode().convert(srcLen, src,
			utf16_len, utf16_str.getBuffer(utf16_len));

		USHORT errCode;
		ULONG errPos;

		// convert UTF-16 to UTF-32
		return UnicodeUtil::utf16ToUtf32(utf16_len, Firebird::Aligner<USHORT>(utf16_str.begin(), utf16_len),
			dstLen, Firebird::OutAligner<ULONG>(dst, dstLen), &errCode, &errPos) / sizeof(ULONG);
	}

	fb_assert(
		(tt->texttype_canonical_width == 0 && !tt->texttype_fn_canonical) ||
		tt->texttype_canonical_width == getCharSet()->minBytesPerChar());
	fb_assert(dstLen >= srcLen);

	memcpy(dst, src, srcLen);

	return srcLen / getCharSet()->minBytesPerChar();
}


}	// namespace Jrd
