#include <gtest/gtest.h>

#include <utility>
#include <vector>
#include <queue>
#include <tuple>

namespace {
	int bfs(int start, int end, std::vector<std::vector<int>> const& adjList)
	{
		if (start == end)
			return 0;


		std::vector<bool> visited(1 + adjList.size(), false); // edges are 1-based
		std::vector<int> distance(1 + adjList.size(), std::numeric_limits<int>::max()); // edges are 1-based
		std::queue<int> q;
		visited[start] = true;
		distance[start] = 0;
		q.push(start);
		while (!q.empty())
		{
			int current = q.front();
			q.pop();
			for (int vertex : adjList[current])
			{
				if (!visited[vertex])
				{
					distance[vertex] = distance[current] + 1;
					if (vertex == end) {
						return distance[vertex];  // Early exit if end is reached
					}
					visited[vertex] = true;
					q.push(vertex);
				}
			}
		}
		return distance[end] == std::numeric_limits<int>::max() ? -1 : distance[end];  // Check if end is reachable
	}


	
	int numberOfWays(std::vector<std::pair<int, int>> roads) {
		int maxVertex = 0;
		for_each(roads.begin(), roads.end(), [&](auto edge){maxVertex = std::max(maxVertex, std::max(edge.first, edge.second));});

		std::vector<std::vector<int>> adjList(1 + maxVertex); // 1-based
		for_each(roads.begin(), roads.end(), [&](auto edge)
			{
				adjList[edge.first].push_back(edge.second);
				adjList[edge.second].push_back(edge.first);
			});


		// Let's calculate map of distances
		std::map<std::pair<int, int>, int> distances;
		for (int i = 1; i < maxVertex; ++i)
		{
			for (int j = i + 1; j <= maxVertex; ++j)
			{
				distances[{i, j}] = bfs(i, j, adjList);
			}
		}

		// Brute force to check each combination of three nodes
		int ans = 0;
		for (int i = 1; i < maxVertex - 1; ++i) {
			for (int j = i + 1; j < maxVertex; ++j) {
				for (int k = j + 1; k <= maxVertex; ++k) {
					if (distances[{i, j}] != distances[{i, k}]) continue;
					if (distances[{i, j}] != distances[{j, k}]) continue;
					ans++;
				}
			}
		}
		return ans;
	}
}

TEST(hotel_construction, example)
{
	EXPECT_EQ(4, numberOfWays({ {1, 2}, {1, 3}, {1, 4}, {1, 5} }));
}

TEST(hotel_construction, sample0)
{
	EXPECT_EQ(2, numberOfWays({ {1, 2}, {2, 5}, {3, 4}, {4, 5}, {5, 6}, {7, 6} }));
}
TEST(hotel_construction, sample1)
{
	EXPECT_EQ(0, numberOfWays({ {1, 2}, {2, 3}, {3, 4}, {4, 5} }));
}

TEST(hotel_construction, case0)
{
	EXPECT_EQ(2, numberOfWays({ {1, 2}, {2, 5}, {3, 4}, {4, 5}, {5, 6}, {7, 6} }));
}

TEST(hotel_construction, case1)
{
	EXPECT_EQ(0, numberOfWays({ {1, 2}, {2, 3}, {3, 4}, {4, 5} }));
}

TEST(hotel_construction, case2)
{
	EXPECT_EQ(1, numberOfWays({ {1, 2}, {1, 3}, {2, 4}, {2, 5} }));
}

TEST(hotel_construction, case3)
{
	EXPECT_EQ(11, numberOfWays({ {9, 5}, {12, 5}, {11, 9}, {13, 9}, {1, 12}, {8, 12}, {2, 11}, {3, 11}, {14, 13}, {4, 13}, {6, 1}, {7, 1}, {10, 8} }));
}

TEST(hotel_construction, case4)
{
	EXPECT_EQ(66, numberOfWays({ {8,19}, {7,19}, {9,8}, {15,8}, {20,7}, {23,7}, {21,9}, {14,9}, {12,15}, {16,15}, {18,20}, {17,20}, {4,23}, {10,23}, {5,21}, {22,21}, {6,14}, {2,14}, {13,12}, {11,12}, {1,16}, {3,16} }));
}

TEST(hotel_construction, case5)
{
	EXPECT_EQ(66, numberOfWays({ {13,10}, {8,10}, {22,13}, {19,13}, {16,8}, {20,8}, {5,22}, {18,22}, {9,19}, {2,19}, {21,16}, {4,16}, {17,20}, {1,20}, {11,5}, {12,5}, {6,18}, {7,18}, {23,9}, {15,9}, {3,2}, {14,2} }));
}


