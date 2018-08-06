/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */

     Dict<string, int> hashtable(5000);

    while (infile.good()) {
        string word = infile.getNextWord();
        if (hashtable.keyExists(word)) {
            hashtable[word]++;
        } else {
            hashtable.insert(word, 1);
        }
    }

    for (auto it = hashtable.begin(); it != hashtable.end(); it++) {
        string key = it->first;
        int count = it->second;
        if (count - threshold >= 0) {
            ret.push_back(make_pair(key, count));
        }
    }

    return ret;
}
