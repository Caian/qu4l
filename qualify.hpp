/*
 * Copyright (C) 2019 Caian Benedicto <caianbene@gmail.com>
 *
 * This file is part of qu4l.
 *
 * qu4l is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * qu4l is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Make; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define QU4L_TEXT(z, n, Text) Text

#define QU4L_NAMESPACE(s, State, Namespace) \
    State namespace Namespace {

#define QU4L_NAMESPACE_STR(s, Sep, Namespace) \
    BOOST_PP_STRINGIZE(Namespace) Sep

#define QU4L_NAMESPACE_EXPAND(s, State, Namespace) \
    State Namespace

#define QU4L_OPEN_NAMESPACES(Namespaces) \
    BOOST_PP_SEQ_FOLD_LEFT(QU4L_NAMESPACE, , Namespaces)

#define QU4L_CLOSE_NAMESPACES(Namespaces) \
    BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(Namespaces), QU4L_TEXT, } )

#define QU4L_NAMESPACES_STR(Namespaces, Sep) \
    BOOST_PP_SEQ_FOLD_LEFT(QU4L_NAMESPACE_EXPAND, , \
        BOOST_PP_SEQ_TRANSFORM(QU4L_NAMESPACE_STR, Sep, Namespaces))

#define QU4L_MAKE_ENTITY(Namespaces, What, Name, Identifier, Body, IdFunName, Sep) \
    QU4L_OPEN_NAMESPACES(Namespaces) \
        What Name Identifier { \
        Body \
        static const char* IdFunName(){return \
            QU4L_NAMESPACES_STR(Namespaces, Sep) \
            BOOST_PP_STRINGIZE(Name) \
        ;} }; \
    QU4L_CLOSE_NAMESPACES(Namespaces)
