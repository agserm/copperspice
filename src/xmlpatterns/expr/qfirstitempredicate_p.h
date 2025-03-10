/***********************************************************************
*
* Copyright (c) 2012-2022 Barbara Geller
* Copyright (c) 2012-2022 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://www.gnu.org/licenses/
*
***********************************************************************/

#ifndef QFirstItemPredicate_P_H
#define QFirstItemPredicate_P_H

#include <qsinglecontainer_p.h>

QT_BEGIN_NAMESPACE

namespace QPatternist {
class FirstItemPredicate : public SingleContainer
{
 public:
   /**
    * Creates a FirstItemPredicate that filters @p source.
    */
   FirstItemPredicate(const Expression::Ptr &source);

   /**
    * @returns the first item, if any, from evaluating the source expression.
    */
   Item evaluateSingleton(const DynamicContext::Ptr &) const override;

   /**
    * @returns a list containing one CommonSequenceTypes::ZeroOrMoreItems instance.
    */
   SequenceType::List expectedOperandTypes() const override;

   /**
    * @returns a SequenceType where the item type is the same as the source expression
    * and where the cardinality is either Cardinality::zeroOrOne() or Cardinality::exactlyOne(),
    * depending on the source expression.
    */
   SequenceType::Ptr staticType() const override;
   ExpressionVisitorResult::Ptr accept(const ExpressionVisitor::Ptr &visitor) const override;

   /**
    * Rewrites <tt>expression[1][1]</tt> into <tt>expression[1]</tt>.
    */
   Expression::Ptr compress(const StaticContext::Ptr &context) override;

   /**
    * @returns always IDFirstItemPredicate.
    */
   ID id() const override;
};
}

QT_END_NAMESPACE

#endif
