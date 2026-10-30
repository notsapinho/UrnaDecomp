/*
 * DataLengthCounter.cxx
 *
 * Abstract Syntax Notation 1 Encoding Rules
 *
 * Copyright (c) 1993-1998 Equivalence Pty. Ltd.
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
 * The Original Code is Portable Windows Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Portions are Copyright (C) 1993 Free Software Foundation, Inc.
 * All Rights Reserved.
 *
 * Contributor(s): Huang-Ming Huang
 *
 * The code is adapted from asner.cxx of PWLib, but the dependancy on PWLib has
 * been removed.
 *
 * The code is modified by Genesys Telecommunications Labs UK, 2003-2011
 * Contributors: 
 *    Arunas Ruksnaitis <arunas.ruksnaitis@genesyslab.com>
 *    Rustam Mirzaev <rustam.mirzaev@genesyslab.com>
 */

// The reconstruction's file: BEREncoder.cxx upstream holds this code. In the target DataLengthCounter's vtable lies after
// PEREncoder's, not with BEREncoder's and PrimitiveChecker's, and BEREncoder::encodeHeader calls getDataLength, which
// clang would inline in one TU. The file's name is chosen: no evidence names it.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "asn1.h"

namespace ASN1 {

extern unsigned getIntegerDataLength(INT_TYPE value);

static unsigned getObjectLength(const AbstractData& data, unsigned tag);

unsigned getHeaderLength(unsigned tag, int l)
{
  int len = 1;

  unsigned tagVal = tag & 0x1FFFFFFF;

  if (tagVal >= 31)
    len += (CountBits(tagVal)+6)/7;

  if (l < 128)
    ++len;
  else
    len += (CountBits(l)+7)/8 + 1;

  return len;
}

class DataLengthCounter : public ConstVisitor
{
public:
  DataLengthCounter() : length(0) {}

  unsigned getDataLen() const { return length; }

private:
  using ConstVisitor::do_visit;
  bool do_visit(const Null& value) {
    return true;
  }
  bool do_visit(const BOOLEAN& value) {
    ++length;
    return true;
  }
  bool do_visit(const INTEGER& value) {
    length += getIntegerDataLength(value.getValue());
    return true;
  }
  bool do_visit(const ENUMERATED& value) {
    length += getIntegerDataLength(value.asInt());
    return true;
  }
  bool do_visit(const OBJECT_IDENTIFIER& value) {
    ASN1_STD vector<char> dummy;
    value.encodeCommon(dummy);
    length += dummy.size();
    return true;
  }
  bool do_visit(const BIT_STRING& value) {
    length += (value.size()+7)/8 + 1;
    return true;
  }
  bool do_visit(const OCTET_STRING& value) {
    length += value.size();
    return true;
  }
  bool do_visit(const AbstractString& value) {
    length += value.size();
    return true;
  }
  bool do_visit(const BMPString& value) {
    length += value.size()*2;
    return true;
  }
  bool do_visit(const CHOICE& value) {
    if (value.currentSelection() >=0 )
      length +=  getObjectLength(*value.getSelection(), value.getSelectionTagInternal());
    return true;
  }
  bool do_visit(const OpenData& value) {
    if(value.has_data())
      length += getObjectLength(value.get_data(), value.get_data().getTag());
    else if(value.has_buf())
      length += value.get_buf().size();
    return true;
  }
  bool do_visit(const UTCTime& value) {
    length += value.get().size();
    return true;
  }
  bool do_visit(const GeneralizedTime& value) {
    length += value.get().size();
    return true;
  }
  bool do_visit(const SEQUENCE_OF_Base& value) {
    for (SEQUENCE_OF_Base::const_iterator i = value.begin(), last = value.end(); i != last; ++i)
      length += getObjectLength(**i, InvalidTag);
    return true;
  }

  bool preVisitExtensionRoots(const SEQUENCE& value) {
    return true;
  }
  bool visitExtensionRoot(const SEQUENCE& value, int index) {
    int l = getObjectLength(*value.getField(index), value.getFieldTag(index));
    length += l;
    return true;
  }
  bool VisitExtensions(const SEQUENCE& value) {
    return true;
  }
  bool visitKnownExtension(const SEQUENCE& value, int index) {
    length += getObjectLength(*value.getField(index), value.getFieldTag(index));
    return true;
  }

  unsigned length;
};

unsigned getDataLength(const AbstractData& data)
{
  DataLengthCounter counter;
  data.accept(counter);
  return counter.getDataLen();
}

unsigned getObjectLength(const AbstractData& data, unsigned tag)
{
  int l = getDataLength(data);

  unsigned obj_tag = tag;

  if (tag==InvalidTag)
    obj_tag = data.getTag();

  if(obj_tag==InvalidTag) return l;

  if(isExplicit(obj_tag) || isExplicit(data.getTag())) {
    unsigned tag1 = isExplicit(tag) ? data.getTag() : data.getParentTag();
    if(tag1) l += getHeaderLength(tag1, l);
  }
  return l + getHeaderLength(obj_tag, l);
}

} // namespace ASN1
