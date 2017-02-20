#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <map>
#include <queue>
#include <boost/multiprecision/cpp_int.hpp>
/*
unsigned long	maximum：18446744073709551615	minimum：0
long         	maximum：9223372036854775807	    minimum：-9223372036854775808
long long    	maximum：9223372036854775807	    minimum：-9223372036854775808
*/
// define the type of the hash value.
typedef boost::multiprecision::int128_t HASHVALUE;

// get the hash value of an integer array.
HASHVALUE hash_array(int *index, int dimension)
{
	HASHVALUE array_hash = 0;
	for(int i=0; i<dimension; ++i)
	{
		array_hash = array_hash*2001 + index[i];
		/*limits of the hash algorithm.
            GN*(M^n - 1)/(M-1) <= 2^m
            GN： the maximum value of the array
            M: the prime number for hash
            n: the length of the array
            m: the bits of the HASHVALUE
            log2(1500*(1501**6-1)/1500) = 63.31024956972413
            log2(1000*(1001**6-1)/1000) = 59.803357553015964
            log2(1000*(1001**7-1)/1000) = 69.77058381185195
            log2(500*(501**7-1)/500) = 62.78066755236646
        */
	}

    return array_hash;
}

template <typename Template>
class hashTable
{
public:
    hashTable();
    hashTable(int _dimension, int _length=500);
    void initialize(int _dimension, int _length=500);
    void insert(int *index, Template &value);
    bool query(int *index, Template &value);
	#ifdef DEBUG
	void stat();
	#endif
private:
    // dimension: dimension of the integer array.
    // max_length: maximum length of the storage table.
    int dimension, max_length;
    // storage of the results.
	std::map<HASHVALUE, Template> stortable;
    // storage of the hash values.
	std::queue<HASHVALUE> hashqueue;
    int count;
	#ifdef DEBUG
    std::map<HASHVALUE, int> records;
    #endif
};
template <typename Template>
hashTable<Template>::hashTable(){;}
template <typename Template>
hashTable<Template>::hashTable(int _dimension, int _length)
{
    dimension = _dimension;
	max_length = _length;
    count = 0;
}
template <typename Template>
void hashTable<Template>::initialize(int _dimension, int _length)
{
    dimension = _dimension;
    max_length = _length;
	count = 0;
}
template <typename Template>
void hashTable<Template>::insert(int *index, Template &value)
{
    // 1. get the hash value of the integer array.
	HASHVALUE hashv = hash_array(index, dimension);
    // 2. store the record.
	stortable.insert(std::make_pair(hashv, Template(value)));
	hashqueue.push(hashv);
    
    // 3. cut off the number of records.    
    count += 1;
	if(count >= max_length)
	{
		int popsize = int(0.01*max_length);
		for(int i=0; i<popsize; ++i)
		{
			HASHVALUE hashv = hashqueue.front();
			hashqueue.pop();
			stortable.erase(hashv);
			count -= 1;
		}
	}
}
// try to query an record from the storage table.
template <typename Template>
bool hashTable<Template>::query(int *index, Template &value)
{
    // 1. get the hash value of the integer array.
    HASHVALUE hashv = hash_array(index, dimension);
	#ifdef DEBUG
	if(records.count(hashv))
	{
		records[hashv] += 1;
	}
	else
	{
		records.insert(std::make_pair(hashv, 1));
	}
	#endif

    // 2. try to retrieve the record from the storage table.
	typename std::map<HASHVALUE, Template>::iterator it;
	it = stortable.find(hashv);
    
    // 3. if record exists, return it.
	if(it != stortable.end())
	{
		value = Template(it->second);
		return true;
	}
    
    // 4. if record does not exist, return false.
    return false;
}
#ifdef DEBUG
// print the efficiency of the hash table.
template <typename Template>
void hashTable<Template>::stat()
{
	for(auto pair=records.begin(); pair!=records.end(); ++pair)
	{
		std::cout<<pair->first<<"\t"<<pair->second<<std::endl;
	}
}
#endif
#endif
