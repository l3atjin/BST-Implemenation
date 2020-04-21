// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_empty) {
    // Add your tests here
	BinarySearchTree<int> tree;

    ASSERT_TRUE(tree.empty());

	BinarySearchTree<int> tree2;

	tree2.insert(2);

	ASSERT_FALSE(tree2.empty());
	ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_size)
{
	BinarySearchTree<int> tree;
	//BinarySearchTree<int>::Iterator iter = tree.begin();

	ASSERT_TRUE(tree.size() == 0);

	tree.insert(7);
	ASSERT_TRUE(tree.size() == 1);

	tree.insert(4);
	tree.insert(1);
	tree.insert(15);
	tree.insert(10);
	tree.insert(24);
	tree.insert(6);
	tree.insert(3);

	ASSERT_TRUE(tree.size() == 8);
	ASSERT_TRUE(tree.check_sorting_invariant());
}

//Incomplete. Use iterator to check order
TEST(test_insert)
{
	BinarySearchTree<int> tree;

	tree.insert(10);
	ASSERT_TRUE(tree.size() == 1);

	tree.insert(5);
	tree.insert(9);
	ASSERT_TRUE(tree.size() == 3);

	tree.insert(16);
	tree.insert(20);
	tree.insert(2);
	tree.insert(4);
	tree.insert(14);
	tree.insert(12);

	ASSERT_TRUE(tree.check_sorting_invariant());
	*tree.begin() = 21;
	cout << endl;
	cout << *tree.max_element() << endl;
	cout << *tree.min_element() << endl;
	//ASSERT_FALSE(tree.check_sorting_invariant());
	//BinarySearchTree<int>::Iterator iter = tree.begin();	
	//ASSERT_TRUE(*iter == 10);	
	//ASSERT_TRUE(tree.find(5)++ == tree.find(9));	
	//ASSERT_TRUE(tree.find(4)++ == tree.find(5));

	BinarySearchTree<int> tree1;

	tree1.insert(5);
	tree1.insert(2);
	tree1.insert(6);
	tree1.insert(4);

	auto it = tree1.begin();
	*it = 10;
	//ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_height)
{
	BinarySearchTree<int> tree;
	BinarySearchTree<int> tree1;
	BinarySearchTree<int> tree2;
	//BinarySearchTree<int>::Iterator iter = tree.begin();

	tree.insert(1);

	ASSERT_TRUE(tree.height() == 1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);

	ASSERT_TRUE(tree.height() == 7);

	tree1.insert(4);
	tree1.insert(1);
	tree1.insert(2);
	tree1.insert(3);
	tree1.insert(5);
	tree1.insert(6);
	tree1.insert(7);

	ASSERT_TRUE(tree1.height() == 4);
	ASSERT_TRUE(tree2.height() == 0);
	ASSERT_TRUE(tree.check_sorting_invariant());

}

// Test more
TEST(test_copy)
{
	BinarySearchTree<int> tree;
	BinarySearchTree<int> tree2;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);

	BinarySearchTree<int> tree1 = tree;

	ASSERT_TRUE(tree.size() == tree1.size());
	ASSERT_TRUE(tree.height() == tree1.height());
	ASSERT_TRUE(tree.check_sorting_invariant());

	tree = tree2;
	ASSERT_TRUE(tree.empty());
}

TEST(test_find)
{
	BinarySearchTree<int> tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);

	BinarySearchTree<int>::Iterator iter = tree.find(1);

	ASSERT_TRUE(*iter == 1);

	ASSERT_TRUE(*tree.find(5) == 5);

	ASSERT_TRUE(tree.find(9) == tree.end());
	ASSERT_TRUE(tree.find(10) == tree.end());
	ASSERT_TRUE(tree.find(11) == tree.end());
	ASSERT_TRUE(*tree.find(4) == 4);
	ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_min_element)
{
	BinarySearchTree<int> tree;
	BinarySearchTree<int> tree1;
	BinarySearchTree<int> tree2;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);

	tree2.insert(-1);
	tree2.insert(-2);
	tree2.insert(-3);
	tree2.insert(-4);
	tree2.insert(5);
	tree2.insert(6);
	tree2.insert(7);


	ASSERT_TRUE(*tree.min_element() == 1);

	ASSERT_TRUE(*tree2.min_element() == -4);

	ASSERT_TRUE(tree1.min_element() == tree.end());

	ASSERT_TRUE(*tree.max_element() == 7);

	ASSERT_TRUE(*tree2.max_element() == 7);

	ASSERT_TRUE(tree1.max_element() == tree.end());
	ASSERT_TRUE(tree.check_sorting_invariant());
}



TEST(test_traverse)
{
	BinarySearchTree<int> tree;
	BinarySearchTree<int> tree1;
	BinarySearchTree<int> tree2;

	tree.insert(4);
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);

	tree2.insert(-1);
	tree2.insert(-2);
	tree2.insert(-3);
	tree2.insert(-4);
	tree2.insert(5);
	tree2.insert(6);
	tree2.insert(7);
	
	cout << "Test output" << endl;
	tree.traverse_inorder(cout);

	cout << endl;

	tree2.traverse_inorder(cout);

	cout << endl;

	cout << "Test output" << endl;
	tree.traverse_preorder(cout);

	cout << endl;

	tree2.traverse_preorder(cout);

	cout << endl;
}

TEST(test_min_greater_than)
{
	BinarySearchTree<int> tree;
	BinarySearchTree<int> tree1;
	BinarySearchTree<int> tree2;
	BinarySearchTree<int> tree3;
	BinarySearchTree<int> tree4;

	tree.insert(7);
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(6);
	tree.insert(5);
	tree.insert(10);
	tree.insert(8);
	tree.insert(14);
	tree.insert(13);
	tree.insert(16);

	tree2.insert(-1);
	tree2.insert(-2);
	tree2.insert(-3);
	tree2.insert(-4);
	tree2.insert(5);
	tree2.insert(6);
	tree2.insert(7);

	tree3.insert(3);
	tree3.insert(2);
	tree3.insert(1);

	auto it = tree3.begin();
	ASSERT_EQUAL(*it, 1);
	it++;
	ASSERT_EQUAL(*it, 2);
	it++;
	ASSERT_EQUAL(*it, 3);

	tree4.insert(20);
	tree4.insert(15);
	tree4.insert(25);

	ASSERT_TRUE(*tree4.min_greater_than(20) == 25);

	ASSERT_TRUE(*tree.min_greater_than(12) == 13);
	ASSERT_TRUE(*tree2.min_greater_than(-5) == -4);
	ASSERT_TRUE(*tree2.min_greater_than(4) == 5);
	ASSERT_TRUE(tree2.min_greater_than(8) == tree2.end());
	ASSERT_TRUE(tree1.min_greater_than(8) == tree1.end());
	ASSERT_TRUE(tree.check_sorting_invariant());
}


TEST_MAIN()