TEST(hotel_construction, case6)
{
	EXPECT_EQ(560, numberOfWays({ {31,12}, {26,12}, {1,12}, {29,31}, {27,31}, {16,31}, {19,26}, {5,26}, {25,26}, {3,1}, {33,1}, {30,1}, {9,29}, {14,29}, {32,29}, {35,27}, {4,27}, {24,27}, {28,16}, {21,16}, {15,16}, {23,19}, {11,19}, {22,19}, {2,5}, {6,5}, {20,5}, {7,25}, {13,25}, {10,25}, {8,3}, {34,3}, {18,3}, {17,33} }));
}


TEST(hotel_construction, case7)
{
	EXPECT_EQ(40, numberOfWays({ {8,5}, {11,5}, {10,5}, {4,8}, {2,8}, {7,8}, {1,11}, {9,11}, {3,11}, {12,10}, {13,10}, {6,10} }));
}


TEST(hotel_construction, case8)
{
	EXPECT_EQ(41, numberOfWays({ {8,4}, {12,4}, {7,4}, {13,8}, {3,8}, {15,8}, {2,12}, {6,12}, {10,12}, {1,7}, {5,7}, {14,7}, {11,13}, {9,13} }));
}


TEST(hotel_construction, case9)
{
	EXPECT_EQ(3296, numberOfWays({ {29,5}, {14,5}, {9,5}, {3,5}, {30,5}, {27,5}, {6,5}, {15,5}, {1,5}, {26,5}, {31,5}, {16,5}, {8,5}, {12,5}, {24,5}, {11,5}, {4,5}, {22,5}, {28,5}, {18,5}, {23,5}, {19,5}, {25,5}, {33,5}, {21,5}, {20,5}, {32,5}, {2,5}, {34,8}, {7,22}, {17,23}, {13,15}, {35,21}, {10,32} }));
}


TEST(hotel_construction, case10)
{
	EXPECT_EQ(2981, numberOfWays({ {30,18}, {16,18}, {34,18}, {3,18}, {32,18}, {12,18}, {5,18}, {25,18}, {2,18}, {7,18}, {22,18}, {33,18}, {17,18}, {21,18}, {24,18}, {20,18}, {19,18}, {14,18}, {28,18}, {15,18}, {27,18}, {6,18}, {1,18}, {13,18}, {26,18}, {31,18}, {11,25}, {29,21}, {23,18}, {8,12}, {4,17}, {9,30}, {36,34}, {10,33}, {35,2} }));
}


TEST(hotel_construction, case11)
{
	EXPECT_EQ(3654, numberOfWays({ {29,9}, {15,9}, {31,9}, {4,9}, {26,9}, {14,9}, {23,9}, {13,9}, {20,9}, {18,9}, {5,9}, {30,9}, {8,9}, {3,9}, {32,9}, {1,9}, {6,9}, {25,9}, {12,9}, {11,9}, {10,9}, {24,9}, {22,9}, {7,9}, {28,9}, {19,9}, {27,9}, {2,9}, {17,9}, {21,29}, {16,4} }));
}


TEST(hotel_construction, case12)
{
	EXPECT_EQ(371, numberOfWays({ {19,8}, {4,19}, {39,8}, {5,8}, {46,4}, {24,8}, {27,5}, {13,4}, {16,13}, {44,16}, {36,13}, {45,46}, {1,46}, {47,13}, {35,5}, {43,8}, {2,19}, {33,2}, {18,19}, {28,36}, {40,39}, {29,2}, {42,45}, {15,44}, {21,2}, {6,42}, {26,5}, {20,27}, {37,33}, {25,40}, {30,28}, {23,30}, {3,27}, {14,44}, {10,35}, {7,47}, {31,46}, {22,47}, {41,13}, {9,42}, {12,36}, {17,40}, {32,13}, {48,1}, {11,42}, {34,40}, {38,17} }));
}


TEST(hotel_construction, case13)
{
	EXPECT_EQ(166, numberOfWays({ {11,4}, {12,11}, {22,12}, {10,11}, {19,11}, {15,11}, {23,11}, {13,11}, {6,12}, {17,23}, {21,23}, {16,22}, {20,11}, {7,12}, {9,19}, {1,16}, {5,10}, {14,6}, {18,4}, {2,19}, {3,20}, {8,7} }));
}


TEST(hotel_construction, case14)
{
	EXPECT_EQ(44, numberOfWays({ {22,6}, {5,22}, {17,5}, {2,17}, {1,22}, {7,1}, {21,5}, {15,21}, {13,15}, {10,6}, {16,10}, {14,22}, {3,13}, {18,6}, {11,13}, {20,21}, {4,15}, {19,20}, {12,19}, {8,14}, {9,15} }));
}
