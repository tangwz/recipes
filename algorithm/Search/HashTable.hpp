/*
 * Algorithm--HashTable：https://en.wikipedia.org/wiki/Hash_table
 * 
 */

/** 元素的哈希函数 */
template<typename elem_t>
int elem_hash(const elem_t &e);
/** 元素的比较函数 */
template<typename elem_t>
bool operator==(const elem_t &e1, const elem_t &e2);
/** 哈希集合, elem_t 是元素的数据类型. */
template<typename elem_t>
class hash_set
{
public:
    hash_set(int prime, int capacity);
    ~hash_set();
    bool find(const elem_t &elem); /** 查找某个元素是否存在. */
    bool insert(const elem_t &elem); /** 添加一个元素，如果已存在则添加失败. */
private:
    int prime; /** 哈希表取模的质数，也即哈希桶的个数，小于 capacity. */
    int capacity; /** 哈希表容量，一定要大于元素最大个数 */
    int *head/*[PRIME]*/; /** 首节点下标 */
    struct node_t
    {
        elem_t elem;
        int next;
        node_t():next(-1) {}
    } *node/*[HASH_SET_CAPACITY]*/; /** 静态链表 */
    int size; /** 实际元素个数 */
};
template<typename elem_t>
hash_set<elem_t>::hash_set(int prime, int capacity)
{
    this->prime = prime;
    this->capacity = capacity;
    head = new int[prime];
    node = new node_t[capacity];
    fill(head, head + prime, -1);
    fill(node, node + capacity, node_t());
    size = 0;
}
template<typename elem_t>
hash_set<elem_t>::~hash_set()
{
    this->prime = 0;
    6.2 哈希表 75
    this->capacity = 0;
    delete[] head;
    delete[] node;
    head = NULL;
    node = NULL;
    size = 0;
}
template<typename elem_t>
bool hash_set<elem_t>::find(const elem_t &elem)
{
    for (int i = head[elem_hash(elem)]; i != -1; i = node[i].next)
        if (elem == node[i].elem) return true;
    return false;
}
template<typename elem_t>
bool hash_set<elem_t>::insert(const elem_t &elem)
{
    const int hash_code = elem_hash(elem);
    for (int i = head[hash_code]; i != -1; i = node[i].next)
        if (elem == node[i].elem) return false; // 已经存在
    /* 不存在，则插入在首节点之前 */
    node[size].next = head[hash_code];
    node[size].elem = elem;
    head[hash_code] = size++;
    return true;
}
