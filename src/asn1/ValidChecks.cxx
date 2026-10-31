/*
 * ValidChecks.cxx
 *
 * Copyright (c) 2001 Institute for Information Industry, Taiwan, Republic of China
 * (http://www.iii.org.tw/iiia/ewelcome.htm)
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is III ASN.1 Tool
 *
 * The Initial Developer of the Original Code is Institute for Information Industry.
 *
 * Portions are Copyright (C) 1993 Free Software Foundation, Inc.
 * All Rights Reserved.
 *
 * Contributor(s): Huang-Ming Huang
 *
 * The code is modified by Genesys Telecommunications Labs UK, 2003-2011
 * Contributors: 
 *    Arunas Ruksnaitis <arunas.ruksnaitis@genesyslab.com>
 *    Rustam Mirzaev <rustam.mirzaev@genesyslab.com>
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "asn1.h"

namespace ASN1 {

int lexicographic_compare_bytes(const char* first1, size_t size1,
                const char* first2, size_t size2)
{
  if(size1 > size2)
    return 1;
  if(size1 < size2)
    return -1;

  if (first1 == 0 && first2 == 0)
    return 0;
  if (first1 == first2)
    return 0;

  int r;
  for (; size1; ++first1, --size1, ++first2)
  {
    r = *first1 - *first2;
    if (r != 0) return r;
  }

  return 0;
}

bool INTEGER::isValid() const
{
  return getConstraintType() == ExtendableConstraint || isStrictlyValid();
}

bool INTEGER::isStrictlyValid() const
{
  if (getConstraintType() == Unconstrained)
    return true;
  INT_TYPE v = static_cast<INT_TYPE>(value);
  if (getLowerLimit() >= 0)
    return value >= static_cast<UINT_TYPE>(getLowerLimit()) && value <= getUpperLimit();
  return v >= getLowerLimit() && v <= static_cast<INT_TYPE>(getUpperLimit());
}


bool AbstractString::isValid() const
{
  size_type invalid = find_first_invalid();
  return size() >= static_cast<UINT_TYPE>(getLowerLimit()) &&
         (size() <= getUpperLimit() || extendable()) &&
         invalid == ASN1_STD string::npos;
}

bool AbstractString::isStrictlyValid() const
{
  return size() >= static_cast<UINT_TYPE>(getLowerLimit()) &&
         size() <= getUpperLimit() &&
         find_first_invalid() == ASN1_STD string::npos;
}

bool BMPString::legalCharacter(wchar_t ch) const
{
  if (ch < getFirstChar())
    return false;

  if (ch > getLastChar())
    return false;

  return true;
}

BMPString::size_type BMPString::first_illegal_at() const
{
  const_iterator first = begin(), last = end();
  for (; first != end(); ++first)
    if (!legalCharacter(*first))
      break;

  return first-begin();
}

bool BMPString::isValid() const
{
  return size() >= static_cast<UINT_TYPE>(getLowerLimit()) &&
         (size() <= getUpperLimit() || extendable()) &&
         first_illegal_at() == size();
}

bool BMPString::isStrictlyValid() const
{
  return size() >= static_cast<UINT_TYPE>(getLowerLimit()) &&
         size() <= getUpperLimit() &&
         first_illegal_at() == size();
}

bool UTCTime::isStrictlyValid() const
{
  if (year <= 0 || month < 1 || month > 12 || day <= 0)
    return false;

  switch (month)
  {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      if (day > 31)
        return false;
      break;

    case 4: case 6: case 9: case 11:
      if (day > 30)
        return false;
      break;

    case 2:
      if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
      {
        if (day > 29)
          return false;
      }
      else if (day > 28)
        return false;
      break;
  }

  return (hour >= 0 && hour <= 23) &&
         (minute >= 0 && minute <= 59) &&
         (second >= 0 && second <= 59) &&
         (mindiff >= -720 && mindiff <= 720);
}

bool CHOICE::isValid() const
{
  return choiceID >=0 && (static_cast<unsigned>(choiceID) < info()->numChoices || extendable() ) && choice->isValid();
}

bool CHOICE::isStrictlyValid() const
{
  return choiceID >= 0 && static_cast<unsigned>(choiceID) < info()->numChoices && choice->isStrictlyValid();
}

bool SEQUENCE_OF_Base::isValid() const
{
  if (container.size() >= static_cast<UINT_TYPE>(getLowerLimit()) &&
      (extendable() || container.size() <= getUpperLimit()))
  {
    Container::const_iterator first = container.begin(),
                            last  = container.end();
    for (; first != last; ++ first)
    {
      if (!(*first)->isValid())
        return false;
    }

    return true;
  }
  return false;
}

bool SEQUENCE_OF_Base::isStrictlyValid() const
{
  if (container.size() >= static_cast<UINT_TYPE>(getLowerLimit()) &&
      container.size() <= getUpperLimit())
  {
    Container::const_iterator first = container.begin(),
                            last  = container.end();
    for (; first != last; ++ first)
    {
      if (!(*first)->isStrictlyValid())
        return false;
    }

    return true;
  }
  return false;
}

bool OpenData::isValid() const
{
  if (has_data())
    return get_data().isValid();
  return has_buf();
}

bool OpenData::isStrictlyValid() const
{
  if (has_data())
    return get_data().isStrictlyValid();
  return has_buf();
}

}// namespace ASN1
