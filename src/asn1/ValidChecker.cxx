/*
 * ValidChecker.cxx
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

class StrictlyValidChecker : public ConstVisitor
{
public:
  using ConstVisitor::do_visit;
  bool do_visit(const Null& value) { return true;}
  bool do_visit(const BOOLEAN& value) { return true;}
  bool do_visit(const INTEGER& value) { return value.isStrictlyValid(); }
  bool do_visit(const ENUMERATED& value) { return value.isStrictlyValid(); }
  bool do_visit(const OBJECT_IDENTIFIER& value) { return value.isStrictlyValid(); }
  bool do_visit(const BIT_STRING& value) { return value.isStrictlyValid(); }
  bool do_visit(const OCTET_STRING& value) { return value.isStrictlyValid(); }
  bool do_visit(const AbstractString& value) { return value.isStrictlyValid(); }
  bool do_visit(const BMPString& value) { return value.isStrictlyValid(); }
  bool do_visit(const CHOICE& value) { return value.isStrictlyValid(); }
  bool do_visit(const OpenData& value){ return value.isStrictlyValid(); }
  bool do_visit(const UTCTime& value)  { return value.isStrictlyValid(); }
  bool do_visit(const GeneralizedTime& value)  { return value.isStrictlyValid(); }
  bool do_visit(const SEQUENCE_OF_Base& value){ return value.isStrictlyValid(); }

  bool visitExtensionRoot(const SEQUENCE& value, int index) {
    return value.getField(index)->isStrictlyValid();
  }
  bool visitKnownExtension(const SEQUENCE& value, int index) {
    return value.getField(index)->isStrictlyValid();
  }
};

class ValidChecker : public ConstVisitor
{
public:
  using ConstVisitor::do_visit;
  bool do_visit(const Null& value){ return true;}
  bool do_visit(const BOOLEAN& value){ return true;}
  bool do_visit(const INTEGER& value){ return value.isValid(); }
  bool do_visit(const ENUMERATED& value){ return value.isValid(); }
  bool do_visit(const OBJECT_IDENTIFIER& value){ return value.isValid(); }
  bool do_visit(const BIT_STRING& value){ return value.isValid(); }
  bool do_visit(const OCTET_STRING& value){ return value.isValid(); }
  bool do_visit(const AbstractString& value){ return value.isValid(); }
  bool do_visit(const BMPString& value){ return value.isValid(); }
  bool do_visit(const CHOICE& value){ return value.isValid(); }
  bool do_visit(const OpenData& value){ return value.isValid(); }
  bool do_visit(const UTCTime& value){ return value.isValid(); }
  bool do_visit(const GeneralizedTime& value){ return value.isValid(); }
  bool do_visit(const SEQUENCE_OF_Base& value){ return value.isValid(); }

  bool visitExtensionRoot(const SEQUENCE& value, int index) {
    return value.getField(index)->isValid();
  }
  bool visitKnownExtension(const SEQUENCE& value, int index) {
    return value.getField(index)->isValid();
  }
};

AbstractData::AbstractData(const void* information)
: info_(information)
{
}

bool AbstractData::isValid() const
{
  ValidChecker checker;
  return accept(checker);
}

bool AbstractData::isStrictlyValid() const
{
  StrictlyValidChecker checker;
  return accept(checker);
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
  return size() >= static_cast<UINT_TYPE>(getLowerLimit()) &&
         (size() <= getUpperLimit() || extendable()) &&
         find_first_invalid() == ASN1_STD string::npos;
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
