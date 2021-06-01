/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 5. 9
  *
  */

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
	// ToDo
	HashMapElemType *cur;
	HashMapElemType *next;
	for(int i=0; i < this->capacity; i++) {	
		cur = ht[i];
		while(cur != NULL) {
			next = cur->link;
			delete cur;
			cur = next;
		}
		ht[i] = NULL;
	}
}
	
template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{ 
	// ToDo
	unsigned int hashValue = hashfunction(k);
	HashMapElemType *entry = ht[hashValue];
	
	while (entry != NULL) {
		if(entry == NULL) {
			break;
		}
		if (entry->key.compare(k) == 0) {
			return entry;
		}
		entry = entry->link;
	}
	return NULL;
}
	
template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v)
{
	// ToDo
	unsigned int hashValue = hashfunction(k);
	HashMapElemType *prev = NULL;
	HashMapElemType *entry = ht[hashValue];
	while (entry != NULL && entry->key != k) {
		prev = entry;
		entry = entry->link;
	}
	if (entry == NULL) {
		if (prev == NULL) {
			entry = new HashMapElemType;
			entry->key = k;
			entry->val = v;
			entry->link = NULL;
			ht[hashValue] = entry;
		} else {
			prev->link = entry;
		}
		this->mapsize++;
	} else {
		entry->val = v;
	}
}
		
template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
	// ToDo	
	unsigned int hashValue = hashfunction(k);
	HashMapElemType *prev = NULL;
	HashMapElemType *entry = ht[hashValue];
	
	while (entry != NULL && entry->key != k) {
		prev = entry;
		entry = entry->link;
	}
	
	if (entry == NULL) {
		return false;
	} else {
		if (prev == NULL) {
			ht[hashValue] = entry->link;
		} else {
			prev->link = entry->link;
		}
		delete entry;
		this->mapsize--;
	}
	
	return true;
}
	
template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
	// ToDo
	int p = 31;
    unsigned int powerOfP = 1;
    unsigned int hash_val = 0;
    for (int i = 0; i < k.length(); i++) {
        hash_val
            = (hash_val
               + (k[i] - 'a' + 1) * powerOfP)
              % divisor;
        powerOfP
            = (powerOfP * p) % divisor;
    }
	
	return hash_val;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
	// ToDo
	HashMapElemType *head = NULL;
	HashMapElemType *cur = NULL;
	HashMapElemType *prev = NULL;
	
	for(int i=0; i < this->capacity; i++) {
		HashMapElemType *entry = ht[i];
		while(entry != NULL) {
			// std::cout << entry->key << " " << entry->val << std::endl;
			cur = new HashMapElemType;
			cur->link = NULL;
			cur->key = entry->key;
			cur->val = entry->val;
			if(head == NULL) {
				head = cur;
			} else {
				prev->link = cur;
			}
			prev = cur;
			entry = entry->link;
		}
	}
	
	HashMapElemType *curForSorting = head;
	HashMapElemType *index = NULL;
	std::string tempKey = "";
	int tempVal = 0;
	
	while(curForSorting != NULL) {  
		//Node index will point to node next to current  
		index = curForSorting->link;  

		while(index != NULL) {
			if(curForSorting->val < index->val) {  
				tempKey = curForSorting->key;
				tempVal = curForSorting->val;
				curForSorting->key = index->key;
				curForSorting->val = index->val; 
				index->key = tempKey;
				index->val = tempVal;
			}
			index = index->link;  
		}  
		curForSorting = curForSorting->link;  
	}
	
	while(head != NULL) {
		std::cout << head->key << ":" << head->val << std::endl;
		head = head->link;
	}
}
