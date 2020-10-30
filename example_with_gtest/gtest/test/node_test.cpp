#include"node.h"
#include<gtest/gtest.h>

using namespace std;
class TestLink:public testing::Test
{
public:
    virtual void SetUp()
    {
        cout<<"SetUp"<<endl;
        for(int i=1;i<=5;i++){
            link.PushBack(i);
        }
    }
    virtual void TearDown()
    {
        cout<<"TearDown"<<endl;
        link.Destroy();
    }
    Link link;
};

TEST_F(TestLink,PushBack)
{
    ASSERT_FALSE(link.pHead == NULL);
    link.PushBack(9);
    LinkNode *res=link.FindNode(9);
    ASSERT_FALSE(res == NULL);
}

TEST_F(TestLink,PopBack)
{
    for(int i=1;i<=5;i++){
        link.PopBack();
    }
}

TEST_F(TestLink,FindNode)
{
    ASSERT_TRUE(link.FindNode(3));
    ASSERT_TRUE(link.FindNode(2));
    ASSERT_TRUE(link.FindNode(4));
    ASSERT_TRUE(link.FindNode(5));
    ASSERT_TRUE(link.FindNode(1));
    ASSERT_FALSE(link.FindNode(7));
}

TEST_F(TestLink,Delete)
{
    ASSERT_FALSE(link.pHead == NULL);
    ASSERT_TRUE(link.Delete(3) == true);
    ASSERT_TRUE(link.Delete(9) == false);
}
