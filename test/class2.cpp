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

namespace {

class base_class
{
public:
    int k;

    base_class() : k(6)
    {
    }
};

QU4L_MAKE_ENTITY(
    (hello)(world),
    class, hello_world, : public base_class,

public:
    static const int i = 5;
    int j;

    hello_world() : j(i)
    {
    }

    int get_value() const
    {
        return i;
    }

    , get_id, ".")

/**
 *
 */
TEST(TestClassWithInheritance, Use)
{
    hello::world::hello_world foo;

    ASSERT_EQ(static_cast<int>(hello::world::hello_world::i), foo.j);

    ASSERT_EQ(static_cast<int>(hello::world::hello_world::i), foo.get_value());

    ASSERT_EQ(6, foo.k);

    ASSERT_STREQ("hello.world.hello_world",
        hello::world::hello_world::get_id());
}

}
