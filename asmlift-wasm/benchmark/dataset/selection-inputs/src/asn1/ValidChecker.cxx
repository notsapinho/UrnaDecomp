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

ASN1_STD string AbstractData::getTypeName() const
{
  return "AbstractData";
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

bool ConstVisitor::visit(const SEQUENCE& value)
{
  if (!preVisitExtensionRoots(value))
    return false;

  unsigned i;
  int lastOptionalId = -1;
  for (i = 0; i < value.info()->numFields ; ++i)
  {
    int optionalId = value.info()->ids[i];
    if (optionalId == -1 || value.hasOptionalField(optionalId))
    {
      if (value.fields[i] == NULL || !visitExtensionRoot(value, i))
        return false;
    }
    lastOptionalId = ( optionalId != -1 ? optionalId : lastOptionalId);
  }

  if (value.extensionMap.size())
  {
    assert(value.extendable());
    if (!preVisitExtensions(value))
      return false;

    for (; i < value.fields.size(); ++i)
    {
      if (!value.hasOptionalField(++lastOptionalId))
        continue;

      if (value.fields[i] == NULL || !visitKnownExtension(value, i))
        return false;
    }
  }
  return afterVisitSequence(value);
}

}// namespace ASN1
