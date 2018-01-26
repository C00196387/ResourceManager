#include "pch.h"
#include <JSONReader.h>
#include <JSON_Reader\JSON.h>
#include <JSON_Reader\JSONValue.h>

TEST(TestCaseName, TestName) 
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(LoadLevelData, test)
{
	ResourceManager::JSONReader j = ResourceManager::JSONReader("..\Demo\Resources\Config\config.json");
	std::string holder = j.ElementGetter("Message");
	EXPECT_EQ(holder, "test text test text, sam i am");
}