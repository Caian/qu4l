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
 * along with qu4l.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <qu4l/qualify.hpp>

#include <gtest/gtest.h>

#include <string>

namespace {

QU4L_MAKE_ENTITY(
    (foo)(bar),
    struct, baz, ,

    , get_id, "::")

QU4L_MAKE_ENTITY(
    (hello)(world),
    template <typename T>
    struct, hello_world, ,

    static std::string get_id()
    {
        return std::string(_get_id()) + "/" + T::get_id();
    }

private:

    , _get_id, "::")

/**
 *
 */
TEST(TestNestedQualifyStruct, Use)
{
    typedef hello::world::hello_world<foo::bar::baz> hello_world;

    hello_world foo;

    std::string id = hello_world::get_id();

    ASSERT_STREQ("hello::world::hello_world/foo::bar::baz", id.c_str());
}

}
