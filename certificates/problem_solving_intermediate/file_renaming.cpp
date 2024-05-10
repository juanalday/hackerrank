#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>

namespace {

	int renameFile(std::string reducedName, std::string oldLongName)
	{
		// Initialize vector with 1s. 
		// This vector is used to keep track of the number of ways to form subsequences of newName from prefixes of oldName.
		std::vector<int> output(oldLongName.size() + 1, 1);

		for (int i = 0; i < reducedName.size(); ++i) { //Loop over each character in newName
			std::vector<int> temp(oldLongName.size() + 1, 0); // Initialize vector with 0s for this iteration

			// Start from i+1 to ensure that there are enough characters left in oldLongName to match the remaining characters in newName
			for (int j = i + 1; j <= oldLongName.size(); ++j) {
				temp[j] = temp[j - 1]; // Carry forward the count from the previous position
				if (reducedName[i] == oldLongName[j - 1]) { // Check if current newName character matches the oldName character at position j-1
					temp[j] += output[j - 1]; // If they match, add the count of ways to form the subsequence up to j-1
				}
			}
			output = std::move(temp); // Efficiently transfer the content
		}

		constexpr int moduler = 1000000007; // 10^9 + 7
		return output.back() % moduler;
	}
}

TEST(renameFile, example)
{
	EXPECT_EQ(4, renameFile("aba", "ababa"));
}

TEST(renameFile, sample0)
{
	EXPECT_EQ(4, renameFile("ccc", "cccc"));
}

TEST(renameFile, sample1)
{
	EXPECT_EQ(0, renameFile("abc", "abba"));
}


TEST(renameFile, case0)
{
	EXPECT_EQ(4, renameFile("ccc", "cccc"));
}

TEST(renameFile, case1)
{
	EXPECT_EQ(0, renameFile("abc", "abba"));
}

TEST(renameFile, case2)
{
	EXPECT_EQ(27, renameFile("abc", "aaabbbccc"));
}

TEST(renameFile, case3)
{
	EXPECT_EQ(3174, renameFile("mzb", "mmzzzzzzzzzzbbbbbzzzbbbbbbbbbbbbbzzzzzzzzzzzbbbbbbbbbbbbbbbbbbzzzzzzzzzzzzzzzbbbbbbbbbbbbbbbbbbbbbbbb"));
}

TEST(renameFile, case4)
{
	EXPECT_EQ(6060, renameFile("rcz", "rrrrccccccccccccccccccccccccccccccccccccccccccccccczzzzzzzzzzcccccccccccccccczzzzzcccccccccczzzzzzzzzz"));
}

TEST(renameFile, case5)
{
	EXPECT_EQ(6610, renameFile("whw", "swxxrxuzzfhkplwunfagppcoildagktgdarveusjuqfistulgbglwmfgzrnyxryetwzhlnfewczmnoozlqatugmdjwgzcfabbkoxyjxkatjmpprswkdkobdagwdwxsufeesrvncbszcepigpbzuzoootorzfskcwbqorvwdrmklfdczatfarqdkelalxzxillkfdvpfpxabqlngdscrentzamztvvcvrtcmbqlizijdwtuyfrxolsysxlfebpolcmqsppmrfkyunydtmwbexsngxhwvroandfqjamzkpttslildlrkjoyrpxugiceahgiakevsjoadmkfnkswrawkjxwcmcciabzbrskzazjqtlkiqydptpkcsdgcqjshzndpvannrywfrnrghljjqrxpxnlkcwdpdkswvtxganwwyoosxtnexeezjxouyfjhnwpqfxexzxfolpcfblpncetyhtrwxkbosccskxbuvcrosavnpxzoeoyyghbbqkflsutpwmhqwkvirmlfcpidlqyikzmnttaifcbopnwezesomkxhaiafmvkbjaisyrbtultpnxbcjmornqumatserhieqggrivouwfnbnghdfallcprvngikcamvprzaeapqmilwkbkgogocniaaisorfqxzjztvcgvzlcedwnezbwxmpobmrvxaskwvvwquudrnwhmmzheqxiwhfuxavlwftgyxxhpygspvwdnvmgnwnpkdrnznzvrkmjjmwisyrdkodoafwsjfuvmeewpdwpiymwbhoxebjibxphiefgtsawcdivtltrshjqnkkmdtjgsc"));
}

TEST(renameFile, case6)
{
	EXPECT_EQ(1994, renameFile("omo", "jnhigippjemzzzbcvoyplxenffmfdzdiojuodgbulvivhtbhayeeebiactyaovqbivudydgxwsgmhlracaayipsojleqhpygshcvxwwlneblfmnqgddqpcjxzftwrlgptrkbkrlwgsnlcaudzdujbbqlfzikgxohvhtuvcjmmwvhkxcgyekjkklcjqoneppydpspiwqbkpsunedqixlsifcokfrcvrszcvdyfwuhtzptbbnxbhqjomxrbhjqxvdaserffcvkecqylqprawyquevhvuzcvfmbewpxicskpmzsbsusmaddqkwgfirlzzbczeghmuhxnxejrspcvqejwowqsfhovhctwnhuuveprriyfwstsjdecyyfjbjsdlegqlklxiyrwvlppomdfdtvtkwokiwwpejxibdknponpsxrytoqgjrtjpatmdlhmqegvjhvlehsykrlvvssmambzusxuszyybdrdvzdbexsglyokvmykifwgfncsacjlkathfmnlctsqejfoxyvmtottlhrlypbzisucllqgaaitmxpmfinsowjaawsnmluizvpjbewqcipcqwvsqfbeutdcsdrviozobdytwsimseetqcklnkxtawoxiysv"));
}

TEST(renameFile, case7)
{
	EXPECT_EQ(339, renameFile("rrk", "eispnddxtnfqalswxsmksfooiwxynamdjxnsmkiewkwdpzjpkibcbbmzbiwpmjczcehtczqjzlkgyvszpuuvetdfluuhxpeopuxmdylaysttenjmcedcumoeeicjtxkkvxcxjowrcvlttsqhwkbbmigtqlovjgviyzgcqjvpvotwucsetidicyhtcmajphxyyooeovuxvuploklpbovqdwdypbxgajuqwadgeedjkgurhsxdvylmyfjqlwzldrouylqobsgemwdoibqvcyedfvqopfhkqmhusxqacoogjxcoxbfzlwcxfvqaavfegkcirqqgdyhljmaqzqifuaoubukypavebvdujgsulahkprfpnzqaqgvfdxwtqflceilpmszizfwbonxplcyqittpkpbcfsesgfbiqnipolefrelphjthqrzsphbnumgrifmwiztfuhqibgaxdvysyvgxlspminykbyumepubrxuoavyovdbielzdobgqcjznjbexalkghywioxzbvxzfcshcozmefwcrvyibjdfqvqmhxdpccjodlgvkplrfdedpzoprfeechwszhvcdooejlchcwcektfrdmowhsueavbrawmihzsnfhrafbqeawdixznppfwieaivtmpqzqtsvnvwjmgvhuesssaxgmoywdgvwiouzuqdebijcqycftaftuwtgxavemciuqmxenprpmyzrexshnvtesstwhytmatxbuzxpstpygfxphpfckjdbfbximeeswyndfhomcnwjtfruvzwbhlzbvebyeucepgcdpmghcibfxg"));
}

