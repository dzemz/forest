/*
    MIT License

    Copyright(c) 2017 George Fotopoulos

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/BinarySearchTree.hpp>

SCENARIO(
    "Test Binary Search Tree"
) {
    GIVEN("A Binary Search Tree") {
        forest::BinarySearchTree<int, int> BinarySearchTree;
        WHEN("The Binary Search Tree is empty") {
            THEN("Test height()") {
                REQUIRE(BinarySearchTree.height() == 0);
            }
            THEN("Test size()") {
                REQUIRE(BinarySearchTree.size() == 0);
            }
            THEN("Test maximum()") {
                REQUIRE(BinarySearchTree.maximum() == nullptr);
            }
            THEN("Test minimum()") {
                REQUIRE(BinarySearchTree.minimum() == nullptr);
            }
            THEN("Test search(555)") {
                REQUIRE(BinarySearchTree.search(555) == nullptr);
            }
            THEN("Test clear()") {
                BinarySearchTree.clear();
                REQUIRE(BinarySearchTree.height() == 0);
                REQUIRE(BinarySearchTree.size() == 0);
            }
        }
        WHEN("Nodes are inserted in random order") {
            BinarySearchTree.insert(4, 0);
            BinarySearchTree.insert(2, 0);
            BinarySearchTree.insert(90, 0);
            BinarySearchTree.insert(3, 0);
            BinarySearchTree.insert(0, 0);
            BinarySearchTree.insert(14, 0);
            BinarySearchTree.insert(45, 0);
            THEN("Test height()") {
                REQUIRE(BinarySearchTree.height() == 4);
            }
            THEN("Test size()") {
                REQUIRE(BinarySearchTree.size() == 7);
            }
            THEN("Test maximum()") {
                auto max = BinarySearchTree.maximum();
                REQUIRE(max != nullptr);
                REQUIRE(max->key == 90);
            }
            THEN("Test minimum()") {
                auto min = BinarySearchTree.minimum();
                REQUIRE(min != nullptr);
                REQUIRE(min->key == 0);
            }
            THEN("Test search(1337)") {
                REQUIRE(BinarySearchTree.search(1337) == nullptr);
            }
            THEN("Test search(3)") {
                auto result = BinarySearchTree.search(3);
                REQUIRE(result != nullptr);
                REQUIRE(result->key == 3);
            }
            THEN("Test remove(45)") {
                BinarySearchTree.remove(45);
                REQUIRE(BinarySearchTree.search(45) == nullptr);
                REQUIRE(BinarySearchTree.height() == 3);
                REQUIRE(BinarySearchTree.size() == 6);
            }
            THEN("Test clear()") {
                BinarySearchTree.clear();
                REQUIRE(BinarySearchTree.height() == 0);
                REQUIRE(BinarySearchTree.size() == 0);
            }
        }
        WHEN("Nodes are inserted in ascending order") {
            for (int i = 0; i < 10; ++i) {
                BinarySearchTree.insert(i, 0);
            }
            THEN("Test height()") {
                REQUIRE(BinarySearchTree.height() == 10);
            }
            THEN("Test size()") {
                REQUIRE(BinarySearchTree.size() == 10);
            }
            THEN("Test maximum()") {
                auto max = BinarySearchTree.maximum();
                REQUIRE(max != nullptr);
                REQUIRE(max->key == 9);
            }
            THEN("Test minimum()") {
                auto min = BinarySearchTree.minimum();
                REQUIRE(min != nullptr);
                REQUIRE(min->key == 0);
            }
            THEN("Test search(1337)") {
                REQUIRE(BinarySearchTree.search(1337) == nullptr);
            }
            THEN("Test search(3)") {
                auto result = BinarySearchTree.search(3);
                REQUIRE(result != nullptr);
                REQUIRE(result->key == 3);
            }
            THEN("Test remove(0)") {
                BinarySearchTree.remove(0);
                REQUIRE(BinarySearchTree.search(0) == nullptr);
                REQUIRE(BinarySearchTree.height() == 9);
                REQUIRE(BinarySearchTree.size() == 9);
            }
            THEN("Test clear()") {
                BinarySearchTree.clear();
                REQUIRE(BinarySearchTree.height() == 0);
                REQUIRE(BinarySearchTree.size() == 0);
            }
        }
        WHEN("Nodes are inserted in descending order") {
            for (int i = 9; i >= 0; --i) {
                BinarySearchTree.insert(i, 0);
            }
            THEN("Test height()") {
                REQUIRE(BinarySearchTree.height() == 10);
            }
            THEN("Test size()") {
                REQUIRE(BinarySearchTree.size() == 10);
            }
            THEN("Test maximum()") {
                auto max = BinarySearchTree.maximum();
                REQUIRE(max != nullptr);
                REQUIRE(max->key == 9);
            }
            THEN("Test minimum()") {
                auto min = BinarySearchTree.minimum();
                REQUIRE(min != nullptr);
                REQUIRE(min->key == 0);
            }
            THEN("Test search(1337)") {
                REQUIRE(BinarySearchTree.search(1337) == nullptr);
            }
            THEN("Test search(3)") {
                auto result = BinarySearchTree.search(3);
                REQUIRE(result != nullptr);
                REQUIRE(result->key == 3);
            }
            THEN("Test remove(0)") {
                BinarySearchTree.remove(0);
                REQUIRE(BinarySearchTree.search(0) == nullptr);
                REQUIRE(BinarySearchTree.height() == 9);
                REQUIRE(BinarySearchTree.size() == 9);
            }
            THEN("Test clear()") {
                BinarySearchTree.clear();
                REQUIRE(BinarySearchTree.height() == 0);
                REQUIRE(BinarySearchTree.size() == 0);
            }
        }
    }
}
